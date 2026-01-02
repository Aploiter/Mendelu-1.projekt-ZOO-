#include "MapState.h"
#include "Controls.h"

void MapState::handle(Controls* controls, char input) {
    controls->executeCommand(input);
}
