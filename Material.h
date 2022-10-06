//
// Created by avary on 10/6/2022.
//

#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MATERIAL_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MATERIAL_H

#include "Block.h"
#include "Workbench.h"
#include "MechanicalCrusher.h"
#include "MechanicalSieve.h"

namespace Material::Items {
    Item Null{"", 0, "", "", 7, 0};
    Item WOOD{"Wood", 1, "block", "|", 6, 1};
    Item STONE{"Stone", 1, "block", "#", 8, 2};
    Item SAND{"Sand", 1, "block", "*", 14, 3};
    Item WORKBENCH{"Workbench", 1, "block", "%", 6, 4};
    Item PICKAXE{"Pickaxe", 1, "tool ", "⛏", 7, 5};
    Item AXE{"Axe", 1, "tool", "⚒", 7, 6};
    Item WATER_SCAFFOLDING{"Water Scaffolding", 1, "block", "▢", 6, 7};
    Item MECHANICAL_SIEVE{"Mechanical Sieve", 1, "block", "▣", 6, 8};
    Item MECHANICAL_CRUSHER{"Mechanical Crusher", 1, "block", "₪", 6, 9};

    Item get(int ITEM_ID) {
        switch (ITEM_ID) {
            case 1:
                return WOOD;
            case 2:
                return STONE;
            case 3:
                return SAND;
            case 4:
                return WORKBENCH;
            case 5:
                return PICKAXE;
            case 6:
                return AXE;
            case 7:
                return WATER_SCAFFOLDING;
            case 8:
                return MECHANICAL_SIEVE;
            case 9:
                return MECHANICAL_CRUSHER;
            default:
                return Null;
        }
    }
}

namespace Material::Blocks {
    Block Null{"", "", 0, true, "", "", false, 0, 0};
    Block AIR{"Air", "Gas", 2, true, "-", "None", false, 1, 1};
    Block WOOD{"Wood", "Block", 6, false, "|", "Axe", false, 1, 2};
    Block STONE{"Stone", "Block", 8, false, "#", "Pickaxe", false, 2, 3};
    Block SAND{"Sand", "Block", 14, true, "*", "Pickaxe", false, 3, 4};
    Block WATER{"Water", "Liquid", 9, true, ",", "Bucket", false, 0, 5};
    Workbench WORKBENCH{"Workbench", "Block", 6, true, "%", "Axe", false, 4, 6};
    Block WATER_SCAFFOLDING{"Water Scaffolding", "Block", 6, true, "▢", "Axe", false, 7, 7};
    MechanicalSieve MECHANICAL_SIEVE{"Mechanical Sieve", "MechanicalSieve", 6, true, "▣", "Pickaxe", true, 8, 8};
    MechanicalCrusher MECHANICAL_CRUSHER{"Mechanical Crusher", "MechanicalCrusher", 6, true, "₪", "Pickaxe", true, 9,
                                         9};

    Block get(int ITEM_ID) {
        switch (ITEM_ID) {
            case 1:
                return AIR;
            case 2:
                return WOOD;
            case 3:
                return STONE;
            case 4:
                return SAND;
            case 5:
                return WATER;
            case 6:
                return WORKBENCH;
            case 7:
                return WATER_SCAFFOLDING;
            case 8:
                return MECHANICAL_SIEVE;
            case 9:
                return MECHANICAL_CRUSHER;
            default:
                return Null;
        }
    }
}
#endif //TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MATERIAL_H
