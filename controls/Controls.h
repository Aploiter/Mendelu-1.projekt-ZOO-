#pragma once
#include "Game.h"
#include "InputHandler.h"
#include "KeyBinding.h"
#include "InputState.h"

class Controls {
private:
    Game* game;
    InputHandler input;
    KeyBinding bindings;
    InputState* state;

public:
    Controls(Game* g);

    void handleInput();
    void executeCommand(char key);
    void setState(InputState* newState);
};
