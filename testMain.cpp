#include "Slot.h"
#include "Employee.h"

int main()
{
    Slot s1(1, 1.5, 3.0, 1, 2, 3);
    s1.addToSlot(2);
    s1.addToSlot(3);
    s1.displayEmployees();
    s1.removeFromSlot(2);
    s1.displayEmployees();

    Slot s2(2, 3.0, 6.0, 1, 2, 3);

    Employee e(1, "Lydia", 2, 4);
    e.addAvailability(1);
    e.addAvailability(2);
    e.addAssigned(2);
    e.addAssigned(1);
    e.removeAssigned(1);
    e.displaySchedule();

}