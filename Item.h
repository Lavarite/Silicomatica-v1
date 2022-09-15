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
    string getName(){return name;};
    int getQuantity(){return quantity;};
    string getType(){return type;};
    string getSymbol(){return symbol;};
    void setName(string name){this->name = name;};
    void setQuantity(int quantity){this->quantity = quantity;};
    void setType(string type){this->type = type;};
    void setSymbol(string symbol){this->symbol = symbol;};
};
#endif
