#include <string>
#include <assert.h>
#include <vector>
#include <iostream>

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
   vector<int>  _assignedToSlot;
public:
    Slot(int id, double start, double end, int day, int min, int capacity){
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
    int getId();
    double getStart();
    double getEnd();
    int getDay();
    int getMin();
    int getCapacity();
    int getCurrent();
    vector<int> getEmployees();
    void setID(int newId);
    void setStart(double newStart);
    void setEnd(double newEnd);
    void setMin(int newMin);
    void setCapacity(int newCapacity);
    void addToSlot(int e);
    void removeFromSlot(int e);
    void displayEmployees();
};

#endif