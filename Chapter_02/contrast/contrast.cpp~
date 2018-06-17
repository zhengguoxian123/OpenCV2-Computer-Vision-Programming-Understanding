//contrast
//对每个像素进行处理

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//
void sharpen(const cv::Mat& image,cv::Mat& result)
{
    result.create(image.size(),image.type());
    //表示问题，看for循环中的就行
    //row 行
    for(int j=1;j<image.rows-1;j++)
    {
        const uchar* previous =image.ptr<const uchar>(j-1);
        const uchar* current =image.ptr<const uchar>(j);
        const uchar* next =image.ptr<const uchar>(j+1);

        uchar* output = result.ptr<uchar>(j);

        for(int i=0;i<image.cols-1;i++)
        {
            //cv::saturate_cast<uchar>() 防止数据溢出
            //两行表达的是同一个意思，但是算法是什么?
//            *output++=cv::saturate_cast<uchar>(5*current[i]-current[i-1]-current[i+1]-previous[i]-next[i]);
            output[i]=cv::saturate_cast<uchar>(5*current[i]-current[i-1]-current[i+1]-previous[i]-next[i]);
        }
    }
    //第0行，第0列，最后一行，最后一列都设置成0
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}

void sharpen2(const cv::Mat& image, cv::Mat& result)
{
    result.create(image.size(),image.type());

    //??step1  data
    //step1 目的：只是为了给出下一行的地址,那为甚不用size呢????可以啊。
    int step = image.step1(0);

    const uchar* previous =image.data;
    const uchar* current = image.data+step;
    const uchar* next = image.data+2*step;

    uchar* output = result.data+step;

    for(int j =1;j<image.rows-1;j++)
    {
        //??
        for(int i=1;i<image.cols-1;i++)
        {
            output[i]=cv::saturate_cast<uchar>(5*current[i]-current[i-1]-current[i+1]-previous[i]-next[i]);
        }

        previous+=step;
        current+=step;
        next+=step;
        output+=step;
    }

    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}

void sharpen2D(const cv::Mat& image,cv::Mat& result)
{
    //
    cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
    kernel.at<float>(1,1)=5.0;
    kernel.at<float>(0,1)=-1.0;
    kernel.at<float>(2,1)=-1.0;
    kernel.at<float>(1,0)=-1.0;
    kernel.at<float>(1,2)=-1.0;

    cv::filter2D(image,result,image.depth(),kernel);
}

//????
void sharpen3(const cv::Mat& image,cv::Mat& result)
{
    //???为什么要家上image.step这么大的数呢？用image.size[1]就行。用image.step容易误解。
    cv::Mat_<uchar>::const_iterator it =image.begin<uchar>()+image.size[1];
    cv::Mat_<uchar>::const_iterator itend = image.end<uchar>()-image.size[1];
    cv::Mat_<uchar>::const_iterator itup = image.begin<uchar>();
    cv::Mat_<uchar>::const_iterator itdown =image.begin<uchar>()+2*image.size[1];

    result.create(image.size(),image.type());

    cv::Mat_<uchar>::iterator itout =result.begin<uchar>()+result.step;

    for(;it!=itend;++it,++itup,++itdown)
    {
        //???it-1??迭代器本身就是这样的。是一个元素一个元素地进行操作的
        *itout=cv::saturate_cast<uchar>(*it*5-*(it-1)-*(it+1)-*itup-*itdown);
    }
}

int main()
{
    //??
    cv::Mat image = cv::imread("../image.jpg",0);

    if(!image.data)
        return 0;
    std::cout<<"!image.data: "<<(!image.data)<<std::endl;
    std::cout<<"*(image.data): "<<*(image.data)<<std::endl;

    //不能这么写
    //std::cout<<"*(image.data+image.step1): "<<*(image.data+image.step1)<<std::endl;
    std::cout<<"image.channels(): "<<image.channels()<<std::endl;
    std::cout<<"image.depth(): "<<image.depth()<<std::endl;
    std::cout<<"image.size(): "<<image.size()<<std::endl;
    std::cout<<"image.size().width: "<<image.size().width<<std::endl;
    std::cout<<"image.size().height: "<<image.size().height<<std::endl;
    std::cout<<"image.cols: "<<image.cols<<std::endl;
    std::cout<<"image.rows: "<<image.rows<<std::endl;
    std::cout<<"image.size[0]: "<<image.size[0]<<std::endl;
    std::cout<<"image.size[1]: "<<image.size[1]<<std::endl;
    std::cout<<std::endl;
    std::cout<<"image.step: "<<image.step<<std::endl;
    std::cout<<"image.step[0]: "<<image.step[0]<<std::endl;
    std::cout<<"image.step[1]: "<<image.step[1]<<std::endl;
    std::cout<<std::endl;
    std::cout<<"image.step1(0): "<<image.step1(0)<<std::endl;
    std::cout<<"image.step1(1): "<<image.step1(1)<<std::endl;
    std::cout<<std::endl;
    std::cout<<"image.elemSize(): "<<image.elemSize()<<std::endl;
    std::cout<<"image.elemSize1(): "<<image.elemSize1()<<std::endl;
    std::cout<<std::endl;
    std::cout<<"image.type(): "<<image.type()<<std::endl;

    cv::Mat result;

    result.create(image.size(),image.type());
    //1
    double time =static_cast<double>(cv::getTickCount());
    sharpen(image,result);

    time = (static_cast<double>(cv::getTickCount()-time))/cv::getTickFrequency();

    std::cout<<"time: "<<time<<std::endl;

    cv::namedWindow("Image");
    cv::imshow("Image",result);
    //2
    time =static_cast<double>(cv::getTickCount());
    sharpen2(image,result);

    time = (static_cast<double>(cv::getTickCount()-time))/cv::getTickFrequency();

    std::cout<<"time: "<<time<<std::endl;

    cv::namedWindow("Image2");
    cv::imshow("Image2",result);
    //3
    time =static_cast<double>(cv::getTickCount());
    sharpen3(image,result);

    time = (static_cast<double>(cv::getTickCount()-time))/cv::getTickFrequency();

    std::cout<<"time: "<<time<<std::endl;

    cv::namedWindow("Image3");
    cv::imshow("Image3",result);
    //4
    time= static_cast<double>(cv::getTickCount());
    sharpen2D(image,result);
    time=(static_cast<double>(cv::getTickCount()-time))/cv::getTickFrequency();
    std::cout<<"time="<<time<<std::endl;
    cv::namedWindow("Image4");
    cv::imshow("Image4",result);

    cv::waitKey(5000);
}


