#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_ITEM_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item {
public:
    string name = "";
    int quantity = 0;
    string type = "";
    string symbol = "";
    int color = 7;
    int id = 0;

    string getName() { return name; };

    int getQuantity() { return quantity; };

    string getType() { return type; };

    string getSymbol() { return symbol; };

    void setName(string name) { this->name = name; };

    void setQuantity(int quantity) { this->quantity = quantity; };

    void setType(string type) { this->type = type; };

    void setSymbol(string symbol) { this->symbol = symbol; };
};
namespace Material {
#define WOOD Item{"Wood", 1, "block", "|", 6,1};
#define STONE Item{"Stone", 1, "block", "#", 8,2};
#define WORKBENCH Item{"Workbench", 1, "workbench", "%", 6,3};
#define PICKAXE Item{"Pickaxe", 1, "tool", "⛏", 7,4};
#define AXE Item{"Axe", 1, "tool", "⚒", 7,5};
#define WATER_SCAFFOLDING Item{"Water Scaffolding", 1, "block", "▢", 6,6};
#define MECHANICAL_SIEVE Item{"Mechanical Sieve", 1, "mechanical_sieve", "▩", 6,7};
#define MECHANICAL_CRUSHER Item{"Mechanical Crusher", 1, "mechanical_crusher", "§", 6,8};

    Item get(int ITEM_ID) {
        switch (ITEM_ID) {
            case 1:
                return WOOD;
            case 2:
                return STONE;
            case 3:
                return WORKBENCH;
            case 4:
                return PICKAXE;
            case 5:
                return AXE;
            case 6:
                return WATER_SCAFFOLDING;
            case 7:
                return MECHANICAL_SIEVE;
            case 8:
                return MECHANICAL_CRUSHER;
            default:
                return WOOD;
        }
    }
}
#endif
