#include "VideoService.h"
#include <chrono>
#include <opencv2/highgui.hpp>
#include <cmath>
#include <thread>

using namespace std;
using namespace  cv;
using namespace chrono;



void VideoService::ToggleBckSubMethod()
{
    if (getTrackbarPos("Background Subtraction Method", "Settings Tab") == 0)
    {
        _settings.SetBckGndSubMethod(0);
        //Disable MOG Trackbars
    }
    else
    {
        _settings.SetBckGndSubMethod(1);
        //Enable MOG Trackbars
    }
}

void VideoService::ToggleDebug()
{
    if (getTrackbarPos("Debugging", "Settings Tab") == 0)
    {
        _settings.SetDebug(false);
        //Disable MOG Trackbars
    }
    else
    {
        _settings.SetDebug(true);
        //Enable MOG Trackbars
    }
}

void VideoService::SetMOG2Shadows()
{
    if (getTrackbarPos("MOG2 Shadow", "Settings Tab") == 0)
    {
        _settings.SetShadow(false);
        //Disable MOG Trackbars
    }
    else
    {
        _settings.SetShadow(true);
        //Enable MOG Trackbars
    }
}



void NothingCallBack(int, void*)
{
    /*ToggleBckSubMethod();
    ToggleDebug();
    SetMOG2Shadows();*/
}

void VideoService::SettingsPanel(int sliderValue)
{
    //int a = 0;
    
    namedWindow("Settings Tab", WINDOW_NORMAL);

    createTrackbar("Background Subtraction Method", "Settings Tab", &sliderValue, 1, NothingCallBack);
    createTrackbar("Debugging", "Settings Tab", &sliderValue, 1, NothingCallBack);
    createTrackbar("MOG2 Shadow", "Settings Tab", &sliderValue, 1, NothingCallBack);

    createTrackbar("Minimum Area", "Settings Tab", &sliderValue, 200, NothingCallBack);
    createTrackbar("Minimum Movement", "Settings Tab", &sliderValue, 20, NothingCallBack);
    createTrackbar("Maximum Movement", "Settings Tab", &sliderValue, 100, NothingCallBack);
    createTrackbar("Movement Time", "Settings Tab", &sliderValue, 50, NothingCallBack);
    createTrackbar("ThreshHold", "Settings Tab", &sliderValue, 75, NothingCallBack);
    createTrackbar("Dilation Pixels", "Settings Tab", &sliderValue, 35, NothingCallBack);
   // createTrackbar("Gaussain Pixels", "Settings Tab", &sliderValue, 36, NothingCallBack);
    createTrackbar("MOG2 Threshold", "Settings Tab", &sliderValue, 40, NothingCallBack);
    createTrackbar("MOG2 History", "Settings Tab", &sliderValue, 100, NothingCallBack);





    NothingCallBack(sliderValue, 0);
    /*ToggleBckSubMethod();
    ToggleDebug();
    SetMOG2Shadows();*/


    //Variate Settings To See effects


}
void VideoService::SetTrackVariables()
{
    setTrackbarPos("Background Subtraction Method", "Settings Tab", _settings.GetBckGndSubMethod());
    if (_settings.IsDebug())
    {
        setTrackbarPos("Debugging", "Settings Tab", 1);
    }
    else
    {
        setTrackbarPos("Debugging", "Settings Tab", 0);
    }

    if (_settings.IsShadow())
    {
        setTrackbarPos("MOG2 Shadow", "Settings Tab", 1);
    }
    else
    {
        setTrackbarPos("MOG2 Shadow", "Settings Tab", 0);
    }


    setTrackbarPos("Minimum Area", "Settings Tab", sqrt(_settings._minArea));
    setTrackbarPos("Minimum Movement", "Settings Tab", _settings.GetMinMove());
    setTrackbarPos("Maximum Movement", "Settings Tab", _settings.GetMaxMove());
    setTrackbarPos("Movement Time", "Settings Tab", _settings.GetMoveTime());

    setTrackbarPos("ThreshHold", "Settings Tab", _settings.GetThresholdLimit());
    setTrackbarPos("Dilation Pixels", "Settings Tab", _settings._dilationPixels);
    //setTrackbarPos("Gaussian Pixels", "Settings Tab", _settings._gaussainPixels);

    setTrackbarPos("MOG2 Threshold", "Settings Tab", _settings.GetThreshold());
    setTrackbarPos("MOG2 History", "Settings Tab", _settings.GetHistory());

    ToggleBckSubMethod();

    
}

void VideoService::SetVariables()
{
	ToggleDebug();
	SetMOG2Shadows();
	ToggleBckSubMethod();
	_settings._minArea = getTrackbarPos("Minimum Area", "Settings Tab");
	_settings._minMove = getTrackbarPos("Minimum Movement", "Settings Tab");
	_settings._maxMove = getTrackbarPos("Maximum Movement", "Settings Tab");
	_settings._moveTime = getTrackbarPos("Movement Time", "Settings Tab");
	_settings._threseholdLimit = getTrackbarPos("ThreshHold", "Settings Tab");
	_settings._dilationPixels = getTrackbarPos("Dilation Pixels", "Settings Tab");
	//_settings._gaussainPixels = getTrackbarPos("Gaussian Pixels", "Settings Tab");
	_settings._mog2History = getTrackbarPos("MOG2 History", "Settings Tab");
	_settings._mog2Threshold = getTrackbarPos("MOG2 Threshold", "Settings Tab");
}


VideoService::VideoService()
{
    _settings = Settings();
    _camera = VideoCapture(_settings.GetSource());
    _bckGndSub = BackgroundSubtraction();
    _persons = Persons(_settings.GetMaxMove(), _settings.GetMinMove(), _settings.GetMoveTime());
    
    _startTime = high_resolution_clock::now();
    //WebService???

    _errorCount = 0;
    _alertLogList = {};
    _frameCount = 1;  
}


VideoService::~VideoService()
= default;

void VideoService::NextFrame()
{    
    //_camera.read(_frame);
    if(!_camera.read(_frame))
    {
        DestroyAll();
    }
    ConvertFrame();
}

void VideoService::ShowFrame() const
{
    int a = 0;
    if (_settings.IsDebug())
    {
        cv::imshow("Threshold", _thresholdFrame);
        
    }
	else
	{
		cv::destroyWindow("Threshold");
	}
    namedWindow("Feed", WINDOW_AUTOSIZE);
    imshow("Feed", _frame);

}

void
VideoService::DestroyAll()
{
    _camera.release();
    cv::destroyAllWindows();
}

bool
VideoService::TestDestroy()
{
    auto key = (char)waitKey(1);
    if (key == 'q' || key == 'Q')
    {
        DestroyAll();
        return true;
    }
    return  false;
}

void
VideoService::ResetBackGroundFrame()
{
    _camera.read(_frame);
    ConvertFrame();
    _bckGndSub.ResetBackGround(_frame);
    _persons = Persons(_settings.GetMaxMove(), _settings.GetMinMove(), _settings.GetMoveTime());
}

void VideoService::TestBackGroundFrame()
{
    auto key = (char)waitKey(1);
    if (key == 'n' || key == 'N')
    {
        _bckGndSub.DeleteBackGround();
    }
}

void
VideoService::UpdateBackGround()
{
    _bckGndSub.UpdateBackGround(_frame);
}

void
VideoService::TestSettings()
{
    auto key = (char)waitKey(1);

    switch (key)
    {
    case '0':
        _settings._minArea += 50;
        break;
    case '1':
        _settings._minArea -= 50;
        break;
    case '2':
        _settings._dilationPixels += 1;
        break;;
    case '3':
        _settings._dilationPixels -= 1;
        break;
    case '4':
        _settings._threseholdLimit += 1;
        break;
    case '5':
        _settings._threseholdLimit -= 1;
        break;
    case '6':
        _settings._maxMove += 1.0;
        break;
    case '7':
        _settings._maxMove -= 1.0;
        break;
    case '8':
        _settings._minMove += 1.0;
        break;
    case '9':
        _settings._minMove -= 1.0;
        break;
    case 'g':
    case 'G':
        if (_settings._isGaussian)
        {
            _settings._isGaussian = false;
        }
        else
        {
            _settings._isGaussian = true;
        }
        ResetBackGroundFrame();
        break;
    case '+':
        _settings._moveTime += 1;
        break;
    case  '-':
        _settings._moveTime -= 1;
        break;
    default:
        break;
    }

}

void
VideoService::ConvertFrame()
{
    if (_settings._isResized)
    {
        const auto height =  (750.0 / _frame.size().width) * _frame.size().height;


        const auto dim = Size(800, int(height));
        
        resize(_frame, _frame, dim, INTER_AREA);
    }

    if (_settings._isBW)
    {
        cvtColor(_frame, _frame, COLOR_BGR2GRAY);
    }

    if (_settings._isGaussian)
    {
        GaussianBlur(_frame, _frame, Size(_settings._gaussainPixels, _settings._gaussainPixels), 0);
    }
}

void VideoService::CompareFrame()
{
    _thresholdFrame = _bckGndSub.CompareBackGround(_frame);

    dilate(_thresholdFrame, _thresholdFrame, Mat(), Point(-1, -1), _settings._dilationPixels);

    vector<vector<Point>> contours;
    findContours(_thresholdFrame, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    _persons.TickTimer();
    
    _detectStatus = "Idle";

    for (vector<Point> contour : contours)
    {
        if (contourArea(contour) < _settings._minArea)
        {
            continue;
        }
        Rect rect = boundingRect(contour);
        
       /* auto familiar = _persons.FamiliarPerson(rect.x, rect.y, rect.width, rect.height);
        if (familiar)
        {
            _detectStatus = "Idel Mode";
        }*/
        Person newPerson = _persons.AddPerson(rect.x, rect.y, rect.width, rect.height);
        
        auto color = Scalar(0, 255, 0);
        //cvtColor(_frame, _frame, CV_GRAY2BGR);
        if (newPerson.GetAlert())
        {
            color = Scalar(0, 0, 255);
            line(_frame, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height), color, 2);
            line(_frame, Point(rect.x + rect.width, rect.y), Point(rect.x, rect.y + rect.height), color, 2);
            _detectStatus = "Alarm NOT MOVING";

            if (!newPerson._alarmReported)
            {
                //Web Service
                newPerson._alarmReported = true;
            }
        }
        else
        {
            _detectStatus = "Idle Mode";
        }
        //cvtColor(_frame, _frame, CV_GRAY2BGR);
        rectangle(_frame, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height), color, 2);


        const auto contourAreaStr = std::to_string(contourArea(contour));
        const auto personId = "Person ID: " + std::to_string(newPerson.GetId()) + " Last Moved: " + std::to_string(newPerson.GetLastMoveTime());

        putText(_frame, contourAreaStr, Point(rect.x, rect.y + rect.height + 20), FONT_HERSHEY_COMPLEX_SMALL, 0.7, color, 1);
        putText(_frame, personId, Point(rect.x, rect.y + 20), FONT_HERSHEY_COMPLEX_SMALL, 0.8,color,1);

        
         

    }

    if (_settings.IsDebug())
    {
        const auto endTime = high_resolution_clock::now();
        duration<double> durationSpent = endTime - _startTime;
        //const auto secsSpent = chrono::duration_cast<double>(durationSpent);
        const auto durationCount = durationSpent.count();
        const auto framesPerSecond = round(1.0/ durationCount);

        _startTime = high_resolution_clock::now();

        const auto status = "STATUS: " + _detectStatus;
        const auto fps = "FPS: " + std::to_string(framesPerSecond);

        putText(_frame, status, Point(10, 470), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 127, 255), 1);
        putText(_frame, fps, Point(400, 470), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 128, 255), 1);
    }
}

void VideoService::NewLightSettings()
{
    _errorCount += 1;
    if (_errorCount > 10)
    {
        this_thread::sleep_for(seconds(3));
        ResetBackGroundFrame();
        _errorCount = 0;
    }
}





