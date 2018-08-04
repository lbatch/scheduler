#include "Scheduler.h"

Schedule Scheduler::getSchedule()
{
    return _schedule;
}

const int Scheduler::getNumEmployees()
{
    return _employeeAvail.size();
}

void Scheduler::addEmployee(Employee e)
{
   _employeeAvail.push_back(e);
}

void Scheduler::removeEmployee(Employee e)
{
    for(int i = 0; i < _employeeAvail.size(); i++)
    {
        if(_employeeAvail[i].getId() == e.getId())
        {
            _employeeAvail.erase(_employeeAvail.begin()+i);
        }
    }
}

void Scheduler::displayAvailability()
{
    vector <Slot> slots = _schedule.getSlots();
    vector <string> days = _schedule.getDays();
    for(int i = 0; i < _employeeAvail.size(); i++)
    {
        cout << _employeeAvail[i].getName() << ": " << endl;
        for(int s = 0; s < slots.size(); s++)
        {
            cout << "Slot ID: " << slots[s].getId() << endl;  
            cout << "Slot Day: " << days[slots[s].getDay()] << endl;
            cout << "Slot Time: " << slots[s].getStart();
            cout << "Available? " << _employeeAvail[i].checkAvailable(s) << endl;
            cout << "Available? " << _employeeAvail[i].checkAvailable(slots[s].getId()) << endl;
        }
    }
}

void Scheduler::assignSchedule()
{
    OsiClpSolverInterface solver;
    CelModel model(solver);

    int E = getNumEmployees(); 
    int S = _schedule.getNumSlots();
    CelNumVarArray x;
    x.multiDimensionResize(2, E, S);

    CelExpression objective;
    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j<S; j++)
        {
            objective += 0 - x[i][j];
        }
    }
    model.setObjective(objective);

    vector <Slot> slots = _schedule.getSlots();

    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j < S; j++)
        {
            model.addConstraint(0 <= x[i][j]);
        }
    }

    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j < S; j++)
        {
            model.addConstraint(-1 <= 0 - x[i][j]);
        }
    }

    for(int i = 0; i < E; i++)
    {
        for(int j = 0; j < S; j++)
        {
            model.addConstraint(x[i][j] <= _employeeAvail[i].checkAvailable(j));
        }
    }

    for(int i = 0; i<E; i++)
    {
        CelExpression numHours;
        for(int j = 0; j<S; j++)
        {
            numHours += x[i][j];
        }
        model.addConstraint(0 - numHours <= 0 - _employeeAvail[i].getMin());
        model.addConstraint(numHours <= _employeeAvail[i].getMax());
    }

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

    solver.setObjSense(1.0);
    model.builderToSolver();
    solver.setLogLevel(0);
    solver.initialSolve();

    for(int i = 0; i<E; i++)
    {
        for(int j = 0; j<S; j++)
        {
            double x_i_j_value = model.getSolutionValue(x[i][j]);
            if(x_i_j_value)
            {
                _schedule.addEmployeeToSlot(_employeeAvail[i],j);
            }
          //printf("Solution for x_%d_%d : %g\n", i, j, x_i_j_value);
        }
    }

}
