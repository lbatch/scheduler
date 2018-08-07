/*********************************************************************
 * Employee.cpp
 * Stores employee data and availability for scheduling
 * *******************************************************************/

#include "Employee.h"

const int Employee::getId()
{
    return _id;
}

const string Employee::getName()
{
    return _name;
}

// Minimum number of hours for which employee must be scheduled
const int Employee::getMin()
{
    return _minHours;
}

// Maximum number of hours for which employee can be scheduled
const int Employee::getMax()
{
    return _maxHours;
}

void Employee::setId(int newId)
{
    _id = newId;
}

void Employee::setName(string newName)
{
    _name = newName;
}

// Set minimum number of hours for which employee must be scheduled
void Employee::setMin(int min)
{
    _minHours = min;
}

// Set maximum number of hours for which employee can be scheduled
void Employee::setMax(int max)
{
    _maxHours = max;
}

// Adds availability for a given time slot
void Employee::addAvailability(int slot)
{
    _availability[slot] = 1;
}

// Removes availability for a given time slot
void Employee::removeAvailability(int slot)
{
    _availability[slot] = 0;
}

// Checks whether the employee is available during a given time slot
// Accepts int rather than Slot object because of constraint functionality in scheduler
bool Employee::checkAvailable(int slot)
{
    if(_availability[slot] == 1)
    {
        return true;
    }
    return false;
}