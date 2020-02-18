#pragma once
#include <list>
#include "Person.h"
#include <vector>
using  namespace std;

class Persons
{
private:
    /**
     * \brief 
     */
    vector<Person> _personsList;
    float _moveTime{}, _maxMove{}, _minMove{};
    Person _person;
    Person _familiarPerson;

public:
    Persons();
    Persons(float maxMove, float minMove, float moveTime);
    ~Persons();

    Person AddPerson(int xPos, int yPos, int width, int height);

    bool FamiliarPerson(int xPos, int yPos, int width, int height);

    void TickTimer();

};

