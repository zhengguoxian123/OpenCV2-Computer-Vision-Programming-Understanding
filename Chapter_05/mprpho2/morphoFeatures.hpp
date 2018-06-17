#ifndef MORPHOFEATURES_HPP
#define MORPHOFEATURES_HPP

class MorphoFeatures
{
private:
    int threshold;
    cv::Mat cross;
    cv::Mat diamond;
    cv::Mat square;
    cv::Mat x;

    void applyThreshold(cv::Mat& result)
    {
        if(threshold>0)
            cv::threshold(result,result,threshold,255,cv::THRESH_BINARY_INV);

    }
public:
    MorphoFeatures() :threshold(-1),cross(5,5,CV_8U,cv::Scalar(0)),
                                                        diamond(5,5,CV_8U,cv::Scalar(1)),
                                                        square(5,5,CV_8U,cv::Scalar(1)),
                                                        x(5,5,CV_8U,cv::Scalar(0))
    {
        //创建十字形元素
        for(int i=0;i<5;i++)
        {
            cross.at<uchar>(2,i) =1;
            cross.at<uchar>(i,2) =1;
        }
        //创建菱形元素
        diamond.at<uchar>(0,0) =0;
        diamond.at<uchar>(0,1) =0;
        diamond.at<uchar>(1,0) =0;
        diamond.at<uchar>(4,4) =0;
        diamond.at<uchar>(3,4) =0;
        diamond.at<uchar>(4,3) =0;
        diamond.at<uchar>(4,0) =0;
        diamond.at<uchar>(4,1) =0;
        diamond.at<uchar>(3,0) =0;
        diamond.at<uchar>(0,4) =0;
        diamond.at<uchar>(0,3) =0;
        diamond.at<uchar>(1,4) =0;

        //创建X形元素
        for(int i =0;i<5;i++)
        {
            x.at<uchar>(i,i) =1;
            x.at<uchar>(4-i,i) =1;
        }
    }

    void setThreshold(int t)
    {
        threshold =t;
    }

    int getThreshold() const
    {
        return threshold;
    }

    cv::Mat getEdges(const cv::Mat& image)
    {
        cv::Mat result;
        //得到梯度图
        cv::morphologyEx(image,result,cv::MORPH_GRADIENT,cv::Mat());
        //阈值化得到2值图像
        applyThreshold(result);

        return result;
    }

    cv::Mat getCorners(const cv::Mat& image)
    {
        cv::Mat result;
        //十字形膨胀
        cv::dilate(image,result,cross);
        //菱形腐蚀
        cv::erode(result,result,diamond);

        cv::Mat result2;
        //X形膨胀
        cv::dilate(image,result2,x);
        //方形腐蚀
        cv::erode(result2,result2,square);
        //通过对两张图片做差值得到角点图像
        cv::absdiff(result2,result,result);
        //阈值化以得到2值图像
        applyThreshold(result);

        return result;
    }

    void drawOnImage(const cv::Mat& binary,cv::Mat& image)
    {
        cv::Mat_<uchar>::const_iterator it = binary.begin<uchar>();
        cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();
        //遍历每个像素
        for(int i=0;it!=itend;++it,++i)
        {
            if(!*it)
                cv::circle(image,cv::Point(i%image.step,i/image.step),5,cv::Scalar(255,0,0));
        }
    }

};
#endif
