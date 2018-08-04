#include <string>
#include "Slot.h"
#include "Employee.h"
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

#define MAX_SLOTS 10

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule
{
private:
    int _id;
    string * _days;
    string _scheduleName;
    vector <Slot> _slots;
public:
    Schedule() {
    }
    Schedule(int id, string name, string* days){
        _id = id;
        _scheduleName = name;
        _days = days;
    };
    virtual ~Schedule(){
    };
    const int getId();
    const string getName();
    const string getDay(int idx);
    const vector<Slot> getSlots();
    void setName(string newName);
    void addSlot(Slot newSlot);
    void display();
    void addEmployeeToSlot(Employee emp, int slotId);
};

#endif