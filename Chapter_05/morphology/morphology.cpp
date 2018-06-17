//对图像进行腐蚀和膨胀
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

int main()
{
    cv::Mat image = cv::imread("../binary.bmp");
    if(!image.data)
        return 0;
    cv::namedWindow("Image");
    cv::imshow("Image",image);
    //腐蚀图像
    cv::Mat eroded;
    cv::erode(image,eroded,cv::Mat());

    cv::namedWindow("Eroded Image");
    cv::imshow("Eroded Image",eroded);
    //膨胀图像
    cv::Mat dilated;
    cv::dilate(image,dilated,cv::Mat());

    cv::namedWindow("Dilated Image");
    cv::imshow("Dilated Image",dilated);
    //腐蚀效果更具有毁灭性
    cv::Mat element(7,7,CV_8U,cv::Scalar(1));
    cv::erode(image,eroded,element);

    cv::namedWindow("Eroded Image(7x7)");
    cv::imshow("Eroded Image(7x7)",eroded);
    //腐蚀图像3次
    cv::erode(image,eroded,cv::Mat(),cv::Point(-1,-1),3);

    cv::namedWindow("Eroded Image(3 times)");
    cv::imshow("Eroded Image(3 times)",eroded);

    cv::Mat element5(5,5,CV_8U,cv::Scalar(1));
    cv::Mat closed;
    //对图像进行闭运算
    cv::morphologyEx(image,closed,cv::MORPH_CLOSE,element5);

    cv::namedWindow("CLosed Image");
    cv::imshow("Closed Image",closed);

    //应用形态学开运算
    cv::Mat opened;
    cv::morphologyEx(image,opened,cv::MORPH_OPEN,element5);

    cv::namedWindow("Opened Image");
    cv::imshow("Opened Image",opened);

    //???运用图像学进行闭开运算
    cv::morphologyEx(image,image,cv::MORPH_CLOSE,element5);
    cv::morphologyEx(image,image,cv::MORPH_OPEN,element5);

    cv::namedWindow("Closed and Opened Image");
    cv::imshow("Closed and Opened Image",image);
    cv::imwrite("binaryGroup.bmp",image);

    //运用图像学进行开闭运算
    image = cv::imread("../binary.bmp");
    cv::morphologyEx(image,image,cv::MORPH_OPEN,element5);
    cv::morphologyEx(image,image,cv::MORPH_CLOSE,element5);

    cv::namedWindow("Opened and Closed Image");
    cv::imshow("Opened and Closed Image",image);

    cv::waitKey();
    return 0;

}
