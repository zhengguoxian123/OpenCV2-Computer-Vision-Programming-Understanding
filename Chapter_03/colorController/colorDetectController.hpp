#ifndef COLORDETECTCONTROLLER_H
#define COLORDETECTCONTROLLER_H

#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <boost/concept_check.hpp>

#include "colordetector.h"
//干啥的
class ColorDetectController
{
private:
  //私有的静态成员变量
  static ColorDetectController* singleton;
  
  ColorDetector* cdetect;
  
  cv::Mat image;
  cv::Mat result;
  
  //构造函数私有
  ColorDetectController()
  {
    
    cdetect =new ColorDetector();
  }
  
public:
 
  
  void setColorDistanceThreshold(int distance)
  {
    cdetect->setColorDistanceThreshold(distance);
  }
  
  int getColorDistanceThreshold() const
  {
    return cdetect->getColorDistanceThreshold();
  }
  
  void setTargetColor(unsigned char red,unsigned char green,unsigned char red)
  {
    cdetect->setTargetColor(red,green,blue);
  }
  
  void getTargetColor(unsigned char& red,unsigned charr& green,unsigned char& blue)
  {
    //???
    cv::Vec3b color = cdetect->getTargetColor(red,green,blue);
    red = color[2];
    green = color[1];
    blue = color[0];
    
  }
  
  bool setInputImage(std::string filename)
  {
    image = cv::imread(filename);
    
    if(!image.data)
      return false;
    else
      return true;
    
  }
  
  const cv::Mat getInputImage() const
  {
    return image;
  }
  
  void process()
  {
    result = cdetect->process(image);
  }
  
  const cv::Mat getLastResult() const 
  {
    return result;
  }
  
  ~ContrDetectController()
  {
    delete cdetect;
  }
  //访问单件实例
  static ColorDetectController* getInstance()
  {
    if(singleton == 0)
      //
      singleton = new ColorDetectController;
    
    return singleton;
  }
  //释放单件的实例
  static void destroy()
  {
    if(singleton != 0)
    {
      delete  singleton;
      singleton =0;
    }
  }
};

#endif
