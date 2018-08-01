#include "Scheduler.h"

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

void Scheduler::assignSchedule()
{
    OsiClpSolverInterface solver;
    CelModel model(solver);

    CelNumVarArray x;
    int E = 10; // number of employees
    int S = 10; // number of slots
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

    for(int i = 0; i<E; i++)
    {
        for(int j = 0; j<S; j++)
        {
            model.addConstraint(0 <= x[i][j]);
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
            printf("Solution for x_%d_%d : %g\n", i, j, x_i_j_value);
        }
    }

}
/*void Scheduler::assignSchedule()
{
    OsiClpSolverInterface solver;
    CelModel model(solver);

    CelIntVar e0s0;
    CelIntVar e1s0;
    CelIntVar e2s0;
    CelIntVar e3s0;
    CelIntVar e4s0;
    CelIntVar e5s0;
    CelIntVar e6s0;
    CelIntVar e7s0;
    CelIntVar e8s0;
    CelIntVar e9s0;

    CelIntVar e0s1;
    CelIntVar e1s1;
    CelIntVar e2s1;
    CelIntVar e3s1;
    CelIntVar e4s1;
    CelIntVar e5s1;
    CelIntVar e6s1;
    CelIntVar e7s1;
    CelIntVar e8s1;
    CelIntVar e9s1;

    CelIntVar e0s2;
    CelIntVar e1s2;
    CelIntVar e2s2;
    CelIntVar e3s2;
    CelIntVar e4s2;
    CelIntVar e5s2;
    CelIntVar e6s2;
    CelIntVar e7s2;
    CelIntVar e8s2;
    CelIntVar e9s2;

    CelIntVar e0s3;
    CelIntVar e1s3;
    CelIntVar e2s3;
    CelIntVar e3s3;
    CelIntVar e4s3;
    CelIntVar e5s3;
    CelIntVar e6s3;
    CelIntVar e7s3;
    CelIntVar e8s3;
    CelIntVar e9s3;

    CelIntVar e0s4;
    CelIntVar e1s4;
    CelIntVar e2s4;
    CelIntVar e3s4;
    CelIntVar e4s4;
    CelIntVar e5s4;
    CelIntVar e6s4;
    CelIntVar e7s4;
    CelIntVar e8s4;
    CelIntVar e9s4;

    CelIntVar e0s5;
    CelIntVar e1s5;
    CelIntVar e2s5;
    CelIntVar e3s5;
    CelIntVar e4s5;
    CelIntVar e5s5;
    CelIntVar e6s5;
    CelIntVar e7s5;
    CelIntVar e8s5;
    CelIntVar e9s5;

    CelIntVar e0s6;
    CelIntVar e1s6;
    CelIntVar e2s6;
    CelIntVar e3s6;
    CelIntVar e4s6;
    CelIntVar e5s6;
    CelIntVar e6s6;
    CelIntVar e7s6;
    CelIntVar e8s6;
    CelIntVar e9s6;

    CelIntVar e0s7;
    CelIntVar e1s7;
    CelIntVar e2s7;
    CelIntVar e3s7;
    CelIntVar e4s7;
    CelIntVar e5s7;
    CelIntVar e6s7;
    CelIntVar e7s7;
    CelIntVar e8s7;
    CelIntVar e9s7;

    CelIntVar e0s8;
    CelIntVar e1s8;
    CelIntVar e2s8;
    CelIntVar e3s8;
    CelIntVar e4s8;
    CelIntVar e5s8;
    CelIntVar e6s8;
    CelIntVar e7s8;
    CelIntVar e8s8;
    CelIntVar e9s8;

    CelIntVar e0s9;
    CelIntVar e1s9;
    CelIntVar e2s9;
    CelIntVar e3s9;
    CelIntVar e4s9;
    CelIntVar e5s9;
    CelIntVar e6s9;
    CelIntVar e7s9;
    CelIntVar e8s9;
    CelIntVar e9s9;

    model.setObjective( 
                        0 - e0s0 - e1s0 - e2s0 - e3s0 - e4s0 - e5s0 - e6s0 - e7s0 - e8s0 - e9s0
                        - e0s1 - e1s1 - e2s1 - e3s1 - e4s1 - e5s1 - e6s1 - e7s1 - e8s1 - e9s1 
                        - e0s2 - e1s2 - e2s2 - e3s2 - e4s2 - e5s2 - e6s2 - e7s2 - e8s2 - e9s2 
                        - e0s3 - e1s3 - e2s3 - e3s3 - e4s3 - e5s3 - e6s3 - e7s3 - e8s3 - e9s3 
                        - e0s4 - e1s4 - e2s4 - e3s4 - e4s4 - e5s4 - e6s4 - e7s4 - e8s4 - e9s4 
                        - e0s5 - e1s5 - e2s5 - e3s5 - e4s5 - e5s5 - e6s5 - e7s5 - e8s5 - e9s5 
                        - e0s6 - e1s6 - e2s6 - e3s6 - e4s6 - e5s6 - e6s6 - e7s6 - e8s6 - e9s6 
                        - e0s7 - e1s7 - e2s7 - e3s7 - e4s7 - e5s7 - e6s7 - e7s7 - e8s7 - e9s7 
                        - e0s8 - e1s8 - e2s8 - e3s8 - e4s8 - e5s8 - e6s8 - e7s8 - e8s8 - e9s8 
                        - e0s9 - e1s9 - e2s9 - e3s9 - e4s9 - e5s9 - e6s9 - e7s9 - e8s9 - e9s9 );

    vector <Slot> slots = _schedule.getSlots();

    int s0Cap = slots[0].getCapacity();
    int s1Cap = slots[1].getCapacity();
    int s2Cap = slots[2].getCapacity();
    int s3Cap = slots[3].getCapacity();
    int s4Cap = slots[4].getCapacity();
    int s5Cap = slots[5].getCapacity();
    int s6Cap = slots[6].getCapacity();
    int s7Cap = slots[7].getCapacity();
    int s8Cap = slots[8].getCapacity();
    int s9Cap = slots[9].getCapacity();

    int s0Min = slots[0].getMin();
    int s1Min = slots[1].getMin();
    int s2Min = slots[2].getMin();
    int s3Min = slots[3].getMin();
    int s4Min = slots[4].getMin();
    int s5Min = slots[5].getMin();
    int s6Min = slots[6].getMin();
    int s7Min = slots[7].getMin();
    int s8Min = slots[8].getMin();
    int s9Min = slots[9].getMin();

    model.addConstraint(e0s0 + e1s0 + e2s0 + e3s0 + e4s0 + e5s0 + e6s0 + e7s0 + e8s0 + e9s0 <= s0Cap);
    model.addConstraint(0 - e0s0 - e1s0 - e2s0 - e3s0 - e4s0 - e5s0 - e6s0 - e7s0 - e8s0 - e9s0 <= 0 -s0Min);

    model.addConstraint(e0s1 + e1s1 + e2s1 + e3s1 + e4s1 + e5s1 + e6s1 + e7s1 + e8s1 + e9s1 <= s1Cap);
    model.addConstraint(0 - e0s1 - e1s1 - e2s1 - e3s1 - e4s1 - e5s1 - e6s1 - e7s1 - e8s1 - e9s1 <= 0 -s1Min);

    model.addConstraint(e0s2 + e1s2 + e2s2 + e3s2 + e4s2 + e5s2 + e6s2 + e7s2 + e8s2 + e9s2 <= s2Cap);
    model.addConstraint(0 - e0s2 - e1s2 - e2s2 - e3s2 - e4s2 - e5s2 - e6s2 - e7s2 - e8s2 - e9s2 <= 0 -s2Min);

    model.addConstraint(e0s3 + e1s3 + e2s3 + e3s3 + e4s3 + e5s3 + e6s3 + e7s3 + e8s3 + e9s3 <= s3Cap);
    model.addConstraint(0 - e0s3 - e1s3 - e2s3 - e3s3 - e4s3 - e5s3 - e6s3 - e7s3 - e8s3 - e9s3 <= 0 -s3Min);

    model.addConstraint(e0s4 + e1s4 + e2s4 + e3s4 + e4s4 + e5s4 + e6s4 + e7s4 + e8s4 + e9s4 <= s4Cap);
    model.addConstraint(0 - e0s4 - e1s4 - e2s4 - e3s4 - e4s4 - e5s4 - e6s4 - e7s4 - e8s4 - e9s4 <= 0 -s4Min);

    model.addConstraint(e0s5 + e1s5 + e2s5 + e3s5 + e4s5 + e5s5 + e6s5 + e7s5 + e8s5 + e9s5 <= s5Cap);
    model.addConstraint(0 - e0s5 - e1s5 - e2s5 - e3s5 - e4s5 - e5s5 - e6s5 - e7s5 - e8s5 - e9s5 <= 0 -s5Min);

    model.addConstraint(e0s6 + e1s6 + e2s6 + e3s6 + e4s6 + e5s6 + e6s6 + e7s6 + e8s6 + e9s6 <= s6Cap);
    model.addConstraint(0 - e0s6 - e1s6 - e2s6 - e3s6 - e4s6 - e5s6 - e6s6 - e7s6 - e8s6 - e9s6 <= 0 -s6Min);

    model.addConstraint(e0s7 + e1s7 + e2s7 + e3s7 + e4s7 + e5s7 + e6s7 + e7s7 + e8s7 + e9s7 <= s7Cap);
    model.addConstraint(0 - e0s7 - e1s7 - e2s7 - e3s7 - e4s7 - e5s7 - e6s7 - e7s7 - e8s7 - e9s7 <= 0 -s7Min);

    model.addConstraint(e0s8 + e1s8 + e2s8 + e3s8 + e4s8 + e5s8 + e6s8 + e7s8 + e8s8 + e9s8 <= s8Cap);
    model.addConstraint(0 - e0s8 - e1s8 - e2s8 - e3s8 - e4s8 - e5s8 - e6s8 - e7s8 - e8s8 - e9s8 <= 0 -s8Min);

    model.addConstraint(e0s9 + e1s9 + e2s9 + e3s9 + e4s9 + e5s9 + e6s9 + e7s9 + e8s9 + e9s9 <= s9Cap);
    model.addConstraint(0 - e0s9 - e1s9 - e2s9 - e3s9 - e4s9 - e5s9 - e6s9 - e7s9 - e8s9 - e9s9 <= 0 -s9Min);


    int e0Cap = _employeeAvail[0].getMax();
    int e1Cap = _employeeAvail[1].getMax();
    int e2Cap = _employeeAvail[2].getMax();
    int e3Cap = _employeeAvail[3].getMax();
    int e4Cap = _employeeAvail[4].getMax();
    int e5Cap = _employeeAvail[5].getMax();
    int e6Cap = _employeeAvail[6].getMax();
    int e7Cap = _employeeAvail[7].getMax();
    int e8Cap = _employeeAvail[8].getMax();
    int e9Cap = _employeeAvail[9].getMax();

    int e0Min = _employeeAvail[0].getMin();
    int e1Min = _employeeAvail[1].getMin();
    int e2Min = _employeeAvail[2].getMin();
    int e3Min = _employeeAvail[3].getMin();
    int e4Min = _employeeAvail[4].getMin();
    int e5Min = _employeeAvail[5].getMin();
    int e6Min = _employeeAvail[6].getMin();
    int e7Min = _employeeAvail[7].getMin();
    int e8Min = _employeeAvail[8].getMin();
    int e9Min = _employeeAvail[9].getMin();


    model.addConstraint(e0s0 + e0s1 + e0s2 + e0s3 + e0s4 + e0s5 + e0s6 + e0s7 + e0s8 + e0s9 <= e0Cap);
    model.addConstraint(0 - e0s0 - e0s1 - e0s2 - e0s3 - e0s4 - e0s5 - e0s6 - e0s7 - e0s8 - e0s9 <= 0 - e0Min);

    model.addConstraint(e1s0 + e1s1 + e1s2 + e1s3 + e1s4 + e1s5 + e1s6 + e1s7 + e1s8 + e1s9 <= e1Cap);
    model.addConstraint(0 - e1s0 - e1s1 - e1s2 - e1s3 - e1s4 - e1s5 - e1s6 - e1s7 - e1s8 - e1s9 <= 0 - e1Min);

    model.addConstraint(e2s0 + e2s1 + e2s2 + e2s3 + e2s4 + e2s5 + e2s6 + e2s7 + e2s8 + e2s9 <= e2Cap);
    model.addConstraint(0 - e2s0 - e2s1 - e2s2 - e2s3 - e2s4 - e2s5 - e2s6 - e2s7 - e2s8 - e2s9 <= 0 - e2Min);

    model.addConstraint(e3s0 + e3s1 + e3s2 + e3s3 + e3s4 + e3s5 + e3s6 + e3s7 + e3s8 + e3s9 <= e3Cap);
    model.addConstraint(0 - e3s0 - e3s1 - e3s2 - e3s3 - e3s4 - e3s5 - e3s6 - e3s7 - e3s8 - e3s9 <= 0 - e3Min);

    model.addConstraint(e4s0 + e4s1 + e4s2 + e4s3 + e4s4 + e4s5 + e4s6 + e4s7 + e4s8 + e4s9 <= e4Cap);
    model.addConstraint(0 - e4s0 - e4s1 - e4s2 - e4s3 - e4s4 - e4s5 - e4s6 - e4s7 - e4s8 - e4s9 <= 0 - e4Min);
 
    model.addConstraint(e5s0 + e5s1 + e5s2 + e5s3 + e5s4 + e5s5 + e5s6 + e5s7 + e5s8 + e5s9 <= e5Cap);
    model.addConstraint(0 - e5s0 - e5s1 - e5s2 - e5s3 - e5s4 - e5s5 - e5s6 - e5s7 - e5s8 - e5s9 <= 0 - e5Min);

    model.addConstraint(e6s0 + e6s1 + e6s2 + e6s3 + e6s4 + e6s5 + e6s6 + e6s7 + e6s8 + e6s9 <= e6Cap);
    model.addConstraint(0 - e6s0 - e6s1 - e6s2 - e6s3 - e6s4 - e6s5 - e6s6 - e6s7 - e6s8 - e6s9 <= 0 - e6Min);

    model.addConstraint(e7s0 + e7s1 + e7s2 + e7s3 + e7s4 + e7s5 + e7s6 + e7s7 + e7s8 + e7s9 <= e7Cap);
    model.addConstraint(0 - e7s0 - e7s1 - e7s2 - e7s3 - e7s4 - e7s5 - e7s6 - e7s7 - e7s8 - e7s9 <= 0 - e7Min);

    model.addConstraint(e8s0 + e8s1 + e8s2 + e8s3 + e8s4 + e8s5 + e8s6 + e8s7 + e8s8 + e8s9 <= e8Cap);
    model.addConstraint(0 - e8s0 - e8s1 - e8s2 - e8s3 - e8s4 - e8s5 - e8s6 - e8s7 - e8s8 - e8s9 <= 0 - e8Min);

    model.addConstraint(e9s0 + e9s1 + e9s2 + e9s3 + e9s4 + e9s5 + e9s6 + e9s7 + e9s8 + e9s9 <= e9Cap);
    model.addConstraint(0 - e9s0 - e9s1 - e9s2 - e9s3 - e9s4 - e9s5 - e9s6 - e9s7 - e9s8 - e9s9 <= 0 - e9Min);

    model.addConstraint(e9s0 + e9s1 + e9s2 + e9s3 + e9s4 + e9s5 + e9s6 + e9s7 + e9s8 + e9s9 <= e9Cap);
    model.addConstraint(0 - e9s0 - e9s1 - e9s2 - e9s3 - e9s4 - e9s5 - e9s6 - e9s7 - e9s8 - e9s9 <= 0 - e9Min);

    model.addConstraint(0 - e0s0 <= 0);
    model.addConstraint(0 - e0s1 <= 0);
    model.addConstraint(0 - e0s2 <= 0);
    model.addConstraint(0 - e0s3 <= 0);
    model.addConstraint(0 - e0s4 <= 0);
    model.addConstraint(0 - e0s5 <= 0);
    model.addConstraint(0 - e0s6 <= 0);
    model.addConstraint(0 - e0s7 <= 0);
    model.addConstraint(0 - e0s8 <= 0);
    model.addConstraint(0 - e0s9 <= 0);

    model.addConstraint(0 - e1s0 <= 0);
    model.addConstraint(0 - e1s1 <= 0);
    model.addConstraint(0 - e1s2 <= 0);
    model.addConstraint(0 - e1s3 <= 0);
    model.addConstraint(0 - e1s4 <= 0);
    model.addConstraint(0 - e1s5 <= 0);
    model.addConstraint(0 - e1s6 <= 0);
    model.addConstraint(0 - e1s7 <= 0);
    model.addConstraint(0 - e1s8 <= 0);
    model.addConstraint(0 - e1s9 <= 0);

    model.addConstraint(0 - e2s0 <= 0);
    model.addConstraint(0 - e2s1 <= 0);
    model.addConstraint(0 - e2s2 <= 0);
    model.addConstraint(0 - e2s3 <= 0);
    model.addConstraint(0 - e2s4 <= 0);
    model.addConstraint(0 - e2s5 <= 0);
    model.addConstraint(0 - e2s6 <= 0);
    model.addConstraint(0 - e2s7 <= 0);
    model.addConstraint(0 - e2s8 <= 0);
    model.addConstraint(0 - e2s9 <= 0);

    model.addConstraint(0 - e3s0 <= 0);
    model.addConstraint(0 - e3s1 <= 0);
    model.addConstraint(0 - e3s2 <= 0);
    model.addConstraint(0 - e3s3 <= 0);
    model.addConstraint(0 - e3s4 <= 0);
    model.addConstraint(0 - e3s5 <= 0);
    model.addConstraint(0 - e3s6 <= 0);
    model.addConstraint(0 - e3s7 <= 0);
    model.addConstraint(0 - e3s8 <= 0);
    model.addConstraint(0 - e3s9 <= 0);

    model.addConstraint(0 - e4s0 <= 0);
    model.addConstraint(0 - e4s1 <= 0);
    model.addConstraint(0 - e4s2 <= 0);
    model.addConstraint(0 - e4s3 <= 0);
    model.addConstraint(0 - e4s4 <= 0);
    model.addConstraint(0 - e4s5 <= 0);
    model.addConstraint(0 - e4s6 <= 0);
    model.addConstraint(0 - e4s7 <= 0);
    model.addConstraint(0 - e4s8 <= 0);
    model.addConstraint(0 - e4s9 <= 0);

    model.addConstraint(0 - e5s0 <= 0);
    model.addConstraint(0 - e5s1 <= 0);
    model.addConstraint(0 - e5s2 <= 0);
    model.addConstraint(0 - e5s3 <= 0);
    model.addConstraint(0 - e5s4 <= 0);
    model.addConstraint(0 - e5s5 <= 0);
    model.addConstraint(0 - e5s6 <= 0);
    model.addConstraint(0 - e5s7 <= 0);
    model.addConstraint(0 - e5s8 <= 0);
    model.addConstraint(0 - e5s9 <= 0);

    model.addConstraint(0 - e6s0 <= 0);
    model.addConstraint(0 - e6s1 <= 0);
    model.addConstraint(0 - e6s2 <= 0);
    model.addConstraint(0 - e6s3 <= 0);
    model.addConstraint(0 - e6s4 <= 0);
    model.addConstraint(0 - e6s5 <= 0);
    model.addConstraint(0 - e6s6 <= 0);
    model.addConstraint(0 - e6s7 <= 0);
    model.addConstraint(0 - e6s8 <= 0);
    model.addConstraint(0 - e6s9 <= 0);

    model.addConstraint(0 - e7s0 <= 0);
    model.addConstraint(0 - e7s1 <= 0);
    model.addConstraint(0 - e7s2 <= 0);
    model.addConstraint(0 - e7s3 <= 0);
    model.addConstraint(0 - e7s4 <= 0);
    model.addConstraint(0 - e7s5 <= 0);
    model.addConstraint(0 - e7s6 <= 0);
    model.addConstraint(0 - e7s7 <= 0);
    model.addConstraint(0 - e7s8 <= 0);
    model.addConstraint(0 - e7s9 <= 0);

    model.addConstraint(0 - e8s0 <= 0);
    model.addConstraint(0 - e8s1 <= 0);
    model.addConstraint(0 - e8s2 <= 0);
    model.addConstraint(0 - e8s3 <= 0);
    model.addConstraint(0 - e8s4 <= 0);
    model.addConstraint(0 - e8s5 <= 0);
    model.addConstraint(0 - e8s6 <= 0);
    model.addConstraint(0 - e8s7 <= 0);
    model.addConstraint(0 - e8s8 <= 0);
    model.addConstraint(0 - e8s9 <= 0);

    model.addConstraint(0 - e9s0 <= 0);
    model.addConstraint(0 - e9s1 <= 0);
    model.addConstraint(0 - e9s2 <= 0);
    model.addConstraint(0 - e9s3 <= 0);
    model.addConstraint(0 - e9s4 <= 0);
    model.addConstraint(0 - e9s5 <= 0);
    model.addConstraint(0 - e9s6 <= 0);
    model.addConstraint(0 - e9s7 <= 0);
    model.addConstraint(0 - e9s8 <= 0);
    model.addConstraint(0 - e9s9 <= 0);

    solver.setObjSense(-1.0);
    model.builderToSolver();
    solver.setLogLevel(0);
    solver.initialSolve();

    CbcModel cbcModel(solver);
    cbcModel.branchAndBound();

    printf("Solution for e0s0 : %g\n", model.getSolutionValue(e0s0, *cbcModel.solver()));
    printf("Solution for e0s1 : %g\n", model.getSolutionValue(e0s1, *cbcModel.solver()));
    printf("Solution for e0s2 : %g\n", model.getSolutionValue(e0s2, *cbcModel.solver()));
    printf("Solution for e0s3 : %g\n", model.getSolutionValue(e0s3, *cbcModel.solver()));        
    printf("Solution for e0s4 : %g\n", model.getSolutionValue(e0s4, *cbcModel.solver()));
    printf("Solution for e0s5 : %g\n", model.getSolutionValue(e0s5, *cbcModel.solver()));
    printf("Solution for e0s6 : %g\n", model.getSolutionValue(e0s6, *cbcModel.solver()));
    printf("Solution for e0s7 : %g\n", model.getSolutionValue(e0s7, *cbcModel.solver()));
    printf("Solution for e0s8 : %g\n", model.getSolutionValue(e0s8, *cbcModel.solver()));
    printf("Solution for e0s9 : %g\n", model.getSolutionValue(e0s9, *cbcModel.solver()));

    printf("Solution for e1s0 : %g\n", model.getSolutionValue(e1s0, *cbcModel.solver()));
    printf("Solution for e1s1 : %g\n", model.getSolutionValue(e1s1, *cbcModel.solver()));
    printf("Solution for e1s2 : %g\n", model.getSolutionValue(e1s2, *cbcModel.solver()));
    printf("Solution for e1s3 : %g\n", model.getSolutionValue(e1s3, *cbcModel.solver()));        
    printf("Solution for e1s4 : %g\n", model.getSolutionValue(e1s4, *cbcModel.solver()));
    printf("Solution for e1s5 : %g\n", model.getSolutionValue(e1s5, *cbcModel.solver()));
    printf("Solution for e1s6 : %g\n", model.getSolutionValue(e1s6, *cbcModel.solver()));
    printf("Solution for e1s7 : %g\n", model.getSolutionValue(e1s7, *cbcModel.solver()));
    printf("Solution for e1s8 : %g\n", model.getSolutionValue(e1s8, *cbcModel.solver()));
    printf("Solution for e1s9 : %g\n", model.getSolutionValue(e1s9, *cbcModel.solver()));

    printf("Solution for e2s0 : %g\n", model.getSolutionValue(e2s0, *cbcModel.solver()));
    printf("Solution for e2s1 : %g\n", model.getSolutionValue(e2s1, *cbcModel.solver()));
    printf("Solution for e2s2 : %g\n", model.getSolutionValue(e2s2, *cbcModel.solver()));
    printf("Solution for e2s3 : %g\n", model.getSolutionValue(e2s3, *cbcModel.solver()));        
    printf("Solution for e2s4 : %g\n", model.getSolutionValue(e2s4, *cbcModel.solver()));
    printf("Solution for e2s5 : %g\n", model.getSolutionValue(e2s5, *cbcModel.solver()));
    printf("Solution for e2s6 : %g\n", model.getSolutionValue(e2s6, *cbcModel.solver()));
    printf("Solution for e2s7 : %g\n", model.getSolutionValue(e2s7, *cbcModel.solver()));
    printf("Solution for e2s8 : %g\n", model.getSolutionValue(e2s8, *cbcModel.solver()));
    printf("Solution for e2s9 : %g\n", model.getSolutionValue(e2s9, *cbcModel.solver()));

    printf("Solution for e3s0 : %g\n", model.getSolutionValue(e3s0, *cbcModel.solver()));
    printf("Solution for e3s1 : %g\n", model.getSolutionValue(e3s1, *cbcModel.solver()));
    printf("Solution for e3s2 : %g\n", model.getSolutionValue(e3s2, *cbcModel.solver()));
    printf("Solution for e3s3 : %g\n", model.getSolutionValue(e3s3, *cbcModel.solver()));        
    printf("Solution for e3s4 : %g\n", model.getSolutionValue(e3s4, *cbcModel.solver()));
    printf("Solution for e3s5 : %g\n", model.getSolutionValue(e3s5, *cbcModel.solver()));
    printf("Solution for e3s6 : %g\n", model.getSolutionValue(e3s6, *cbcModel.solver()));
    printf("Solution for e3s7 : %g\n", model.getSolutionValue(e3s7, *cbcModel.solver()));
    printf("Solution for e3s8 : %g\n", model.getSolutionValue(e3s8, *cbcModel.solver()));
    printf("Solution for e3s9 : %g\n", model.getSolutionValue(e3s9, *cbcModel.solver()));

    printf("Solution for e4s0 : %g\n", model.getSolutionValue(e4s0, *cbcModel.solver()));
    printf("Solution for e4s1 : %g\n", model.getSolutionValue(e4s1, *cbcModel.solver()));
    printf("Solution for e4s2 : %g\n", model.getSolutionValue(e4s2, *cbcModel.solver()));
    printf("Solution for e4s3 : %g\n", model.getSolutionValue(e4s3, *cbcModel.solver()));        
    printf("Solution for e4s4 : %g\n", model.getSolutionValue(e4s4, *cbcModel.solver()));
    printf("Solution for e4s5 : %g\n", model.getSolutionValue(e4s5, *cbcModel.solver()));
    printf("Solution for e4s6 : %g\n", model.getSolutionValue(e4s6, *cbcModel.solver()));
    printf("Solution for e4s7 : %g\n", model.getSolutionValue(e4s7, *cbcModel.solver()));
    printf("Solution for e4s8 : %g\n", model.getSolutionValue(e4s8, *cbcModel.solver()));
    printf("Solution for e4s9 : %g\n", model.getSolutionValue(e4s9, *cbcModel.solver()));

    printf("Solution for e5s0 : %g\n", model.getSolutionValue(e5s0, *cbcModel.solver()));
    printf("Solution for e5s1 : %g\n", model.getSolutionValue(e5s1, *cbcModel.solver()));
    printf("Solution for e5s2 : %g\n", model.getSolutionValue(e5s2, *cbcModel.solver()));
    printf("Solution for e5s3 : %g\n", model.getSolutionValue(e5s3, *cbcModel.solver()));        
    printf("Solution for e5s4 : %g\n", model.getSolutionValue(e5s4, *cbcModel.solver()));
    printf("Solution for e5s5 : %g\n", model.getSolutionValue(e5s5, *cbcModel.solver()));
    printf("Solution for e5s6 : %g\n", model.getSolutionValue(e5s6, *cbcModel.solver()));
    printf("Solution for e5s7 : %g\n", model.getSolutionValue(e5s7, *cbcModel.solver()));
    printf("Solution for e5s8 : %g\n", model.getSolutionValue(e5s8, *cbcModel.solver()));
    printf("Solution for e5s9 : %g\n", model.getSolutionValue(e5s9, *cbcModel.solver()));

    printf("Solution for e6s0 : %g\n", model.getSolutionValue(e6s0, *cbcModel.solver()));
    printf("Solution for e6s1 : %g\n", model.getSolutionValue(e6s1, *cbcModel.solver()));
    printf("Solution for e6s2 : %g\n", model.getSolutionValue(e6s2, *cbcModel.solver()));
    printf("Solution for e6s3 : %g\n", model.getSolutionValue(e6s3, *cbcModel.solver()));        
    printf("Solution for e6s4 : %g\n", model.getSolutionValue(e6s4, *cbcModel.solver()));
    printf("Solution for e6s5 : %g\n", model.getSolutionValue(e6s5, *cbcModel.solver()));
    printf("Solution for e6s6 : %g\n", model.getSolutionValue(e6s6, *cbcModel.solver()));
    printf("Solution for e6s7 : %g\n", model.getSolutionValue(e6s7, *cbcModel.solver()));
    printf("Solution for e6s8 : %g\n", model.getSolutionValue(e6s8, *cbcModel.solver()));
    printf("Solution for e6s9 : %g\n", model.getSolutionValue(e6s9, *cbcModel.solver()));

    printf("Solution for e7s0 : %g\n", model.getSolutionValue(e7s0, *cbcModel.solver()));
    printf("Solution for e7s1 : %g\n", model.getSolutionValue(e7s1, *cbcModel.solver()));
    printf("Solution for e7s2 : %g\n", model.getSolutionValue(e7s2, *cbcModel.solver()));
    printf("Solution for e7s3 : %g\n", model.getSolutionValue(e7s3, *cbcModel.solver()));        
    printf("Solution for e7s4 : %g\n", model.getSolutionValue(e7s4, *cbcModel.solver()));
    printf("Solution for e7s5 : %g\n", model.getSolutionValue(e7s5, *cbcModel.solver()));
    printf("Solution for e7s6 : %g\n", model.getSolutionValue(e7s6, *cbcModel.solver()));
    printf("Solution for e7s7 : %g\n", model.getSolutionValue(e7s7, *cbcModel.solver()));
    printf("Solution for e7s8 : %g\n", model.getSolutionValue(e7s8, *cbcModel.solver()));
    printf("Solution for e7s9 : %g\n", model.getSolutionValue(e7s9, *cbcModel.solver()));

    printf("Solution for e8s0 : %g\n", model.getSolutionValue(e8s0, *cbcModel.solver()));
    printf("Solution for e8s1 : %g\n", model.getSolutionValue(e8s1, *cbcModel.solver()));
    printf("Solution for e8s2 : %g\n", model.getSolutionValue(e8s2, *cbcModel.solver()));
    printf("Solution for e8s3 : %g\n", model.getSolutionValue(e8s3, *cbcModel.solver()));        
    printf("Solution for e8s4 : %g\n", model.getSolutionValue(e8s4, *cbcModel.solver()));
    printf("Solution for e8s5 : %g\n", model.getSolutionValue(e8s5, *cbcModel.solver()));
    printf("Solution for e8s6 : %g\n", model.getSolutionValue(e8s6, *cbcModel.solver()));
    printf("Solution for e8s7 : %g\n", model.getSolutionValue(e8s7, *cbcModel.solver()));
    printf("Solution for e8s8 : %g\n", model.getSolutionValue(e8s8, *cbcModel.solver()));
    printf("Solution for e8s9 : %g\n", model.getSolutionValue(e8s9, *cbcModel.solver()));

    printf("Solution for e9s0 : %g\n", model.getSolutionValue(e9s0, *cbcModel.solver()));
    printf("Solution for e9s1 : %g\n", model.getSolutionValue(e9s1, *cbcModel.solver()));
    printf("Solution for e9s2 : %g\n", model.getSolutionValue(e9s2, *cbcModel.solver()));
    printf("Solution for e9s3 : %g\n", model.getSolutionValue(e9s3, *cbcModel.solver()));        
    printf("Solution for e9s4 : %g\n", model.getSolutionValue(e9s4, *cbcModel.solver()));
    printf("Solution for e9s5 : %g\n", model.getSolutionValue(e9s5, *cbcModel.solver()));
    printf("Solution for e9s6 : %g\n", model.getSolutionValue(e9s6, *cbcModel.solver()));
    printf("Solution for e9s7 : %g\n", model.getSolutionValue(e9s7, *cbcModel.solver()));
    printf("Solution for e9s8 : %g\n", model.getSolutionValue(e9s8, *cbcModel.solver()));
    printf("Solution for e9s9 : %g\n", model.getSolutionValue(e9s9, *cbcModel.solver()));

    printf("Solution objective value = : %g\n", cbcModel.solver()->getObjValue());

    
}
*/