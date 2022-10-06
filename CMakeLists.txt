cmake_minimum_required(VERSION 3.23)
project(too_hot_outside_for_a_bit_too_long)

set(CMAKE_CXX_STANDARD 23)

add_executable(too_hot_outside_for_a_bit_too_long main.cpp Inventory.h Item.h Player.h World.h Block.h Button.h PerlinNoise.h MechanicalSieve.h MechanicalCrusher.h Controller.h Workbench.h Material.h)
