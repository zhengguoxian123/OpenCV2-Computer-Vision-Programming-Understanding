#include<iostream>
#include<iomanip>

#include<string>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

#include "CameraCalibrator.hpp"

int main()
{
    cv::namedWindow("Image");
    cv::Mat image;
    std::vector<std::string> filelist;

    for(int i=1;i<=20;i++)
    {
        std::stringstream str;
        //setfill('0') :use '0' to fill space
        str<<"../chessboards/chessboard"<<std::setw(2)<<std::setfill('0')<<i<<".jpg";
        std::cout<<str.str() <<std::endl;
        filelist.push_back(str.str());
        image =cv::imread(str.str(),0);
        //imshow 之前检测一下
        if(!image.data)
            return 0;

        cv::imshow("Image",image);
        cv::waitKey(100);
    }


    CameraCalibrator cameraCalibrator;
    //棋盘中角点数目
    cv::Size boardSize(6,4);

    cameraCalibrator.addChessboardPoints(filelist,boardSize);

    cameraCalibrator.calibrate(image.size());

    image =cv::imread(filelist[6]);

    cv::Mat uImage = cameraCalibrator.remap(image);

    cv::Mat cameraMatrix = cameraCalibrator.getCameraMatrix();
    std::cout<<"Camera intricsic: "<<cameraMatrix.rows<<"x"<<cameraMatrix.cols<<std::endl;

    std::cout<<cameraMatrix.at<double>(0,0)<<" "<<cameraMatrix.at<double>(0,1)<<" "<<cameraMatrix.at<double>(0,2)<<std::endl;
    std::cout<<cameraMatrix.at<double>(1,0)<<" "<<cameraMatrix.at<double>(1,1)<<" "<<cameraMatrix.at<double>(1,2)<<std::endl;
    std::cout<<cameraMatrix.at<double>(2,0)<<" "<<cameraMatrix.at<double>(2,1)<<" "<<cameraMatrix.at<double>(2,2)<<std::endl;

    imshow("Original Image",image);
    imshow("Undistorted Image",uImage);

    cv::waitKey();
    return 0;

}
