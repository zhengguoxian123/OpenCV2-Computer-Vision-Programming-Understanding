//程序的功能：检测图像的通道数，并随机取3000个像素点进行处理，设置成白色
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

void salt(cv::Mat& image,int n)
{
    int i,j;
    for(int k=0;k<n;k++)
    {
        i=rand()%image.cols;
        //row 行
        j=rand()%image.rows;

        if(image.channels() ==1)
        {
            image.at<uchar>(j,i) =255;
        }
        else if(image.channels() ==3)
        {
            image.at<cv::Vec3b>(j,i)[0] =255;
            image.at<cv::Vec3b>(j,i)[1] =255;
            image.at<cv::Vec3b>(j,i)[2] =255;
        }
    }
}

int main()
{
    //这个屏蔽也没事
    //srand(cv::getTickCount());


    cv::Mat image= cv::imread("boldt.jpg",0);

    std::cout<<image.channels()<<std::endl;

    salt(image,3000);

    cv::namedWindow("Image");

    cv::imshow("Image",image);

    cv::imwrite("salted.bmp",image);

    cv::waitKey(5000);

    return 0;
}
