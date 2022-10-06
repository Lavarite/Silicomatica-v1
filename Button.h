#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_BUTTON_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_BUTTON_H

#include <windows.h>
#include "iostream"

using namespace std;

class Button {
public:
    int x;
    int y;
    int height;
    int width;
    string text;
    string text1;
    string text2;
    int color = 7;
    int itemColor = 7;

    string getText() { return text; };

    void setText(string text) { this->text = text; };

    bool isPressed(int mX, int mY) {
        if (mX >= this->x && mX <= this->x + width && mY >= this->y && mY <= this->y + height) {
            return true;
        }
        return false;
    };

    void print() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(x + 1), static_cast<SHORT>(y)});
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        for (int i = 0; i < width - 1; i++) {
            cout << "-";
        }
        for (int i = 0; i < (height - 2); i++) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                     {static_cast<SHORT>(x), static_cast<SHORT>(y + i + 1)});
            cout << "|";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                     {static_cast<SHORT>(x + width), static_cast<SHORT>(y + i + 1)});
            cout << "|";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                 {static_cast<SHORT>(x + 1), static_cast<SHORT>(y + height - 1)});
        for (int i = 0; i < width - 1; i++) {
            cout << "-";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                 {static_cast<SHORT>(x + 1),
                                  static_cast<SHORT>(y + height / 2)});
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for (int i = 0; i < width / 2 - text.length() / 2 - 1; i++) {
            cout << " ";
        }
        cout << text;
        for (int i = 0; i < width / 2 - text.length() / 2 - 1; i++) {
            cout << " ";
        }
        if (!text1.empty()) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                     {static_cast<SHORT>(x + 1),
                                      static_cast<SHORT>(y + height / 2 + 1)});
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            for (int i = 0; i < width / 2 - text1.length() / 2 - 1; i++) {
                cout << " ";
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), itemColor);
            cout << text1[0];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << text1.substr(1);
            for (int i = 0; i < width / 2 - text1.length() / 2 - 1; i++) {
                cout << " ";
            }
        }
        if (!text2.empty()) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                     {static_cast<SHORT>(x + 1),
                                      static_cast<SHORT>(y + height / 2 - 1)});
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            for (int i = 0; i < width / 2 - text2.length() / 2 - 1; i++) {
                cout << " ";
            }
            cout << text2;
            for (int i = 0; i < width / 2 - text2.length() / 2 - 1; i++) {
                cout << " ";
            }
        }
    }
};

#endif
