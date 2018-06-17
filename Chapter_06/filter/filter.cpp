//分块
//解析
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

int main()
{
    cv::Mat image = cv::imread("../boldt.jpg",0);
    if(!image.data)
        return 0;

    cv::namedWindow("Original Image");
    cv::imshow("Original Image",image);

    cv::Mat result;
    //??高斯模糊，后面几个参数是啥？？
    cv::GaussianBlur(image,result,cv::Size(5,5),1.5);

    cv::namedWindow("Gaussian filtered Image");
    cv::imshow("Gaussian filtered Image",result);

    cv::medianBlur(image,result,5);

    cv::namedWindow("Median filtered S&P Image");
    cv::imshow("Median filtered S&P Image",result);
//..................................................
    //???P128
    cv::Mat gauss = cv::getGaussianKernel(9,1.5,CV_32F);

    cv::Mat_<float>::const_iterator it = gauss.begin<float>();
    cv::Mat_<float>::const_iterator itend = gauss.end<float>();
    std::cout<<" [";
    for(;it!=itend;it++)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<" ]"<<std::endl;

    gauss = cv::getGaussianKernel(9,0.5,CV_32F);

    it = gauss.begin<float>();
    itend = gauss.end<float>();
    std::cout<<" [";
    for(;it!=itend;it++)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<" ]"<<std::endl;

    //???P128
    gauss = cv::getGaussianKernel(9,2.5,CV_32F);

    it = gauss.begin<float>();
    itend = gauss.end<float>();
    std::cout<<" [";
    for(;it!=itend;it++)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<"]"<<std::endl;

    cv::Mat kx,ky;
    //???
    cv::getDerivKernels(kx,ky,2,2,7,true);

    cv::Mat_<float>::const_iterator kit =kx.begin<float>();
    cv::Mat_<float>::const_iterator kitend = kx.end<float>();
    std::cout<<" [";
    for(;kit!=kitend;kit++)
    {
        std::cout<<*kit<<" ";
    }
    std::cout<<" ]"<<std::endl;

//............................................
    //低通滤波器
    cv::blur(image,result,cv::Size(5,5));

    cv::namedWindow("Mean filtered Image");
    cv::imshow("Mean filtered Image",result);
//............................................
//    image = cv::imread("../salt.bmp",0);
//    if(!image.data)
//        return 0;

//    cv::namedWindow("S&P Image");
//    cv::imshow("S&P Image",image);

//    cv::blur(image,result,cv::Size(5,5));

//    cv::namedWindow("Mean filtered S&P Image");
//    cv::imshow("Mean filter S&P Image",result);

//    cv::medianBlur(image,result,5);

//    cv::namedWindow("Median filtered S&P Image");
//    cv::imshow("Median filtered S&P Image",result);
//...........................................................
    //???糟糕的做法
    image = cv::imread("../boldt.jpg",0);
    //图像尺寸减半
    cv::Mat reduced(image.rows/2,image.cols/2,CV_8U);

    for(int i=0;i<reduced.rows;i++)
    {
        for(int j = 0;j<reduced.cols;j++)
        {
            reduced.at<uchar>(i,j)= image.at<uchar>(i*2,j*2);
        }
    }

    cv::namedWindow("Badly reduced Image");
    cv::imshow("Badly reduced Image",reduced);

    cv::waitKey();

    return 0;


}
