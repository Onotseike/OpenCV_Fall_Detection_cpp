#include "Settings.h"



Settings::Settings()
{
    _isDebug = true;
    _isGaussian = true;
    _isBW = false;
    _isResized = false;
    _isMOG2Shadows = true;

    _mog2LearningRate = 0.001;

    _source = 0;//1; 
    _bckGndSubMethod = 0;
    _mog2Shadow = 0;
    _mog2History = 100;
    _mog2Threshold = 20;
    _minArea = 150 * 150;
    _threseholdLimit = 50;
    _dilationPixels = 30;
    _gaussainPixels = 31;
    _maxMove = 150;
    _minMove = 3;
    _moveTime = 50;
    
    

}


Settings::~Settings()
= default;

int
Settings::GetBckGndSubMethod() const
{
    return  _bckGndSubMethod;
}

void Settings::SetBckGndSubMethod(int value)
{
    _bckGndSubMethod = value;
}

int
Settings::GetHistory()
{
    return  _mog2History;
}

int
Settings::GetThreshold() const
{
    return  _mog2Threshold;
}

int
Settings::GetShadow() const
{
    return _mog2Shadow;
}

int
Settings::GetThresholdLimit() const
{
    return _threseholdLimit;
}

int
Settings::GetSource() const
{
    return _source;
}

float
Settings::GetMaxMove() const
{
    return _maxMove;
}

float
Settings::GetMinMove() const
{
    return _minMove;
}

float
Settings::GetMoveTime() const
{
    return _moveTime;
}

double
Settings::GetLearningRate() const
{
    return _mog2LearningRate;
}

bool
Settings::IsShadow() const
{
    return _isMOG2Shadows;
}

bool Settings::IsDebug() const
{
    return _isDebug;
}

void Settings::SetDebug(bool i)
{
    _isDebug = i;
}

void Settings::SetShadow(bool b)
{
    _isMOG2Shadows = b;
}
