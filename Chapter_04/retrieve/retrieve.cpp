//比较完直方图，然后呢
#include<iostream>
using namespace std;

#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include "imageComparator.hpp"

int main()
{
    cv::Mat image = cv::imread("../waves.jpg");
    if(!image.data)
        return 0;
    cv::namedWindow("Query Image");
    cv::imshow("Query Image", image);

    ImageComparator c;
    c.setReferenceImage(image);

    cv::Mat input = cv::imread("../dog.jpg");
    cout<<"waves vs dog: "<<c.compare(input)<<endl;

    input = cv::imread("../bear.jpg");
    cout<<"waves vs bear "<<c.compare(input)<<endl;

    input = cv::imread("../beach.jpg");
    cout<<"waves vs beach"<<c.compare(input)<<endl;

    input = cv::imread("../polar.jpg");
    cout<<"waves vs polar"<<c.compare(input)<<endl;

    input = cv::imread("../moose.jpg");
    cout<<"waves vs moose: "<<c.compare(input)<<endl;

    input = cv::imread("../lake.jpg");
    cout<<"waves vs lake: "<<c.compare(input)<<endl;

    input = cv::imread("../fundy.jpg");
    cout<<"waves vs fundy: "<<c.compare(input)<<endl;

    cv::waitKey();

    return 0;
}
