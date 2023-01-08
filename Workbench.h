//
// Created by avary on 10/6/2022.
//

#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORKBENCH_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORKBENCH_H

#include "Block.h"
#include "Item.h"
#include "CraftingRecipe.h"
#include "Button.h"

using namespace std;

class Workbench : public Block {
public:

    void interact(Inventory *inventory, int *selectedSlot, Controller *controller) override {
        if (in.empty()) {
            in = vector<Item>({Item{"", 0, "", "", 7, 0}, Item{"", 0, "", "", 7, 0}, Item{"", 0, "", "", 7, 0},
                               Item{"", 0, "", "", 7, 0}, Item{"", 0, "", "", 7, 0}, Item{"", 0, "", "", 7, 0},
                               Item{"", 0, "", "", 7, 0}, Item{"", 0, "", "", 7, 0}, Item{"", 0, "", "", 7, 0}});
        }
        if (out.empty()) {
            out = vector<Item>({Item{"", 0, "", "", 7, 0}});
        }
        vector<Button> inventoryButtons = vector<Button>(9);
        vector<Button> craftingButtons = vector<Button>(9);

        int craftingSelected = 0;
        for (int i = 0; i < 9; i++) {
            inventoryButtons[i] = Button{63 + 27 * i, 1, 5, 26};
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                craftingButtons[i + j * 3] = Button{27 * i, 33 + 6 * j, 5, 26};
            }
        }
        while (true) {
            if (controller->irInBuf[0].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                controller->irInBuf[0].Event.KeyEvent.wVirtualKeyCode = 0;
                system("cls");
                return;
            }
            if (controller->irInBuf[0].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                POINT mCoord = {controller->irInBuf[0].Event.MouseEvent.dwMousePosition.X,
                                controller->irInBuf[0].Event.MouseEvent.dwMousePosition.Y};
                for (int i = 0; i < 9; i++) {
                    if (inventoryButtons[i].isPressed(mCoord.x, mCoord.y)) {
                        *selectedSlot = i;
                    } else if (craftingButtons[i].isPressed(mCoord.x, mCoord.y)) {
                        craftingSelected = i;
                    }
                }
            }
            if (controller->irInBuf[0].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
                POINT mCoord = {controller->irInBuf[0].Event.MouseEvent.dwMousePosition.X,
                                controller->irInBuf[0].Event.MouseEvent.dwMousePosition.Y};
                for (int i = 0; i < 9; i++) {
                    if (inventoryButtons[i].isPressed(mCoord.x, mCoord.y)) {
                        *selectedSlot = i;
                    } else if (craftingButtons[i].isPressed(mCoord.x, mCoord.y)) {
                        craftingSelected = i;
                    }
                }
                for (int i = 0; i < 9; i++) {
                    if (inventoryButtons[i].isPressed(mCoord.x, mCoord.y)) {
                        if (GetKeyState(VK_SHIFT)) {
                            inventory->addItem(in[i]);
                            in[i] = Item{"", 0, "", "", 7, 0};
                        } else {
                            if (in[craftingSelected].getQuantity() > 0) {
                                inventory->addItem(in[craftingSelected], 1);
                                in[craftingSelected].setQuantity(in[craftingSelected].getQuantity() - 1);
                            }
                        }
                    } else if (craftingButtons[i].isPressed(mCoord.x, mCoord.y)) {
                        if (GetKeyState(VK_SHIFT)) {
                            inventory->addItem(in[i]);
                            in[i] = Item{"", 0, "", "", 7, 0};
                        } else {
                            if (in[i].getQuantity() > 0) {
                                inventory->addItem(in[i], 1);
                                in[i].setQuantity(in[i].getQuantity() - 1);
                            }
                        }
                    }
                }

            }
            for (int i = 0; i < 9; i++) {
                craftingButtons[i].color = 7;
                craftingButtons[craftingSelected].color = 2;
                craftingButtons[i].itemColor = in[i].color;
                craftingButtons[i].text = in[i].name;
                craftingButtons[i].text1 = in[i].symbol + " " + to_string(in[i].quantity);
                craftingButtons[i].print();

                inventoryButtons[i].color = 7;
                inventoryButtons[*selectedSlot].color = 4;
                inventoryButtons[i].itemColor = inventory->items[i].color;
                inventoryButtons[i].text = inventory->items[i].name;
                inventoryButtons[i].text1 =
                        inventory->items[i].symbol + " " + to_string(inventory->items[i].quantity);
                inventoryButtons[i].print();
            }
        }
        system("cls");
    };

};

#endif //TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORKBENCH_H
