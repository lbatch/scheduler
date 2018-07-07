#include <string>
#include "Slot.h"

using std::string;

#define MAX_SLOTS 100

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule
{
private:
    int _scheduleID;
    string * _days;
    string _scheduleName;
    Slot * _slots;
public:
    Schedule(int id, string name, string* days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}){
        _scheduleID = id;
        _scheduleName = name;
        _slots = new Slot[MAX_SLOTS];
        _days = days;
    };
    virtual ~Schedule(){
        delete [] _slots;
        delete [] _days;
    };
    int getId();
    string getName();
    int getDay(int idx);
    void setName(string newName);
    void addSlot(Slot newSlot);
    void display();
};

#endif