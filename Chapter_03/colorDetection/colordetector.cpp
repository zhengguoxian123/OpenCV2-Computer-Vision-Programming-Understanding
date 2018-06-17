#include "colordetector.hpp"

cv::Mat ColorDetector::process(const cv::Mat& image)
{
  result.create(image.rows,image.cols,CV_8U);
  
  cv::Mat_<cv::Vec3b>::const_iterator it =image.begin<cv::Vec3b>();
  cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
  cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
  
  for(;it!=itend;++it,++itout)
  {
    if(getDistance(*it)<minDist)
      *itout =255;
    else
      *itout =0;
  }
  
  return result;
}
