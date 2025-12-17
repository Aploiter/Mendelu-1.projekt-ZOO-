#include "GameState.h"
#include <iostream>

GameState* GameState::instance = nullptr;

GameState::GameState()
    : currentPlayer(100, 10, 20),
      currentEnemy("Goblin", 40, 7) // default enemy (můžeš změnit)
{
}

GameState* GameState::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameState();
    }
    return instance;
}

void GameState::save()
{
    savedPlayer = currentPlayer.clone();
    savedEnemy  = currentEnemy.clone();

    hasSavedState = true;
    std::cout << "Game saved." << std::endl;
}

void GameState::load()
{
    if (!hasSavedState)
    {
        std::cerr << "No save is available." << std::endl;
        return;
    }

    currentPlayer = savedPlayer.clone();
    currentEnemy  = savedEnemy.clone();

    std::cout << "Game loaded." << std::endl;
}

Player& GameState::getCurrentPlayer()
{
    return currentPlayer;
}

void GameState::setCurrentPlayer(const Player& player)
{
    currentPlayer = player.clone();
}

Enemy& GameState::getCurrentEnemy()
{
    return currentEnemy;
}

void GameState::setCurrentEnemy(const Enemy& enemy)
{
    currentEnemy = enemy.clone();
}

bool GameState::hasSave() const
{
    return hasSavedState;
}
