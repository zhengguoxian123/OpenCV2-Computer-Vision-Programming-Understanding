#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/video/tracking.hpp>

#include "featuretracker.hpp"


int main()
{
    VideoProcessor processor;

    FeatureTracker tracker;

    processor.setInput("../bike.avi");

    processor.setFrameProcessor(&tracker);

    processor.displayOutput("Tracked Features");

    processor.setDelay(1000./processor.getFrameRate());

    processor.run();

    cv::waitKey();
}
