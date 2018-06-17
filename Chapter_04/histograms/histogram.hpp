#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


class Histogram1D
{
private:
  int histSize[1];
  float hranges[2];
  const float* ranges[1];
  int channels[1];
  
public:
  
  Histogram1D()
  {
    histSize[0]=256;
    hranges[0]=0.0;
    hranges[1]=255.0;
    //???
    ranges[0]=hranges;
    
    channels[0]=0;
  } 
  void setChannel(int c)
  {
      channels[0]=c;
  }
    
  int getChannel()
  {
      return channels[0];
  }
    
  void setRange(float minValue, float maxValue)
  {
    hranges[0]=minValue;
    hranges[1]=maxValue;
  }
    
  float getMinValue()
  {
    return hranges[0];
  }
    
  float getMaxValue()
  {
    return hranges[1];
  }
    
    //???
  void setNBins(int nbins)
  {
    histSize[0]=nbins;
  }
    
  int getNBins()
    {
      return histSize[0];
    }
    
  cv::MatND getHistogram(const cv::Mat& image)
  {
    cv::MatND hist;
    cv::calcHist(&image,   //
		   1,
           channels,      //
           cv::Mat(),
           hist,         //返回的直方图
           1,            //
           histSize,     //
           ranges        //
      );
      
      return hist;
  }
  
  cv::Mat getHistogramImage(const cv::Mat& image)
  {
    //首先计算直方图
    cv::MatND hist = getHistogram(image);

    //获取最大值和最小值
    double maxVal =0;
    double minVal =0;
    cv::minMaxLoc(hist,&minVal,&maxVal,0,0);
    
    //显示直方图的图像？？？
    cv::Mat histImg(histSize[0],histSize[0],CV_8U,cv::Scalar(255));
    
    //设置最高点为nbins的90%???
    int hpt = static_cast<int>(0.9*histSize[0]);
    
    //每个条目都绘制一条垂直线
    for(int h=0;h<histSize[0];h++)
    {
      float binVal = hist.at<float>(h);
      int intensity = static_cast<int>(binVal*hpt/maxVal);
      //两点之间绘制一条线
      cv::line(histImg,cv::Point(h,histSize[0]),cv::Point(h,histSize[0]-intensity),cv::Scalar::all(0));
    }
    
    return histImg;
    
  }
  
  cv::Mat equalize(const cv::Mat& image)
  {
    cv::Mat result;
    //直方图均衡化   间接增强图像对比度的方法
    cv::equalizeHist(image,result);
    
    return result;
  }
  

  cv::Mat stretch(const cv::Mat& image,int minValue=0)
  {
    //首先计算直方图
    cv::MatND hist = getHistogram(image);
    
    //寻找直方图最左端大于minValue的像素
    int imin = 0;
    for(;imin < histSize[0];imin++)
    {
      std::cout<<hist.at<float>(imin)<<std::endl;
      if(hist.at<float>(imin)>minValue)
            break;
    }
    
    //寻找直方图最右端大于minValue的像素
    int imax = histSize[0]-1;
    for(;imax>=0;imax--)
    {
        if(hist.at<float>(imax)>minValue)
            break;
    }

    //创建查找表
    int dims[1] = {256};
    cv::MatND lookup(1,dims,CV_8U);
    
    //填充查找表
    for(int i=0;i<256;i++)
    {
      if(i<imin) lookup.at<uchar>(i) =0;
      else if(i>imax) lookup.at<uchar>(i)=255;
      //
      else lookup.at<uchar>(i)=static_cast<uchar>(255.0*(i-imin)/(imax-imin)+0.5);
    }

    cv::Mat result;
    result= applyLookUp(image,lookup);

    return result;
  }

  //lookup   1x256 uchar matrix
  //应用查找表
  //啥用的？？？
  cv::Mat applyLookUp(const cv::Mat& image,const cv::MatND& lookup)
  {
      cv::Mat result(image.rows,image.cols,CV_8U);
      cv::Mat_<uchar>::iterator itr = result.begin<uchar>();

      cv::Mat_<uchar>::const_iterator it =image.begin<uchar>();
      cv::Mat_<uchar>::const_iterator itend = image.end<uchar>();

      for(;it!=itend;++it,++itr)
      {
          *itr = lookup.at<uchar>(*it);
      }

      return result;
  }
  
};
#endif
