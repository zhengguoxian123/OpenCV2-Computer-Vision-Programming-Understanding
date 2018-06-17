#include<iostream>
using namespace std;

#include "histogram.hpp"
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

int main()
{
  //以黑白模式打开
  cv::Mat image =cv::imread("../group.jpg",0);
  
  if(!image.data)
    return 0;
  
  cv::namedWindow("Image");
  cv::imshow("Image",image);
  
  Histogram1D h;
  
  cv::MatND histo = h.getHistogram(image);
  
  for(int i=0;i<256;i++)
    cout<<"Value "<<i <<" = "<<histo.at<float>(i)<<endl;
  
  //以图形的方式显示直方图
  cv::namedWindow("Histgram");
  cv::imshow("Histgram",h.getHistogramImage(image));
  
  cv::Mat thresholded;
  //60是个临界值，大于这个值为255，小于这个值为0
  cv::threshold(image,thresholded,60,255,cv::THRESH_BINARY);
  
  cv::namedWindow("Binary Image");
  cv::imshow("Binary Image",thresholded);
  cv::imwrite("binary.bmp",thresholded);
  
  cv::Mat eq =h.equalize(image);
  //显示直方图均衡化的图像
  //直方图均衡化的目标是增强图像的对比度
  cv::namedWindow("Equalized Image");
  cv::imshow("Equalized Image",eq);
  
  //显示图像的直方图
  cv::namedWindow("Equalized Histgram");
  cv::imshow("Equalized Histogram",h.getHistogramImage(eq));
  
  //这一部分是
  //通过查找表将像素值转换为新的像素值
  cv::Mat str = h.stretch(image,5);
  
  cv::namedWindow("Stretched Image");
  cv::imshow("Stretched Image",str);
  
  cv::namedWindow("Stretched Histogram");
  cv::imshow("Stretched Histogram",h.getHistogramImage(str));

////格式对不上报错
//  uchar lookup[256];
  
//  for(int i=0;i<256;i++)
//  {
//    lookup[i] = 255-i;
//  }

  int dims[1] = {256};
  cv::MatND lookup(1,dims,CV_8U);

  //填充查找表
  for(int i=0;i<256;i++)
  {
    lookup.at<uchar>(i) =255-i;
  }


  cv::namedWindow("Negative image");
  cv::imshow("Negative image", h.applyLookUp(image,lookup));
  
  cv::waitKey();
  return 0;
}
