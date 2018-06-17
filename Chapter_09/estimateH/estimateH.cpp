#include<iostream>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/calib3d/calib3d.hpp>

#include "matcher.hpp"

int main()
{
    cv::Mat image1 = cv::imread("../parliament1.bmp",0);
    cv::Mat image2 = cv::imread("../parliament2.bmp",0);

    if(!image1.data || !image2.data)
        return 0;

    cv::namedWindow("Image 1");
    cv::imshow("Image 1",image1);

    cv::namedWindow("Image 2");
    cv::imshow("Image 2",image2);

    RobustMatcher rmatcher;
    rmatcher.setConfidenceLevel(0.98);
    rmatcher.setMinDistanceToEpipolar(1.0);
    rmatcher.setRatio(0.65f);
    cv::Ptr<cv::FeatureDetector> pfd = new cv::SurfFeatureDetector(10);
    rmatcher.setFeatureDetector(pfd);

    std::vector<cv::DMatch> matches;
    std::vector<cv::KeyPoint> keypoints1,keypoints2;
    cv::Mat fundamental = rmatcher.match(image1,image2,matches,keypoints1,keypoints2);

    cv::Mat imageMatches;
    cv::drawMatches(image1,keypoints1,
                    image2,keypoints2,
                    matches,imageMatches,cv::Scalar(255,255,255));
    cv::namedWindow("Matches");
    cv::imshow("Matches",imageMatches);

    std::vector<cv::Point2f> points1,points2;
//    for(std::vector<cv::DMatch>::const_iterator it = matches.begin();it != matches.end();++it)
//    {
//        float x = keypoints1[it->queryIdx].pt.x;
//        float y = keypoints1[it->queryIdx].pt.y;

//        points1.push_back(cv::Point2f(x,y));

//        x = keypoints2[it->trainIdx].pt.x;
//        y = keypoints2[it->trainIdx].pt.y;

//        points2.push_back(cv::Point2f(x,y));

//    }

    for(int i =0;i<(int)matches.size();i++)
    {
        points1.push_back(keypoints1[matches[i].queryIdx].pt);
        points2.push_back(keypoints2[matches[i].trainIdx].pt);
    }

    std::cout<<points1.size()<<" "<<points2.size() <<std::endl;

    std::vector<uchar> inliers(points1.size(),0);

    cv::Mat homography = cv::findHomography(points1,points2,inliers,CV_RANSAC,1.);

    std::vector<cv::Point2f>::const_iterator itPts = points1.begin();
    std::vector<uchar>::const_iterator itIn = inliers.begin();
    while(itPts != points1.end())
    {
        if(*itIn)
            cv::circle(image1,*itPts,3,cv::Scalar(255,255,255),2);
        ++itPts;
        ++itIn;
    }

    itPts = points2.begin();
    itIn = inliers.begin();
    while(itPts != points2.end())
    {
        if(*itIn)
          cv::circle(image2,*itPts,3,cv::Scalar(255,255,255),2);
        ++itPts;
        ++itIn;
        }

    cv::namedWindow("Image 1 Homography Points");
    cv::imshow("Image 1 Homography Points",image1);

    cv::namedWindow("Image 2 Homography Points");
    cv::imshow("Image 2 Homography Points",image2);

    cv::Mat result;
    cv::warpPerspective(image1,result,homography,cv::Size(2*image1.cols,image1.rows));

    cv::Mat half(result,cv::Rect(0,0,image2.cols,image2.rows));
    image2.copyTo(half);

    cv::namedWindow("After warping");
    cv::imshow("After warping",result);

    cv::waitKey();
    return 0;



}
