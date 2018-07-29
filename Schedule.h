#include <string>
#include "Slot.h"
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

#define MAX_SLOTS 100

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
        delete [] _days;
    };
    const int getId();
    const string getName();
    const string getDay(int idx);
    void setName(string newName);
    void addSlot(Slot newSlot);
    void display();
};

#endif