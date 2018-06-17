//使用均值漂移查找物体
#include<iostream>
#include<vector>
using namespace std;

#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/video/tracking.hpp>

#include "objectfinder.hpp"
#include "colorhistogram.hpp"

int main()
{
    //
    cv::Mat image = cv::imread("../baboon1.jpg");
    if(!image.data)
        return 0;
    //狒狒脸部的ROI
    cv::Mat imageROI = image(cv::Rect(110,260,35,40));
    //在一个图像上画方框
    cv::rectangle(image,cv::Rect(110,260,35,40),cv::Scalar(0,0,255));

    cv::namedWindow("Image");
    cv::imshow("Image",image);

    //???
    int minSat= 65;
    ColorHistogram hc;
    //没有对应的函数
    cv::MatND colorhist = hc.getHueHistogram(imageROI,minSat);
    //获取直方图
    //cv::MatND colorhist = hc.getHueHistogram(imageROI);
    ObjectFinder finder;
    //直方图归一化
    finder.setHistogram(colorhist);
    finder.setThreshold(0.2f);

    cv::Mat hsv;
    cv::cvtColor(image,hsv,CV_BGR2HSV);

    //??
    vector<cv::Mat> v;
    //图像通道分离
    cv::split(hsv,v);
    //??
    cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);
    cv::namedWindow("Saturation");
    cv::imshow("Saturation",v[1]);

    int ch[1] ={0};
    cv::Mat result = finder.find(hsv,0.0f,180.0f,ch,1);

    cv::namedWindow("Result Hue");
    cv::imshow("Result Hue", result);

    //对像素进行加和
    cv::bitwise_and(result,v[1],result);
    cv::namedWindow("Result Hue");
    cv::imshow("Result Hue",result);

    image = cv::imread("../baboon2.jpg");
    cv::namedWindow("Image 2");
    cv::imshow("Image 2",image);

    //转换格式   转换到HSV空间
    cv::cvtColor(image,hsv,CV_BGR2HSV);
    //通道分离
    cv::split(hsv,v);
    //识别低饱和度的像素
    cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);
    cv::namedWindow("Saturation");
    cv::imshow("Saturation",v[1]);

    //反投影直方图
    result = finder.find(hsv,0.0f,180.0f,ch,1);
    cv::namedWindow("Result Hue");
    cv::imshow("Result Hue",result);

    //对像素进行加和
    //用来干什么？？？ 去掉低饱和度的像素
    cv::bitwise_and(result,v[1],result);
    cv::namedWindow("Result Hue and");
    cv::imshow("Result Hue and",result);

    //叠加的目的是干啥呢
    finder.setThreshold(-1.0f);
    result=finder.find(hsv,0.0f,180.0f,ch,1);
    cv::bitwise_and(result,v[1],result);
    cv::namedWindow("Result Hue and raw");
    cv::imshow("Result Hue and raw",result);

    //初始区域
    cv::Rect rect(110,260,35,40);
    //画个红色方框
    cv::rectangle(image,rect,cv::Scalar(0,0,255));
    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,10,0.01);
    //???返回的是本次调用迭代的次数
    cout<<"meanshift= "<<cv::meanShift(result,rect,criteria)<<endl;

    //最终找到的区域  找到狒狒的脸了
    cv::rectangle(image,rect,cv::Scalar(0,255,0));

    cv::namedWindow("Image 2 result");
    cv::imshow("Image 2 result",image);

    cv::waitKey();
    return 0;


}
