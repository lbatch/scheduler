#include <string>
#include "Employee.h"

using std::string;

#ifndef SLOT_H
#define SLOT_H

class Slot
{
private:
    int _id;
    double _start;
    double _end;
    int _day;
    int _capacity;
    int _current;
    int _remaining;
    Employee * _assignedToSlot;
public:
    Slot(int id, double start, double end, int day, int capacity){
        _id = id;
        _start = start;
        _end = end;
        _day = day;
        _capacity = capacity;
        _current = 0;
        _remaining = capacity;
        _assignedToSlot = new Employee[capacity];
    };
    virtual ~Slot(){
        delete _assignedToSlot;
    };
    int getId();
    double getStart();
    double getEnd();
    int getDay();
    int getCapacity();
    int getCurrent();
    int getRemaining();
    void setID(int newId);
    void setStart(double newStart);
    void setEnd(double newEnd);
    void setCapacity(int newCapacity);
    void addToSlot(Employee e);
    void removeFromSlot(Employee e);
    void displayEmployees();
};

#endif