#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CONTROLLER_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CONTROLLER_H

#include <windows.h>
#include <cstdio>
#include <thread>

using namespace std;

class Controller {
public:

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwSaveOldMode{};
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[1];

    [[noreturn]] void handle() {
        while (true) {
            ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
        }
    }

    thread mouseThread = thread(&Controller::handle, this);

    Controller() {
        mouseThread.detach();
    }
};


#endif
