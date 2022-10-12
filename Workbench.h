//
// Created by avary on 10/6/2022.
//

#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORKBENCH_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORKBENCH_H

#include "Block.h"
#include "Item.h"

using namespace std;

class Workbench : public Block {
public:
    vector<vector<Item>> grid = vector<vector<Item>>(3, vector<Item>(3));

    void interact() override {
        system("cls");
        cout << "Workbench";
        getch();
    };

};

#endif //TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORKBENCH_H
