//降低颜色数量
//为什么颜色算法呈现的效果不一样呢
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

void colorReduce0(cv::Mat& image,int div = 64)
{
    //row 行
    int nl= image.rows;
    int nc= image.cols*image.channels();

    for(int j=0;j<nl;j++)
    {
        //得到第j行的首地址
        uchar* data=image.ptr<uchar>(j);
        //处理每一个像素
        for(int i=0;i<nc;i++)
        {
            data[i] = data[i]/div*div+div/2;
        }
    }
}

void colorReduce1(cv::Mat& image,int div=64)
{
    //number of lines
    int nl =image.rows;
    //total number of elements per line
    int nc =image.cols*image.channels();

    for(int j=0;j<nl;j++)
    {
        //uchar 整数范围在0到255
        uchar* data = image.ptr<uchar>(j);
        for(int i=0;i<nc;i++)
        {
            //process each pixel
            *data++=*data/div*div+div/2;
        }
    }
}

void colorReduce2(cv::Mat& image,int div =64)
{
    int nl = image.rows;
    int nc = image.cols*image.channels();

    for(int j=0;j<nl;j++)
    {
        uchar* data = image.ptr<uchar>(j);
        for(int i= 0;i<nc;i++)
        {
            int v = *data;
            //另一种颜色数目降低的方法，举个例子就行
            *data++=v-v%div+div/2;
        }
    }
}

void colorReduce3(cv::Mat& image,int div =64)
{
    int nl =image.rows;
    int nc =image.cols*image.channels();
    //static_cast  标准数据类型转换
    int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //???颜色缩减的另一种方式
    uchar mask =0xFF<<n;
    //
    for(int j=0;j<nl;j++)
    {
        uchar* data = image.ptr<uchar>(j);
        for(int i=0;i<nc;i++)
        {
            //+div是为了取颜色缩减数目每个范围对应的中间值
            *data++=*data&mask+div/2;
        }
    }
}

//这个怎么这么费时
void colorReduce4(cv::Mat& image,int div=64)
{
    int nl = image.rows;
    int nc = image.cols*image.channels();
    int n =  static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //???有效的宽度
    int step = image.step;
    //???
    uchar mask=0xFF<<n;
    //??
    uchar* data = image.data;
    //??
    for(int j=0;j<nl;j++)
    {
        for(int i=0;i<nc;i++)
        {
            *(data+i)=*data&mask+div/2;
        }
        data+=step;
    }

}

void colorReduce5(cv::Mat& image, int div = 64)
{
    int nl=image.rows;
    int nc=image.cols*image.channels();

    int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));
    uchar mask=0xFF<<n;
    for(int j =0;j<nl;j++)
    {
        uchar* data = image.ptr<uchar>(j);
        for(int i=0;i<nc;i++)
        {
            *data++=*data&mask+div/2;
        }
    }
}

void colorReduce6(cv::Mat& image,int div =64)
{
    int nl= image.rows;
    int nc =image.cols*image.channels();
    //判断图像是否在行尾扩大若干元素，如果没进行填补的话，那就是连续的
    if(image.isContinuous())
    {
        nc= nc*nl;
        nl =1;
    }

    int n =static_cast<int>(log(static_cast<double>(div))/log(2.0));

    uchar mask= 0xFF<<n;

    for(int j=0;j<nl;j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for(int i=0;i<nc;i++ )
        {
            *data++=*data&mask+div/2;
        }
    }
}

void colorReduce7(cv::Mat& image,int div =64)
{
    int nl = image.rows;
    int nc = image.cols;

    if(image.isContinuous())
    {
        nc = nc*nl;
        nl = 1;
    }

    int n =static_cast<int>(log(static_cast<double>(div))/log(2.0));

    uchar mask=0xFF<<n;

    for(int j=0;j<nl;j++)
    {
        uchar* data = image.ptr<uchar>(j);

        //???because nc is cols
        for(int i=0;i<nc;i++)
        {
            *data++=*data&mask +div/2;
            *data++=*data&mask +div/2;
            *data++=*data&mask +div/2;
        }
    }

}

void colorReduce8(cv::Mat& image,int div =64)
{
    //it 对应每个像素的地址
    cv::Mat_<cv::Vec3b>::iterator it =image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();

    for(;it!=itend;++it)
    {
        //一个像素有3个通道
        (*it)[0]=(*it)[0]/div*div+div/2;
        (*it)[1]=(*it)[1]/div*div+div/2;
        (*it)[2]=(*it)[2]/div*div+div/2;
    }
}

void colorReduce9(cv::Mat& image,int div=64)
{
    int n =static_cast<int>(log(static_cast<double>(div))/log(2.0));

    uchar mask=0xFF<<n;

    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend= image.end<cv::Vec3b>();

    for(;it!=itend;++it)
    {
        (*it)[0]=(*it)[0]/div*div+div/2;
        (*it)[1]=(*it)[1]/div*div+div/2;
        (*it)[2]=(*it)[2]/div*div+div/2;
    }
}

void colorReduce10(cv::Mat& image,int div=64)
{
    cv::Mat_<cv::Vec3b> cimage=image;
    cv::Mat_<cv::Vec3b>::iterator it= cimage.begin();
    cv::Mat_<cv::Vec3b>::iterator itend= cimage.end();

    for(;it!=itend;++it)
    {
        (*it)[0]=(*it)[0]/div*div+div/2;
        (*it)[1]=(*it)[1]/div*div+div/2;
        (*it)[2]=(*it)[2]/div*div+div/2;
    }
}

void colorReduce11(cv::Mat &image, int div=64)
{
    int nl = image.rows;
    int nc = image.cols;

    for(int j=0;j<nl;j++)
    {
        for(int i=0;i<nc;i++)
        {
            image.at<cv::Vec3b>(j,i)[0]=image.at<cv::Vec3b>(j,i)[0]/div*div+div/2;
            image.at<cv::Vec3b>(j,i)[1]=image.at<cv::Vec3b>(j,i)[1]/div*div+div/2;
            image.at<cv::Vec3b>(j,i)[2]=image.at<cv::Vec3b>(j,i)[2]/div*div+div/2;
        }
    }
}

void colorReduce12(const cv::Mat& image,cv::Mat& result,int div=64)
{
    int nl = image.rows;
    int nc = image.cols;

    result.create(image.rows,image.cols,image.type());

    nc = nc*nl;
    nl= 1;

    int n =static_cast<int>(log(static_cast<double>(div))/log(2.0));

    uchar mask= 0xFF<<n;

    for(int j=0;j<nl;j++)
    {
        uchar* data = result.ptr<uchar>(j);
        const uchar* idata= image.ptr<uchar>(j);

        for(int i=0;i<nc;i++)
        {
            *data++=(*idata++)&mask+div/2;
            *data++=(*idata++)&mask+div/2;
            *data++=(*idata++)&mask+div/2;
        }
    }
}
void colorReduce13(cv::Mat& image,int div =64)
{
    //
    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));

    uchar mask=0xFF<<n;
    //??cv::Scalar() usage Scalar有3个通道，做法还是和之前一样
    image =(image&cv::Scalar(mask,mask,mask))+cv::Scalar(div/2,div/2,div/2);
}


#define NTESTS 14
#define NITERATIONS 20

int main()
{
    int64 t[NTESTS],tinit;
    cv::Mat image1;
    cv::Mat image2;

    for(int i=0;i<NTESTS;i++)
        t[i]=0;

    int n = NITERATIONS;
    for(int k=0;k<n;k++)
    {
        std::cout<<k<<" of "<<n<<std::endl;

        image1 = cv::imread("../image.jpg");
        if(!image1.data)
            return 0;

        //getTickCount() 统计colorReduce()的时间
        tinit =cv::getTickCount();
        //colorReduce0到底做了什么
        colorReduce0(image1);
        t[0]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit =cv::getTickCount();
//        colorReduce1(image1);
//        t[1]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit = cv::getTickCount();
//        colorReduce2(image1);
//        t[2]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit = cv::getTickCount();
//        colorReduce3(image1);
//        t[3]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit = cv::getTickCount();
//        colorReduce4(image1);
//        t[4]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit =cv::getTickCount();
//        colorReduce5(image1);
//        t[5]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit= cv::getTickCount();
//        colorReduce6(image1);
//        t[6]+=cv::getTickCount()-tinit;


//        image1= cv::imread("../image.jpg");
//        tinit= cv::getTickCount();
//        colorReduce7(image1);
//        t[7]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit= cv::getTickCount();
//        colorReduce8(image1);
//        t[8]+=cv::getTickCount()-tinit;

        image1= cv::imread("../image.jpg");
        tinit= cv::getTickCount();
        colorReduce9(image1);
        t[9]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit= cv::getTickCount();
//        colorReduce10(image1);
//        t[10]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit= cv::getTickCount();
//        colorReduce11(image1);
//        t[11]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit= cv::getTickCount();
//        colorReduce12(image1,image2);
//        t[12]+=cv::getTickCount()-tinit;

//        image1= cv::imread("../image.jpg");
//        tinit= cv::getTickCount();
//        colorReduce13(image1);
//        t[13]+=cv::getTickCount()-tinit;


    }

    cv::namedWindow("Image Result");
    cv::imshow("Image Result",image1);
//    cv::namedWindow("Image Result");
//    cv::imshow("Image Result",image2);


    cv::waitKey(5000);

    //统计平均执行时间
    std::cout<<"//////////////////////////////"<<std::endl;
    //
//    std::cout<<1000.*t[0]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[1]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[2]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[3]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[4]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[5]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[6]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[7]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[8]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[9]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[10]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[11]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[12]/cv::getTickFrequency()/n<<"ms"<<std::endl;
//    std::cout<<1000.*t[13]/cv::getTickFrequency()/n<<"ms"<<std::endl;

}
