#include "CameraCalibrator.hpp"

int CameraCalibrator::addChessboardPoints(const std::vector<std::string>& filelist, cv::Size& boardSize)
{
    //输出图像角点的vector
    std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;

    for(int i=0;i<boardSize.height;i++)
    {
        for(int j =0;j<boardSize.width;j++)
        {
            objectCorners.push_back(cv::Point3f(i,j,0.0f));
        }
    }

    cv::Mat image;

    int successes = 0;

    for(int i=0;i<filelist.size();i++)
    {
        image = cv::imread(filelist[i],0);
	//获取棋盘的角点
        bool found = cv::findChessboardCorners(image,boardSize,imageCorners);
        //??? huan hang mei huan hao
        cv::cornerSubPix(image,imageCorners,cv::Size(5,5),cv::Size(-1,-1),cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,30,0.1));

        if(imageCorners.size() == boardSize.area())
        {
            addPoints(imageCorners,objectCorners);
            successes++;
        }
	//绘制角点
        cv::drawChessboardCorners(image,boardSize,imageCorners,found);//found 已经找到的角点
        if(!image.data)
            continue;
        cv::imshow("Corners on Chessboard",image);
        cv::waitKey(100);
    }

    return successes;
}

void CameraCalibrator::addPoints(const std::vector<cv::Point2f>& imageCorners,const std::vector<cv::Point3f>& objectCorners )
{
    imagePoints.push_back(imageCorners);
    objectPoints.push_back(objectCorners);
}


double CameraCalibrator::calibrate(cv::Size imageSize)
{
    mustInitUndistort = true;
    std::vector<cv::Mat> rvecs,tvecs;

    return calibrateCamera(objectPoints,imagePoints,imageSize,cameraMatrix,distCoeffs,rvecs,tvecs,flag);

}

cv::Mat CameraCalibrator::remap(const cv::Mat& image)
{
    cv::Mat undistorted;
    if(mustInitUndistort)
    {
        cv::initUndistortRectifyMap(cameraMatrix,distCoeffs,cv::Mat(),cv::Mat(),cv::Size(640,480),CV_32FC1,map1,map2);
        mustInitUndistort = false;
    }

    cv::remap(image,undistorted,map1,map2,cv::INTER_LINEAR);

    return undistorted;
}


//void CameraCalibrator::setCalibrationFlag(bool radial8CoffEnabled,bool tangentialParamEnabled)
//{
//    flag = 0;
//    if(!tangentialParamEnabled) flag+=CV_CALIB_ZERO_TANGENT_DIST;
//    if(radial8CoffEnabled) flag+=CV_CALIB_RATIONAL_MODEL;
//}
