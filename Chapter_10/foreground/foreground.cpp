#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/video/background_segm.hpp>

#include "videoprocessor.hpp"
#include "BGFGSegmentor.hpp"



int main()
{
    cv::VideoCapture capture("../bike.avi");
    if(!capture.isOpened())
        return 0;
    cv::Mat frame;

    cv::Mat foreground;

    //for mog!!!!
    cv::BackgroundSubtractorMOG mog;

    cv::namedWindow("Extracted Foreground");

    bool stop(false);

    while(1)
    {
        if(!capture.read(frame))
            break;


        mog(frame,foreground,0.01);

        cv::threshold(foreground,foreground,128,255,cv::THRESH_BINARY_INV);

        cv::imshow("Extracted Foreground",foreground);


        cv::waitKey(30);
    }

    cv::waitKey(1000);
//...............................................................................
    VideoProcessor processor;

    BGFGSegmentor segmentor;

    segmentor.setThreshold(25);

    processor.setInput("../bike.avi");

    processor.setFrameProcessor(&segmentor);



    processor.displayOutput("Extracted Foreground");

    processor.setDelay(1000./processor.getFrameRate());

    processor.run();

    cv::waitKey();
    return 0;
}
