#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Inventory.h"
#include "Player.h"
#include "World.h"
#include "Button.h"

static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
static const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
static CONSOLE_FONT_INFOEX font;

vector<string> createMap() {
    vector<string> map;
    map.emplace_back(
            "--------------************----------------###############-------------------------------------------");
    map.emplace_back(
            "----------------**********-----------------###########----------------------------------------------");
    map.emplace_back(
            "-------------------*****----------------------####--------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------|||||||||||----------------------------------------------************---------------------");
    map.emplace_back(
            "--------|||||||||||||||||-----------------------------------------********,,*****-------------------");
    map.emplace_back(
            "---------|||||||||||||||||----------------------------------------******,,,,******------------------");
    map.emplace_back(
            "----------||||||||||||||||-----------------------------------------*******,,,******-----------------");
    map.emplace_back(
            "-----------|||||||||||||---------------------------------------------*******,,******----------------");
    map.emplace_back(
            "-------------|||||||||-------------------------------------------------******,******----------------");
    map.emplace_back(
            "---------------|||||-----------------------------------------------------**********-----------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "-----------------------------------*******-----------------------------------------------------#####");
    map.emplace_back(
            "#######-----------------------****************--------------------------------------------##########");
    map.emplace_back(
            "##########-----------------**********************--------------------------------------#############");
    map.emplace_back(
            "--##########-------------*********,,,,,,,,*********---------------------------------############----");
    map.emplace_back(
            "----#########------------*******,,,,,,,,,,,,,********----------------------------#############------");
    map.emplace_back(
            "-----#########-----------*******,,,,,,,,,,,,,,********------------------------###############-------");
    map.emplace_back(
            "---###########-----------********,,,,,,,,,,,,,*********---------------------#####################---");
    map.emplace_back(
            "##############-------------*****************************-------------------#########################");
    map.emplace_back(
            "#############----------------****************************------------------#########################");
    map.emplace_back(
            "-#########-------------------------***********************-----------------#####################----");
    map.emplace_back(
            "------------------------------------------*****************------------------##########-------------");
    map.emplace_back(
            "----------------------------------------------**************----------------------------------------");
    map.emplace_back(
            "-------------------------------------------------************---------------------------------------");
    map.emplace_back(
            "-------------------------------------------------------***--------------|||||-----------------------");
    map.emplace_back(
            "*****-----------------------#########--------------------------------||||||||||---------------******");
    map.emplace_back(
            "**********----------------###############--------------------------||||||||||||||----------*********");
    map.emplace_back(
            ",,,*********--------------###################-----------------------|||||||||||||--------*********,,");
    map.emplace_back(
            ",,,,,,********-------------######################-------------------|||||||||||||||-----********,,,,");
    map.emplace_back(
            ",,,,,,,,********------------##########################----------------||||||||----------*******,,,,,");
    map.emplace_back(
            ",,,,,,,,*********------------##############################--------------|||------------********,,,,");
    map.emplace_back(
            ",,,,,,,***********-------------###############################---------------------------*********,,");
    map.emplace_back(
            "********************--------------#############################---------------------------**********");
    map.emplace_back(
            "*********************---------------###########################------------------------------*******");
    map.emplace_back(
            "------*****************----------------######################---------------------------------------");
    map.emplace_back(
            "--------------************----------------###############-------------------------------------------");
    map.emplace_back(
            "----------------**********-----------------###########----------------------------------------------");
    map.emplace_back(
            "-------------------*****----------------------####--------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------|||||||||||----------------------------------------------************---------------------");
    map.emplace_back(
            "--------|||||||||||||||||-----------------------------------------********,,*****-------------------");
    map.emplace_back(
            "---------|||||||||||||||||----------------------------------------******,,,,******------------------");
    map.emplace_back(
            "----------||||||||||||||||-----------------------------------------*******,,,******-----------------");
    map.emplace_back(
            "-----------|||||||||||||---------------------------------------------*******,,******----------------");
    map.emplace_back(
            "-------------|||||||||-------------------------------------------------******,******----------------");
    map.emplace_back(
            "---------------|||||-----------------------------------------------------**********-----------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "----------------------------------------------------------------------------------------------------");
    map.emplace_back(
            "-----------------------------------*******-----------------------------------------------------#####");
    map.emplace_back(
            "#######-----------------------****************--------------------------------------------##########");
    map.emplace_back(
            "##########-----------------**********************--------------------------------------#############");
    map.emplace_back(
            "--##########-------------*********,,,,,,,,*********---------------------------------############----");
    map.emplace_back(
            "----#########------------*******,,,,,,,,,,,,,********----------------------------#############------");
    map.emplace_back(
            "-----#########-----------*******,,,,,,,,,,,,,,********------------------------###############-------");
    map.emplace_back(
            "---###########-----------********,,,,,,,,,,,,,*********---------------------#####################---");
    map.emplace_back(
            "##############-------------*****************************-------------------#########################");
    map.emplace_back(
            "#############----------------****************************------------------#########################");
    map.emplace_back(
            "-#########-------------------------***********************-----------------#####################----");
    map.emplace_back(
            "------------------------------------------*****************------------------##########-------------");
    map.emplace_back(
            "----------------------------------------------**************----------------------------------------");
    map.emplace_back(
            "-------------------------------------------------************---------------------------------------");
    map.emplace_back(
            "-------------------------------------------------------***--------------|||||-----------------------");
    map.emplace_back(
            "*****-----------------------#########--------------------------------||||||||||---------------******");
    map.emplace_back(
            "**********----------------###############--------------------------||||||||||||||----------*********");
    map.emplace_back(
            ",,,*********--------------###################-----------------------|||||||||||||--------*********,,");
    map.emplace_back(
            ",,,,,,********-------------######################-------------------|||||||||||||||-----********,,,,");
    map.emplace_back(
            ",,,,,,,,********------------##########################----------------||||||||----------*******,,,,,");
    map.emplace_back(
            ",,,,,,,,*********------------##############################--------------|||------------********,,,,");
    map.emplace_back(
            ",,,,,,,***********-------------###############################---------------------------*********,,");
    map.emplace_back(
            "********************--------------#############################---------------------------**********");
    map.emplace_back(
            "*********************---------------###########################------------------------------*******");
    map.emplace_back(
            "------*****************----------------######################---------------------------------------");
    map.emplace_back(
            "----#########------------*******,,,,,,,,,,,,,********----------------------------#############------");
    map.emplace_back(
            "-----#########-----------*******,,,,,,,,,,,,,,********------------------------###############-------");
    map.emplace_back(
            "---###########-----------********,,,,,,,,,,,,,*********---------------------#####################---");
    map.emplace_back(
            "##############-------------*****************************-------------------#########################");
    map.emplace_back(
            "#############----------------****************************------------------#########################");
    map.emplace_back(
            "-#########-------------------------***********************-----------------#####################----");
    map.emplace_back(
            "------------------------------------------*****************------------------##########-------------");
    map.emplace_back(
            "----------------------------------------------**************----------------------------------------");
    map.emplace_back(
            "-------------------------------------------------************---------------------------------------");
    map.emplace_back(
            "-------------------------------------------------------***--------------|||||-----------------------");
    map.emplace_back(
            "*****-----------------------#########--------------------------------||||||||||---------------******");
    map.emplace_back(
            "**********----------------###############--------------------------||||||||||||||----------*********");
    map.emplace_back(
            ",,,*********--------------###################-----------------------|||||||||||||--------*********,,");
    map.emplace_back(
            ",,,,,,********-------------######################-------------------|||||||||||||||-----********,,,,");
    map.emplace_back(
            ",,,,,,,,********------------##########################----------------||||||||----------*******,,,,,");
    map.emplace_back(
            ",,,,,,,,*********------------##############################--------------|||------------********,,,,");
    map.emplace_back(
            ",,,,,,,***********-------------###############################---------------------------*********,,");
    map.emplace_back(
            "********************--------------#############################---------------------------**********");
    map.emplace_back(
            "*********************---------------###########################------------------------------*******");
    map.emplace_back(
            "------*****************----------------######################---------------------------------------");
    return map;
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


    World world;
    Player player;
    world.addPlayer(player);
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
        while (true) {
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
                    world.generate(2);
                    break;
                }
                if (load.isPressed(mCoord.x, mCoord.y)) { break; }
            }
        }
        system("cls");
        SetConsoleCursorPosition(hOut, topLeft);
        while (!player.controller(world.getMap())) {
            SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
            SetConsoleCursorPosition(hOut, topLeft);
            world.updatePlayer(player);
            world.printMap(player);
        }
        system("cls");
    }

}

