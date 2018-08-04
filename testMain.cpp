#include "Slot.h"
#include "Employee.h"
#include "Schedule.h"
#include "Scheduler.h"

vector<Slot> getSlots()
{
    vector<Slot> slots;
    slots.push_back(Slot(0, 1, 2, 1, 2, 3));
    slots.push_back(Slot(1, 2, 3, 1, 2, 3));
    slots.push_back(Slot(2, 3, 4, 1, 2, 3));
    slots.push_back(Slot(3, 4, 5, 1, 2, 3));
    slots.push_back(Slot(4, 5, 6, 1, 2, 3));
    slots.push_back(Slot(5, 1, 2, 2, 2, 3));
    slots.push_back(Slot(6, 2, 3, 2, 2, 3));
    slots.push_back(Slot(7, 3, 4, 2, 2, 3));
    slots.push_back(Slot(8, 4, 5, 2, 2, 3));
    slots.push_back(Slot(9, 5, 6, 2, 2, 3));

    return slots;
}

vector<Employee> getEmployees()
{
    vector<Employee> emps;

    Employee e0(0, "Lydia", 2, 4);
    e0.addAvailability(0);
    e0.addAvailability(1);
    e0.addAvailability(2);
    e0.addAvailability(3);
    e0.addAvailability(4);
    e0.addAvailability(5);
    emps.push_back(e0);

    Employee e1(1, "Lauren", 2, 4);
    e1.addAvailability(1);
    e1.addAvailability(2);
    e1.addAvailability(3);
    e1.addAvailability(4);
    e1.addAvailability(5);
    e1.addAvailability(6);
    emps.push_back(e1);

    Employee e2(2, "Laurel", 2, 4);
    e2.addAvailability(2);
    e2.addAvailability(3);
    e2.addAvailability(4);
    e2.addAvailability(5);
    e2.addAvailability(6);
    e2.addAvailability(7);
    emps.push_back(e2);

    Employee e3(3, "Brenda", 2, 4);
    e3.addAvailability(3);
    e3.addAvailability(4);
    e3.addAvailability(5);
    e3.addAvailability(6);
    e3.addAvailability(7);
    e3.addAvailability(8);
    emps.push_back(e3);

    Employee e4(4, "Kassie", 2, 4);
    e4.addAvailability(4);
    e4.addAvailability(5);
    e4.addAvailability(6);
    e4.addAvailability(7);
    e4.addAvailability(8);
    e4.addAvailability(9);
    emps.push_back(e4);

    Employee e5(5, "Bessie", 2, 4);
    e5.addAvailability(5);
    e5.addAvailability(6);
    e5.addAvailability(7);
    e5.addAvailability(8);
    e5.addAvailability(9);
    e5.addAvailability(0);
    emps.push_back(e5);

    Employee e6(6, "Jaycie", 2, 4);
    e6.addAvailability(6);
    e6.addAvailability(7);
    e6.addAvailability(8);
    e6.addAvailability(9);
    e6.addAvailability(0);
    e6.addAvailability(1);
    emps.push_back(e6);

    Employee e7(7, "Bayleigh", 2, 4);
    e7.addAvailability(7);
    e7.addAvailability(8);
    e7.addAvailability(9);
    e7.addAvailability(0);
    e7.addAvailability(1);
    e7.addAvailability(2);
    emps.push_back(e7);

    Employee e8(8, "Hannah", 2, 4);
    e8.addAvailability(8);
    e8.addAvailability(9);
    e8.addAvailability(0);
    e8.addAvailability(1);
    e8.addAvailability(2);
    e8.addAvailability(3);
    emps.push_back(e8);

    Employee e9(9, "Hannah", 2, 4);
    e9.addAvailability(9);
    e9.addAvailability(0);
    e9.addAvailability(1);
    e9.addAvailability(2);
    e9.addAvailability(3);
    e9.addAvailability(4);
    emps.push_back(e9);

    return emps;
}

Scheduler setUp(string name, string* days, vector<Slot> slots, vector <Employee> emps) {
    Schedule schedule(0, name, days, slots);
    Scheduler scheduler(schedule, emps);

    return scheduler;
}

int main()
{
    string days[7] = {"Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday"};
    
    vector <Slot> slots = getSlots();
    vector <Employee> employees = getEmployees();

    Scheduler scheduler = setUp("Schedule", days, slots, employees);

    scheduler.assignSchedule();

    Schedule schedule = scheduler.getSchedule();
    schedule.display();    

}