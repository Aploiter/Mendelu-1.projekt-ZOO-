// Interactions.h (OPRAVENÝ)

#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "Map.h"
#include <iostream>



class GameController {
public:
    GameController();

    void runGameLoop();

private:
    Map gameMap;
    bool isRunning;
    int moveCount = 0;
    void handleInput(char input);
};

#endif // INTERACTIONS_H