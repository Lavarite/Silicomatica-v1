#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALCRUSHER_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MECHANICALCRUSHER_H

#include <utility>

#include "Block.h"

class MechanicalCrusher : public Block {
public:
    Item in;
    Item out;

    void interact() override {
        system("cls");
        cout << "Crusher";
        getch();
    };
};


#endif
