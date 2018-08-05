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

const int Schedule::getTotalMinHours()
{
    int total = 0;
    for(int s = 0; s < getNumSlots(); s++)
    {
        total += _slots[s].getMin();
    }

    return total;
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

void Schedule::writeToFile()
{
    cout << "Writing schedule to file..." << endl;

    string fileName = _scheduleName + ".txt";
    ofstream f(fileName);
    if(f)
    {
        for (auto slot: _slots)
        {
            f << _days[slot.getDay()] << ": " << endl;
            f << slot.getStart() << " - " << slot.getEnd() << endl;
            vector <Employee> emps = slot.getEmployees();
            for(auto emp : emps)
            {
                f << emp.getId() << ": " << emp.getName() << endl;
            }
            f << endl;
        }
    }

}