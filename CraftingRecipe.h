//
// Created by avary on 10/8/2022.
//

#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CRAFTINGRECIPE_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CRAFTINGRECIPE_H

#include "Material.h"

using namespace std;

class CraftingRecipe {
public:
    vector<Item> in;
    vector<Item> out;

    vector<vector<int>> shape;
    bool isShapeless = false;

    void create(vector<Item> in, vector<Item> out, vector<vector<int>> shape, bool isShapeless) {
        this->in = in;
        this->out = out;
        this->shape = shape;
        this->isShapeless = isShapeless;
    }

    virtual bool enoughResources() { return true; };
};

#endif //TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CRAFTINGRECIPE_H
