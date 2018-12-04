/*********************************************************************
 * Scheduler.cpp
 * Assigns employees to schedule, using Coin-Or Rehearse linear
 * programming library to achieve optimal value within constraints
 * *******************************************************************/

#include "Scheduler.h"

Schedule Scheduler::getSchedule()
{
    return _schedule;
}

// Assign schedule using linear programming library
void Scheduler::assignSchedule(vector<Employee> emps)
{
    OsiClpSolverInterface solver;
    CelModel model(solver);

    // Set dimensions of variable array to number of employees * number of slots
    int E = emps.size(); 
    int S = _schedule.getNumSlots();
    CelNumVarArray x;
    x.multiDimensionResize(2, E, S);

    // Set objective; default objective is minimzizing the number of person-hours scheduled
    CelExpression objective;

    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j<S; j++)
        {
            objective += x[i][j];
        }
    }

    model.setObjective(objective);
    
    vector <Slot> slots = _schedule.getSlots();

    // Constraint 1: Value of employee's placement in slot cannot be negative
    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j < S; j++)
        {
            model.addConstraint(0 <= x[i][j]);
        }
    }

    // Constraint 2: Value of employee's placement in slot cannot be greater than 1 (must be 0 or 1)
    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j < S; j++)
        {
            model.addConstraint(-1 <= 0 - x[i][j]);
        }
    }

    // Constraint 3: Employee must be available to be scheduled for slot
    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j < S; j++)
        {
            model.addConstraint(x[i][j] <= emps[i].checkAvailable(j));
        }
    }

    // Constraint 4: Employee cannot be scheduled for less than their minimum number of hours
    // or for more than their maximum number of hours
    for(int i = 0; i<E; i++)
    {
        CelExpression numHours;
        for(int j = 0; j<S; j++)
        {
            numHours += x[i][j];
        }
        model.addConstraint(0 - numHours <= 0 - emps[i].getMin());
        model.addConstraint(numHours <= emps[i].getMax());
    }

    // Constraint 5: Slot cannot contain less than its minimum number of employees
    // or more than its maximum number of employees
    for(int j = 0; j<S; j++)
    {
        CelExpression numEmp;
        for(int i = 0; i<E; i++)
        {
            numEmp += x[i][j];
        }
        model.addConstraint(0 - numEmp <= 0 - slots[j].getMin());
        model.addConstraint(numEmp <= slots[j].getCapacity());
    }

    // Initial solve
    solver.setObjSense(1.0);
    model.builderToSolver();
    solver.setLogLevel(0);
    solver.initialSolve();

    // Secure solution values; when a solution value is 1, assign that employee (i) to that slot (j)
    for(int i = 0; i<E; i++)
    {
        for(int j = 0; j<S; j++)
        {
            double x_i_j_value = model.getSolutionValue(x[i][j]);
            if(x_i_j_value)
            {
                _schedule.addEmployeeToSlot(emps[i],j);
            }
          // For testng:
          // printf("Solution for x_%d_%d : %g\n", i, j, x_i_j_value);
        }
    }

    // If solver exits without an optimal solution, return error
    if(!solver.isProvenOptimal())
    {
        throw "Solution could not be reached within constraints; you might not have enough employees with the correct availability to fill your minimum slots. Please re-run program with new information.";
    }

    return;

}
