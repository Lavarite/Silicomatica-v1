#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_INVENTORY_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_INVENTORY_H

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Inventory {
public:
    int size = 9;
    vector<Item> items = vector<Item>(size);

    void setSize(int size) {
        this->size = size;
        items.resize(size);
    };


    void addItem(Item item) {
        for (int i = 0; i < size; i++) {
            if (items[i].getName() == item.getName()) {
                items[i].setQuantity(items[i].getQuantity() + item.getQuantity());
                return;
            }
        }
        for (int i = 0; i < size; i++) {
            if (items[i].getQuantity() == 0) {
                items[i] = item;
                return;
            }
        }
    };

    void removeItem(Item item, int quantity) {
        item.quantity = quantity;
        for (int i = 0; i < size; i++) {
            if (items[i].getName() == item.getName()) {
                items[i].setQuantity(items[i].getQuantity() - item.getQuantity());
                if (items[i].getQuantity() <= 0) {
                    items[i].setQuantity(0);
                    items[i].setName("");
                    items[i].setType("");
                    items[i].setSymbol("");
                    items[i].id = 0;
                }
                return;
            }
        }
    };

    void moveItem(Item item, Inventory *i) {
        this->removeItem(item, item.quantity);
        i->addItem(item);
    }
};

#endif