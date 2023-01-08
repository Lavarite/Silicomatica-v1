#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALSIEVE_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALSIEVE_H

#include "Block.h"
#include "Material.h"

class MechanicalSieve : public Block {
public:

    void interact(Inventory *inventory, int *selectedSlot, Controller *controller) override {
        system("cls");
        cout << "Sieve";
        getch();
    };
};

#endif
