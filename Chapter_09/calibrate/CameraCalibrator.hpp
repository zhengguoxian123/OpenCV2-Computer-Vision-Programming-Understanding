#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H

#include<vector>
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include<opencv2/highgui/highgui.hpp>

class CameraCalibrator
{
    //?
    //位于世界坐标的点
    std::vector<std::vector<cv::Point3f>> objectPoints;
    //像素坐标的点
    std::vector<std::vector<cv::Point2f>> imagePoints;
    
    //输出矩阵
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    //标定的方式
    int flag;
    //用于图像去畸变
    cv::Mat map1,map2;

    bool mustInitUndistort;
public:
    CameraCalibrator():flag(0),mustInitUndistort(true) {};

    int addChessboardPoints(const std::vector<std::string>& filelist,cv::Size& boardSize);

    void addPoints(const std::vector<cv::Point2f>& imageCorners,const std::vector<cv::Point3f>& objectCorners);

    double calibrate(cv::Size imageSize);

//    void setCalibrationFlag(bool radial8CoffEnabled= false, bool tangentialParamEnabled = false);

    cv::Mat remap(const cv::Mat& image);

    cv::Mat getCameraMatrix() {return cameraMatrix;}
    cv::Mat getDistCoeffs()   {return distCoeffs;}

};





#endif
