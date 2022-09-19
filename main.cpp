#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Inventory.h"
#include "Player.h"
#include "World.h"
#include "Button.h"

static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
static const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
static CONSOLE_FONT_INFOEX font;

void clearKeyboardBuffer() {
    while (_kbhit()) {
        _getche();
    }
}

void set_cursor(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void GetMouseCursorPos(POINT *mC) {
    font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hOut, 0, &font);
    GetCursorPos(mC);
    mC->y = mC->y - 22.5;
    mC->x = mC->x / font.dwFontSize.X;
    mC->y = mC->y / font.dwFontSize.Y;
}

void gameLoop(Player &player, World &world) {
    system("cls");
    SetConsoleCursorPosition(hOut, {0, 0});
    while (!player.controller(world.getMap())) {
        SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
        SetConsoleCursorPosition(hOut, {0, 0});
        world.updatePlayer(player);
        world.printMap(player);
        clearKeyboardBuffer();
    }
    system("cls");
    delete &world;
}

int main() {
    font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hOut, 0, &font);
    font.FontWeight = 700;
    font.dwFontSize.X = 10;
    font.dwFontSize.Y = 10;

    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    SetCurrentConsoleFontEx(hOut, 0, &font);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    set_cursor(false);


    POINT mCoord;
    COORD topLeft = {0, 0};

    Button newWorld, load, settings, exit;
    newWorld.height = 5;
    newWorld.width = 20;
    newWorld.x = 10;
    newWorld.y = 10;
    newWorld.text = "New World";
    load.height = 5;
    load.width = 20;
    load.x = 10;
    load.y = 20;
    load.text = "Load";
    settings.height = 5;
    settings.width = 20;
    settings.x = 10;
    settings.y = 30;
    settings.text = "Settings";
    exit.height = 5;
    exit.width = 20;
    exit.x = 10;
    exit.y = 40;
    exit.text = "Exit";

    while (true) {
        clearKeyboardBuffer();
        newWorld.print();
        load.print();
        settings.print();
        exit.print();
        if (GetAsyncKeyState(VK_LBUTTON)) {
            GetMouseCursorPos(&mCoord);
            if (exit.isPressed(mCoord.x, mCoord.y)) {
                system("cls");
                Button yes, no, areyousure;
                areyousure.height = 3;
                areyousure.width = 32;
                areyousure.x = 93;
                areyousure.y = 10;
                areyousure.text = "Are you sure you want to exit?";
                yes.height = 5;
                yes.width = 100;
                yes.x = 58;
                yes.y = 24;
                yes.text = "Yes";
                no.height = 5;
                no.width = 100;
                no.x = 58;
                no.y = 48;
                no.text = "No";
                yes.print();
                no.print();
                areyousure.print();
                clearKeyboardBuffer();
                while (true) {
                    if (GetAsyncKeyState(VK_LBUTTON)) {
                        GetMouseCursorPos(&mCoord);
                        if (yes.isPressed(mCoord.x, mCoord.y)) {
                            return 0;
                        }
                        if (no.isPressed(mCoord.x, mCoord.y)) {
                            system("cls");
                            break;
                        }
                    }
                }
            }
            if (newWorld.isPressed(mCoord.x, mCoord.y)) {
                clearKeyboardBuffer();
                bool Name = false;
                bool Seed = false;
                bool Size = false;
                system("cls");
                World world;
                world.seed = 0;
                world.size = 100;
                Player player;
                Button name, size, seed, returnToMenu, create;
                name.width = 40;
                name.height = 5;
                name.x = 50;
                name.y = 10;
                name.text = "Name: ";
                size.width = 40;
                size.height = 5;
                size.x = 50;
                size.y = 20;
                size.text = "Size: 100x100";
                seed.width = 40;
                seed.height = 5;
                seed.x = 50;
                seed.y = 30;
                seed.text = "Seed: 0";
                returnToMenu.width = 40;
                returnToMenu.height = 5;
                returnToMenu.x = 100;
                returnToMenu.y = 40;
                returnToMenu.text = "Return to menu";
                create.width = 40;
                create.height = 5;
                create.x = 50;
                create.y = 40;
                create.text = "Create the world";
                while (true) {
                    clearKeyboardBuffer();
                    name.text = "Name: " + world.name;
                    size.text = "Size: " + to_string(world.size) + "x" + to_string(world.size);
                    seed.text = "Seed: " + to_string(world.seed);
                    name.print();
                    size.print();
                    seed.print();
                    returnToMenu.print();
                    create.print();
                    if (Name) {
                        int c = _getch();
                        if (c != 0) {
                            if (c == 13) {
                                Name = false;
                            } else if (c == 8) {
                                if (world.name.size() > 0) {
                                    world.name.pop_back();
                                }
                            } else {
                                if (world.name.size() < 31) world.name = world.name + (char) c;
                            }
                        }
                        clearKeyboardBuffer();
                    }
                    if (Size) {
                        int c = _getch();
                        if (c != 0) {
                            if (c == 13) {
                                Size = false;
                            } else if (c == 8) {
                                world.size = world.size / 10;
                            } else if (c >= 48 && c <= 57) {
                                if (world.size * 10 + (c - 48) >= 200) world.size = 200;
                                else world.size = world.size * 10 + (c - 48);
                            }
                        }
                        clearKeyboardBuffer();
                    }
                    if (Seed) {
                        int c = _getch();
                        if (c != 0) {
                            if (c == 13) {
                                Seed = false;
                            } else if (c == 8) {
                                world.seed = world.seed / 10;
                            } else if (c >= 48 && c <= 57) {
                                if (world.seed * 10 + c - 48 > 32767) {
                                    world.seed = 32767;
                                } else world.seed = world.seed * 10 + c - 48;
                            }
                        }
                        clearKeyboardBuffer();
                    }
                    if (GetAsyncKeyState(VK_LBUTTON)) {
                        clearKeyboardBuffer();
                        GetMouseCursorPos(&mCoord);
                        if (returnToMenu.isPressed(mCoord.x, mCoord.y)) {
                            system("cls");
                            break;
                        }
                        if (name.isPressed(mCoord.x, mCoord.y)) {
                            Name = true;
                        } else {
                            Name = false;
                        }
                        if (size.isPressed(mCoord.x, mCoord.y)) {
                            Size = true;
                        } else {
                            Size = false;
                        }
                        if (seed.isPressed(mCoord.x, mCoord.y)) {
                            Seed = true;
                        } else {
                            Seed = false;
                        }
                        if (create.isPressed(mCoord.x, mCoord.y)) {
                            world.addPlayer(player);
                            world.generate(world.getSeed());
                            gameLoop(player, world);
                            world.saveFile();
                            break;
                        }
                    }
                }
            }
            if (load.isPressed(mCoord.x, mCoord.y)) {
                system("cls");
                string path = "../saves";
                vector<Button> worlds;
                Button returnToMenu;
                returnToMenu.width = 40;
                returnToMenu.height = 5;
                returnToMenu.x = 100;
                returnToMenu.y = 50;
                returnToMenu.text = "Return to menu";
                for (const auto &entry: filesystem::directory_iterator(path)) {
                    Button b;
                    b.setText(entry.path().filename().string().substr(0, entry.path().filename().string().size() - 4));
                    b.x = 50;
                    b.y = 10 + worlds.size() * 3;
                    b.width = 50;
                    b.height = 3;
                    worlds.push_back(b);
                }
                while (true) {
                    clearKeyboardBuffer();
                    for (int i = 0; i < worlds.size(); i++) {
                        worlds[i].print();
                    }
                    returnToMenu.print();
                    if (GetAsyncKeyState(VK_LBUTTON)) {
                        clearKeyboardBuffer();
                        GetMouseCursorPos(&mCoord);
                        for (int i = 0; i < worlds.size(); i++) {
                            if (worlds[i].isPressed(mCoord.x, mCoord.y)) {
                                World world;
                                world.loadFile("../saves/" + worlds[i].text + ".txt");
                                Player player;
                                world.addPlayer(player);
                                gameLoop(world.players[0], world);
                                world.saveFile();
                                break;
                            }
                        }
                        if (returnToMenu.isPressed(mCoord.x, mCoord.y)) {
                            system("cls");
                            break;
                        }
                    }
                }
            }
        }
    }
}

