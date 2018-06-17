#ifndef LINEFINDER_H
#define LINEFINDER_H

#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#define PI 3.1415926

class LineFinder
{
private:

    cv::Mat img;
    std::vector<cv::Vec4i> lines;
    //累加器的分辨率
    double deltaRho;
    double deltaTheta;
    //直线被接受时所需要的最小投票数
    int minVote;
    //直线的最小长度
    double minLength;
    //沿着直线方向的最大缺口
    double maxGap;

public:

    LineFinder():deltaRho(1),deltaTheta(PI/180),minVote(10),minLength(0.),maxGap(0.){}

    void setAccResolution(double dRho,double dTheta)
    {
        deltaRho = dRho;
        deltaTheta = dTheta;
    }

    void setMinVote(int minv)
    {
        minVote = minv;
    }

    void setLineLengthAndGap(double length,double gap)
    {
        minLength = length;
        maxGap = gap;
    }

    std::vector<cv::Vec4i> findLines(cv::Mat& binary)
    {
        lines.clear();
        //霍夫概率变换
        cv::HoughLinesP(binary,lines,deltaRho,deltaTheta,minVote,minLength,maxGap);

        return lines;
    }

    void drawDetectedLines(cv::Mat& image, cv::Scalar color = cv::Scalar(255,255,255))
    {
        std::vector<cv::Vec4i>::const_iterator it2 = lines.begin();

        while(it2 != lines.end())
        {
            cv::Point pt1((*it2)[0],(*it2)[1]);
            cv::Point pt2((*it2)[2],(*it2)[3]);
            cv::line(image,pt1,pt2,color);

            ++it2;
        }

    }

    std::vector<cv::Vec4i> removeLinesOfInconsistentOrientations(const cv::Mat& orientations,double percentage,double delta)
    {
        std::vector<cv::Vec4i>::iterator it = lines.begin();

        while(it != lines.end())
        {
            int x1 = (*it)[0];
            int y1 = (*it)[1];
            int x2 = (*it)[2];
            int y2 = (*it)[3];

            double ori1 = atan2(static_cast<double>(y1-y2),static_cast<double>(x1-x2))+PI/2;
            if(ori1 >PI) ori1 = ori1 -2*PI;

            double ori2 = atan2(static_cast<double>(y2-y1),static_cast<double>(x2-x1))+PI/2;
            if(ori2>PI) ori2 = ori2-2*PI;

            cv::LineIterator lit(orientations,cv::Point(x1,y1),cv::Point(x2,y2));

            int i,count =0;

            for(i=0,count = 0;i<lit.count;i++,++lit)
            {
                float ori = *(reinterpret_cast<float *>(*lit));

                if(std::min(fabs(ori-ori1),fabs(ori-ori2))<delta)
                    count++;

            }

            double consistency = count/static_cast<double>(i);
            if(consistency <percentage)
            {
                (*it)[0]= (*it)[1] = (*it)[2] =(*it)[3] =0;
            }

            ++it;
        }

        return lines;
    }

};



#endif
