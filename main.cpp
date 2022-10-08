#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <memory>
#include "Inventory.h"
#include "Player.h"
#include "World.h"
#include "Button.h"
#include "Controller.h"
#include "Material.h"

#define LMB controller.irInBuf[0].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
#define RMB controller.irInBuf[0].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED
#define KEY_DOWN controller.irInBuf[0].Event.KeyEvent.wVirtualKeyCode
#define KEY_EXACT controller.irInBuf[0].Event.KeyEvent.uChar.AsciiChar

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
        return;
    }
}


void gameLoop(Player &player, World &world) {
    POINT mapCoord;
    system("cls");
    SetConsoleCursorPosition(hOut, {0, 0});
    vector<Button> inventoryButtons = vector<Button>(9);
    Button back{50, 10, 4, 116, "Back to the game"};
    Button settings{58, 24, 4, 100, "Settings"};
    Button exit{54, 38, 4, 108, "Save & Exit"};
    for (int i = 0; i < 9; i++) {
        inventoryButtons[i] = Button{63 + 27 * i, 1, 5, 26};
    }
    while (true) {
        for (int i = 0; i < 9; i++) {
            inventoryButtons[i].color = 7;
        }
        for (int i = 0; i < 9; i++) {
            inventoryButtons[player.selectedSlot].color = 4;
            inventoryButtons[i].itemColor = player.inventory.items[i].color;
            inventoryButtons[i].text = player.inventory.items[i].name;
            inventoryButtons[i].text1 =
                    player.inventory.items[i].symbol + " " + to_string(player.inventory.items[i].quantity);
            inventoryButtons[i].print();
        }
        if (LMB) {
            GetMouseCursorPos(&mCoord);
            for (int i = 0; i < 9; i++) {
                if (inventoryButtons[i].isPressed(mCoord.x, mCoord.y)) {
                    player.selectedSlot = i;
                }
            }
            if (mCoord.x < 61 && mCoord.y > 0 && mCoord.y < 32) {
                mapCoord.x = mCoord.x / 2 + mCoord.x % 2 - 15;
                mapCoord.y = mCoord.y - 16;
                if (mapCoord.x + player.x < world.size && mapCoord.x + player.x >= 0 &&
                    mapCoord.y + player.y < world.size &&
                    mapCoord.y + player.y >= 0) {
                    mapCoord.x += player.x;
                    mapCoord.y += player.y;
                    if (world.map[mapCoord.y][mapCoord.x]->type != "Gas") {
                        player.inventory.addItem(Material::Items::get(world.map[mapCoord.y][mapCoord.x]->drop));
                        world.setBlock(mapCoord.y, mapCoord.x, Material::Blocks::AIR);
                    }
                }
            }
        }
        if (RMB) {
            GetMouseCursorPos(&mCoord);
            if (mCoord.x < 61 && mCoord.y > 0 && mCoord.y < 32) {
                mapCoord.x = mCoord.x / 2 + mCoord.x % 2 - 15;
                mapCoord.y = mCoord.y - 16;
                if (mapCoord.x + player.x < world.size && mapCoord.x + player.x >= 0 &&
                    mapCoord.y + player.y < world.size &&
                    mapCoord.y + player.y >= 0) {
                    mapCoord.x += player.x;
                    mapCoord.y += player.y;
                    if (world.map[mapCoord.y][mapCoord.x]->interactable) {
                        if (GetAsyncKeyState(VK_SHIFT)) {
                            if (world.map[mapCoord.y][mapCoord.x]->isTransparent() &&
                                player.inventory.items[player.selectedSlot].type == "block") {
                                world.setBlock(mapCoord.y, mapCoord.x,
                                               player.inventory.items[player.selectedSlot].symbol);
                                player.inventory.removeItem(player.inventory.items[player.selectedSlot], 1);
                            }
                        } else {
                            world.map[mapCoord.y][mapCoord.x]->interact();
                        }
                    } else if (world.map[mapCoord.y][mapCoord.x]->isTransparent() &&
                               player.inventory.items[player.selectedSlot].type == "block") {

                        world.setBlock(mapCoord.y, mapCoord.x,
                                       player.inventory.items[player.selectedSlot].symbol);
                        player.inventory.removeItem(player.inventory.items[player.selectedSlot], 1);
                    }
                }
            }
        }
        switch (KEY_DOWN) {
            case VK_ESCAPE:
                system("cls");
                while (true) {
                    back.print();
                    settings.print();
                    exit.print();
                    if (LMB) {
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
                break;
        }
        if (GetAsyncKeyState(0x57)) {
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
        }
        SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
        SetConsoleCursorPosition(hOut, {0, 0});
        world.updatePlayer(player);
        world.printMap(player);

    }
}


void loadWorld() {
    system("cls");
    string path = "saves";
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

        for (int i = 0; i < worlds.size(); i++) {
            worlds[i].print();
        }
        returnToMenu.print();
        if (LMB) {

            GetMouseCursorPos(&mCoord);
            for (int i = 0; i < worlds.size(); i++) {
                if (worlds[i].isPressed(mCoord.x, mCoord.y)) {
                    World world;
                    string dir = "saves/" + worlds[i].text + ".txt";
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
                        if (LMB) {

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
                        if (ignBool) {
                            if (GetAsyncKeyState(KEY_DOWN) < 0)KEY_DOWN = 0;
                            if (KEY_DOWN) {
                                if (KEY_DOWN == 13) {
                                    ignBool = false;
                                } else if (KEY_DOWN == 8) {
                                    if (!player.name.empty()) {
                                        player.name.pop_back();
                                    }
                                } else {
                                    if (player.name.size() < 31) player.name = player.name + (char) KEY_EXACT;
                                }
                            }
                            KEY_DOWN = 0;
                        }
                        if (colorBool) {
                            if (GetAsyncKeyState(KEY_DOWN) < 0)KEY_DOWN = 0;
                            if (KEY_DOWN) {
                                if (KEY_DOWN == 13) {
                                    colorBool = false;
                                } else if (KEY_DOWN == 8) {
                                    player.color = player.color / 10;
                                } else if (KEY_DOWN >= 48 && KEY_DOWN <= 57) {
                                    if (player.color * 10 + (KEY_DOWN - 48) >= 32) player.color = 32;
                                    else player.color = player.color * 10 + (KEY_DOWN - 48);
                                }
                            }
                            KEY_DOWN = 0;
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

        name.text = "Name: " + world.name;
        size.text = "Size: " + to_string(world.size) + "x" + to_string(world.size);
        seed.text = "Seed: " + to_string(world.seed);
        name.print();
        size.print();
        seed.print();
        returnToMenu.print();
        create.print();
        if (LMB) {

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
                    if (LMB) {
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
                    if (ignBool) {
                        if (GetAsyncKeyState(KEY_DOWN) < 0)KEY_DOWN = 0;
                        if (KEY_DOWN) {
                            if (KEY_DOWN == 13) {
                                ignBool = false;
                            } else if (KEY_DOWN == 8) {
                                if (!player.name.empty()) {
                                    player.name.pop_back();
                                }
                            } else {
                                if (player.name.size() < 31) player.name = player.name + (char) KEY_EXACT;
                            }
                        }
                        KEY_DOWN = 0;

                    }
                    if (colorBool) {
                        if (GetAsyncKeyState(KEY_DOWN) < 0)KEY_DOWN = 0;
                        if (KEY_DOWN) {
                            if (KEY_DOWN == 13) {
                                colorBool = false;
                            } else if (KEY_DOWN == 8) {
                                player.color = player.color / 10;
                            } else if (KEY_DOWN >= 48 && KEY_DOWN <= 57) {
                                if (player.color * 10 + (KEY_DOWN - 48) >= 32) player.color = 32;
                                else player.color = player.color * 10 + (KEY_DOWN - 48);
                            }
                        }
                        KEY_DOWN = 0;

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
        if (Name) {
            if (GetAsyncKeyState(KEY_DOWN) < 0)KEY_DOWN = 0;
            if (KEY_DOWN) {
                if (KEY_DOWN == 13) {
                    Name = false;
                } else if (KEY_DOWN == 8) {
                    if (!world.name.empty()) {
                        world.name.pop_back();
                    }
                } else {
                    if (world.name.size() < 31) world.name = world.name + (char) KEY_EXACT;
                }
            }
            KEY_DOWN = 0;

        }
        if (Size) {
            if (GetAsyncKeyState(KEY_DOWN) < 0)KEY_DOWN = 0;
            if (KEY_DOWN) {
                if (KEY_DOWN == 13) {
                    Size = false;
                } else if (KEY_DOWN == 8) {
                    world.size = world.size / 10;
                } else if (KEY_DOWN >= 48 && KEY_DOWN <= 57) {
                    if (world.size * 10 + (KEY_DOWN - 48) >= 200) world.size = 200;
                    else world.size = world.size * 10 + (KEY_DOWN - 48);
                }
            }
            KEY_DOWN = 0;

        }
        if (Seed) {
            if (GetAsyncKeyState(KEY_DOWN) < 0)KEY_DOWN = 0;
            if (KEY_DOWN) {
                if (KEY_DOWN == 13) {
                    Seed = false;
                } else if (KEY_DOWN == 8) {
                    world.seed = world.seed / 10;
                } else if (KEY_DOWN >= 48 && KEY_DOWN <= 57) {
                    if (world.seed * 10 + KEY_DOWN - 48 > 32767) {
                        world.seed = 32767;
                    } else world.seed = world.seed * 10 + KEY_DOWN - 48;
                }
            }
            KEY_DOWN = 0;
        }

    }
}

int main() {
    Material::init();
    filesystem::create_directory("saves");
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

        newWorld.print();
        load.print();
        settings.print();
        exit.print();
        if (LMB) {
            GetMouseCursorPos(&mCoord);
            if (exit.isPressed(mCoord.x, mCoord.y)) {
                system("cls");
                Button yes{58, 24, 5, 100, "Yes"}, no{58, 48, 5, 100, "No"}, areyousure{93, 10, 3, 32,
                                                                                        "Are you sure you want to exit?"};
                yes.print();
                no.print();
                areyousure.print();

                while (true) {
                    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
                    if (LMB) {
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

