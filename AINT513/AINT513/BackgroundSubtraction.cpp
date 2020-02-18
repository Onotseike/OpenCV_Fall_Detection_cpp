#include "BackgroundSubtraction.h"

//OpenCV Headers
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>



BackgroundSubtraction::BackgroundSubtraction()
{
    _settings = Settings();
    _selectedMethod = _settings.GetBckGndSubMethod();
    
    if (_selectedMethod == 0)
    {
        _fgbgMaskMOG2 = cv::createBackgroundSubtractorMOG2(_settings.GetHistory(), _settings.GetThreshold(), _settings.GetShadow());

        _foreGroundMask = cv::Mat();
    }

    if (_selectedMethod == 1)
    {
        _backGroundFrame = cv::Mat();
        _frameCount = 1;
    }

}

BackgroundSubtraction::~BackgroundSubtraction()
= default;

void
BackgroundSubtraction::UpdateBackGround(cv::Mat frame)
{
    if (_selectedMethod == 0)
    {
        _fgbgMaskMOG2->apply(frame, _foreGroundMask, _settings.GetLearningRate());
    }

    if (_selectedMethod == 1)
    {
        double alpha = 1.0 / double(_frameCount);
        if (_backGroundFrame.empty())
        {
            _backGroundFrame = frame;            
        }
        cv::addWeighted(frame, alpha, _backGroundFrame, 1.0 - alpha, 0,_backGroundFrame);
        _frameCount += 1;

    }
}

cv::Mat
BackgroundSubtraction::CompareBackGround(cv::Mat frame)
{
    if (_selectedMethod == 0)
    {
        return _foreGroundMask;
    }

    if (_selectedMethod == 1)
    {
        cv::Mat frameDelta;
        absdiff(_backGroundFrame, frame, frameDelta);
        threshold(frameDelta, _foreGroundMask, _settings.GetThresholdLimit(), 255.00, CV_THRESH_BINARY);
        return _foreGroundMask;
    }
    return {};
}

void
BackgroundSubtraction::DeleteBackGround()
{
    if (_selectedMethod == 0)
    {
        _foreGroundMask = cv::Mat();
    }

    if (_selectedMethod == 1)
    {
        _backGroundFrame = cv::Mat();
    }
}

void
BackgroundSubtraction::ResetBackGround(cv::Mat frame)
{
    if (_selectedMethod == 0)
    {
        if (_foreGroundMask.empty())
        {
            _fgbgMaskMOG2->apply(frame, _foreGroundMask,_settings.GetLearningRate());
        }
    }

    if (_selectedMethod == 1)
    {
        if (_backGroundFrame.empty())
        {
            UpdateBackGround(frame);
            _frameCount = 1;
        }
    }
}
