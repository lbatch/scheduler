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

#define MAX_SLOTS 10
#define MAX_EMPLOYEES 10

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