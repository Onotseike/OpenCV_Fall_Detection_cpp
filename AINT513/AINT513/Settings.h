#pragma once
#include <string>
using namespace  std;

class Settings
{
private:
    int _source, _bckGndSubMethod;
    
    double _mog2LearningRate;// = 0.001;
    
    std::string _location, _phone;
    
public:
    int _minArea ,_threseholdLimit, _dilationPixels, _gaussainPixels;
    float _maxMove, _minMove, _moveTime;
    bool _isGaussian, _isBW, _isResized, _isDebug, _isMOG2Shadows;
	int _mog2Shadow, _mog2History, _mog2Threshold;

    Settings();
    ~Settings();
    
    int GetBckGndSubMethod() const;
    void SetBckGndSubMethod(int value);
    int GetHistory();
    int GetThreshold() const;
    int GetShadow() const;
    int GetThresholdLimit() const;
    int GetSource() const;
    
    float GetMaxMove() const;
    float GetMinMove() const;
    float GetMoveTime() const;

    double GetLearningRate() const;

    bool IsShadow() const;
    bool IsDebug() const;
    void SetDebug(bool i);
    void SetShadow(bool b);
};

