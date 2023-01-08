#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALCRUSHER_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALCRUSHER_H

#include <utility>

#include "Block.h"

class MechanicalCrusher : public Block {
public:

    void interact(Inventory *inventory, int *selectedSlot, Controller *controller) override {
        system("cls");
        cout << "Crusher";
        getch();
    };
};


#endif
