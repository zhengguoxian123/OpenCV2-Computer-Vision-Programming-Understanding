//2.7
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

int main()
{
    cv::Mat image1;
    cv::Mat image2;

    image1= cv::imread("../boldt.jpg");
    image2= cv::imread("../rain.jpg");

    if(!image1.data)
        return 0;
    if(!image2.data)
        return 0;

//    cv::namedWindow("Image 1");
//    cv::imshow("Image 1",image1);

//    cv::namedWindow("Image 2");
//    cv::imshow("Image 2",image2);

//    cv::Mat result;

//    //0.0 is ?
//    cv::addWeighted(image1,0.7,image2,0.9,0.0,result);
//    cv::namedWindow("result");
//    cv::imshow("result",result);

    //运行命令行有点问题
//    result=0.7*image1+0.9*image2;
//    cv::namedWindow("result with operator");
//    cv::imshow("result with operators",result);

//    //??0  grayscale image
//    image2= cv::imread("../rain.jpg",0);
//    //create vector of 3 images
//    std::vector<cv::Mat> planes;
//    //split 1-3 channel image into 1-3 channel images
//    //split  分离
//    //将3个通道的数据分成单通道数据
//    cv::split(image1,planes);
//    //?? add to blue channel
//    //在一个通道上增加数据
//    planes[0]+=image2;
//    //重新将3个单通道的图像合并成一个3通道的图像
//    cv::merge(planes,result);
//    cv::namedWindow("Result on blue channel");
//    cv::imshow("Result on blue channel",result);


    cv::Mat image = cv::imread("../boldt.jpg");
    cv::Mat logo = cv::imread("../logo.bmp");

    cv::Mat imageROI;
//    //很小的图片
//    imageROI = image(cv::Rect(385,270,logo.cols,logo.rows));

//    cv::addWeighted(imageROI,1.0,logo,0.3,0.,imageROI);

//    cv::namedWindow("with logo");
//    cv::imshow("with logo",imageROI);

//    image = cv::imread("../boldt.jpg");
//    logo= cv::imread("../logo.bmp");

//    //很小的图片
//    imageROI = image(cv::Rect(385,270,logo.cols,logo.rows));
//    cv::namedWindow("imageROI");
//    cv::imshow("imageROI",imageROI);

//    //加载掩模（必须是灰度图）
//    cv::Mat mask = cv::imread("logo.bmp",0);
//    //见简书
//    logo.copyTo(imageROI,mask);

//    cv::namedWindow("with logo 2");
//    cv::imshow("with logo 2",image);

    //grayscale image
    logo = cv::imread("../logo.bmp",0);
    image1 =cv::imread("../boldt.jpg");

    //split 1 3-channel image into 3 1-channel image
    std::vector<cv::Mat> channels;
    cv::split(image1,channels);
    //vector中的第一个元素
    imageROI =channels.at(1);

    cv::addWeighted(imageROI(cv::Rect(385,270,logo.cols,logo.rows)),1.0,logo,0.5,0.,imageROI(cv::Rect(385,270,logo.cols,logo.rows)));
    //操作imageROI 为什么会影响channels呢
    //改变某个通道的值
    channels.at(1) =imageROI;

    cv::merge(channels,image1);

    cv::namedWindow("with logo 3");
    cv::imshow("with logo 3",image1);


    cv::waitKey(500000000);



}
