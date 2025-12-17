#include "InventoryCommand.h"

InventoryCommand::InventoryCommand(Game* g) : game(g) {}

void InventoryCommand::execute() {
    game->getInventory().print();
}
