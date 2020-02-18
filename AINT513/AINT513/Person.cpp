#include "Person.h"
#include "cmath"


using namespace  std;

Person::Person()
{
    //amount = 0;
}

Person::Person(int xPos, int yPos, int width, int height, float maxMove, float minMove, float moveTime)
{
    _xPos = xPos;
    _yPos = yPos;
    _width = width;
    _height = height;

    _maxMove = maxMove;
    _minMove = minMove;
    _moveTime = moveTime;

    _lastMoveTime = 0;
    _alert = 0;
    _alarmReported = false;
    _remove = false;

    amount += 1;
    amount = amount > 100 ? 0 : amount;

    _id = amount;
}



Person::~Person()
= default;


bool Person::SamePerson(int xPos, int yPos, int width, int height) const
{
    if (((_maxMove + xPos ) > _xPos) &&  ((xPos - _maxMove) < _xPos))
    {
        return ((yPos + _maxMove) > _yPos) && yPos - _maxMove < _yPos;
    }
    else
    {
        return false;
    }
}


void Person::EditPerson(int xPos, int yPos, int width, int height)
{
    if (std::abs(xPos - _xPos) > _minMove || std::abs(yPos - _yPos) > _minMove || std::abs(width - _width) > _minMove || std::abs(height - _height) > _minMove)
    {
        _lastMoveTime = 0;
        _xPos = xPos;
        _yPos = yPos;
        _width = width;
        _height = height;

        _lastSeenTime = 0;
    }   
}


void Person::TickTimer()
{
    _lastMoveTime += 1;
    _lastSeenTime += 1;

    if (_lastMoveTime > _moveTime)
    {
        _alert = 1;
    }
    if (_lastSeenTime > 4)
    {
        _remove = true;
    }
}


int Person::GetAlert() const
{
    return _alert;
}


bool Person::GetRemove() const
{
    return _remove;
}

int Person::GetId() const
{
    return _id;
}

int Person::GetLastMoveTime() const
{
    return _lastMoveTime;
}
