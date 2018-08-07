/*********************************************************************
 * Employee.h
 * Stores employee data and availability for scheduling
 * *******************************************************************/

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
private:
    int _id;
    string _name;
    int _minHours; // Minimum number of hours for which employee must be scheduled
    int _maxHours; // Maximum number of hours for which employee can be scheduled
    vector<int> _availability; // Vector of slot IDs for which employee is available
public:
    Employee(){
    }
    Employee(int id, string name, int min, int max, int numSlots){
        _id = id;
        _name = name;
        _minHours = min;
        _maxHours = max;
        _availability.resize(numSlots, 0);

    };
    virtual ~Employee(){
    };
    const int getId();
    const string getName();
    const int getMin();
    const int getMax();
    void setId(int newId);
    void setName(string newName);
    void setMin(int min);
    void setMax(int max);
    void addAvailability(int slot); // Adds availability for a given time slot
    void removeAvailability(int slot); // Removes availability for a given time slot
    bool checkAvailable(int slot); // Checks whether the employee is available during a given time slot
};

#endif