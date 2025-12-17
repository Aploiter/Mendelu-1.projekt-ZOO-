#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Player.h"

class GameState
{
private:
    static GameState* instance;
    Player currentPlayer;
    Player savedPlayer;
    bool hasSavedState = false;
    GameState();
public:
    static GameState* getInstance();
    void save();
    void load();
    Player& getCurrentPlayer();
    void setCurrentPlayer(const Player& player);
    bool hasSave() const;
};

#endif //GAMESTATE_H