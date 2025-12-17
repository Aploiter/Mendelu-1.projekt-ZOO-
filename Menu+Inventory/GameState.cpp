#include "GameState.h"
#include <iostream>

GameState* GameState::instance = nullptr;

GameState::GameState() : currentPlayer(100, 10, 20) {}

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
    savedPlayer = currentPlayer.clone();  // Použij clone()
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
    currentPlayer = savedPlayer.clone();  // Použij clone()
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

bool GameState::hasSave() const
{
    return hasSavedState;
}