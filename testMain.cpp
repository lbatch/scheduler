#include "Slot.h"
#include "Employee.h"
#include "Schedule.h"
#include "Scheduler.h"

int main()
{
    Slot s0(0, 1, 2, 1, 2, 3);
    Slot s1(1, 2, 3, 1, 2, 3);
    Slot s2(2, 3, 4, 1, 2, 3);
    Slot s3(3, 4, 5, 1, 2, 3);
    Slot s4(4, 5, 6, 1, 2, 3);
    Slot s5(5, 1, 2, 2, 2, 3);
    Slot s6(6, 2, 3, 2, 2, 3);
    Slot s7(7, 3, 4, 2, 2, 3);
    Slot s8(7, 4, 5, 2, 2, 3);
    Slot s9(7, 5, 6, 2, 2, 3);

    string days[7] = {"Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday"};
    Schedule schedule(0, "Schedule", days);
    schedule.addSlot(s0); 
    schedule.addSlot(s1); 
    schedule.addSlot(s2); 
    schedule.addSlot(s3); 
    schedule.addSlot(s4); 
    schedule.addSlot(s5); 
    schedule.addSlot(s6); 
    schedule.addSlot(s7); 
    schedule.addSlot(s8); 
    schedule.addSlot(s9);

    Employee e0(0, "Lydia", 2, 4);
    e0.addAvailability(0);
    e0.addAvailability(1);
    e0.addAvailability(2);
    e0.addAvailability(3);
    e0.addAvailability(4);
    e0.addAvailability(5);

    Employee e1(1, "Lauren", 2, 4);
    e1.addAvailability(1);
    e1.addAvailability(2);
    e1.addAvailability(3);
    e1.addAvailability(4);
    e1.addAvailability(5);
    e1.addAvailability(6);

    Employee e2(2, "Laurel", 2, 4);
    e2.addAvailability(2);
    e2.addAvailability(3);
    e2.addAvailability(4);
    e2.addAvailability(5);
    e2.addAvailability(6);
    e2.addAvailability(7);

    Employee e3(3, "Brenda", 2, 4);
    e3.addAvailability(3);
    e3.addAvailability(4);
    e3.addAvailability(5);
    e3.addAvailability(6);
    e3.addAvailability(7);
    e3.addAvailability(8);

    Employee e4(4, "Kassie", 2, 4);
    e4.addAvailability(4);
    e4.addAvailability(5);
    e4.addAvailability(6);
    e4.addAvailability(7);
    e4.addAvailability(8);
    e4.addAvailability(9);

    Employee e5(5, "Bessie", 2, 4);
    e5.addAvailability(5);
    e5.addAvailability(6);
    e5.addAvailability(7);
    e5.addAvailability(8);
    e5.addAvailability(9);
    e5.addAvailability(0);

    Employee e6(6, "Jaycie", 2, 4);
    e6.addAvailability(6);
    e6.addAvailability(7);
    e6.addAvailability(8);
    e6.addAvailability(9);
    e6.addAvailability(0);
    e6.addAvailability(1);

    Employee e7(7, "Bayleigh", 2, 4);
    e7.addAvailability(7);
    e7.addAvailability(8);
    e7.addAvailability(9);
    e7.addAvailability(0);
    e7.addAvailability(1);
    e7.addAvailability(2);

    Employee e8(8, "Hannah", 2, 4);
    e8.addAvailability(8);
    e8.addAvailability(9);
    e8.addAvailability(0);
    e8.addAvailability(1);
    e8.addAvailability(2);
    e8.addAvailability(3);

    Employee e9(9, "Hannah", 2, 4);
    e9.addAvailability(9);
    e9.addAvailability(0);
    e9.addAvailability(1);
    e9.addAvailability(2);
    e9.addAvailability(3);
    e9.addAvailability(4);

    Scheduler scheduler(schedule);
    scheduler.addEmployee(e0);
    scheduler.addEmployee(e1);
    scheduler.addEmployee(e2);
    scheduler.addEmployee(e3);
    scheduler.addEmployee(e4);
    scheduler.addEmployee(e5);
    scheduler.addEmployee(e6);
    scheduler.addEmployee(e7);
    scheduler.addEmployee(e8);
    scheduler.addEmployee(e9);

    scheduler.assignSchedule();

    Schedule newSched = scheduler.getSchedule();
    newSched.display();    

}