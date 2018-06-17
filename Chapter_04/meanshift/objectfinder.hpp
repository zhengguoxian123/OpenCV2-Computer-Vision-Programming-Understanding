#ifndef OBJECTFIND_H
#define OBJECTFIND_H

class ObjectFinder
{
private:
    float hranges[2];
    const float* ranges[3];
    int channels[3];

    float threshold;
    cv::MatND histogram;
    cv::SparseMat shistogram;
    bool isSparse;

public:
    ObjectFinder():threshold(0.1f),isSparse(false)
    {
        ranges[0] = hranges;
        ranges[1] = hranges;
        ranges[2] = hranges;
    }

    void setThreshold(float t)
    {
        threshold = t;
    }

    float getThreshold()
    {
        return threshold;
    }

    void setHistogram(const cv::MatND& h)
    {
        isSparse = false;
        histogram = h;
        //归一化直方图
        cv::normalize(histogram,histogram,1.0);

    }

    void setHistogram(const cv::SparseMat& h)
    {
        isSparse = true;
        shistogram = h;
        cv::normalize(shistogram,shistogram,1.0,cv::NORM_L2);
    }

    cv::Mat find(const cv::Mat& image)
    {
        cv::Mat result;

        hranges[0] = 0.0;
        hranges[1] = 255.0;
        channels[0] = 0;
        channels[1] =1;
        channels[2] =2;

        if(isSparse)
        {
            cv::calcBackProject(&image,
                                1,
                                channels,
                                shistogram,
                                result,
                                ranges,
                                255.0


                        );
        }
        else
        {
            //反投影直方图
            cv::calcBackProject(&image,
                                1,
                                channels,
                                histogram,
                                result,
                                ranges,
                                255.0
            );
        }

        if(threshold >0.0)
            //参考简书的内容
            cv::threshold(result,result,255*threshold,255,cv::THRESH_BINARY);
        return result;

    }
    cv::Mat find(const cv::Mat& image,float minValue,float maxValue, int* channels,int dim)
    {
        cv::Mat result;

        hranges[0] = minValue;
        hranges[1] = maxValue;

        for(int i =0;i<dim;i++)
            this->channels[i] = channels[i];

        if(isSparse)
        {
            cv::calcBackProject(&image,
                                1,
                                channels,
                                shistogram,
                                result,
                                ranges,
                                255.0
                        );
        }
        else
        {
            cv::calcBackProject(&image,
                                1,
                                channels,
                                histogram,
                                result,
                                ranges,
                                255.0);
        }

        if(threshold>0.0)
            cv::threshold(result,result,255*threshold,255,cv::THRESH_BINARY);

        return result;
    }


};



#endif
