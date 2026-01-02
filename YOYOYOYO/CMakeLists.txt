cmake_minimum_required(VERSION 4.0)
project(YOYOYOYO)

set(CMAKE_CXX_STANDARD 20)

add_executable(YOYOYOYO main.cpp
        Item.cpp
        Item.h
        Weapon.cpp
        Weapon.h
        Armor.cpp
        Armor.h
        consumable.cpp
        consumable.h
        Inventory.cpp
        Inventory.h)
