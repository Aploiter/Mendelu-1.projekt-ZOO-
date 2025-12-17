#pragma once
#include "Command.h"
#include "Game.h"

class MenuCommand : public Command {
private:
    Game* game;

public:
    MenuCommand(Game* g);
    void execute() override;
};
