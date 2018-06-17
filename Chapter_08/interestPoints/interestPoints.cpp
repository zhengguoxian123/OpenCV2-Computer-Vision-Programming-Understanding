//analyze
//opencv3相比于opencv2特征点检测接口变了，需要另外安装contrib
#include<iostream>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
//additional hpp for SURF
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>

#include "harrisDetector.hpp"

int main()
{
    cv::Mat image = cv::imread("../church01.jpg",0);
    if(!image.data)
        return 0;

    cv::namedWindow("Original Image");
    cv::imshow("Original Image",image);

    cv::Mat cornerStrength;

    cv::cornerHarris(image,cornerStrength,
                     3,//相邻像素的尺寸
                     3,//滤波器的孔径大小
                     0.01);//Harris 参数

    cv::Mat harrisCorners;
    double threshold = 0.0001;

    cv::threshold(cornerStrength,harrisCorners,threshold,255,cv::THRESH_BINARY_INV);

    cv::namedWindow("Harris Corner Map");
    cv::imshow("Harris Corner Map",harrisCorners);
//..................................................................
    HarrisDetector harris;//创建Harris检测器的对象

    harris.detect(image);//计算Harris值

    std::vector<cv::Point> pts;//检测Harris角点
    harris.getCorners(pts,0.01);

    harris.drawOnImage(image,pts);//绘制Harris角点

    cv::namedWindow("Harris Corners");
    cv::imshow("Harris Corners",image);

//...................................................................
    image = cv::imread("../church01.jpg",0);

    //计算适合跟踪的优质特征
    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(image,corners,
                            500,//返回的最大特征点数目
                            0.01,//质量等级
                            10);//两点之间的最小允许的距离
    std::vector<cv::Point2f>::const_iterator it = corners.begin();
    while(it != corners.end())
    {
        cv::circle(image,*it,3,cv::Scalar(255,255,255),2);
        ++it;
    }

    cv::namedWindow("Good Features to Track");
    cv::imshow("Good Features to Track",image);

//......................................................................
    //特征点向量
    std::vector<cv::KeyPoint> keypoints;

    //????opencv3相比于opencv2特征点检测接口变了，需要另外安装contrib
    //检测器的构造函数
    cv::GoodFeaturesToTrackDetector gftt(500,//返回的最大特征点数目
                0.01,//质量等级
                10);//两点之间允许的最小距离
    //使用FeatureDetector函数进行检测
    gftt.detect(image,keypoints);

    cv::drawKeypoints(image,
                     keypoints,
                     image,
                     cv::Scalar(255,255,255),
                     cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    cv::namedWindow("Good Features to Track Detector");
    cv::imshow("Good Features to Track Detector",image);
//.................................................................
    image = cv::imread("../church01.jpg",0);

    keypoints.clear();
    //???opencv3相比于opencv2特征点检测接口变了，需要另外安装contrib
    //构造Fast特征检测器
    cv::FastFeatureDetector fast(40);//检测阈值
    //进行检测
    fast.detect(image,keypoints);

    cv::drawKeypoints(image,//原始图像
		      keypoints,//特征点向量
		      image,//输出图像
		      cv::Scalar(255,255,255),//特征点颜色
		      cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);//绘制标记

    cv::namedWindow("FAST Features");
    cv::imshow("FAST Features",image);
//..........................................................................
    image = cv::imread("../church03.jpg",0);

    keypoints.clear();
    //???opencv3相比于opencv2特征点检测接口变了，需要另外安装contrib
    //#include<opencv2/nonfree/features2d.hpp>
    //构造SURF特征检测器
    cv::SurfFeatureDetector surf(2500);//阈值
    //检测SURF特征
    surf.detect(image,keypoints);
    //
    cv::Mat featureImage;
    cv::drawKeypoints(image,//原始图像
		      keypoints,//特征点向量
		      featureImage,//生成图像
		      cv::Scalar(255,255,255),//特征点颜色
		      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);//标志位

    cv::namedWindow("SURF Features");
    cv::imshow("SURF Features",featureImage);
//............................................................................
    image = cv::imread("../church01.jpg",0);

    keypoints.clear();
    //构造SURF特征检测器
    cv::SiftFeatureDetector sift(
                0.03,//特征的阈值
                10.);//用于降低直线敏感度的阈值
    //检测SURF特征
    sift.detect(image,keypoints);

    cv::drawKeypoints(image,keypoints,featureImage,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);


    cv::namedWindow("SIFT Features");
    cv::imshow("SIFT Features",featureImage);
//............................................................

    image = cv::imread("../church01.jpg",0);
    keypoints.clear();

    cv::MserFeatureDetector mser;
    mser.detect(image,keypoints);

    cv::drawKeypoints(image,
                      keypoints,
                      featureImage,
                      cv::Scalar(255,255,255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS
                      );

    cv::namedWindow("MSER Features");
    cv::imshow("MSER Features",featureImage);

    cv::waitKey();

    return 0;

}
