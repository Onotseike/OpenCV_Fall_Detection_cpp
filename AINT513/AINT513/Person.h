#pragma once
class Person
{
public:
    /**
     * \brief 
     */
    int amount = 0;
    bool _alarmReported;
    Person();
    Person(int xPos, int yPos, int width, int height, float maxMove, float minMove, float moveTime);
    ~Person();

    bool SamePerson(int xPos, int yPos, int width, int height) const;
    void EditPerson(int xPos, int yPos, int width, int height);
    void TickTimer();
    int GetAlert() const;
    bool GetRemove() const;

    int GetId() const;
    int GetLastMoveTime() const;

private:
    /*Private Member Functions*/
    int _xPos, _yPos, _width, _height;
    float _moveTime, _maxMove, _minMove;
    bool _remove;
    int _lastMoveTime, _alert, _lastSeenTime, _id;
    
};

