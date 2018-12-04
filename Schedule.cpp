/*********************************************************************
 * Schedule.cpp
 * Stores information on a employment schedule
 * *******************************************************************/

#include "Schedule.h"

const int Schedule::getId()
{
    return _id;
}
const string Schedule::getName()
{
    return _scheduleName;
}

 // Get the string name of the day on the schedule idx days after day 0
const string Schedule::getDay(int idx)
{
    return _days[idx];
}

const vector <Slot> Schedule::getSlots()
{
    return _slots;
}

const vector<string> Schedule::getDays() {
    return _days;
}

// Get number of slots currently on the schedule
const int Schedule::getNumSlots()
{
    return _slots.size();
}

// Get the total of the minimum hours from all slots on the schedule 
// Used when user asks that employees not be scheduled above or below the average # of hours by more than 1 hour
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

// Assign employee to a slot
void Schedule::addEmployeeToSlot(Employee e, int s)
{
    _slots[s].addToSlot(e);
}

// Display schedule; used for testing
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

// Write schedule to a .txt file
// File is named after schedule name: "scheduleName.txt"
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

    cout << "You can find your schedule at " << fileName << endl;

}
