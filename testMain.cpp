#include "Slot.h"
#include "Employee.h"
#include "Schedule.h"
#include "Scheduler.h"
#include "CSVRow.h"

using std::istream;
using std::stoi;

/* SET UP FUNCTIONS */

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

Scheduler setUp(string name, vector<string> days, vector<Slot> slots, vector <Employee> emps) {
    Schedule schedule(0, name, days, slots);
    Scheduler scheduler(schedule, emps);

    return scheduler;
}

/* TERMINAL INPUT */

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
    int resp;
    int start;
    int end;

    cout << "How many employees do you want to add? ";
    cin >> numEmps;
    cout << endl;

    for(int e = 0; e < numEmps; e++)
    {
        cout << "Next employee..." << endl;
        cout << "What is the employee's name? ";
        cin.ignore();
        getline(cin, name);

        cout << "What is the minimum number of hours you want to schedule " << name << " for? ";
        cin >> minHrs;
        cout << "What is the maximum number of hours you want to schedule " << name << " for? ";
        cin >> maxHrs;

        emps.push_back(Employee(empId, name, minHrs, maxHrs, slots.size()));

        int s = 0;
        while(s < slots.size())
        {
            int currDay = slots[s].getDay();
            cout << "Does the employee have any availability on " << days[currDay] << "? "
            << "1 for yes, 0 for no: ";
            cin >> resp;

            while(resp && slots[s].getDay() == currDay)
            {
                cout << "Enter the start time of this block of availability: ";
                cin >> start;
                cout <<  "Enter the end time of this block of availability: ";
                cin >> end;

                while(slots[s].getEnd() <= end && slots[s].getDay() == currDay)
                {
                    if(slots[s].getStart() >= start)
                    {
                        emps[e].addAvailability(slots[s].getId());
                    }
                    s++;
                }

                cout << "Does the employee have any more availability on " << days[currDay] << "? "
                << "1 for yes, 0 for no: ";
                cin >> resp;
            }
            while(slots[s].getDay() == currDay)
            {
                s++;
            }
        }
        empId++;   
        cout << endl;
    }

    return emps;
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

/* FILE INPUT */
istream& operator>>(istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

vector<Slot> getSlots(vector <string> days, string slotFile)
{
    ifstream f;
    f.open(slotFile);
    int id;
    int day;
    double start;
    double end;
    int min;
    int max;

    CSVRow row;
    vector<Slot> slots;
    while(f >> row)
    {
        id = stoi(row[0]);
        day = stoi(row[1]);
        start = stof(row[2]);
        end = stof(row[3]);
        min = stoi(row[4]);
        max = stoi(row[5]);

        slots.push_back(Slot(id, day, start, end, min, max));
    }

    f.close();
    return slots;
}

vector<Employee> getEmployees(vector <Slot> slots, vector<string> days, string empFile)
{
    ifstream f;
    f.open(empFile);
    vector <Employee> emps;
    int empId;
    string name;
    int minHrs;
    int maxHrs;
    int e = 0;
    int avail;
    int rowInd;

    CSVRow row;

    while(f >> row)
    {
        empId = stoi(row[0]);
        name = row[1];
        minHrs = stoi(row[2]);
        maxHrs = stoi(row[3]);
        emps.push_back(Employee(empId, name, minHrs, maxHrs, slots.size()));

        rowInd = 4;
        while(row[rowInd].compare("") != 0)
        {
            avail = stoi(row[rowInd]);
            emps[e].addAvailability(avail);
            rowInd++;
        }
        cout << endl;
        e++;
    }

    f.close();
    return emps;
}

Scheduler fileInput()
{
    string slotFile;
    string empFile;
    ifstream f;
    cout << "Welcome to Employee Scheduler!" << endl << endl;

    vector<string> days = getDays();

    cout << "Please provide the name of a slot file." << endl;
    cout << "File must be in CSV format; each row must represent one slot." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "Slot ID: 0-indexed and sequential" << endl;
    cout << "Day of the week, where first day of the scheduler is represented as a 0 and each day counts from there" << endl;
    cout << "Start time: In decimal format; eg, 8am is represented as 8; 12:30pm is represented as 12.5; 5:30pm is represented as 17.5" << endl;
    cout << "End time: In decimal format; eg, 8am is represented as 8; 12:30pm is represented as 12.5; 5:30pm is represented as 17.5" << endl;
    cout << "Minimum number of employees required for the slot" << endl;
    cout << "Maximum number of employees allowed for the spot" << endl << endl;

    cout << "File name here: ";
    cin.ignore();
    getline(cin, slotFile);

    vector <Slot> slots = getSlots(days, slotFile);

    cout << "Please provide the name of an employee file." << endl;
    cout << "File must be in CSV format; each row must represent one employee." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "Employee ID: 0-indexed and sequential" << endl;
    cout << "Name of employee" << endl;
    cout << "Minimum number of hours to schedule the employee" << endl;
    cout << "Maxmimum number of hours to schedule the employee" << endl;
    cout << "One column for each slot for which the employee is available, with that slot's id" << endl << endl;

    cout << "File name here: ";
    getline(cin, empFile);

    cout << empFile << endl;
    vector <Employee> employees = getEmployees(slots, days, empFile);

    Scheduler scheduler = setUp("Schedule", days, slots, employees);

    return scheduler;
}


int main()
{
    Scheduler scheduler = fileInput();

    //Scheduler scheduler = input();
    //scheduler.displayAvailability();

    scheduler.assignSchedule();

    Schedule schedule = scheduler.getSchedule();
    schedule.display();   

}