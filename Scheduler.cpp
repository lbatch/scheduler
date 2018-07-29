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

}
