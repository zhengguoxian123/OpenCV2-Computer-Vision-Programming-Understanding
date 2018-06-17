#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class ColorHistogram
{
private:
    int histSize[3];
    float hranges[2];
    const float* ranges[3];
    int channels[3];

public:
    ColorHistogram()
    {
        histSize[0] =histSize[1]=histSize[2]=256;
        hranges[0] =0.0;
        hranges[1] =255.0;
        ranges[0] = hranges;
        ranges[1] = hranges;
        ranges[2] = hranges;
        channels[0] = 0;
        channels[1] = 1;
        channels[2] = 2;

    }

    cv::MatND getHistogram(const cv::Mat& image)
    {
        cv::MatND  hist;
        hranges[0] = 0.0;
        hranges[1] = 255.0;
        channels[0] =0;
        channels[1] =1;
        channels[2] =2;

        cv::calcHist(&image,
                     1,
                     channels,
                     cv::Mat(),
                     hist,
                     3,
                     histSize,
                     ranges

                    );
        return hist;
    }

    cv::SparseMat getSparseHistogram(const cv::Mat& image)
    {
        cv::SparseMat hist(3,histSize,CV_32F);
        hranges[0] = 0.0;
        hranges[1] = 255.0;
        channels[0] =0;
        channels[1] =1;
        channels[2] =2;

        cv::calcHist(&image,
                     1,
                     channels,
                     cv::Mat(),
                     hist,
                     3,
                     histSize,
                     ranges

                    );
        return hist;
    }

    cv::MatND getabHistogram(const cv::Mat& image)
    {
        cv::MatND hist;
        cv::Mat lab;
        cv::cvtColor(image,lab,CV_BGR2Lab);

        hranges[0] = -128.0;
        hranges[1] = 127.0;
        channels[0] = 1;
        channels[1] = 2;

        cv::calcHist(&lab,
                     1,
                     channels,
                     cv::Mat(),
                     hist,
                     2,
                     histSize,
                     ranges

                    );

         return hist;
    }

    cv::MatND getHueHistogram(const cv::Mat& image)
    {
        cv::MatND hist;

        cv::Mat hue;

        cv::cvtColor(image,hue,CV_BGR2HSV);

        hranges[0] =0.0;
        hranges[1] =180.0;
        channels[0] = 0;

        cv::calcHist(&hue,
                     1,
                     channels,
                     cv::Mat(),
                     hist,
                     1,
                     histSize,
                     ranges
                    );
        return hist;
    }

    cv::Mat colorReduce(const cv::Mat& image,int div = 64)
    {
        int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));

        //???
        uchar mask= 0xFF<<n;

        cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
        cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();

        cv::Mat result(image.rows,image.cols,image.type());
        cv::Mat_<cv::Vec3b>::iterator  itr = result.begin<cv::Vec3b>();
        for(;it!= itend; ++it,++itr)
        {
            (*itr)[0] = ((*it)[0]&mask) +div/2;
            (*itr)[1] = ((*it)[1]&mask) +div/2;
            (*itr)[2] = ((*it)[2]&mask) +div/2;
        }

        return result;
    }
};

#endif
