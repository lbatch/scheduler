#include "Slot.h"

int Slot::getId()
{
    return _id;
}

// start time of slot
double Slot::getStart()
{
    return _start;
}

// end time of slot
double Slot::getEnd()
{
    return _end;
}

int Slot::getDay()
{
    return _day;
}

// number of employees needed for slot
int Slot::getMin()
{
    return _min;
}

// number of employees allowed for slot
int Slot::getCapacity()
{
    return _capacity;
}

// current number of employees scheduled in slot
int Slot::getCurrent()
{
    return _current;
}

vector<int> Slot::getEmployees()
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

void Slot::addToSlot(int e)
{
    assert(_current < _capacity);
    _assignedToSlot.push_back(e);
    _current++;
}

void Slot::removeFromSlot(int e)
{
    for(int i = 0; i < _current; i++)
    {
        if(_assignedToSlot[i] == e)
        {
            _assignedToSlot.erase(_assignedToSlot.begin() + i);
            _current--;
        }
    }
}

void Slot::displayEmployees()
{
    for(auto emp : _assignedToSlot)
    {
        cout << emp << ' ';
    }
    cout << endl;
}