#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_INVENTORY_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_INVENTORY_H
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Inventory {
public:
    vector<Item> items;
    void addItem(Item item){
        for (int i = 0; i < 9; i++) {
            if (items[i].getName() == item.getName()) {
                items[i].setQuantity(items[i].getQuantity() + item.getQuantity());
                return;
            }
        }
        if (items.size() < 9) {
            items.push_back(item);
        }
    };
    void removeItem(Item item){
        for (int i = 0; i < 9; i++) {
            if (items[i].getName() == item.getName()) {
                items[i].setQuantity(items[i].getQuantity() - item.getQuantity());
                if (items[i].getQuantity() <= 0) {
                    items[i].setQuantity(0);
                    items[i].setName("");
                    items[i].setType("");
                    items[i].setSymbol("");
                }
                return;
            }
        }
    };
};
#endif