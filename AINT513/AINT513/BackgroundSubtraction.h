#pragma once
#include "Settings.h"

//OpenCV Headers
#include "opencv2/imgproc.hpp"
#include <opencv2/video/background_segm.hpp>

class BackgroundSubtraction
{
private:
    Settings _settings;
    int _selectedMethod;

    cv::Ptr<cv::BackgroundSubtractorMOG2> _fgbgMaskMOG2;
    cv::Mat _foreGroundMask;

    cv::Mat _backGroundFrame;
    int _frameCount;



public:
    BackgroundSubtraction();
    ~BackgroundSubtraction();

    void UpdateBackGround(cv::Mat frame);

    cv::Mat CompareBackGround(cv::Mat frame);

    void DeleteBackGround();

    void ResetBackGround(cv::Mat frame);
};

