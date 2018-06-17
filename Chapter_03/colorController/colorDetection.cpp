#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include "colordetector.hpp"

int main()
{
  ColorDetector cdetect;
  
  cv::Mat image = cv::imread("../boldt.jpg");
  if(!image.data)
    return 0;
  
  cdetect.setTargetColor(130,190,230);
  
  cv::namedWindow("result");
  cv::imshow("result",cdetect.process(image));
  cv::waitKey();
  return 0;
}
