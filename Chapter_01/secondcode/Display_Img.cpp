//实现什么功能：显示图像和翻转
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

//function that creates and returns an image
cv::Mat function()
{
    cv::Mat ima(240,320,CV_8U,cv::Scalar(100));

    return ima;
}

int main()
{
    cv::Mat image;
    std::cout<<"size: "<<image.size().height<<" , "<<image.size().width<<std::endl;
    image = cv::imread("img.png");
    if(!image.data)
    {
        return 0;
    }

    std::cout<<"size(atter reading):"<<image.size().height<<" , "<<image.size().width<<std::endl;

    cv::namedWindow("Original Image");
    cv::imshow("Original Image",image);

    cv::Mat result;
    //翻转
    //1:水平翻转
    //0:垂直翻转

    cv::flip(image,result,1);

    cv::namedWindow("Output Image");
    cv::imshow("Output Image",result);
    //cv::waitKey(0);//无限等待
    //cv::waitKey(5000);//等待5s
    cv::waitKey(5000);

    cv::imwrite("output.bmp",result);

    cv::Mat image2,image3;
    image2 =result;
    result.copyTo(image3);

    cv::flip(result,result,0);

    cv::namedWindow("image 2");
    cv::imshow("image 2",image2);

    cv::namedWindow("image 3");
    cv::imshow("image 3",image3);

    cv::Mat gray =function();
    cv::namedWindow("Gray Image");
    cv::imshow("Gray Image",gray);
    std::cout<<gray.size().height<<"///"<<gray.size().width<<std::endl;
    cv::waitKey(0);

    return 1;
}
