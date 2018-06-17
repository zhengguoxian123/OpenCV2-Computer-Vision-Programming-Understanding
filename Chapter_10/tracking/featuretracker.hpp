#ifndef FEATURETRACKER_HPP
#define FEATURETRACKER_HPP


#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>

#include "videoprocessor.hpp"

class FeatureTracker:public FrameProcessor
{
    cv::Mat gray;
    cv::Mat gray_prev;
    std::vector<cv::Point2f> points[2];
    std::vector<cv::Point2f> initial;
    std::vector<cv::Point2f> features;
    int max_count;
    double qlevel;
    double minDist;
    std::vector<uchar> status;

    std::vector<float> err;

public:
    FeatureTracker():max_count(500),qlevel(0.01),minDist(10.) {}

    void process(cv::Mat& frame,cv::Mat& output)
    {
        cv::cvtColor(frame,gray,CV_BGR2GRAY);
        frame.copyTo(output);

        if(addNewPoints())
        {
            detectedFeaturePoints();
            points[0].insert(points[0].end(),features.begin(),features.end());
            initial.insert(initial.end(),features.begin(),features.end());
        }

        if(gray_prev.empty())
            gray.copyTo(gray_prev);

        cv::calcOpticalFlowPyrLK(gray_prev,gray,
                                 points[0],
                                 points[1],
                                 status,
                                 err);

        int k = 0;

        for(int i = 0;i<points[1].size();i++)
        {
            if(acceptTrackedPoint(i))
            {
                initial[k] = initial[i];
                points[1][k++] = points[1][i];

            }
         }
        points[1].resize(k);
        initial.resize(k);

        handleTrackedPoints(frame,output);

        std::swap(points[1],points[0]);
        cv::swap(gray_prev,gray);

    }

    void detectedFeaturePoints()
    {
        cv::goodFeaturesToTrack(gray,features,max_count,qlevel,minDist);
    }

    bool addNewPoints()
    {
        return points[0].size() <=10;
    }

    bool acceptTrackedPoint(int i)
    {
        return status[i]&& (abs(points[0][i].x-points[1][i].x)+(abs(points[0][i].y-points[1][i].y))>2);
    }

    void handleTrackedPoints(cv::Mat& frame,cv::Mat& output)
    {
        for(int i =0;i<points[i].size();i++)
        {
            cv::line(output,initial[i],points[1][i],cv::Scalar(255,255,255));
            cv::circle(output,points[1][i],3,cv::Scalar(255,255,255),-1);
        }
    }


};




#endif
