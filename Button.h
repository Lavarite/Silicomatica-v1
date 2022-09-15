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
    string getText(){return text;};
    void setText(string text){this->text = text;};
    bool isPressed(int mX, int mY){
        if (mX >= this->x && mX <= this->x + width && mY >= this->y && mY <= this->y + height) {
            return true;
        }
        return false;
    };
    void print(){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(x+1), static_cast<SHORT>(y)});
        for (int i = 0; i < width-1; i++) {
            cout << "-";
        }
        for (int i = 0; i < (height-2); i++){
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(x), static_cast<SHORT>(y+i+1)});
            cout << "|";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(x+width), static_cast<SHORT>(y+i+1)});
            cout << "|";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(x+1), static_cast<SHORT>(y+height-1)});
        for (int i = 0; i < width-1; i++) {
            cout << "-";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(x+width/2-text.length()/2), static_cast<SHORT>(y+height/2)});
        cout << text;
    }
};

#endif
