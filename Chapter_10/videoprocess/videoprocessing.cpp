#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include "videoprocessor.hpp"

void draw(cv::Mat& img,cv::Mat& out)
{
    img.copyTo(out);
    cv::circle(out,cv::Point(100,100),5,cv::Scalar(255,0,0),2);
}

void canny(cv::Mat& img,cv::Mat& out)
{
    cv::cvtColor(img,out,CV_BGR2GRAY);

    cv::Canny(out,out,100,200);

    cv::threshold(out,out,128,255,cv::THRESH_BINARY_INV);
}

int main()
{
    cv::VideoCapture capture("../bike.avi");
    if(!capture.isOpened())
        return 1;

    double rate = capture.get(CV_CAP_PROP_FPS);

    bool stop(false);

    cv::Mat frame;

    cv::namedWindow("Extracted Frame");

    int delay =1000/rate;
    int i = 0;
    while(!stop)
    {
        if(!capture.read(frame))
            break;

        cv::imshow("Extracted Frame",frame);
        //????
        cv::waitKey(30);

    }

    capture.release();

    cv::waitKey(1000);

    std::cout<<"AAAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
    VideoProcessor processor;

    processor.setInput("../bike.avi");

    processor.displayInput("Input Video");

    processor.displayOutput("Output Video");

    processor.setDelay(1000./processor.getFrameRate());

    processor.setFrameProcessor(canny);

    processor.run();

    cv::waitKey(1000);


    processor.setInput("../bike.avi");
    cv::Size size =processor.getFrameSize();
    std::cout<<size.width<<" "<<size.height<<std::endl;
    std::cout<<processor.getFrameRate()<<std::endl;
    std::cout<<processor.getTotalFrameCount()<<std::endl;
    std::cout<<processor.getFrameNumber()<<std::endl;
    std::cout<<processor.getPositionMS()<<std::endl;

    processor.dontCallProcess();

    char codec[4];

    processor.setOutput("../output/bike.avi",processor.getCodec(codec),processor.getFrameRate());
    std::cout<<"Codec: "<<codec[0]<<codec[1]<<codec[2]<<codec[3]<<std::endl;

    processor.displayInput("Current Frame");
    processor.displayOutput("Output Frame");

    processor.setDelay(1000./processor.getFrameRate());

    processor.run();

    std::cout<<processor.getFrameNumber()<<std::endl;
    std::cout<<processor.getPositionMS()<<std::endl;

    cv::waitKey();

}
