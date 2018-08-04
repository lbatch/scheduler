#include "Employee.h"

const int Employee::getId()
{
    return _id;
}

const string Employee::getName()
{
    return _name;
}

const int Employee::getMin()
{
    return _minHours;
}

const int Employee::getMax()
{
    return _maxHours;
}

bool Employee::checkAvailable(int slot)
{
    if(_availability[slot] == 1)
    {
        return true;
    }
    return false;
}

void Employee::setId(int newId)
{
    _id = newId;
}

void Employee::setName(string newName)
{
    _name = newName;
}

void Employee::setMin(int min)
{
    _minHours = min;
}

void Employee::setMax(int max)
{
    _maxHours = max;
}

void Employee::addAvailability(int slot)
{
    _availability[slot] = 1;
}

void Employee::removeAvailability(int slot)
{
    _availability[slot] = 0;
}