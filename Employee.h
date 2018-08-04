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
    vector<int> _availability;
    int _minHours;
    int _maxHours;
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
    bool checkAvailable(int slot);
    void setId(int newId);
    void setName(string newName);
    void setMin(int min);
    void setMax(int max);
    void addAvailability(int slot);
    void removeAvailability(int slot);
};

#endif