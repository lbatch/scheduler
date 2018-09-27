# scheduler
Shift scheduler using C++.

Depending on user settings, uses staff availability and schedule needs to schedule staff members, focusing either on close-to-equitable hours or minimum total person-hours scheduled.

Makes use of the Rehearse linear optimization library to approach the scheduling task as a linear programming problem with a goal of minimizing person-hours scheduled: https://github.com/coin-or/Rehearse
