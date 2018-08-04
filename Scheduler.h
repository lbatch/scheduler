#include <string>
#include "Schedule.h"
#include "Employee.h"

#include <CelModel.h>
#include <CelNumVar.h>
#include <CelIntVar.h>
#include <CelBoolVar.h>
#include <CelNumVarArray.h>
#include <CelBoolVarArray.h>

#include "CbcModel.hpp"
#include "OsiClpSolverInterface.hpp"
#include "OsiCbcSolverInterface.hpp"

using namespace std;
using namespace rehearse;

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
    Scheduler(Schedule sched, vector <Employee> emps)
    {
        _schedule = sched;
        _employeeAvail = emps;
    }
    virtual ~Scheduler(){
    };
    Schedule getSchedule();
    const int getNumEmployees();
    void addEmployee(Employee e);
    void removeEmployee(Employee e);
    void assignSchedule();
};

#endif