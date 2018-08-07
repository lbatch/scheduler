/*********************************************************************
 * Slot.cpp
 * Stores information on a given time slot within a schedule
 * *******************************************************************/

#include "Slot.h"

const int Slot::getId()
{
    return _id;
}

// Day of slot, 0-indexed from first day of schedule
const int Slot::getDay()
{
    return _day;
}

// Start time of slot (0-24, 13.5 = 1:30 PM)
const double Slot::getStart()
{
    return _start;
}

// End time of slot (0-24, 13.5 = 1:30 PM)
const double Slot::getEnd()
{
    return _end;
}

// Number of employees needed for slot
const int Slot::getMin()
{
    return _min;
}

// Number of employees allowed for slot
const int Slot::getCapacity()
{
    return _capacity;
}

// Current number of employees scheduled in slot
const int Slot::getCurrent()
{
    return _current;
}

// Returns a vector of employees scheduled in slot
const vector<Employee> Slot::getEmployees()
{
    return _assignedToSlot;
}

void Slot::setID(int newId)
{
    _id = newId;
}

// Set start time of slot (0-24, 13.5 = 1:30 PM)
void Slot::setStart(double newStart)
{
    _start = newStart;
}

// Set end time  of slot (0-24, 13.5 = 1:30 PM)
void Slot::setEnd(double newEnd)
{
    _end = newEnd;
}

// Set minimum number of employees needed for slot
void Slot::setMin(int newMin)
{
    _min = newMin;
}

// Set maximum number of employees allowed for slot
void Slot::setCapacity(int newCapacity)
{
    _capacity = newCapacity;
}

// Add employee to slot
void Slot::addToSlot(Employee e)
{
    _assignedToSlot.push_back(e);
    _current++;
}

// Remove employee from slot
void Slot::removeFromSlot(Employee e)
{
    for(int i = 0; i < _current; i++)
    {
        if(_assignedToSlot[i].getId() == e.getId())
        {
            _assignedToSlot.erase(_assignedToSlot.begin() + i);
            _current--;
        }
    }
}

// Display employees currently assigned to slot; used for testing
const void Slot::displayEmployees()
{
    for(auto emp : _assignedToSlot)
    {
        cout << emp.getId() << ": " << emp.getName() << endl;
    }
    cout << endl;
}