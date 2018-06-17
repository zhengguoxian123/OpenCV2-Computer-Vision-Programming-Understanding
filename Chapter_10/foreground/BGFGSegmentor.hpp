#ifndef BGFGSEGMENTOR_HPP
#define BGFGSEGMENTOR_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



#include "videoprocessor.hpp"


class BGFGSegmentor:public FrameProcessor
{
    cv::Mat gray;
    cv::Mat background;
    cv::Mat backImage;
    cv::Mat foreground;
    double learningRate;
    int threshold;

public:
    BGFGSegmentor():threshold(10),learningRate(0.01) {}

    void setThreshold(int t)
    {
        threshold = t;
    }

    void setLearningRate(double r)
    {
        learningRate = r;
    }

    void process(cv::Mat& frame,cv::Mat& output)
    {
        cv::cvtColor(frame,gray,CV_BGR2GRAY);

        if(background.empty())
            gray.convertTo(background,CV_32F);

        background.convertTo(backImage,CV_8U);

        cv::absdiff(backImage,gray,foreground);

        cv::threshold(foreground,output,threshold,255,cv::THRESH_BINARY_INV);

        cv::accumulateWeighted(gray,background,learningRate,output);
    }

};
#endif
