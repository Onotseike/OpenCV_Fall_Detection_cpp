#include "Persons.h"



Persons::Persons()
= default;

Persons::Persons(float maxMove, float minMove, float moveTime)
{
    _personsList = {};
    _maxMove = maxMove;
    _minMove = minMove;
    _moveTime = moveTime;
   // _person = Person();
    _person.amount = 0;
}


Persons::~Persons()
= default;

Person
Persons::AddPerson(int xPos, int yPos, int width, int height)
{
    if (FamiliarPerson(xPos,yPos,width,height))
    {
        _familiarPerson.EditPerson(xPos,yPos,width,height);
        return _familiarPerson;
    }
    else
    {
        _person = Person(xPos, yPos, width, height, _maxMove, _minMove, _moveTime);
        _personsList.push_back(_person);
        return _person;
    }
}


bool Persons::FamiliarPerson(int xPos, int yPos, int width, int height)
{
    for (const Person& person : _personsList)
    {
        if (person.SamePerson(xPos,yPos,width,height))
        {
            _familiarPerson = person;
            return  true;
        }
    }
    return false;
}


void Persons::TickTimer()
{
 /*   const int list_size = _personsList.size();
    for (size_t idx = 0; idx < list_size; ++idx)
    {
        auto person = _personsList[idx];
        person.TickTimer();
        if (person.GetRemove())
        {
            auto iter = _personsList.begin() + idx;
            _personsList.erase(iter);
        }
        
    }*/

    for(auto iter = _personsList.begin(); iter != _personsList.end(); ++iter)
    {
        iter->TickTimer();
        if (iter->GetRemove())
        {
            _personsList.erase(iter);
        }
    }
}
