#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_PLAYER_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_PLAYER_H

#include <iostream>
#include <string>
#include "Inventory.h"
#include "Button.h"
#include "Block.h"

class Player {
public:
    Inventory inventory;
    string name = "";
    int color = 7;
    string symbol = "^";
    int x = 20;
    int y = 20;
    int selectedSlot = 0;

    Inventory getInventory() { return inventory; };

    string getName() { return name; };

    string getSymbol() { return symbol; };

    int getX() { return x; };

    int getY() { return y; };

    int getColor() { return color; };

    int getSelectedSlot() { return selectedSlot; };

    void setInventory(Inventory inventory) { this->inventory = inventory; };

    void setName(string name) { this->name = name; };

    void setSymbol(string symbol) { this->symbol = symbol; };

    void setX(int x) { this->x = x; };

    void setY(int y) { this->y = y; };

    void setSelectedSlot(int selectedSlot) { this->selectedSlot = selectedSlot; };

    void setColor(int color) { this->color = color; };

    bool moveUp(vector<vector<Block>> map) {
        if (y == 0) {
            return false;
        }
        if (map[y - 1][x].isTransparent()) {
            y--;
            symbol = "^";
            return true;
        }
        symbol = "^";
        return false;
    };

    bool moveDown(vector<vector<Block>> map) {
        if (y == map.size() - 1) {
            return false;
        }
        if (map[y + 1][x].isTransparent()) {
            y++;
            symbol = "v";
            return true;
        }
        symbol = "v";
        return false;
    };

    bool moveRight(vector<vector<Block>> map) {
        if (x == map[0].size() - 1) {
            return false;
        }
        if (map[y][x + 1].isTransparent()) {
            x++;
            symbol = ">";
            return true;
        }
        symbol = ">";
        return false;
    };

    bool moveLeft(vector<vector<Block>> map) {
        if (x == 0) {
            return false;
        }
        if (map[y][x - 1].isTransparent()) {
            x--;
            symbol = "<";
            return true;
        }
        symbol = "<";
        return false;
    };
};

#endif
