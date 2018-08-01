#include <string>
#include <iostream>
#include "Slot.h"

using std::string;
using std::cout;
using std::endl;

#define MAX_SLOTS 10

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
private:
    int _id;
    string _name;
    int _availability[MAX_SLOTS];
    int _assigned[MAX_SLOTS];
    int _hoursAssigned;
    int _minHours;
    int _maxHours;
public:
    Employee(){
    }
    Employee(int id, string name, int min, int max){
        _id = id;
        _name = name;
        _minHours = min;
        _maxHours = max;
        _assigned;
        _availability;

    };
    virtual ~Employee(){
    };
    const int getId();
    const string getName();
    const int getHours();
    const int getMin();
    const int getMax();
    bool checkAvailable(int slot);
    bool checkAssigned(int slot);
    void setId(int newId);
    void setName(string newName);
    void setMin(int min);
    void setMax(int max);
    void addAvailability(int slot);
    void removeAvailability(int slot);
    void addAssigned(int slot);
    void removeAssigned(int slot);
    void displaySchedule();
};

#endif