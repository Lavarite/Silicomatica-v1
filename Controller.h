#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CONTROLLER_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CONTROLLER_H

#include <windows.h>
#include <cstdio>
#include <thread>

using namespace std;

class Controller {
public:
    bool LMB = false;
    bool RMB = false;

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwSaveOldMode{};
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[1];

    void handleMouse() {
        while (true) {
            SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
            ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
            if (irInBuf[0].EventType == MOUSE_EVENT) {
                if (irInBuf[0].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    LMB = true;
                    RMB = false;
                } else if (irInBuf[0].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
                    RMB = true;
                    LMB = false;
                } else {
                    LMB = false;
                    RMB = false;
                }
            }
        }
    }

    thread mouseThread = thread(&Controller::handleMouse, this);

    Controller() {
        mouseThread.detach();
    }
};


#endif
