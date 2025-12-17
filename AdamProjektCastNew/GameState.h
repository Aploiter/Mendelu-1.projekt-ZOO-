#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Player.h"

class GameState
{
private:
    static GameState* instance; // poznámka
    Player currentPlayer;
    Player savedPlayer;
    bool hasSavedState = false;
    GameState(); // poznámka
public:
    static GameState* getInstance(); // poznámka
    void save();
    void load();
    Player& getCurrentPlayer();
    void setCurrentPlayer(const Player& player); // poznámka
    bool hasSave() const;
};

#endif