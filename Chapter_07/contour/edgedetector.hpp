#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H

#define PI 3.1415926


#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core.hpp>

class EdgeDetector
{
private:

    cv::Mat img;

    cv::Mat sobel;

    int aperture;

    cv::Mat sobelMagnitude;

    cv::Mat sobelOrientation;

public:

    EdgeDetector(): aperture(3) {}

    void setAperture(int a)
    {
        aperture = a;
    }

    int getAperture() const
    {
        return aperture;
    }
    //!!!void computeSobel(const cv::Mat& image,cv::Mat& sobelX = cv::Mat(),cv::Mat& sobelY=cv::Mat())
    void computeSobel(const cv::Mat& image,cv::Mat sobelX = cv::Mat(),cv::Mat sobelY=cv::Mat())
    {
        cv::Sobel(image,sobelX,CV_32F,1,0,aperture);
        cv::Sobel(image,sobelY,CV_32F,0,1,aperture);

        cv::cartToPolar(sobelX,sobelY,sobelMagnitude,sobelOrientation);

    }

    cv::Mat getMagnitude()
    {
        return sobelMagnitude;
    }

    cv::Mat getOrientation()
    {
        return sobelOrientation;
    }

    cv::Mat getBinaryMap(double threshold)
    {
        cv::Mat bin;
        //低于阈值的像素将变成255
        cv::threshold(sobelMagnitude,bin,threshold,255,cv::THRESH_BINARY_INV);

        return bin;
    }

    cv::Mat getSobelImage()
    {
        cv::Mat bin;

        double minval,maxval;

        cv::minMaxLoc(sobelMagnitude,&minval,&maxval);
        sobelMagnitude.convertTo(bin,CV_8U,255/maxval);

        return bin;
    }

    cv::Mat getSobelOrientationImage()
    {
        cv::Mat bin;
        //???
        sobelOrientation.convertTo(bin,CV_8U,90/PI);

        return bin;
    }
};

#endif
