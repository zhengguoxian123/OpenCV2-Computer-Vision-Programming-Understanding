#ifndef VIDEOPROCESSOR_HPP
#define VIDEOPROCESSOR_HPP

#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>

class FrameProcessor
{
public:
    virtual void process(cv::Mat& input, cv::Mat& output)=0;
};

class VideoProcessor
{
private:
    cv::VideoCapture capture;

    void (*process)(cv::Mat&,cv::Mat&);

    FrameProcessor* frameProcessor;

    bool callIt;

    std::string windowNameInput;
    std::string windowNameOutput;

    int delay;

    long fnumber;

    long frameToStop;

    bool stop;

    std::vector<std::string> images;

    std::vector<std::string>::const_iterator itImg;

    cv::VideoWriter writer;

    std::string outputFile;

    int currentIndex;

    int digits;

    std::string extension;

    bool readNextFrame(cv::Mat& frame)
    {
        if(images.size() ==0)
            return capture.read(frame);
        else
        {
            if(itImg != images.end())
                frame = cv::imread(*itImg);
                itImg++;
                return frame.data != 0;

        }
    }

    void writeNextFrame(cv::Mat& frame)
    {
        if(extension.length())
        {
            std::stringstream ss;
            ss<<outputFile<<std::setfill('0')<<std::setw(digits)<<currentIndex++<<extension;
            cv::imwrite(ss.str(),frame);
        }
        else
        {
            writer.write(frame);
        }
    }

public:
    VideoProcessor():callIt(false),delay(-1),fnumber(0),stop(false),digits(0),frameToStop(-1),process(0),frameProcessor(0) {}

    bool setInput(std::string filename)
    {
        fnumber = 0;
        capture.release();
        images.clear();

        return capture.open(filename);
    }

    bool setInput(int id)
    {
        fnumber = 0;
        capture.release();
        images.clear();

        return capture.open(id);
    }

    bool setInput(const std::vector<std::string>& imgs)
    {
        fnumber =0;

        capture.release();

        images = imgs;

        itImg = images.begin();

        return true;
    }

    bool setOutput(const std::string& filename,int codec =0,double framerate = 0.0,bool isColor =true)
    {
        outputFile = filename;
        extension.clear();

        if(framerate ==0.0)
            framerate = getFrameRate();

        char c[4];

        if(codec == 0)
            codec = getCodec(c);

        return writer.open(outputFile,codec,framerate,getFrameSize(),isColor);
    }

    bool setOutput(const std::string& filename,const std::string& ext,int numberOfDigits=3,int startIndex = 0)
    {
        if(numberOfDigits<0)
            return false;

        outputFile = filename;

        extension = ext;

        digits = numberOfDigits;

        currentIndex = startIndex;

        return true;
    }

    void setFrameProcessor(void (*frameProcessingCallback)(cv::Mat& ,cv::Mat&))
    {
        frameProcessor = 0;
        process= frameProcessingCallback;
        callProcess();
    }

    void setFrameProcessor(FrameProcessor* frameProcessorPtr)
    {
        process = 0;
        frameProcessor = frameProcessorPtr;
        callProcess();
    }

    void stopAtFrameNo(long frame)
    {
        frameToStop = frame;
    }

    void callProcess()
    {
        callIt = true;
    }

    void dontCallProcess()
    {
        callIt = false;
    }

    void displayInput(std::string wn)
    {
        windowNameInput = wn;
        cv::namedWindow(windowNameInput);
    }

    void displayOutput(std::string wn)
    {
        windowNameOutput = wn;
        cv::namedWindow(windowNameOutput);
    }

    void dontDisplay()
    {
        cv::destroyWindow(windowNameInput);
        cv::destroyWindow(windowNameOutput);
        windowNameInput.clear();
        windowNameOutput.clear();
    }

    void setDelay(int d)
    {
        delay =d;
    }

    long getNumberOfProcessedFrames()
    {
        return fnumber;
    }

    cv::Size getFrameSize()
    {
        if(images.size() ==0)
        {
            int w = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
            int h = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));

            return cv::Size(w,h);
        }
        else
        {
            cv::Mat tmp = cv::imread(images[0]);
            if(!tmp.data) return cv::Size(0,0);
            else return tmp.size();
        }
    }

    long getFrameNumber()
    {
        if(images.size() ==0)
        {
            long f = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
            return f;
        }
        else
        {
            return static_cast<long>(itImg-images.begin());
        }

    }

    double getPositionMS()
    {
        if(images.size() !=0)
            return 0.0;

        double t = capture.get(CV_CAP_PROP_POS_MSEC);
        return t;
    }

    double getFrameRate()
    {
        if(images.size() != 0)
            return 0;
        double r = capture.get(CV_CAP_PROP_FPS);
        return r;

    }

    long getTotalFrameCount()
    {
        if(images.size() != 0)
            return images.size();
        long t = capture.get(CV_CAP_PROP_FRAME_COUNT);
        return t;
    }

    int getCodec(char codec[4])
    {
        if(images.size() !=0) return -1;
        union{
            int value;
            char codec[4];} returned;
        returned.value = static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));

        codec[0] = returned.codec[0];
        codec[1] = returned.codec[1];
        codec[2] = returned.codec[2];
        codec[3] = returned.codec[3];

        return returned.value;

    }

    bool setFrameNumber(long pos)
    {
        if(images.size() != 0)
        {
            itImg = images.begin() +pos;
            if(pos < images.size())
                return true;
            else
                return false;

        }
        else
        {
            return capture.set(CV_CAP_PROP_POS_FRAMES,pos);
        }
    }


    bool setPositionMS(double pos)
    {
        if(images.size() != 0)
            return false;
        else
            return capture.set(CV_CAP_PROP_POS_MSEC,pos);
    }

    bool setRelativePosition(double pos)
    {
        if(images.size() != 0)
        {
            long posI = static_cast<long>(pos*images.size()+0.5);
            itImg = images.begin() +posI;

            if(posI <images.size())
                return true;
            else
                return false;

        }
        else
        {
            return capture.set(CV_CAP_PROP_POS_AVI_RATIO,pos);
        }

    }

    void stopIt()
    {
        stop = true;
    }

    bool isStopped()
    {
        return stop;
    }

    bool isOpened()
    {
        return capture.isOpened()||!images.empty();
    }

    void run()
    {
        cv::Mat frame;

        cv::Mat output;

        if(!isOpened())
            return;
        stop = false;

        while(!isStopped())
        {
            if(!readNextFrame(frame))
                break;
            if(windowNameInput.length() != 0)
                cv::imshow(windowNameInput,frame);
            if(callIt)
            {
                if(process)
                    process(frame,output);
                else if(frameProcessor)
                    frameProcessor->process(frame,output);
                fnumber++;
            }
            else
            {
                output = frame;
            }

            if(outputFile.length() != 0)
                writeNextFrame(output);

            if(windowNameOutput.length() !=0)
                cv::imshow(windowNameOutput,output);

            if(delay>=0 && cv::waitKey(delay) >=0)
                stopIt();

            if(frameToStop >=0 && getFrameNumber() ==frameToStop)
                stopIt();
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            cv::waitKey(30);
        }
    }
};

#endif
