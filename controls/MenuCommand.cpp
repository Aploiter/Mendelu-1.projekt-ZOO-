#include "MenuCommand.h"

MenuCommand::MenuCommand(Game* g) : game(g) {}

void MenuCommand::execute() {
    game->openMenu();
}
