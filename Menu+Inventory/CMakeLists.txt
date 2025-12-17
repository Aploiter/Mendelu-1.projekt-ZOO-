cmake_minimum_required(VERSION 4.0)
project(AdamProjektCastNew)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static") #Přidá flagy pro statické linkování knihoven (aby exe fungovalo i bez DLL na jiných PC)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdamProjektCastNew main.cpp
        GameState.cpp
        GameState.h
        Player.cpp
        Player.h
        TitleMenu.cpp
        TitleMenu.h
        IngameMenu.cpp
        IngameMenu.h
        TitleMenu.h
        TitleMenu.h
        TitleMenu.cpp
        GameState.h
        GameState.cpp
        Player.h
        Player.cpp
        IngameMenu.h
        Inventory.h
        Inventory.cpp
        Item.cpp
        Armor.h
        Armor.cpp
        consumable.h
        consumable.cpp
        Weapon.h
        Weapon.cpp
        Enemy.cpp
        Enemy.h
        Fighting.cpp
        Fighting.h)
