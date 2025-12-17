cmake_minimum_required(VERSION 4.0)
project(controls)

set(CMAKE_CXX_STANDARD 20)

add_executable(controls main.cpp
        cmake-build-debug/controls.cpp
        cmake-build-debug/controls.h
        MoveCommand.cpp
        MoveCommand.h
        InventoryCommand.cpp
        InventoryCommand.h
        MenuCommand.cpp
        MenuCommand.h
        MapState.cpp
        MapState.h
        InputHandler.cpp
        InputHandler.h
        InputState.cpp
        InputState.h
        Command.cpp
        Command.h
        KeyBinding.cpp
        KeyBinding.h)
