#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALSIEVE_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALSIEVE_H

#include "Block.h"
#include "Material.h"

class MechanicalSieve : public Block {
public:
    Item in;
    Item out;

    void interact() override {
        system("cls");
        cout << "Sieve";
        getch();
    };
};

#endif
