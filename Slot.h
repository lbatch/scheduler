#include <string>
#include <assert.h>
#include <vector>
#include <iostream>

#include "Employee.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

#ifndef SLOT_H
#define SLOT_H

class Slot
{
private:
    int _id;
    double _start;
    double _end;
    int _day;
    int _min;
    int _capacity;
    int _current;
   vector<Employee>  _assignedToSlot;
public:
    Slot(int id, int day, double start, double end, int min, int capacity){
        _id = id;
        _start = start;
        _end = end;
        _day = day;
        _min = min;
        _capacity = capacity;
        _current = 0;
    };
    virtual ~Slot(){
    };
    const int getId();
    const double getStart();
    const double getEnd();
    const int getDay();
    const int getMin();
    const int getCapacity();
    const int getCurrent();
    const vector<Employee> getEmployees();
    void setID(int newId);
    void setStart(double newStart);
    void setEnd(double newEnd);
    void setMin(int newMin);
    void setCapacity(int newCapacity);
    void addToSlot(Employee e);
    void removeFromSlot(Employee e);
    const void displayEmployees();
};

#endif