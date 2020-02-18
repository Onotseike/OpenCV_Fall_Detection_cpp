#pragma once
#include "Settings.h"
#include <opencv2/videoio.hpp>
#include "BackgroundSubtraction.h"
#include "Persons.h"
#include <chrono>

using namespace  std;
using namespace cv;
using namespace chrono;

class VideoService
{
private:
    
    VideoCapture _camera;
    BackgroundSubtraction _bckGndSub;
    Persons _persons;
    time_point<steady_clock> _startTime;
    int _errorCount;
    std::list<std::string> _alertLogList;
    int _frameCount;
    Mat _frame;
    Mat _thresholdFrame;
    string _detectStatus;
public:
    void SettingsPanel(int sliderValue);
    void SetVariables();
	void SetTrackVariables();
    VideoService();
    ~VideoService();
    Settings _settings;
    void NextFrame();
    void ShowFrame() const;
    void DestroyAll();
    bool TestDestroy();
    void ResetBackGroundFrame();
    void TestBackGroundFrame();
    void UpdateBackGround();
    void TestSettings();

    void ConvertFrame();
    void CompareFrame();
    void NewLightSettings();

    void ToggleBckSubMethod();
    void ToggleDebug();
    void SetMOG2Shadows();
};

