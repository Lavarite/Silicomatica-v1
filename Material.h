//
// Created by avary on 10/6/2022.
//

#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MATERIAL_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MATERIAL_H

#include "Block.h"
#include "Workbench.h"
#include "MechanicalCrusher.h"
#include "MechanicalSieve.h"
#include "CraftingRecipe.h"
#include "unordered_map"
#include <memory>

using namespace std;
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
    Block Null;
    Block AIR;
    Block WOOD;
    Block STONE;
    Block SAND;
    Block WATER;
    Workbench WORKBENCH;
    Block WATER_SCAFFOLDING;
    MechanicalSieve MECHANICAL_SIEVE;
    MechanicalCrusher MECHANICAL_CRUSHER;

    void init() {
        Null.create("", "", 0, true, "", "", false, 0, 0, {}, {});
        AIR.create("Air", "Gas", 2, true, "-", "None", false, 1, 1, {}, {});
        WOOD.create("Wood", "Block", 6, false, "|", "Axe", false, 1, 2, {}, {});
        STONE.create("Stone", "Block", 8, false, "#", "Pickaxe", false, 2, 3, {}, {});
        SAND.create("Sand", "Block", 14, true, "*", "Pickaxe", false, 3, 4, {}, {});
        WATER.create("Water", "Liquid", 9, true, ",", "Bucket", false, 0, 5, {}, {});
        WORKBENCH.create("Workbench", "Block", 6, false, "%", "Axe", true, 4, 6, {}, {});
        WATER_SCAFFOLDING.create("WaterScaffolding", "Block", 6, true, "▢", "Axe", false, 7, 7, {}, {});
        MECHANICAL_SIEVE.create("MechanicalSieve", "Block", 6, false, "▣", "Pickaxe", true, 8, 8, {}, {});
        MECHANICAL_CRUSHER.create("MechanicalCrusher", "Block", 6, false, "₪", "Pickaxe", true, 9, 9, {}, {});
    }

    unique_ptr<Block> get(int ITEM_ID) {

        switch (ITEM_ID) {
            case 1:
                return make_unique<Block>(AIR);
            case 2:
                return make_unique<Block>(WOOD);
            case 3:
                return make_unique<Block>(STONE);
            case 4:
                return make_unique<Block>(SAND);
            case 5:
                return make_unique<Block>(WATER);
            case 6:
                return make_unique<Workbench>(WORKBENCH);
            case 7:
                return make_unique<Block>(WATER_SCAFFOLDING);
            case 8:
                return make_unique<MechanicalSieve>(MECHANICAL_SIEVE);
            case 9:
                return make_unique<MechanicalCrusher>(MECHANICAL_CRUSHER);
            default:
                return make_unique<Block>(Null);
        }
    }
}

namespace Material {
    void init() {
        Material::Blocks::init();
    }
}
#endif //TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_MATERIAL_H
