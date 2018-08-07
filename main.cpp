#include "Slot.h"
#include "Employee.h"
#include "Schedule.h"
#include "Scheduler.h"
#include "CSVRow.h"

using std::istream;
using std::stoi;

/* SET UP FUNCTION */

// Configures scheduler for use; constructs schedule and scheduler and returns scheduler
Scheduler setUp(string name, vector<string> days, vector<Slot> slots, vector <Employee> emps) {

    Schedule schedule(0, name, days, slots);
    Scheduler scheduler(schedule, emps);

    return scheduler;
}

/* DAYS OF WEEK */ 

// Assign days to schedule, using start date and number of days provided
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

// Secure user input for start day and number of days
vector<string> getDays()
{
    bool invalid = true;
    int numDays;
    char startDay;
    int sd;
    vector<string> days;

    // Number of days in schedule
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

    // Start day of schedule
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
        cin.ignore();

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

// Read row from csv file
istream& operator>>(istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

// Secure user input of slot file and create slots array
vector<Slot> getSlots(vector <string> days)
{
    string slotFile;
    ifstream f;
    CSVRow row;
    vector<Slot> slots;
    int id;
    int day;
    double start;
    double end;
    int min;
    int max;

    // Retrieve file name
    cout << "SLOT FILE UPLOAD: " << endl;
    cout << "Please provide the name of a slot file." << endl;
    cout << "File must be in CSV format; each row must represent one slot." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "* Slot ID" << endl;
    cout << "* Day, in # of days from start" << endl;
    cout << "* Start time: Float, 0-24" << endl;
    cout << "* End time: Float, 0-24" << endl;
    cout << "* Minimum number of employees required for the slot" << endl;
    cout << "* Maximum number of employees allowed for the spot" << endl << endl;

    cout << "File name here: ";
    getline(cin, slotFile);
    cout << endl;

    f.open(slotFile);

    // For each row in file, create a slot with specified attributes
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

// Secure user input of conflicts file, if applicable, and make changes to employee availability
vector<Employee> getConflicts(vector<Employee> emps, vector<Slot> slots)
{
    string conflictFile;
    ifstream f;
    CSVRow row;
    int empId;
    int day;
    int startTime;
    int endTime;
    int rowInd;

    // Retrieve file name
    cout << "CONFLICT FILE UPLOAD: " << endl;
    cout << "Please provide the name of a conflict file." << endl;
    cout << "File must be in CSV format; each row must represent one confict." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "* Employee ID" << endl;
    cout << "* Day of conflict (0-indexed from first day of schedule)" << endl;
    cout << "* Start time of conflict" << endl;
    cout << "* End time of conflict" << endl << endl;

    cout << "File name here: ";
    getline(cin, conflictFile);
    cout << endl;

    f.open(conflictFile);

    // For each row in file, add a conflict to the appropriate employee
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

// Secure user input of employee file and create emploee  array
vector<Employee> getEmployees(vector <Slot> slots, vector<string> days, char availMode)
{
    string empFile;
    ifstream f;
    CSVRow row;
    char avg_res;
    bool avg;
    int avg_total;
    int avg_min;
    int avg_max;
    int empId;
    string name;
    int minHrs;
    int maxHrs;
    int e = 0;
    int avail;
    int rowInd;

    // -- FILE INPUT -- 
    // Retrieve file name
    cout << "EMPLOYEE FILE UPLOAD: " << endl;
    cout << "Please provide the name of an employee file." << endl;
    cout << "File must be in CSV format; each row must represent one employee." << endl;
    cout << "Columns in each row must be, in order: " << endl << endl;
    cout << "* Employee ID" << endl;
    cout << "* Name" << endl;
    cout << "* Minimum number of hours to schedule the employee" << endl;
    cout << "* Maxmimum number of hours to schedule the employee" << endl;

    // -- OPTIONS --
    // If creating availability info based on a conflict file
    if(availMode == 'C' || availMode == 'c')
    {
        cout << endl << "You will then upload a SEPARATE file containing employee conflicts." << endl << endl;
    }
    // If creating availability info based on unavailable slots listed in employee row
    else if(availMode == 'U' || availMode == 'u')
    {
        cout << "* One column for each slot ID for which the employee is unavailable" << endl << endl;
    }
    // If creating availability info based on available slots listed in employee row
    else
    {
        cout << "* One column for each slot ID for which the employee is available" << endl << endl;
    }

    cout << "File name here: ";
    getline(cin, empFile);
    cout << endl;

    // Determine whether to apply min/max hour deviation from the average
    cout << "Do you want to restrict employees to within 1 hour of the average # of hours?" << endl;
    cout << "If you choose this option, minimum and maximum hours per employee will be set to 1 hour above and below the average." << endl;
    cout << "Bear in mind that this may impact the scheduler's ability to find an optimal solution." << endl << endl;

    cout << "Y for yes, N for no: ";
    cin >> avg_res;
    cin.ignore();
    cout << endl;


    // If applying min/max hour deviation from average, sum up total number of minimum hours in all slots
    if(avg_res == 'Y' || avg_res == 'y')
    {
        avg_total = 0;
        for (int i = 0; i < slots.size(); i++)
        {
            avg_total += slots[i].getMin();
        }
        avg = true;
    }
    else avg = false;

    // -- EMPLOYEE CREATION --
    f.open(empFile);

    vector <Employee> emps;

    // For each row in file, create employee and assign availability
    while(f >> row)
    {
        empId = stoi(row[0]);
        name = row[1];
        minHrs = stoi(row[2]);
        maxHrs = stoi(row[3]);

        emps.push_back(Employee(empId, name, minHrs, maxHrs, slots.size()));

        // If input is unavailability-based, add availability for employee only if they are not unavailable for that slot
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

        // If input is conflict-based, add availability for all slots; conflicts will be resolved with getConflicts
        else if(availMode == 'C' || availMode == 'c')
        {
            for(int i = 0; i < slots.size(); i++)
            {
                emps[e].addAvailability(i);
            }
        }

        // If input is availability-based, add availability only for slots listed as available
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

    // If input is conflict-based, secure conflicts file and remove availability as appropriate
    if(availMode == 'C' || availMode == 'c')
    {
        emps = getConflicts(emps, slots);
    }

    // If constraining each employee to within one hour of average, reset all employee min and max hours based on avg
    if(avg)
    {
        for(int e = 0; e < emps.size(); e++)
        {
            emps[e].setMin(avg_total/emps.size() - 1);
            emps[e].setMax(avg_total/emps.size() + 1);
        }
    }

    f.close();
    return emps;
}

// Secure input from user
Scheduler input()
{
    char availMode;
    vector <Employee> employees;
    string schedName;

    cout << "***********************************" << endl;
    cout << "**     EMPLOYEE SCHEDULER        **" << endl;
    cout << "***********************************" << endl;
    cout << endl;
    cout << "Welcome to Employee Scheduler!" << endl << endl;
    cout << "The program will ask you for a series of csv files detailing the time slots in your schedule and " << endl
        << "the employees available to schedule. It will then attempt to assign an optimal schedule that meets your " << endl
        << "minimum number of employees per time slot, keeps each employee within their minimum and maximum number of hours, " << endl
        << "and does not schedule employees at times for which they are unavailable." << endl;
    cout << "If it is not possible to do so with the slots and employees provided, you will be asked to try again." << endl << endl;
    cout <<  "Let's get started!" << endl;

    cout << endl << "-------------------------------------------------------------" << endl << endl;;

    vector<string> days = getDays();

    cout << endl << "-------------------------------------------------------------" << endl << endl;;

    vector <Slot> slots = getSlots(days);

    cout << endl << "-------------------------------------------------------------" << endl << endl;;

    cout << "Will your employee file(s) provide..." << endl;
    cout << "...slots for which the employee is (A)VAILABLE" << endl;
    cout << "...slots for which the employee is (U)NAVAILABLE" << endl;
    cout << "...a list of (C)onflicts?" << endl << endl;
    cout << "A for an availability file; U for an unavailability/conflict file; C for a list of conflicts: ";
    cin >> availMode;
    cin.ignore();
    cout << endl;

    cout << endl << "-------------------------------------------------------------" << endl << endl;;

    employees = getEmployees(slots, days, availMode);

    cout << endl << "-------------------------------------------------------------" << endl << endl;;

    cout << "Please provide a name for your schedule: ";
    cin >> schedName;
    cin.ignore();
    cout << endl;

    cout << endl << "-------------------------------------------------------------" << endl << endl;;

    Scheduler scheduler = setUp(schedName, days, slots, employees);
    return scheduler;
}


int main()
{
    Scheduler scheduler = input();

    // Used for testing:
    // scheduler.displayAvailability();

    // Catch error when schedule cannot find optimal solution
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
