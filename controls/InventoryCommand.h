#pragma once
#include "Command.h"
#include "Game.h"

class InventoryCommand : public Command {
private:
    Game* game;

public:
    InventoryCommand(Game* g);
    void execute() override;
};
