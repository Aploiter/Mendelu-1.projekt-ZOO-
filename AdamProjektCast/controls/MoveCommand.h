#pragma once
#include "Command.h"
#include "Game.h"

class MoveCommand : public Command {
private:
    Game* game;
    int dx, dy;

public:
    MoveCommand(Game* g, int dx, int dy);
    void execute() override;
};
