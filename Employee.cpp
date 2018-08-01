#include "Employee.h"

const int Employee::getId()
{
    return _id;
}

const string Employee::getName()
{
    return _name;
}

const int Employee::getHours()
{
    return _hoursAssigned;
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

bool Employee::checkAssigned(int slot)
{
    if(_assigned[slot] == 1)
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

void Employee::addAssigned(int slot)
{
    _assigned[slot] = 1;
}

void Employee::removeAssigned(int slot)
{
    _assigned[slot] = 0;
}

void Employee::displaySchedule()
{
    for(int i = 0; i < MAX_SLOTS; i++)
    {
        if(_assigned[i] == 1)
            cout << i << ' ';
    }
    cout << endl;
}
