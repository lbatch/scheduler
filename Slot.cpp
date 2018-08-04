#include "Slot.h"

const int Slot::getId()
{
    return _id;
}

// start time of slot
const double Slot::getStart()
{
    return _start;
}

// end time of slot
const double Slot::getEnd()
{
    return _end;
}

const int Slot::getDay()
{
    return _day;
}

// number of employees needed for slot
const int Slot::getMin()
{
    return _min;
}

// number of employees allowed for slot
const int Slot::getCapacity()
{
    return _capacity;
}

// current number of employees scheduled in slot
const int Slot::getCurrent()
{
    return _current;
}

const vector<Employee> Slot::getEmployees()
{
    return _assignedToSlot;
}

void Slot::setID(int newId)
{
    _id = newId;
}

void Slot::setStart(double newStart)
{
    _start = newStart;
}

void Slot::setEnd(double newEnd)
{
    _end = newEnd;
}

void Slot::setMin(int newMin)
{
    _min = newMin;
}

void Slot::setCapacity(int newCapacity)
{
    _capacity = newCapacity;
}

void Slot::addToSlot(Employee e)
{
    _assignedToSlot.push_back(e);
    _current++;
}

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

const void Slot::displayEmployees()
{
    for(auto emp : _assignedToSlot)
    {
        cout << emp.getId() << ": " << emp.getName() << endl;
    }
    cout << endl;
}