#include "Schedule.h"

const int Schedule::getId()
{
    return _id;
}
const string Schedule::getName()
{
    return _scheduleName;
}

const string Schedule::getDay(int idx)
{
    return _days[idx];
}

const vector <Slot> Schedule::getSlots()
{
    return _slots;
}

const int Schedule::getNumSlots()
{
    return _slots.size();
}

void Schedule::setName(string newName)
{
    _scheduleName = newName;
}

void Schedule::addSlot(Slot newSlot)
{
    _slots.push_back(newSlot);
}

void Schedule::addEmployeeToSlot(Employee e, int s)
{
    _slots[s].addToSlot(e);
}

void Schedule::display()
{
    for (auto slot: _slots)
    {
        cout << _days[slot.getDay()] << ": " << endl;
        cout << slot.getStart() << " - " << slot.getEnd() << endl;
        slot.displayEmployees();
        cout << endl;

    }
}