#include <string>
#include "Schedule.h"
#include "Employee.h"

using std::string;

#define MAX_SLOTS 100
#define MAX_EMPLOYEES 100

#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler
{
private:
    Schedule _schedule;
    Employee * _employeeAvail;
public:
    Scheduler(Schedule sched){
        _schedule = sched;
        _employeeAvail = new Employee[MAX_EMPLOYEES];
    };
    virtual ~Scheduler(){
        delete [] _employeeAvail;
    };
    void displaySchedule();
    void displayEmployees();
    void addEmployee(Employee e);
    void removeEmployee(Employee e);
    void assignSchedule();
};

#endif