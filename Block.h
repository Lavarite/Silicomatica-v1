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
    string symbol = "/";
    string tool = "";
    bool interactable = false;
    int drop = 0;

    string getName() { return name; };

    string getType() { return type; };

    string getSymbol() { return symbol; };

    int getDrop() { return drop; };

    int getColor() { return color; };

    bool isTransparent() { return transparent; };

    string getTool() { return tool; }

    bool isInteractable() { return interactable; };

    void setName(string name) { this->name = name; };

    void setType(string type) { this->type = type; };

    void setSymbol(char symbol) { this->symbol = symbol; };

    void setDrop(int drop) { this->drop = drop; };

    void setTransparent(bool transparent) { this->transparent = transparent; };

    void setTool(string tool) { this->tool = tool; };

    void setColor(int color) { this->color = color; };

    void setInteractable(bool b) { this->interactable = b; };
};


#endif