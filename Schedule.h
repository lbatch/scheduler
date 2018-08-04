#include <string>
#include "Slot.h"
#include "Employee.h"
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule
{
private:
    int _id;
    vector <string> _days;
    string _scheduleName;
    vector <Slot> _slots;
public:
    Schedule() {
    }
    Schedule(int id, string name, vector <string> days){
        _id = id;
        _scheduleName = name;
        _days = days;
    };
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
    const string getDay(int idx);
    const vector<Slot> getSlots();
    const int getNumSlots();
    void setName(string newName);
    void addSlot(Slot newSlot);
    void display();
    void addEmployeeToSlot(Employee emp, int slotId);
};

#endif