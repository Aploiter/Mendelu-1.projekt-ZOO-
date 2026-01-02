#include "Controls.h"
#include "MoveCommand.h"
#include "InventoryCommand.h"
#include "MenuCommand.h"
#include "MapState.h"
#include <iostream>

Controls::Controls(Game* g) : game(g) {
    state = new MapState();

    bindings.bind('w', new MoveCommand(game, 0, -1));
    bindings.bind('s', new MoveCommand(game, 0, 1));
    bindings.bind('a', new MoveCommand(game, -1, 0));
    bindings.bind('d', new MoveCommand(game, 1, 0));
    bindings.bind('i', new InventoryCommand(game));
    bindings.bind('m', new MenuCommand(game));
}

void Controls::handleInput() {
    std::cout << "\nWASD – pohyb | I – inventář | M – menu\n";
    char inputChar = input.getInput();
    state->handle(this, inputChar);
}

void Controls::executeCommand(char key) {
    Command* cmd = bindings.get(key);
    if (cmd)
        cmd->execute();
    else
        std::cout << "Neplatná akce.\n";
}

void Controls::setState(InputState* newState) {
    state = newState;
}
