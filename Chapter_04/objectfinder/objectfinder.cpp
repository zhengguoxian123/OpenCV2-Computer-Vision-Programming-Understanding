#include<iostream>
using namespace std;

#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "histogram.hpp"
#include "objectfinder.hpp"
#include "colorhistogram.hpp"

int main()
{
    cv::Mat image = cv::imread("../waves.jpg",0);

    if(!image.data)
        return 0;
    cv::Mat imageROI;
    //截取图像的某个区域，360，55是像素的位置，40，50 是区域的大小
    imageROI = image(cv::Rect(360,55,40,50));

    cv::namedWindow("Reference");
    cv::imshow("Reference",imageROI);

    Histogram1D h;
    cv::MatND hist = h.getHistogram(imageROI);
    cv::namedWindow("Reference Hist");
    cv::imshow("Reference Hist",h.getHistogramImage(imageROI));

    //
    ObjectFinder finder;
    finder.setHistogram(hist);

    finder.setThreshold(-1.0f);

    cv::Mat result1;
    //反投影直方图
    result1= finder.find(image);

    cv::Mat tmp;
    //??opencv数据类型转换，tmp是输出
    result1.convertTo(tmp,CV_8U,-1.0,255.0);
    cv::namedWindow("Backprojection result");
    cv::imshow("Backprojection result",tmp);

    finder.setThreshold(0.12f);
    result1 = finder.find(image);
    //cv::Scalar(0,0,0) 方框线条的颜色
    cv::rectangle(image,cv::Rect(360,55,40,50),cv::Scalar(0,0,0));

    cv::namedWindow("Image");
    cv::imshow("Image",image);

    cv::namedWindow("Detection Result");
    cv::imshow("Detection Result",result1);

    cv::Mat image2 = cv::imread("../dog.jpg",0);
    cv::Mat result2;
    //反投影直方图
    result2 = finder.find(image2);

    cv::namedWindow("Result(2)");
    cv::imshow("Result(2)",result2);
//----------------------------------------------------------
    //load color image
    ColorHistogram hc;
    cv::Mat color = cv::imread("../waves.jpg");
    //减色函数P45
    color = hc.colorReduce(color,32);
    cv::namedWindow("Color Image");
    cv::imshow("Color Image",color);
//----------------------------------------------------------
    imageROI = color(cv::Rect(0,0,165,75));
    //获取直方图
    cv::MatND shist = hc.getHistogram(imageROI);
    //归一化直方图
    finder.setHistogram(shist);
    finder.setThreshold(0.05f);
    //反投影直方图
    result1 = finder.find(color);
    //有啥不一样
    cv::namedWindow("Color Backproject Result");
    cv::imshow("Color Backproject Result",result1);
//---------------------------------
    //second color image
    cv::Mat color2 = cv::imread("../dog.jpg");
    //减色函数
    color2 = hc.colorReduce(color2,32);

    //反投影直方图
    result2 = finder.find(color2);
    cv::namedWindow("Result color (2)");
    cv::imshow("Result color (2)",result2);
//-------------------------------------------
    color = cv::imread("../waves.jpg");
    //
    imageROI = color(cv::Rect(0,0,165,75));
    //获取直方图
    cv::MatND colorhist = hc.getabHistogram(imageROI);
    //归一化直方图
    finder.setHistogram(colorhist);
    //阈值化，可以获得最可能是”云“的像素
    finder.setThreshold(0.05f);

    cv::Mat lab;
    cv::cvtColor(color,lab,CV_BGR2Lab);

    int ch[2] = {1,2};
    //反投影直方图
    result1= finder.find(lab,-128.0f,127.0f,ch,2);

    cv::namedWindow("Result ab (1)");
    cv::imshow("Result ab (1)",result1);

    //second color image
    color2 = cv::imread("../dog.jpg");
    cv::namedWindow("Color Image (2)");
    cv::imshow("Color Image (2)",color2);

    cv::cvtColor(color2,lab,CV_BGR2Lab);
    //反投影直方图
    result2 = finder.find(lab,-128.0f,127.0f,ch,2);

    cv::namedWindow("Result ab (2)");
    cv::imshow("Result ab (2)",result2);

    //??
    //get hue color histogram
    color = cv::imread("../waves.jpg");
    imageROI = color(cv::Rect(0,0,165,75));
    //获取直方图
    colorhist = hc.getHueHistogram(imageROI);
    //直方图归一化
    finder.setHistogram(colorhist);
    finder.setThreshold(0.3f);

    //??
    cv::Mat hsv;
    cv::cvtColor(color,hsv,CV_BGR2HSV);

    //??
    ch[0]=0;
    //反投影直方图
    result1 = finder.find(hsv,0.0f,180.0f,ch,1);

    cv::namedWindow("Result Hue (1)");
    cv::imshow("Result Hue (1)",result1);

    //second color image
    color2 = cv::imread("../dog.jpg");
    cv::cvtColor(color2,hsv,CV_BGR2HSV);

    result2 = finder.find(hsv,0.0f,180.0f,ch,1);

    cv::namedWindow("Result Hue (2)");
    cv::imshow("Result Hue (2)",result2);


    cv::waitKey();

    return 0;
}


