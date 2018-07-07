#include <string>
#include "Slot.h"

using std::string;

#define MAX_SLOTS 100

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
private:
    int _id;
    string _name;
    int * _availability;
    Slot * _assigned;
    int _hoursAssigned;
    int _minHours;
    int _maxHours;
public:
    Employee(int id, string name, int min, int max){
        _id = id;
        _name = name;
        _minHours = min;
        _maxHours = max;
        _availability = new int[MAX_SLOTS];
        _assigned = new Slot[MAX_SLOTS];
    };
    virtual ~Employee(){
        delete [] _availability;
        delete [] _assigned;
    };
    int getId();
    int getName();
    int getHours();
    int checkAvailable(int slot);
    int checkAssigned(int slot);
    void setID(int newId);
    void setName(string newName);
    void setMin(int min);
    void setMax(int max);
    void addAvailability(int slot);
    void removeAvailability(int slot);
    void addAssigned(int slot);
    void displaySchedule();
};

#endif