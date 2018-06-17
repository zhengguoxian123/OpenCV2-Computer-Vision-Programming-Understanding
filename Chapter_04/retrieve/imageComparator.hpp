#ifndef IMAGECOMPARATOR_H
#define IMAGECOMPARATOR_H
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "colorhistogram.hpp"


class ImageComparator
{
private:
    cv::Mat reference;
    cv::Mat input;
    cv::MatND refH;
    cv::MatND inputH;

    ColorHistogram hist;

    int div;
public:
    ImageComparator():div(32)
    {}
    //???
    void setColorReduction(int factor)
    {
        div = factor;
    }

    int getColorReduction()
    {
        return div;
    }

    void setReferenceImage(const cv::Mat& image)
    {
        reference = hist.colorReduce(image,div);
        refH = hist.getHistogram(reference);
    }

    double compare(const cv::Mat& image)
    {
        input = hist.colorReduce(image,div);
        inputH = hist.getHistogram(input);

        //???比较直方图
        return cv::compareHist(refH,inputH,CV_COMP_INTERSECT);
    }

};



#endif
