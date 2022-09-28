#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_PLAYER_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_PLAYER_H

#include <iostream>
#include <string>
#include "Inventory.h"
#include "Block.h"
#include "Button.h"

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

    void GetMouseCursorPos(POINT *mC) {
        CONSOLE_FONT_INFOEX font;
        font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &font);
        GetCursorPos(mC);
        mC->y = mC->y - 22.5;
        mC->x = mC->x / font.dwFontSize.X;
        mC->y = mC->y / font.dwFontSize.Y;
    }

    bool controller(vector<vector<Block>> map) {
        POINT mCoord;
        GetMouseCursorPos(&mCoord);
        if (GetAsyncKeyState(VK_ESCAPE)) {
            system("cls");
            Button back{50, 10, 4, 116, "Back to the game"};
            Button settings{58, 24, 4, 100, "Settings"};
            Button exit{54, 38, 4, 108, "Exit & Exit"};
            while (true) {
                back.print();
                settings.print();
                exit.print();
                if (GetAsyncKeyState(VK_LBUTTON)) {
                    if (back.isPressed(mCoord.x, mCoord.y)) {
                        system("cls");
                        break;
                    }
                    if (exit.isPressed(mCoord.x, mCoord.y)) {
                        system("cls");
                        Button yes{58, 24, 5, 100, "Yes"}, no{58, 48, 5, 100, "No"}, areyousure{93, 10, 3, 32,
                                                                                                "Are you sure you want to exit?"};
                        yes.print();
                        no.print();
                        areyousure.print();
                        bool confirm = false;
                        while (!confirm) {
                            if (GetAsyncKeyState(VK_LBUTTON)) {
                                GetMouseCursorPos(&mCoord);
                                if (yes.isPressed(mCoord.x, mCoord.y)) {
                                    return true;
                                }
                                if (no.isPressed(mCoord.x, mCoord.y)) {
                                    system("cls");
                                    confirm = true;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        } else if (GetAsyncKeyState(VK_LBUTTON)) {
            GetMouseCursorPos(&mCoord);
            cout << mCoord.x << " " << mCoord.y << endl;
        } else if (GetAsyncKeyState(VK_UP)) {
            this->setSymbol("^");
        } else if (GetAsyncKeyState(VK_DOWN)) {
            this->setSymbol("v");
        } else if (GetAsyncKeyState(VK_LEFT)) {
            this->setSymbol("<");
        } else if (GetAsyncKeyState(VK_RIGHT)) {
            this->setSymbol(">");
        } else if (GetAsyncKeyState(0x57)) {
            this->moveUp(map);
        } else if (GetAsyncKeyState(0x53)) {
            this->moveDown(map);
        } else if (GetAsyncKeyState(0x44)) {
            this->moveRight(map);
        } else if (GetAsyncKeyState(0x41)) {
            this->moveLeft(map);
        }
        return false;
    }
    //}
};

#endif
