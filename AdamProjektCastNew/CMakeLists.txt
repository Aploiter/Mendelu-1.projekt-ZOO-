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
        IngameMenu.h)
