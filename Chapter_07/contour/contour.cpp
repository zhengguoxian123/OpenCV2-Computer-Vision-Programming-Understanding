//anaylze
//
#include<iostream>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include "linefinder.hpp"
#include "edgedetector.hpp"

#define PI 3.1415926

int main()
{
    //用的是灰度
    cv::Mat image = cv::imread("../road.jpg",0);
    if(!image.data)
        return 0;
    cv::namedWindow("Original Image");
    cv::imshow("Original Image",image);

    EdgeDetector ed;
    ed.computeSobel(image);

    //这个是干啥用的？
    cv::namedWindow("Sobel(orientation)");
    cv::imshow("Sobel(orientation)",ed.getSobelOrientationImage());
    cv::imwrite("ori.bmp",ed.getSobelOrientationImage());

//    //???
    cv::namedWindow("Sobel(low threshold)");
    cv::imshow("Sobel(low threshold)",ed.getBinaryMap(125));

    cv::namedWindow("Sobel(high threshold)");
    cv::imshow("Sobel(high threshold)",ed.getBinaryMap(350));

    //应用Canny算法
    cv::Mat contours;

    cv::Canny(image,    //灰度图
              contours, //输出轮廓
              125,      //低阈值
              350);     //高阈值

    cv::Mat contoursInv;
    //反转后的图像
    cv::threshold(contours,contoursInv,128,255,cv::THRESH_BINARY_INV);

    cv::namedWindow("Canny Contours");
    cv::imshow("Canny Contours",contoursInv);


    cv::Mat test(200,200,CV_8U,cv::Scalar(0));
    cv::line(test,cv::Point(100,0),cv::Point(200,200),cv::Scalar(255));
    cv::line(test,cv::Point(0,50),cv::Point(200,200),cv::Scalar(255));
    cv::line(test,cv::Point(0,200),cv::Point(200,0),cv::Scalar(255));
    //和上面竟然重复
//    cv::line(test,cv::Point(200,0),cv::Point(0,200),cv::Scalar(255));
    cv::line(test,cv::Point(100,0),cv::Point(100,200),cv::Scalar(255));
    cv::line(test,cv::Point(0,100),cv::Point(200,100),cv::Scalar(255));

    cv::namedWindow("Test Image");
    cv::imshow("Test Image",test);
    cv::imwrite("test.bmp",test);

//.................................................
    //霍夫变换检测直线,而不是线段
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(contours,lines,
                   1,PI/180,   //以PI/180为间隔搜索所有可能的角度
                   60);        //
    //
    cv::Mat result(contours.rows,contours.cols,CV_8U,cv::Scalar(255));
    image.copyTo(result);

    std::cout<<"Lines detected: "<<lines.size() <<std::endl;

    std::vector<cv::Vec2f>::const_iterator it = lines.begin();
    while(it != lines.end())
    {
        float rho = (*it)[0]; //第一个参数为距离
        float theta = (*it)[1];//第二个参数为角度

        if(theta <PI/4. || theta > 3.*PI/4.)//
        {
            cv::Point pt1(rho/cos(theta),0);

            cv::Point pt2(rho-result.rows*sin(theta)/cos(theta),result.rows);

            cv::line(result,pt1,pt2,cv::Scalar(255),1);

        }
        else
        {
            cv::Point pt1(0,rho/sin(theta));

            cv::Point pt2(result.cols,(rho-result.cols*cos(theta))/sin(theta));

            cv::line(result,pt1,pt2,cv::Scalar(255),1);
        }

        std::cout<<"line ("<<rho<<" , "<<theta <<"\n";
        ++it;
    }

    cv::namedWindow("Detected Lines with Hough");
    cv::imshow("Detected Lines with Hough",result);
//.....................................................
    LineFinder ld;
    //设置概率Hough参数
    ld.setLineLengthAndGap(100,20);
    ld.setMinVote(80);
    //检测并绘制直线
    std::vector<cv::Vec4i> li = ld.findLines(contours);
    ld.drawDetectedLines(image);
    cv::namedWindow("Detected Lines with HoughP");
    cv::imshow("Deteted Lines with HoughP",image);

    std::vector<cv::Vec4i>::const_iterator it2 = li.begin();
    while (it2!= li.end())
    {
        std::cout<<"("<<(*it)[0]<<","<<(*it)[1]<<")-("
                   <<(*it2)[2]<<","<<(*it2)[3]<<")"<<std::endl;
        ++it2;

    }

    //在图像上画一条线
    image = cv::imread("../road.jpg",0);
    //选择line0
    int n= 0;
    cv::line(image,cv::Point(li[n][0],li[n][1]),cv::Point(li[n][2],li[n][3]),cv::Scalar(255),5);
    cv::namedWindow("One line of the Image");
    cv::imshow("One line of the Image",image);


    cv::Mat oneline(image.size(),CV_8U,cv::Scalar(0));
    cv::line(oneline,cv::Point(li[n][0],li[n][1]),cv::Point(li[n][2],li[n][3]),cv::Scalar(255),5);
    //????为什么要这么做？
    //cv::bitwise_and(contours,oneline,oneline);
    cv::Mat onelineInv;
    cv::threshold(oneline,onelineInv,128,255,cv::THRESH_BINARY_INV);
    cv::namedWindow("One line");
    cv::imshow("One line",onelineInv);

    //遍历得到所有点的位置
    std::vector<cv::Point> points;

    for(int y =0;y <oneline.rows;y++)
    {
        uchar* rowPtr = oneline.ptr<uchar>(y);
        for(int x= 0;x<oneline.cols;x++)
        {
            if(rowPtr[x])
            {
                points.push_back(cv::Point(x,y));
            }

        }
    }

    cv::Vec4f line;
    //找到最适合的线
    cv::fitLine(cv::Mat(points),line,
                CV_DIST_L2,//距离类型
                0,//L2距离不使用该参数
                0.01,0.01);//精确值

    std::cout<<"line: ("<<line[0]<<","<<line[1]<<")("<<line[2]<<","<<line[3]<<")/n";
    int x0 = line[2];//直线上的点
    int y0 = line[3];
    int x1 = x0-200*line[0];//使用单元向量
    int y1 = y0-200*line[1];//添加长度为200的向量

    image = cv::imread("../road.jpg",0);
    cv::line(image,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar(0),3);
    cv::namedWindow("Estimated line");
    cv::imshow("Estimated line",image);

    ld.removeLinesOfInconsistentOrientations(ed.getOrientation(),0.4,0.1);

    image = cv::imread("../road.jpg",0);
    ld.drawDetectedLines(image);
    cv::namedWindow("Detected Lines(2)");
    cv::imshow("Detected Lines(2)",image);

    //创建霍夫累加器
    cv::Mat acc(200,180,CV_8U,cv::Scalar(0));

    //选择点
    int x=50,y=30;
    //遍历所有角度
    for(int i = 0;i<180;i++)
    {
        double theta = i*PI/180;
        double rho = x*cos(theta)+y*sin(theta);
        int j = static_cast<int>(rho+100.5);

        std::cout<<i<<" ,"<<j<<std::endl;

        acc.at<uchar>(j,i)++;
    }

    cv::imwrite("hough1.bmp",acc*100);

    x=30,y=10;

    for(int i =0;i<180;i++)
    {
        double theta= i*PI/180;
        double rho = x*cos(theta)+y*sin(theta);
        int j = static_cast<int>(rho+100.5);

        acc.at<uchar>(j,i)++;

    }

    cv::namedWindow("Hough Accumulator");
    cv::imshow("Hough Accumulator",acc*100);
    cv::imwrite("hough2.bmp",acc*100);

    image = cv::imread("../chariot.jpg",0);
    cv::GaussianBlur(image,image,cv::Size(5,5),1.5);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(image,circles,CV_HOUGH_GRADIENT,
                     2,//累加器的分辨率（图像的尺寸／2）
                     50,//两个圆之间的最小距离
                     200,//Canny 高阈值
                     100,//最小投票数
                     25,100);//极小极大半径
    std::cout<<"Circles: "<<circles.size()<<std::endl;
    image = cv::imread("../chariot.jpg",0);
    std::vector<cv::Vec3f>::const_iterator itc = circles.begin();
    while(itc!= circles.end())
    {
        cv::circle(image,cv::Point((*itc)[0],(*itc)[1]),//圆心
                (*itc)[2],//半径
                cv::Scalar(255),//颜色
                2);//厚度
        ++itc;


    }

    cv::namedWindow("Detected Circles");
    cv::imshow("Detected Circles",image);

    cv::waitKey();
    return 0;
}
