//analyze

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



int main()
{
    cv::Mat image = cv::imread("../binaryGroup.bmp",0);
    if(!image.data)
        return 0;

    cv::namedWindow("Binary Image");
    cv::imshow("Binary Image",image);

    std::vector<std::vector<cv::Point> > contours;

    cv::findContours(image,
                     contours,//轮廓的数组
                     CV_RETR_EXTERNAL,//获取外轮廓
                     CV_CHAIN_APPROX_NONE);//获取每个轮廓的每个像素

    std::cout<<"Contours: "<<contours.size()<<std::endl;
    std::vector<std::vector<cv::Point> >::const_iterator itContours = contours.begin();

    for(;itContours != contours.end();++itContours)
    {
        std::cout<<"Size: "<<itContours->size()<<std::endl;

    }

    //在白色图像上绘制黑色轮廓
    cv::Mat result(image.size(),CV_8U,cv::Scalar(255));
    cv::drawContours(result,contours,
                     -1,//绘制所有轮廓
                     cv::Scalar(0),//颜色为黑色
                     2);//轮廓线的绘制宽度为2
    cv::namedWindow("Contours");
    cv::imshow("Contours",result);

    //移除过长或过短的轮廓
    int cmin= 100;//最小轮廓长度
    int cmax = 1000;//最大轮廓长度

    std::vector<std::vector<cv::Point> >::const_iterator itc = contours.begin();
    //std::vector<std::vector<cv::Point>>::const_iterator itc= contours.begin();
    while(itc!=contours.end())
    {
        if(itc->size() <cmin || itc->size() >cmax)
            //变量的类型不对
            ++itc;//itc = contours.erase(itc);
        else
            ++itc;
    }

    cv::Mat original = cv::imread("../group.jpg");
    cv::drawContours(original,contours,
                     -1,
                     cv::Scalar(255,255,255),
                     2);
    cv::namedWindow("Contours on animals");
    cv::imshow("Contours on animals",original);

    result.setTo(cv::Scalar(255));
    cv::drawContours(result,contours,
                     -1,
                     cv::Scalar(0),
                     1);
    //...................................................................
    image = cv::imread("../binaryGroup.bmp",0);
    //测试包围盒
    //用一个盒子来包围一个轮廓
    cv::Rect r0 = cv::boundingRect(cv::Mat(contours[0]));
    cv::rectangle(result, r0,cv::Scalar(0),2);

    //测试最小包围圆
    float radious;
    cv::Point2f center;
    cv::minEnclosingCircle(cv::Mat(contours[1]),center,radious);
    cv::circle(result,cv::Point(center),static_cast<int>(radious),cv::Scalar(0),2);

    //测试多边形近似
    std::vector<cv::Point> poly;
    cv::approxPolyDP(cv::Mat(contours[2]),poly,5,true);

    std::cout<<"Polygon size:"<<poly.size()<<std::endl;

    //遍历每个片段进行绘制
    std::vector<cv::Point>::const_iterator itp = poly.begin();
    while(itp != (poly.end()-1))
    {
        cv::line(result,*itp,*(itp+1),cv::Scalar(0),2);
        ++itp;
    }
    //首尾用直线相连
    cv::line(result,*(poly.begin()),*(poly.end()-1),cv::Scalar(20),2);

    //测试凸包
    std::vector<cv::Point> hull;
    cv::convexHull(cv::Mat(contours[3]),hull);

    std::vector<cv::Point>::const_iterator it = hull.begin();
    while(it != (hull.end()-1))
    {
        cv::line(result,*it,*(it+1),cv::Scalar(0),2);
        ++it;
    }

    cv::line(result,*(hull.begin()),*(hull.end()-1),cv::Scalar(20),2);

    //测试力距
    //遍历所有轮廓
    itc = contours.begin();
    while(itc != contours.end())
    {
        //计算所有力距
        cv::Moments mom = cv::moments(cv::Mat(*itc++));
        //绘制质心
        cv::circle(result,
                   //质心坐标转换为整数
                   cv::Point(mom.m10/mom.m00,mom.m01/mom.m00),
                   2,cv::Scalar(0),2);//绘制黑点


    }

    cv::namedWindow("Some Shape descripters");
    cv::imshow("Some shape descripters",result);

    image = cv::imread("../binaryGroup.bmp",0);
    cv::findContours(image,
                     contours,
                     CV_RETR_LIST,
                     CV_CHAIN_APPROX_NONE);
    result.setTo(cv::Scalar(255));
    cv::drawContours(result,contours,
                     -1,
                     cv::Scalar(0),
                     2);
    cv::namedWindow("All Contours");
    cv::imshow("All Contours",result);

    cv::waitKey();
    return 0;
}
