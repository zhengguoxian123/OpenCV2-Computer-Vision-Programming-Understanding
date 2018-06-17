#ifndef WATERSHEDSEGMENTATION_H
#define WATERSHEDSEGMENTATION_H

#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class WatershedSegmenter
{
private:
    cv::Mat markers;

public:
    void setMarkers(const cv::Mat& markerImage)
    {
        //转化为整数图像
        markerImage.convertTo(markers,CV_32S);

    }
    cv::Mat process(const cv::Mat& image)
    {
        //使用算法
        cv::watershed(image,markers);

        return markers;
    }

    cv::Mat getSegmentation()
    {
        cv::Mat tmp;
        markers.convertTo(tmp,CV_8U);

        return tmp;
    }

    cv::Mat getWatersheds()
    {
        cv::Mat tmp;
        markers.convertTo(tmp,CV_8U,255,255);
        return tmp;
    }
};
#endif
