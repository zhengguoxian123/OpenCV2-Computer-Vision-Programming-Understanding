#include<iostream>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/calib3d/calib3d.hpp>

#include "matcher.hpp"


int main()
{
    cv::Mat image1 = cv::imread("../canal1.jpg",0);
    cv::Mat image2 = cv::imread("../canal2.jpg",0);

    if(!image1.data ||!image2.data)
        return 0;

    cv::namedWindow("Right Image");
    cv::imshow("Right Image",image1);

    cv::namedWindow("Left Image");
    cv::imshow("Left Image",image2);

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
                    matches,imageMatches,
                    cv::Scalar(255,255,255));

    cv::namedWindow("Matches");
    cv::imshow("Matches",imageMatches);

    std::vector<cv::Point2f> points1,points2;

    for(std::vector<cv::DMatch>::const_iterator it = matches.begin();
        it != matches.end();++it)
    {
        float x = keypoints1[it->queryIdx].pt.x;
        float y = keypoints2[it->queryIdx].pt.y;
        points1.push_back(cv::Point2f(x,y));
        cv::circle(image1,cv::Point(x,y),3,cv::Scalar(255,255,255),3);

        x= keypoints2[it->trainIdx].pt.x;
        y= keypoints2[it->trainIdx].pt.y;
        cv::circle(image2,cv::Point(x,y),3,cv::Scalar(255,255,255),3);

        points2.push_back(cv::Point2f(x,y));
    }

    std::vector<cv::Vec3f> lines1;
    cv::computeCorrespondEpilines(cv::Mat(points1),1,fundamental,lines1);

    for(std::vector<cv::Vec3f>::const_iterator it = lines1.begin();it != lines1.end();++it)
    {
       cv::line(image2,cv::Point(0,-(*it)[2]/(*it)[1]),cv::Point(image2.cols,-((*it)[0]*image1.cols)/(*it)[1]),cv::Scalar(255,255,255));

    }

    std::vector<cv::Vec3f> lines2;
    cv::computeCorrespondEpilines(cv::Mat(points2),1,fundamental,lines2);

    for(std::vector<cv::Vec3f>::const_iterator it = lines2.begin();it != lines2.end();++it)
    {
       cv::line(image1,cv::Point(0,-(*it)[2]/(*it)[1]),cv::Point(image1.cols,-((*it)[0]*image1.cols)/(*it)[1]),cv::Scalar(255,255,255));

    }

    cv::namedWindow("Right Image Eplines (RANSAC)");
    cv::imshow("Right Image Eplines (RANSAC)",image1);

    cv::namedWindow("Left Image Eplines (RANSAC)");
    cv::imshow("Left Image Eplines (RANSAC)",image2);

    cv::waitKey();
    return 0;

}
