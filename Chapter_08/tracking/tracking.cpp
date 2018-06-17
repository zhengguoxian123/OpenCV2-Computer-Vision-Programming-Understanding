#include<iostream>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
// for   cv::BruteForceMatcher<cv::L2<float> > matcher;
#include<opencv2/legacy/legacy.hpp>
int main()
{
    cv::Mat image1 = cv::imread("../church01.jpg",0);
    cv::Mat image2 = cv::imread("../church02.jpg",0);

    if(!image1.data ||!image2.data)
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

    std::cout<<"Number of SURF points(1)"<<keypoints1.size()<<std::endl;
    std::cout<<"Number of SURF points(2)"<<keypoints2.size()<<std::endl;

    cv::Mat imageKP;
    cv::drawKeypoints(image1,keypoints1,imageKP,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow("Right SURF Features");
    cv::imshow("Right SURF Features",imageKP);

    cv::drawKeypoints(image2,keypoints2,imageKP,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow("Left SURF Features");
    cv::imshow("Left SURF Features",imageKP);

    //构造SURF描述子提取器
    cv::SurfDescriptorExtractor surfDesc;
    cv::Mat descriptors1,descriptors2;
    //提取SURF描述子
    surfDesc.compute(image1,keypoints1,descriptors1);
    surfDesc.compute(image2,keypoints2,descriptors2);

    std::cout<<"descriptor matrix size: "<<descriptors1.rows<<" by "<<descriptors1.cols<<std::endl;
    //构造匹配器
    cv::BruteForceMatcher<cv::L2<float> > matcher;
    //匹配两幅图像的描述子
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1,descriptors2,matches);

    std::cout<<"Number of matched points: "<<matches.size()<<std::endl;

    std::nth_element(matches.begin(),//初始位置
		     matches.begin()+24,//排序元素的位置
		     matches.end());//终止位置
    //移除第25位之后的所有元素
    matches.erase(matches.begin()+25,matches.end());
    //
    cv::Mat imageMatches;
    cv::drawMatches(image1,keypoints1,//第一幅图像及其特征点
                    image2,keypoints2,//第二幅图像及其特征点
                    matches,//匹配结果
                    imageMatches,//生成的图像
                    cv::Scalar(255,255,255));//直线的颜色

    cv::namedWindow("Matches");
    cv::imshow("Matches",imageMatches);

    cv::waitKey();
    return 0;

    int size=7;
    cv::Mat imaf1;
    image1.convertTo(imaf1,CV_32F);

    cv::Mat imaf2;
    image2.convertTo(imaf2,CV_32F);

    cv::waitKey();
    return 0;



}
