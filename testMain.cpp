#include "Slot.h"

int main()
{
    Slot s(1, 1.5, 3.0, 1, 2, 3);
    s.addToSlot(2);
    s.addToSlot(3);
    s.displayEmployees();
    s.removeFromSlot(2);
    s.displayEmployees();
}