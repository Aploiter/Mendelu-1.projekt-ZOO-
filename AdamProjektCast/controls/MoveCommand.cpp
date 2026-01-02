#include "MoveCommand.h"

MoveCommand::MoveCommand(Game* g, int dx, int dy)
    : game(g), dx(dx), dy(dy) {}

void MoveCommand::execute() {
    game->movePlayer(dx, dy);
}
