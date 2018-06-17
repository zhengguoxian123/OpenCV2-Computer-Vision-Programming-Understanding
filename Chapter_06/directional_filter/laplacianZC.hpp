#ifndef LAPLACIANZC_H
#define LAPLACIANZC_H

#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class LaplacianZC
{
private:
    cv::Mat img;
    cv::Mat laplace;

    int aperture;

public:
    LaplacianZC():aperture(3) {}

    void setAperture(int a)
    {
        aperture =a;
    }

    int getAperture() const
    {
        return aperture;
    }

    cv::Mat computeLaplacian(const cv::Mat& image)
    {
        cv::Laplacian(image,laplace,CV_32F,aperture);

        img = image.clone();

        return laplace;
    }

    cv::Mat getLaplacianImage(double scale=-1.0)
    {
        if(scale<0)
        {
            double lapmin,lapmax;
            cv::minMaxLoc(laplace,&lapmin,&lapmax);

            scale =127/std::max(-lapmin,lapmax);
        }
        cv::Mat laplaceImage;
        laplace.convertTo(laplaceImage,CV_8U,scale,128);

        return laplaceImage;
    }

    cv::Mat getZeroCrossings(float threshold=1.0)
    {
        cv::Mat_<float>::const_iterator it = laplace.begin<float>()+laplace.step1();
        cv::Mat_<float>::const_iterator itend = laplace.end<float>();
        cv::Mat_<float>::const_iterator itup = laplace.begin<float>();

        cv::Mat binary(laplace.size(),CV_8U,cv::Scalar(255));
        cv::Mat_<uchar>::iterator itout = binary.begin<uchar>()+binary.step1();

        threshold *=-1.0;
        for(;it!=itend;++it,++itup,++itout)
        {
            if(*it * *(it-1)<threshold)
                *itout = 0;
            else if(*it * *itup <threshold)
                *itout =0;
        }
        return binary;
    }

    cv::Mat getZeroCrossingsWithSobel(float threshold)
    {
        cv::Mat sx;
        cv::Sobel(img,sx,CV_32F,1,0,1);
        cv::Mat sy;
        cv::Sobel(img,sy,CV_32F,0,1,1);

        cv::Mat_<float>::const_iterator it = laplace.begin<float>()+laplace.step1();
        cv::Mat_<float>::const_iterator itend = laplace.end<float>();
        cv::Mat_<float>::const_iterator itup = laplace.begin<float>();
        cv::Mat_<float>::const_iterator itx = laplace.begin<float>()+sx.step1();
        cv::Mat_<float>::const_iterator ity = laplace.begin<float>()+sy.step1();

        cv::Mat binary(laplace.size(),CV_8U,cv::Scalar(255));
        cv::Mat_<uchar>::iterator itout = binary.begin<uchar>()+binary.step1();

        for(;it!=itend;++it,++itup,++itout,++itx,++ity)
        {
            if(*it * *(it-1)<0.0 && fabs(*ity)>threshold)
                *itout=0;
            else if(*it * *itup<0.0 && fabs(*ity)>threshold)
                *itout =0;
        }

        return binary;
    }

};
#endif
