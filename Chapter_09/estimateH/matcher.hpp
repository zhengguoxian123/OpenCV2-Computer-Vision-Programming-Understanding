#ifndef MATCHER_HPP
#define MATCHER_HPP

#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>




class RobustMatcher
{
private:
    cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> extractor;
    float ratio;
    bool refineF;
    double distance;
    double confidence;

public:
    RobustMatcher():ratio(0.65f),refineF(true),confidence(0.99),distance(3.0)
    {
        detector = new cv::SurfFeatureDetector();
        extractor = new cv::SurfDescriptorExtractor();
    }

    void setFeatureDetector(cv::Ptr<cv::FeatureDetector>& detect)
    {
        detector = detect;
    }

    void setDescriptorExtractor(cv::Ptr<cv::DescriptorExtractor>& desc)
    {
        extractor = desc;
    }

    void setMinDistanceToEpipolar(double d)
    {
        distance = d;
    }

    void setConfidenceLevel(double c)
    {
        confidence = c;
    }

    void setRatio(float r)
    {
        ratio =r;
    }

    void refineFundamental(bool flag)
    {
        refineF = flag;
    }

    int ratioTest(std::vector<std::vector<cv::DMatch> >& matches)
    {
        int removed = 0;

        for(std::vector<std::vector<cv::DMatch> >::iterator matchIterator = matches.begin();
            matchIterator != matches.end();++matchIterator)
        {
            if(matchIterator->size() >1)
            {
                if((*matchIterator)[0].distance/(*matchIterator)[1].distance >ratio)
                {
                    matchIterator->clear();
                    removed++;
                }
            }
            else
            {
                matchIterator->clear();
                removed++;
            }
        }
        return removed;
    }

    void symmetryTest(const std::vector<std::vector<cv::DMatch> >& matches1,const std::vector<std::vector<cv::DMatch> >& matches2,std::vector<cv::DMatch>& symMatches)
    {
        for(std::vector<std::vector<cv::DMatch> >::const_iterator matchIterator1 =matches1.begin();
            matchIterator1 != matches1.end();++matchIterator1)
        {
            if(matchIterator1->size() <2)
                continue;
            for(std::vector<std::vector<cv::DMatch> >::const_iterator matchIterator2 =matches2.begin();
                matchIterator2 != matches2.end();++matchIterator2)
            {
                if(matchIterator2->size() <2)
                    continue;
                if((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx && (*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx)
                {
                    symMatches.push_back(cv::DMatch((*matchIterator1)[0].queryIdx,(*matchIterator1)[0].trainIdx,(*matchIterator1)[0].distance));
                    break;
                }



            }
        }
    }

    cv::Mat ransacTest(const std::vector<cv::DMatch>& matches,const std::vector<cv::KeyPoint>& keypoints1,const std::vector<cv::KeyPoint>& keypoints2,std::vector<cv::DMatch>& outMatches)
    {
        std::vector<cv::Point2f> points1,points2;
//        for(std::vector<cv::DMatch>::const_iterator it = matches.begin();it != matches.end();++it)
//        {
//            float x = keypoints1[it->queryIdx].pt.x;
//            float y = keypoints1[it->queryIdx].pt.x;
//            points1.push_back(cv::Point2f(x,y));

//            x = keypoints2[it->trainIdx].pt.x;
//            y = keypoints2[it->trainIdx].pt.y;

//            points2.push_back(cv::Point2f(x,y));
//        }
        for(int i =0;i<(int)matches.size();i++)
        {
            points1.push_back(keypoints1[matches[i].queryIdx].pt);
            points2.push_back(keypoints2[matches[i].trainIdx].pt);
        }

        std::vector<uchar> inliers(points1.size(),0);
        cv::Mat fundamental;
        fundamental = cv::findFundamentalMat(points1,points2,
                                                     inliers,
                                                     CV_FM_RANSAC,
                                                     distance,
                                                     confidence);

        std::vector<uchar>::const_iterator itIn =inliers.begin();
        std::vector<cv::DMatch>::const_iterator itM = matches.begin();

        for(;itIn!= inliers.end();++itIn,++itM)
        {
            std::cout<<"*itIn"<<*itIn<<std::endl;
            if(*itIn)
            {
                outMatches.push_back(*itM);
            }
        }
        std::cout<<"Number of inliers(after cleaning):"<<inliers.size()<<std::endl;
        std::cout<<"Number of matched points(after cleaning):"<<outMatches.size()<<std::endl;

        if(refineF)
        {
            points1.clear();
            points2.clear();

            // modify
            for(int i =0;i<(int)outMatches.size();i++)
            {
                points1.push_back(keypoints1[outMatches[i].queryIdx].pt);
                points2.push_back(keypoints2[outMatches[i].trainIdx].pt);
            }
             //???????? yizhiyouwenti
            fundamental = cv::findFundamentalMat(cv::Mat(points1),cv::Mat(points2),CV_FM_8POINT);
        }

        return fundamental;
    }

    cv::Mat match(cv::Mat& image1,cv::Mat& image2,std::vector<cv::DMatch>& matches,std::vector<cv::KeyPoint>& keypoints1,std::vector<cv::KeyPoint>& keypoints2)
    {
        detector->detect(image1,keypoints1);
        detector->detect(image2,keypoints2);

        std::cout<<"Number of SURF points(1)"<<keypoints1.size()<<std::endl;
        std::cout<<"Number of SURF points(2)"<<keypoints2.size()<<std::endl;

        cv::Mat descriptors1,descriptors2;
        extractor->compute(image1,keypoints1,descriptors1);
        extractor->compute(image2,keypoints2,descriptors2);

        std::cout<<"descriptor matrix size"<<descriptors1.rows<<" by "<<descriptors2.cols<<std::endl;

        cv::BruteForceMatcher<cv::L2<float> > matcher;

        std::vector<std::vector<cv::DMatch> > matches1;
        matcher.knnMatch(descriptors1,descriptors2,matches1,2);

        std::vector<std::vector<cv::DMatch> > matches2;
        matcher.knnMatch(descriptors2,descriptors1,matches2,2);

        std::cout<<"Number of matched points 1->2"<<matches1.size()<<std::endl;
        std::cout<<"Number of matched points 2->1"<<matches2.size()<<std::endl;

        int removed = ratioTest(matches1);
        std::cout<<"Number of matched points 1->2(ratio test)"<<matches1.size()-removed<<std::endl;

        removed = ratioTest(matches2);
        std::cout<<"Number of matched points 2->1(ratio test)"<<matches2.size()-removed<<std::endl;

        std::vector<cv::DMatch> symMatches;
        symmetryTest(matches1,matches2,symMatches);

        std::cout<<"number of matched points(symmetry test)"<<symMatches.size()<<std::endl;
        cv::Mat fundamental;
        //???
        fundamental = ransacTest(symMatches,keypoints1,keypoints2,matches);

        return fundamental;
    }
};




#endif
