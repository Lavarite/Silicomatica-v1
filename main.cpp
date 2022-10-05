#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Inventory.h"
#include "Player.h"
#include "World.h"
#include "Button.h"
#include "Controller.h"

static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
static const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
static CONSOLE_FONT_INFOEX font;
Controller controller;
POINT mCoord;

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
    if (controller.irInBuf[0].EventType == MOUSE_EVENT) {
        mC->x = controller.irInBuf[0].Event.MouseEvent.dwMousePosition.X;
        mC->y = controller.irInBuf[0].Event.MouseEvent.dwMousePosition.Y;
        controller.LMB = false;
        controller.RMB = false;
        return;
    }
}

void gameLoop(Player &player, World &world) {
    system("cls");
    SetConsoleCursorPosition(hOut, {0, 0});
    vector<Button> inventoryButtons = vector<Button>(9);
    for (int i = 0; i < 9; i++) {
        inventoryButtons[i] = Button{63 + 27 * i, 1, 5, 26};
    }
    while (true) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                inventoryButtons[j].color = 7;
            }
            inventoryButtons[player.selectedSlot].color = 4;
            inventoryButtons[i].itemColor = player.inventory.items[i].color;
            inventoryButtons[i].text = player.inventory.items[i].name;
            inventoryButtons[i].text1 =
                    player.inventory.items[i].symbol + " " + to_string(player.inventory.items[i].quantity);
            inventoryButtons[i].print();
        }
        if (controller.LMB) {
            GetMouseCursorPos(&mCoord);
            for (int i = 0; i < 9; i++) {
                if (inventoryButtons[i].isPressed(mCoord.x, mCoord.y)) {
                    player.selectedSlot = i;
                }
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            system("cls");
            Button back{50, 10, 4, 116, "Back to the game"};
            Button settings{58, 24, 4, 100, "Settings"};
            Button exit{54, 38, 4, 108, "Save & Exit"};
            while (true) {
                back.print();
                settings.print();
                exit.print();
                if (controller.LMB) {
                    GetMouseCursorPos(&mCoord);
                    if (back.isPressed(mCoord.x, mCoord.y)) {
                        system("cls");
                        break;
                    }
                    if (exit.isPressed(mCoord.x, mCoord.y)) {
                        system("cls");
                        world.saveFile();
                        return;
                    }
                }
            }
        } else if (GetAsyncKeyState(VK_UP)) {
            player.setSymbol("^");
        } else if (GetAsyncKeyState(VK_DOWN)) {
            player.setSymbol("v");
        } else if (GetAsyncKeyState(VK_LEFT)) {
            player.setSymbol("<");
        } else if (GetAsyncKeyState(VK_RIGHT)) {
            player.setSymbol(">");
        } else if (GetAsyncKeyState(0x57)) {
            player.moveUp(world.getMap());
        } else if (GetAsyncKeyState(0x53)) {
            player.moveDown(world.getMap());
        } else if (GetAsyncKeyState(0x44)) {
            player.moveRight(world.getMap());
        } else if (GetAsyncKeyState(0x41)) {
            player.moveLeft(world.getMap());
        } else if (GetAsyncKeyState(0x31)) {
            player.selectedSlot = 0;
        } else if (GetAsyncKeyState(0x32)) {
            player.selectedSlot = 1;
        } else if (GetAsyncKeyState(0x33)) {
            player.selectedSlot = 2;
        } else if (GetAsyncKeyState(0x34)) {
            player.selectedSlot = 3;
        } else if (GetAsyncKeyState(0x35)) {
            player.selectedSlot = 4;
        } else if (GetAsyncKeyState(0x36)) {
            player.selectedSlot = 5;
        } else if (GetAsyncKeyState(0x37)) {
            player.selectedSlot = 6;
        } else if (GetAsyncKeyState(0x38)) {
            player.selectedSlot = 7;
        } else if (GetAsyncKeyState(0x39)) {
            player.selectedSlot = 8;
        } else if (GetAsyncKeyState(0x30)) {
            player.selectedSlot = 9;
        }
        SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
        SetConsoleCursorPosition(hOut, {0, 0});
        world.updatePlayer(player);
        world.printMap(player);
        clearKeyboardBuffer();
    }
}

void loadWorld() {
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
        Button b{50, (int) (10 + worlds.size() * 3), 3, 50,
                 entry.path().filename().string().substr(0, entry.path().filename().string().size() - 4)};
        worlds.push_back(b);
    }
    while (true) {
        SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
        clearKeyboardBuffer();
        for (int i = 0; i < worlds.size(); i++) {
            worlds[i].print();
        }
        returnToMenu.print();
        if (controller.LMB) {
            clearKeyboardBuffer();
            GetMouseCursorPos(&mCoord);
            for (int i = 0; i < worlds.size(); i++) {
                if (worlds[i].isPressed(mCoord.x, mCoord.y)) {
                    World world;
                    string dir = "../saves/" + worlds[i].text + ".txt";
                    world.loadFile(dir);
                    Player player;
                    system("cls");
                    Button ign{100, 10, 5, 40, "IGN: "}, color{100, 20, 5, 40, "Color: "};
                    Button load = {100, 30, 5, 40, "Load"};
                    bool ignBool = false;
                    bool colorBool = false;
                    while (true) {
                        SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
                        ign.text = "IGN: " + player.name;
                        color.text = "Color: " + to_string(player.color);
                        ign.print();
                        color.print();
                        load.print();
                        if (ignBool) {
                            int c = _getch();
                            if (c != 0) {
                                if (c == 13) {
                                    ignBool = false;
                                } else if (c == 8) {
                                    if (player.name.size() > 0) {
                                        player.name.pop_back();
                                    }
                                } else {
                                    if (player.name.size() < 31) player.name = player.name + (char) c;
                                }
                            }
                            clearKeyboardBuffer();
                        }
                        if (colorBool) {
                            int c = _getch();
                            if (c != 0) {
                                if (c == 13) {
                                    colorBool = false;
                                } else if (c == 8) {
                                    player.color = player.color / 10;
                                } else if (c >= 48 && c <= 57) {
                                    if (player.color * 10 + (c - 48) >= 32) player.color = 32;
                                    else player.color = player.color * 10 + (c - 48);
                                }
                            }
                            clearKeyboardBuffer();
                        }
                        if (controller.LMB) {
                            clearKeyboardBuffer();
                            GetMouseCursorPos(&mCoord);
                            if (ign.isPressed(mCoord.x, mCoord.y)) {
                                ignBool = true;
                                colorBool = false;
                            }
                            if (color.isPressed(mCoord.x, mCoord.y)) {
                                colorBool = true;
                                ignBool = false;
                            }
                            if (load.isPressed(mCoord.x, mCoord.y)) {
                                system("cls");
                                break;
                            }
                        }
                    }
                    if (player.name.empty()) player.name = "Player";
                    if (world.findPlayer(player.name) != -1) {
                        player = world.players[world.findPlayer(player.name)];
                        if (player.color != 0)
                            world.players[world.findPlayer(player.name)].color = player.color;
                    } else {
                        world.addPlayer(player);
                    }
                    gameLoop(player, world);
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

void createWorld() {
    clearKeyboardBuffer();
    bool Name = false;
    bool Seed = false;
    bool Size = false;
    system("cls");
    World world;
    world.seed = 0;
    world.size = 100;
    Player player;
    Button name{50, 10, 5, 40, "Name: "}, size{50, 20, 5, 40, "Size: 100x100"};
    Button seed{50, 30, 5, 40, "Seed: 0"}, returnToMenu{100, 40, 5, 40, "Return to menu"};
    Button create{50, 40, 5, 40, "Next"};
    while (true) {
        SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
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
        if (controller.LMB) {
            clearKeyboardBuffer();
            GetMouseCursorPos(&mCoord);
            if (returnToMenu.isPressed(mCoord.x, mCoord.y)) {
                system("cls");
                break;
            }
            if (name.isPressed(mCoord.x, mCoord.y)) {
                Name = true;
                Size = false;
                Seed = false;
            }
            if (size.isPressed(mCoord.x, mCoord.y)) {
                Name = false;
                Size = true;
                Seed = false;
            }
            if (seed.isPressed(mCoord.x, mCoord.y)) {
                Name = false;
                Size = false;
                Seed = true;
            }
            if (create.isPressed(mCoord.x, mCoord.y)) {
                system("cls");
                Button ign{200, 10, 5, 40, "IGN: "}, color{200, 20, 5, 40, "Color: "};
                create = {200, 30, 5, 40, "Create"};
                bool ignBool = false;
                bool colorBool = false;
                while (true) {
                    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
                    ign.text = "IGN: " + player.name;
                    color.text = "Color: " + to_string(player.color);
                    ign.print();
                    color.print();
                    create.print();
                    if (ignBool) {
                        int c = _getch();
                        if (c != 0) {
                            if (c == 13) {
                                ignBool = false;
                            } else if (c == 8) {
                                if (player.name.size() > 0) {
                                    player.name.pop_back();
                                }
                            } else {
                                if (player.name.size() < 31) player.name = player.name + (char) c;
                            }
                        }
                        clearKeyboardBuffer();
                    }
                    if (colorBool) {
                        int c = _getch();
                        if (c != 0) {
                            if (c == 13) {
                                colorBool = false;
                            } else if (c == 8) {
                                player.color = player.color / 10;
                            } else if (c >= 48 && c <= 57) {
                                if (player.color * 10 + (c - 48) >= 32) player.color = 32;
                                else player.color = player.color * 10 + (c - 48);
                            }
                        }
                        clearKeyboardBuffer();
                    }
                    if (controller.LMB) {
                        clearKeyboardBuffer();
                        GetMouseCursorPos(&mCoord);
                        if (ign.isPressed(mCoord.x, mCoord.y)) {
                            ignBool = true;
                            colorBool = false;
                        }
                        if (color.isPressed(mCoord.x, mCoord.y)) {
                            colorBool = true;
                            ignBool = false;
                        }
                        if (create.isPressed(mCoord.x, mCoord.y)) {
                            system("cls");
                            break;
                        }
                    }
                }
                if (world.name.empty()) world.name = "World";
                if (player.name.empty()) player.name = "Player";
                world.addPlayer(player);
                world.generate(world.getSeed());
                gameLoop(player, world);
                break;
            }
        }
    }
}

int main() {
    font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hOut, 0, &font);
    font.FontWeight = 700;
    font.dwFontSize.X = 10;
    font.dwFontSize.Y = 10;
    wcscpy(font.FaceName, L"Cascadia Code");
    SetCurrentConsoleFontEx(hOut, 0, &font);

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleCP(437);
    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    SetCurrentConsoleFontEx(hOut, 0, &font);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    set_cursor(false);


    Button newWorld{10, 10, 5, 20, "New World"}, load{10, 20, 5, 20, "Load World"};
    Button settings{10, 30, 5, 20, "Settings"}, exit{10, 40, 5, 20, "Exit"};
    while (true) {
        SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
        clearKeyboardBuffer();
        newWorld.print();
        load.print();
        settings.print();
        exit.print();
        if (controller.LMB) {
            GetMouseCursorPos(&mCoord);
            if (exit.isPressed(mCoord.x, mCoord.y)) {
                system("cls");
                Button yes{58, 24, 5, 100, "Yes"}, no{58, 48, 5, 100, "No"}, areyousure{93, 10, 3, 32,
                                                                                        "Are you sure you want to exit?"};
                yes.print();
                no.print();
                areyousure.print();
                clearKeyboardBuffer();
                while (true) {
                    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
                    if (controller.LMB) {
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
                createWorld();
            }
            if (load.isPressed(mCoord.x, mCoord.y)) {
                loadWorld();
            }
        }
    }
}

