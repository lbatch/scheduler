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
        int dayOf = start + i;
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

vector<string> getDays()
{
    bool invalid = true;
    int numDays;
    char startDay;
    int sd;
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
        cout << "S(U)nday" << endl;
        cout << "(M)onday" << endl;
        cout << "(T)uesday" << endl;
        cout << "(W)ednesday" << endl;
        cout << "Thu(R)sday" << endl;
        cout << "(F)riday" << endl;
        cout << "(S)aturday" << endl;
        cin >> startDay;

        switch(startDay)
        {
            case 'U': case 'u':
                sd = 0;
                break;
            case 'M': case 'm':
                sd = 1;
                break;
            case 'T': case 't':
                sd = 2;
                break;
            case 'W': case 'w':
                sd = 3;
                break;
            case 'R': case 'r':
                sd = 4;
                break;
            case 'F': case 'f':
                sd = 5;
                break;
            case 'S': case 's':
                sd = 6;
                break;
            default:
                cout <<  "Invalid entry; please try again" << endl;
                sd = -1;
                break;
        }
        if(sd != -1)
        {
            invalid = false;
            days = assignDays(sd, numDays);
            cout << endl;
            return days;
        }
    }
    
}

/* FILE INPUT */
istream& operator>>(istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

vector<Slot> getSlots(vector <string> days)
{
    cout << endl;
    cout << "SLOT FILE UPLOAD: " << endl;
    cout << "Please provide the name of a slot file." << endl;
    cout << "File must be in CSV format; each row must represent one slot." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "Slot ID" << endl;
    cout << "Day, in # of days from start" << endl;
    cout << "Start time: Float, 0-24" << endl;
    cout << "End time: Float, 0-24" << endl;
    cout << "Minimum number of employees required for the slot" << endl;
    cout << "Maximum number of employees allowed for the spot" << endl << endl;

    cout << "File name here: ";

    string slotFile;
    cin.ignore();
    getline(cin, slotFile);

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

    cout << endl;
    f.close();
    return slots;
}

vector<Employee> getConflicts(vector<Employee> emps, vector<Slot> slots)
{
    cout << "CONFLICT FILE UPLOAD: " << endl;
    cout << "Please provide the name of a conflict file." << endl;
    cout << "File must be in CSV format; each row must represent one confict." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "Employee ID" << endl;
    cout << "Day of conflict (0-indexed from first day of schedule)" << endl;
    cout << "Start time of conflict" << endl;
    cout << "End time of conflict" << endl;

    cout << "File name here: ";
    string conflictFile;
    getline(cin, conflictFile);

    ifstream f;
    f.open(conflictFile);
    int empId;
    int day;
    int startTime;
    int endTime;
    int rowInd;

    CSVRow row;

    while(f >> row)
    {
        empId = stoi(row[0]);
        day = stoi(row[1]);
        startTime = stoi(row[2]);
        endTime = stoi(row[3]);

        for(int s = 0; s < slots.size(); s++)
        {
            if(slots[s].getDay() == day && slots[s].getStart() < endTime && slots[s].getEnd() > startTime)
            {
                emps[empId].removeAvailability(s);
            }
        }
    }

    return emps;
}

vector<Employee> getEmployees(vector <Slot> slots, vector<string> days, char availMode)
{
    cout << "EMPLOYEE FILE UPLOAD: " << endl;
    cout << "Please provide the name of an employee file." << endl;
    cout << "File must be in CSV format; each row must represent one employee." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "Employee ID" << endl;
    cout << "Name" << endl;
    cout << "Minimum number of hours to schedule the employee" << endl;
    cout << "Maxmimum number of hours to schedule the employee" << endl;

    if(availMode == 'C' || availMode == 'c')
        cout << endl << "You will then upload a SEPARATE file containing employee conflicts." << endl << endl;
    if(availMode == 'U' || availMode == 'u')
        cout << "One column for each slot ID for which the employee is unavailable" << endl << endl;
    else
        cout << "One column for each slot ID for which the employee is available" << endl << endl;

    cout << "File name here: ";
    string empFile;
    getline(cin, empFile);

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

        if(availMode == 'U' || availMode == 'u')
        {
            int unavail = -1;

            if(row[rowInd].compare("") != 0)
                unavail = stoi(row[rowInd]);

            for(int i = 0; i < slots.size(); i++)
            {
                if(unavail == -1 || i != unavail)
                {
                    emps[e].addAvailability(i);
                }
                else
                {
                    rowInd++;
                    if(row[rowInd].compare("") != 0)
                        unavail = stoi(row[rowInd]);

                }
            }
        }
        else if(availMode == 'C' || availMode == 'c')
        {
            for(int i = 0; i < slots.size(); i++)
            {
                emps[e].addAvailability(i);
            }
        }
        else
        {
            while(rowInd < row.size())
            {
                if(row[rowInd].compare("") != 0)
                {
                    avail = stoi(row[rowInd]);
                    emps[e].addAvailability(avail);
                }
                rowInd++;

            }
        }
        e++;
    }

    if(availMode == 'C' || availMode == 'c')
    {
        vector <Employee> cemps = getConflicts(emps, slots);
        cout << endl;
        f.close();
        return cemps;
    }

    cout << endl;
    f.close();
    return emps;
}

Scheduler input()
{
    cout << "***********************************" << endl;
    cout << "**     EMPLOYEE SCHEDULER        **" << endl;
    cout << "***********************************" << endl;
    cout << endl;
    cout << "Welcome to Employee Scheduler!" << endl << endl;

    vector<string> days = getDays();
    vector <Slot> slots = getSlots(days);

    char availMode;
    cout << "Will your employee file provide slots for which the employee is (A)VAILABLE, slots for which the employee is (U)NAVAILABLE, or a list of (C)onflicts??" << endl;
    cout << "A for an availability file; U for an unavailability/conflict file; C for a list of conflicts: ";
    cin >> availMode;
    cout << availMode;
    cin.ignore();

    vector <Employee> employees = getEmployees(slots, days, availMode);

    string schedName;
    cout << "Please provide a name for your schedule: ";
    cin >> schedName;

    Scheduler scheduler = setUp(schedName, days, slots, employees);

    return scheduler;
}


int main()
{
    Scheduler scheduler = input();

    //scheduler.displayAvailability();

    try{
        scheduler.assignSchedule();
    }   
    catch(char const* msg){
        cout << msg << endl;
        return 1;
    } 
    Schedule schedule = scheduler.getSchedule();
    schedule.writeToFile();   
    return 0;
}