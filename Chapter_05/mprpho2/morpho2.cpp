//检测边缘和角点
//有各种膨胀和腐蚀
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include "morphoFeatures.hpp"

int main()
{
    cv::Mat image = cv::imread("../building.jpg",0);
    if(!image.data)
        return 0;
    cv::namedWindow("Image");
    cv::imshow("Image",image);
    MorphoFeatures morpho;
    morpho.setThreshold(40);

    cv::Mat edges;
    edges = morpho.getEdges(image);

    cv::namedWindow("Edge Image");
    cv::imshow("Edge Image",edges);

    morpho.setThreshold(-1);
    cv::Mat corners;
    corners = morpho.getCorners(image);
    cv::morphologyEx(corners,corners,cv::MORPH_TOPHAT,cv::Mat());
    cv::threshold(corners,corners,40,255,cv::THRESH_BINARY_INV);
    cv::namedWindow("corner Image");
    cv::imshow("corner Image",corners);
    //在2值图像的每个检测点上绘制一个圆
    morpho.drawOnImage(corners,image);
    cv::namedWindow("corners on image");
    cv::imshow("corners on image",image);
//----------------------------------------------------------------
    image = cv::imread("../church01.jpg",0);
    cv::namedWindow("Square Image");
    cv::imshow("Square Image",image);

    cv::Mat cross(5,5,CV_8U,cv::Scalar(0));
    //创建十字形元素
    for(int i= 0;i<5;i++)
    {
        cross.at<uchar>(2,i) =1;
        cross.at<uchar>(i,2) =1;
    }

    cv::Mat result;
    //十字形膨胀
    cv::dilate(image,result,cross);

    cv::namedWindow("Dilated square with cross");
    cv::imshow("Dilated square with cross",result);
    //创建菱形元素
    cv::Mat diamond(5,5,CV_8U,cv::Scalar(1));
    diamond.at<uchar>(0,0) =0;
    diamond.at<uchar>(0,1) =0;
    diamond.at<uchar>(1,0) = 0;
    diamond.at<uchar>(4,4) = 0;
    diamond.at<uchar>(3,4) = 0;
    diamond.at<uchar>(4,3) = 0;
    diamond.at<uchar>(4,0) = 0;
    diamond.at<uchar>(4,1) = 0;
    diamond.at<uchar>(3,0) = 0;
    diamond.at<uchar>(0,4) = 0;
    diamond.at<uchar>(0,3) = 0;
    diamond.at<uchar>(1,4) = 0;

    cv::Mat result2;
    //菱形腐蚀
    cv::erode(result,result2,diamond);
    //diamod
    cv::namedWindow("Eroded square with diamod");
    cv::imshow("Eroded square with diamod",result2);
//----------------------------------------------------
    //以下不知道是什么玩意？？？？？？？
    cv::Mat final(100,300,CV_8U);
    cv::Mat window = final(cv::Rect(0,0,100,100));
    image.copyTo(window);

    window = final(cv::Rect(100,0,100,100));
    result.copyTo(window);

    window = final(cv::Rect(200,0,100,100));
    result2.copyTo(window);

    cv::namedWindow("Combined");
    cv::imshow("Combined",final);
    cv::imwrite("suqare.bmp",final);
//=========================================================
    cv::waitKey();
    return 0;
}
