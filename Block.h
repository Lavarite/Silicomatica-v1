#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_BLOCK_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_BLOCK_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Item.h"
using namespace std;
class Block {
public:
    string name = "";
    string type = "";
    int color = 7;
    bool transparent = true;
    char symbol = ' ';
    string tool = "";
    Item drop;
    string getName(){return name;};
    string getType(){return type;};
    char getSymbol(){return symbol;};
    Item getDrop(){return drop;};
    int getColor(){return color;};
    bool isTransparent(){return transparent;};
    string getTool(){return tool;}
    void setName(string name){this->name = name;};
    void setType(string type){this->type = type;};
    void setSymbol(char symbol){this->symbol = symbol;};
    void setDrop(Item drop){this->drop = drop;};
    void setTransparent(bool transparent){this->transparent = transparent;};
    void setTool(string tool){this->tool = tool;};
    void setColor(int color){this->color = color;};
};



#endif