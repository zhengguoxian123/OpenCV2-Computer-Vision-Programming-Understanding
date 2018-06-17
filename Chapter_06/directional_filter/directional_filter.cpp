//分块
//解析
#include<iostream>
#include<iomanip>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include "laplacianZC.hpp"

int main()
{
    cv::Mat image = cv::imread("../boldt.jpg",0);
    if(!image.data)
        return 0;

    cv::namedWindow("Original Image");
    cv::imshow("Original Image",image);

    //???
    cv::Mat sobelx;
    cv::Sobel(image,sobelx,CV_8U,1,0,3,0.4,128);

    cv::namedWindow("sobelx image");
    cv::imshow("sobelx image",sobelx);

    cv::Mat sobely;
    cv::Sobel(image,sobely,CV_8U,0,1,3,0.4,128);

    cv::namedWindow("sobely image");
    cv::imshow("sobely image",sobely);

    cv::Sobel(image,sobelx,CV_16S,1,0);
    cv::Sobel(image,sobely,CV_16S,0,1);

    cv::Mat sobel;

    sobel = abs(sobelx)+abs(sobely);

    double sobmin,sobmax;
    cv::minMaxLoc(sobel,&sobmin,&sobmax);
    std::cout<<"sobel value range"<<sobmin<<" "<<sobmax<<std::endl;

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            std::cout<<std::setw(5)<<static_cast<int>(sobel.at<short>(i+135,j+362))<<" ";
            std::cout<<std::endl;
        }
    }

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    cv::Mat sobelImage;
    sobel.convertTo(sobelImage,CV_8U,-255./sobmax,255);

    cv::namedWindow("Sobel Image");
    cv::imshow("Sobel Image",sobelImage);

    cv::Mat sobelThresholded;
    cv::threshold(sobelImage,sobelThresholded,255,255,cv::THRESH_BINARY);

    cv::namedWindow("Binary Sobel Image(low)");
    cv::imshow("Binary Sobel Image(low)",sobelThresholded);

    cv::threshold(sobelImage,sobelThresholded,190,255,cv::THRESH_BINARY);

    cv::namedWindow("Binary Sobel Image(high)");
    cv::imshow("Binary Sobel Image(high)",sobelThresholded);

    cv::Mat laplace;
    cv::Laplacian(image,laplace,CV_8U,1,1,128);

    cv::namedWindow("Lapacian Image");
    cv::imshow("Laplacian Image",laplace);

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
            std::cout<<std::setw(5)<<static_cast<int>(laplace.at<uchar>(i+135,j+362)-128)<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    cv::Laplacian(image,laplace,CV_8U,7,0.01,128);

    cv::namedWindow("Laplacian Image");
    cv::imshow("Laplacian Image",laplace);

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
            std::cout<<std::setw(5)<<static_cast<int>(laplace.at<uchar>(i+135,j+362))-128<<" ";
        std::cout<<std::endl;
    }

    cv::Mat window(image,cv::Rect(362,135,12,12));
    cv::namedWindow("Image Window");
    cv::imshow("Image Window",window);
    cv::imwrite("window.bmp",window);
    //................................................
    LaplacianZC laplacian;
    laplacian.setAperture(7);
    cv::Mat flap = laplacian.computeLaplacian(image);
    double lapmin,lapmax;
    cv::minMaxLoc(flap,&lapmin,&lapmax);

    std::cout<<"Laplacian value range=["<<lapmin<<" , "<<lapmax<<"]\n";

    laplace = laplacian.getLaplacianImage();

    cv::namedWindow("Laplacian Image(7x7)");
    cv::imshow("Laplacian Image(7x7)",laplace);

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
            std::cout<<std::setw(5)<<static_cast<int>(flap.at<float>(i+135,j+365)/100)<<" ";
        std::cout<<std::endl;
    }

    std::cout<<std::endl;

    cv::Mat zeros;
    zeros = laplacian.getZeroCrossings(lapmax);
    cv::namedWindow("Zero-crossings");
    cv::imshow("Zero-crossing",zeros);

    zeros = laplacian.getZeroCrossings();
    zeros = laplacian.getZeroCrossingsWithSobel(50);

    cv::namedWindow("Zero-crossings(2)");
    cv::imshow("Zero-crossings(2)",zeros);

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
            std::cout<<std::setw(2)<<static_cast<int>(zeros.at<uchar>(i+135,j+362))<<" ";
        std::cout<<std::endl;
    }

    cv::rectangle(image,cv::Point(362,135),cv::Point(347,147),cv::Scalar(255,255,255));
    cv::namedWindow("Original Image with window");
    cv::imshow("Original Image with window",image);

    cv::waitKey();
    return 0;






}
