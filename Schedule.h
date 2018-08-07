/*********************************************************************
 * Schedule.h
 * Stores information on a employment schedule
 * *******************************************************************/

#include <string>
#include "Slot.h"
#include "Employee.h"
#include <vector>
#include <iostream>
#include <fstream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ofstream;

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule
{
private:
    int _id;
    vector <string> _days; // Names of days on the schedule, in order
    string _scheduleName; // Name of schedule
    vector <Slot> _slots; // Vector of slots in schedule
public:
    Schedule() {
    }
    // Constructor without slots pre-specified
    Schedule(int id, string name, vector <string> days){
        _id = id;
        _scheduleName = name;
        _days = days;
    };
    // Constructor with slots pre-specified
    Schedule(int id, string name, vector<string> days, vector<Slot> slots){
        _id = id;
        _scheduleName = name;
        _days = days;
        _slots = slots;
    };
    virtual ~Schedule(){
    };
    const int getId();
    const string getName();
    const string getDay(int idx); // Get the string name of the day on the schedule idx days after day 0
    const vector<Slot> getSlots(); 
    const vector<string> getDays();
    const int getNumSlots(); // Get number of slots currently on the schedule
    const int getTotalMinHours(); // Get the total of the minimum hours from all slots on the schedule 
    void setName(string newName);
    void addSlot(Slot newSlot);
    void addEmployeeToSlot(Employee emp, int slotId); // Assign employee to a slot
    void display(); // Display schedule; used for testing
    void writeToFile(); // Write schedule to a .txt file
};

#endif