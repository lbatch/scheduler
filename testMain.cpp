#include "Slot.h"
#include "Employee.h"
#include "Schedule.h"
#include "Scheduler.h"

vector<Slot> getSlots(vector <string> days)
{
    int startTime;
    int endTime;
    int ePerS;
    int slotId = 0;

    vector<Slot> slots;
    cout << "Currently, all days must have the same scheduler with the same number of one-hour slots." << endl << endl;
    cout << "What is the start time of your daily schedule? ";
    cin >> startTime;

    cout << "What is the end time of your daily schedule? ";
    cin >> endTime;

    cout << "How many employees do you need for each slot? ";
    cin >> ePerS;

    for(int d = 0; d < days.size(); d++)
    {
        for(int t = startTime; t < endTime; t++)
        {
            slots.push_back(Slot(slotId, d, t, t+1, ePerS, ePerS));
            slotId++;
        }
    }

    return slots;
}

vector<Employee> getEmployees(vector <Slot> slots, vector<string> days)
{
    vector <Employee> emps;
    int numEmps;
    int empId = 0;
    string name;
    int minHrs;
    int maxHrs;
    char resp;

    cout << "How many employees do you want to add? ";
    cin >> numEmps;
    cout << endl;

    for(int e = 0; e < numEmps; e++)
    {
        cout << "Next employee..." << endl;
        cout << "What is the employee's name? ";
        cin.ignore();
        getline(cin, name);
        cout << "Name is: " << name << endl;
        cout << "What is the minimum number of hours you want to schedule " << name << " for? ";
        cin >> minHrs;
        cout << "What is the maximum number of hours you want to schedule " << name << " for? ";
        cin >> maxHrs;

        emps.push_back(Employee(empId, name, minHrs, maxHrs, slots.size()));

        for(int s = 0; s < slots.size(); s++)
        {
            cout << "Is the employee available on "
                << days[slots[s].getDay()] << " from "
                << slots[s].getStart() << ":00 to "
                << slots[s].getEnd() <<  ":00? " 
                << "Type Y for yes, N for no: ";

            cin.ignore();
            cin >> resp;

            switch(resp)
            {
                case 'Y': case 'y':
                    emps[e].addAvailability(slots[s].getId());
                    break;
                case 'N': case 'n':
                    break;
                default:
                    break;
            }
        }
        empId++;   
        cout << endl;
    }

    return emps;
}

Scheduler setUp(string name, vector<string> days, vector<Slot> slots, vector <Employee> emps) {
    Schedule schedule(0, name, days, slots);
    Scheduler scheduler(schedule, emps);

    return scheduler;
}


vector<string> assignDays(int start, int num)
{
    vector<string> days;
    string week[7] = {"Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday"};

    for(int i = 0; i < num; i++)
    {
        int dayOf = start + i -1;
        if(dayOf > 6)
        {
            dayOf = dayOf % 7;
        }

        days.push_back(week[dayOf]);
    }

    return days;
}

vector<string> getDays()
{
    bool invalid = true;
    int numDays;
    int startDay;
    vector<string> days;

    while(invalid)
    {
        cout << "How many days are there on your schedule (up to 7)? ";
        cin >> numDays;
        if(numDays < 1 || numDays > 7)
        {
            cout <<  "Invalid choice; please try again" << endl;
        }
        else invalid = false;
    }

    cout << endl;
    invalid = true;

    while(invalid)
    {
        cout << "On what day does your schedule start?" << endl;
        cout << "1: Sunday" << endl;
        cout << "2: Monday" << endl;
        cout << "3: Tuesday" << endl;
        cout << "4: Wednesday" << endl;
        cout << "5: Thursday" << endl;
        cout << "6: Friday" << endl;
        cout << "7: Saturday" << endl;
        cin >> startDay;

        if(startDay < 1 || startDay > 7)
        {
            cout <<  "Invalid choice; please try again" << endl;
        }
        else
        {
            invalid = false;
            days = assignDays(startDay, numDays);
            cout << endl;
            return days;
        }
    }
    
}

Scheduler input()
{
    cout << "Welcome to Employee Scheduler!" << endl << endl;

    vector<string> days = getDays();
    vector <Slot> slots = getSlots(days);
    vector <Employee> employees = getEmployees(slots, days);

    Scheduler scheduler = setUp("Schedule", days, slots, employees);

    return scheduler;
    
}

int main()
{
    Scheduler scheduler = input();

    scheduler.assignSchedule();

    Schedule schedule = scheduler.getSchedule();
    schedule.display();   

}