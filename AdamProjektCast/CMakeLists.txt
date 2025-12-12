cmake_minimum_required(VERSION 4.0)
project(AdamProjektCast)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")

set(CMAKE_CXX_STANDARD 20)

add_executable(AdamProjektCast main.cpp
        TitleMenu.cpp
        TitleMenu.h
        IngameMenu.cpp
        IngameMenu.h
        Player.cpp
        Player.h
        GameState.cpp
        GameState.h)
