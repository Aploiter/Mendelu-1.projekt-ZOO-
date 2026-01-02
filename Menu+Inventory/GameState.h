#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Player.h"
#include "Enemy.h"

class GameState
{
private:
    static GameState* instance;

    Player currentPlayer;
    Player savedPlayer;

    Enemy currentEnemy;
    Enemy savedEnemy;

    bool hasSavedState = false;

    GameState();

public:
    static GameState* getInstance();

    void save();
    void load();

    Player& getCurrentPlayer();
    void setCurrentPlayer(const Player& player);

    Enemy& getCurrentEnemy();
    void setCurrentEnemy(const Enemy& enemy);

    bool hasSave() const;
};

#endif //GAMESTATE_H
