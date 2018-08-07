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
    vector <Employee>  _employeeAvail; // Employee availability for each slot in schedule
    int _objective; // Will be used to set alternate objectives; not currently in use
public:
    // Constructor without pre-specified employee availability
    Scheduler(Schedule sched)
    {
        _schedule = sched;
        _objective = 0;
    };
    // Constructor with pre-specified employee availability
    Scheduler(Schedule sched, vector <Employee> emps)
    {
        _schedule = sched;
        _employeeAvail = emps;
        _objective  = 0;
    }
    // Constructor to be used with alternate objectives
    Scheduler(Schedule sched, vector <Employee> emps, int obj)
    {
        _schedule = sched;
        _employeeAvail = emps;
        _objective  = obj;
    }
    virtual ~Scheduler(){
    };
    Schedule getSchedule();
    const int getNumEmployees();
    void addEmployee(Employee e);
    void removeEmployee(Employee e);
    void assignSchedule(); // Assigns schedule using Rehearse library
    void displayAvailability(); // Displays employee availability; used for testing
};

#endif