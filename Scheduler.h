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
    vector <Employee>  _employeeAvail;
public:
    Scheduler(Schedule sched)
    {
        _schedule = sched;
    };
    virtual ~Scheduler(){
    };
    void addEmployee(Employee e);
    void removeEmployee(Employee e);
    void assignSchedule();
};

#endif