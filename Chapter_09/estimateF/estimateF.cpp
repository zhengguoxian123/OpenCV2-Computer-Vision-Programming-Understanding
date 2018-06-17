#include<iostream>
#include<vector>

#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/calib3d/calib3d.hpp>

#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>

#include<opencv2/legacy/legacy.hpp>

int main()
{
    cv::Mat image1 = cv::imread("../church01.jpg",0);
    cv::Mat image2 = cv::imread("../church03.jpg",0);

    if(!image1.data || !image2.data)
        return 0;

    cv::namedWindow("Right Image");
    cv::imshow("Right Image",image1);

    cv::namedWindow("Left Image");
    cv::imshow("Left Image",image2);

    std::vector<cv::KeyPoint> keypoints1;
    std::vector<cv::KeyPoint> keypoints2;

    cv::SurfFeatureDetector surf(3000);

    surf.detect(image1,keypoints1);
    surf.detect(image2,keypoints2);

    std::cout<<"Number of SURF points (1)"<<keypoints1.size()<<std::endl;
    std::cout<<"Number of SURF points (2)"<<keypoints2.size()<<std::endl;

    cv::Mat imageKP;

    cv::drawKeypoints(image1,keypoints1,imageKP,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow("Right SURF Features");

    cv::imshow("Right SURF Features",imageKP);

    cv::drawKeypoints(image2,keypoints2,imageKP,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    cv::namedWindow("Left SURF Features");
    cv::imshow("Left SURF Features",imageKP);


    cv::SurfDescriptorExtractor surfDesc;

    cv::Mat descriptors1,descriptors2;

    surfDesc.compute(image1,keypoints1,descriptors1);
    surfDesc.compute(image2,keypoints2,descriptors2);

    std::cout<<"descriptor matrix size: "<<descriptors1.rows<<" by "<<descriptors2.cols<<std::endl;

    cv::BruteForceMatcher<cv::L2<float> > matcher;

    std::vector<cv::DMatch> matches;

    matcher.match(descriptors1,descriptors2,matches);

    std::cout<<"Number of matched points: "<<matches.size()<<std::endl;

    std::vector<cv::DMatch> selMatches;

    selMatches.push_back(matches[14]);
    selMatches.push_back(matches[16]);
    selMatches.push_back(matches[141]);
    selMatches.push_back(matches[146]);
    selMatches.push_back(matches[235]);
    selMatches.push_back(matches[238]);
    selMatches.push_back(matches[262]);

    cv::Mat imageMatches;
    cv::drawMatches(image1,keypoints1,image2,keypoints2,matches,imageMatches,cv::Scalar(255,255,255));
    cv::namedWindow("Matches");
    cv::imshow("Matches",imageMatches);
//.................................................
    std::vector<int> pointIndexes1;
    std::vector<int> pointIndexes2;

    for(std::vector<cv::DMatch>::const_iterator it =selMatches.begin();it !=selMatches.end();++it)
    {
        pointIndexes1.push_back(it->queryIdx);
        pointIndexes2.push_back(it->trainIdx);

    }

    std::vector<cv::Point2f> selPoints1,selPoints2;
    //??????? qu diao di san ge can shu
    cv::KeyPoint::convert(keypoints1,selPoints1);
    cv::KeyPoint::convert(keypoints2,selPoints2);

    std::vector<cv::Point2f>::const_iterator it = selPoints1.begin();
    while(it != selPoints1.end())
    {
        cv::circle(image1,*it,3,cv::Scalar(255,255,255),2);
        ++it;
    }

    it =selPoints2.begin();
    while(it != selPoints2.end())
    {
        cv::circle(image2,*it,3,cv::Scalar(255,255,255),2);
        ++it;
    }
    //关键点的数量不一样
    std::cout<<"selPoints1.size()"<<selPoints1.size()<<std::endl;
    std::cout<<"selPoints2.size()"<<selPoints2.size()<<std::endl;
    
    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;
    
    for(int i =0;i<(int)matches.size();i++)
    {
      points1.push_back(keypoints1[matches[i].queryIdx].pt);
      points2.push_back(keypoints2[matches[i].trainIdx].pt);
    }
    
    std::cout<<"points1.size()"<<points1.size()<<std::endl;
    std::cout<<"points2.size()"<<points2.size()<<std::endl;
    //????findFundamentalMat函数运行正确的关键是两张图的关键点数量必须一致
    //关键点数量如和变得一样呢
    //参考视觉SLAM14讲
    cv::Mat fundamental;
    fundamental = cv::findFundamentalMat(points1,points2,CV_FM_7POINT);

    std::cout<<"F-Matrix size="<<fundamental.rows<<" by "<<fundamental.cols<<std::endl;

    std::vector<cv::Vec3f> lines1;
    cv::computeCorrespondEpilines(cv::Mat(points1),1,fundamental,lines1);

    for(std::vector<cv::Vec3f>::const_iterator it = lines1.begin();it!=lines1.end();++it)
    {
        cv::line(image2,cv::Point(0,-(*it)[2]/(*it)[1]),cv::Point(image2.cols,-((*it)[2]+(*it)[0]*image2.cols)/(*it)[1]),cv::Scalar(255,255,255));
    }

    std::vector<cv::Vec3f> lines2;
    cv::computeCorrespondEpilines(cv::Mat(points2),2,fundamental,lines2);

    for(std::vector<cv::Vec3f>::const_iterator it =lines2.begin();it!= lines2.end();++it)
    {
        cv::line(image1,cv::Point(0,-(*it)[2]/(*it)[1]),cv::Point(image1.cols,-((*it)[2]+(*it)[0]*image1.cols)/(*it)[1]),cv::Scalar(255,255,255));
    }

    cv::namedWindow("Right Image Epilines");
    cv::imshow("Right Image Epilines",image1);
    cv::namedWindow("Left Image Epilines");
    cv::imshow("Left Image Epilines",image2);

    //std::vector<cv::Point2f> points1,points2;
    for(std::vector<cv::DMatch>::const_iterator it =matches.begin();it != matches.end();++it)
    {
        float x = keypoints1[it->queryIdx].pt.x;
        float y = keypoints1[it->queryIdx].pt.y;

        points1.push_back(cv::Point2f(x,y));
        x = keypoints2[it->trainIdx].pt.x;
        y = keypoints2[it->trainIdx].pt.y;

        points2.push_back(cv::Point2f(x,y));

    }

    std::cout<<points1.size()<<" "<<points2.size()<<std::endl;

    std::vector<uchar> inliers(points1.size(),0);
    fundamental = cv::findFundamentalMat(cv::Mat(points1),cv::Mat(points2),
                                         inliers,CV_FM_RANSAC,
                                         1,0.98);
    image1 = cv::imread("../church01.jpg",0);
    image2 = cv::imread("../church03.jpg",0);

    cv::computeCorrespondEpilines(cv::Mat(selPoints1),1,fundamental,lines1);

    for(std::vector<cv::Vec3f>::const_iterator it = lines1.begin();it != lines1.end();++it)
    {
        cv::line(image2,cv::Point(0,-(*it)[2]/(*it)[1]),cv::Point(image2.cols,-((*it)[2]+(*it)[0]*image2.cols)/(*it)[1]),cv::Scalar(255,255,255));

    }

    cv::computeCorrespondEpilines(cv::Mat(selPoints2),2,fundamental,lines2);

    for(std::vector<cv::Vec3f>::const_iterator it = lines2.begin();it != lines2.end();++it)
    {
        cv::line(image1,cv::Point(0,-(*it)[2]/(*it)[1]),cv::Point(image1.cols,-((*it)[0]*image1.cols)/(*it)[1]),cv::Scalar(255,255,255));

    }

    std::vector<cv::Point2f> points1In,points2In;
    std::vector<cv::Point2f>::const_iterator itPts = points1.begin();
    std::vector<uchar>::const_iterator itIn = inliers.begin();

    while(itPts != points1.end())
    {
        if(*itIn)
        {
            cv::circle(image1,*itPts,3,cv::Scalar(255,255,255),2);
            points1In.push_back(*itPts);
        }
        ++itPts;
        ++itIn;
    }

    itPts = points2.begin();
    itIn = inliers.begin();

    while(itPts != points2.end())
    {
        if(*itIn)
        {
            cv::circle(image2,*itPts,3,cv::Scalar(255,255,255),2);
            points2In.push_back(*itPts);
        }
        ++itPts;
        ++itIn;
    }

    cv::namedWindow("Right Image Epilines(RANSAC)");
    cv::imshow("Right Image Epilines(RANSAC)",image1);

    cv::namedWindow("Left Image Epilines(RANSAC)");
    cv::imshow("Left Image Epilines(RANSAC)",image2);

    cv::findHomography(cv::Mat(points1In),cv::Mat(points2In),inliers,CV_RANSAC,1.);
//................................................................
    image1 = cv::imread("../church01.jpg",0);
    image2 = cv::imread("../church03.jpg",0);

    itPts = points1In.begin();
    itIn = inliers.begin();
    while( itPts != points1In.end())
    {
        if(*itIn)
            cv::circle(image1,*itPts,3,cv::Scalar(255,255,255),2);
        ++itPts;
        ++itIn;
    }

    itPts = points2In.begin();
    itIn = inliers.begin();
    while(itPts != points2In.end())
    {
        if(*itIn)
            cv::circle(image2,*itPts,3,cv::Scalar(255,255,255),2);

        ++itPts;
        ++itIn;
    }

    cv::namedWindow("Right Image Homography (RANSAC)");
    cv::imshow("Right Image Homology (RANSAC)",image1);
    cv::namedWindow("Left Image Homography (RANSAC)");
    cv::imshow("Left Image Homology (RANSAC)",image2);

    cv::waitKey();
    return 0;
}


