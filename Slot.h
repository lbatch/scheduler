/*********************************************************************
 * Slot.h
 * Stores information on a given time slot within a schedule
 * *******************************************************************/

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
    int _day; // Day of slot, 0-indexed from first day of schedule
    double _start; // Start time of slot (0-24, 13.5 = 1:30 PM)
    double _end; // End time of slot (0-24, 13.5 = 1:30 PM)
    int _min; // Minimum number of employees needed for slot
    int _capacity; // Maximum number of employees allowed for slot
    int _current; // Number of employees currently assigned
   vector<Employee>  _assignedToSlot; // Vector of employees currently assigned to slot
public:
    Slot(int id, int day, double start, double end, int min, int capacity){
        _id = id;
        _day = day; 
        _start = start;
        _end = end;
        _min = min;
        _capacity = capacity;
        _current = 0;
    };
    virtual ~Slot(){
    };
    const int getId();
    const int getDay();
    const double getStart();
    const double getEnd();
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
    const void displayEmployees(); // Display currently-assigned employees; used for testing
};

#endif