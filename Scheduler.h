/*********************************************************************
 * Scheduler.h
 * Assigns employees to schedule, using Coin-Or Rehearse linear
 * programming library to achieve optimum value within constraints
 * *******************************************************************/

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
    int _objective; // Will be used to set alternate objectives; not currently in use
public:
    // Constructor without pre-specified employee availability
    Scheduler(Schedule sched)
    {
        _schedule = sched;
        _objective = 0;
    };
    // Constructor to be used with alternate objectives
    Scheduler(Schedule sched, int obj)
    {
        _schedule = sched;
        _objective  = obj;
    }
    virtual ~Scheduler(){
    };
    Schedule getSchedule();
    void assignSchedule(vector<Employee> emps); // Assigns schedule using Rehearse library
};

#endif
