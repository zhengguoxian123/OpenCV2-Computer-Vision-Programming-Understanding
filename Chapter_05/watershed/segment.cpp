//分水岭算法
//前景物体是什么 运动的物体
//C.copyTo(A,B) 是什么？C被B覆盖得到A
//
//
//
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "watershedSegmentation.hpp"

int main()
{
    cv::Mat image = cv::imread("../group.jpg");
    if(!image.data)
        return 0;
    cv::namedWindow("Original Image");
    cv::imshow("Original Image",image);

    cv::Mat binary;
    binary = cv::imread("../binary.bmp",0);
    cv::namedWindow("Binary Image");
    cv::imshow("Binary Image",binary);

    cv::Mat fg;
    //腐蚀图像6次
    //目的：移除噪点和微小物体
    cv::erode(binary,fg,cv::Mat(),cv::Point(-1,-1),6);
    cv::namedWindow("Foreground Image");
    cv::imshow("Foreground Image",fg);

    cv::Mat bg;
    //膨胀图像6次
    //???识别不包含物体的像素
    cv::dilate(binary,bg,cv::Mat(),cv::Point(-1,-1),6);
    //阈值化以得到2值图像  128是灰色的
    cv::threshold(bg,bg,1,128,cv::THRESH_BINARY_INV);
    cv::namedWindow("Background Image");
    cv::imshow("Background Image",bg);

    //膨胀图像和腐蚀图像进行加起来
    //创建标记图形
    cv::Mat markers(binary.size(),CV_8U,cv::Scalar(0));
    markers= fg+bg;
    cv::namedWindow("Markers");
    cv::imshow("Markers",markers);
//======================================================

    //创建分水岭分割对象
    WatershedSegmenter segmenter;
    //设置标记并进行处理
    segmenter.setMarkers(markers);
    segmenter.process(image);

    cv::namedWindow("Segmentation");
    //???
    cv::imshow("Segmentation",segmenter.getSegmentation());
    //边界图像
    cv::namedWindow("watersheds");
    cv::imshow("watersheds",segmenter.getWatersheds());

//==========================================================


    image = cv::imread("../tower.jpg");
    //类比上面的例子
    cv::Mat imageMask(image.size(),CV_8U,cv::Scalar(0));
    //
//    cv::rectangle(imageMask,cv::Point(5,5),cv::Point(image.cols-5,image.rows-5),cv::Scalar(255),3);
//    cv::rectangle(imageMask,cv::Point(image.cols/2-10,image.rows/2-10),cv::Point(image.cols/2+10,image.rows/2+10),cv::Scalar(1),10);
//    //设置标记并进行处理
    segmenter.setMarkers(imageMask);
    segmenter.process(image);
    //和上面重复了
    //白色和黑色方框
    cv::rectangle(image,cv::Point(5,5),cv::Point(image.cols-5,image.rows-5),cv::Scalar(255,255,255),3);
    cv::rectangle(image,cv::Point(image.cols/2-10,image.rows/2-10),cv::Point(image.cols/2+10,image.rows/2+10),cv::Scalar(1,1,1),10);
    cv::namedWindow("Image with marker");
    cv::imshow("Image with marker",image);

    //????都是白的，能看出什么？？？？
    //???
    cv::namedWindow("watersheds of foreground object");
    cv::imshow("watersheds of foreground object",segmenter.getWatersheds());
//---------------------------------------------------
    //
    image = cv::imread("../tower.jpg");
    //设置前景物体的包围盒
    cv::Rect rectangle(50,70,image.cols-150,image.rows-180);
    cv::Mat result;//分割的图像，4种可能的值
    cv::Mat bgModel,fgModel;//模型，供内部使用

    //grabcut分割 提取前景物体，和分水岭算法不一样
    //得到什么？提取前景物体
    cv::grabCut(image,
                result,
                rectangle,
                bgModel,fgModel,
                1,
                cv::GC_INIT_WITH_RECT);//使用矩形进行初始化
    //得到可能为前景的像素
    //cv::GC_PR_FGD  可能属于前景的像素
    cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
    //图像大小，格式，白的颜色
    cv::Mat foreground(image.size(),CV_8UC3,cv::Scalar(255,255,255));
    //见简书笔记第二条
    image.copyTo(foreground,result);

    cv::rectangle(image,rectangle,cv::Scalar(255,255,255),1);
    cv::namedWindow("Image");
    cv::imshow("Image",image);
    //为什么啥也没有呢 有啊 前景物体，你看错了
    cv::namedWindow("Segmented Image");
    cv::imshow("Segemented Image",foreground);
//-------------------------------------------------
    //类比上面的例子
    image = cv::imread("../group.jpg");

    cv::Rect rectangle2(10,100,380,180);
    cv::Mat bkgModel,fgrModel;
    cv::grabCut(image,
                result,
                rectangle2,bkgModel,fgrModel,5,cv::GC_INIT_WITH_RECT
                );
    //得到可能为前景的像素
    //cv::GC_PR_FGD  可能属于前景的像素
    cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
    //实行按位与
    //result = result&1;

    foreground.create(image.size(),CV_8UC3);
    //前景设置为白色
    foreground.setTo(cv::Scalar(255,255,255));
    // 见简书笔记第二条
    image.copyTo(foreground,result);

    cv::rectangle (image,rectangle2,cv::Scalar(255,255,255),1);
    cv::namedWindow("Image 2");
    cv::imshow("Image 2",image);
    cv::namedWindow("Foreground objects");
    cv::imshow("Foreground objects",foreground);
    cv::waitKey();
    return 0;
}
