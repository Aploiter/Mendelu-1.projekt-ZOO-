#include "GameState.h"
#include <iostream>

GameState* GameState::instance = nullptr; // // Inicializace statické proměnné singletonu na nullptr (žádná instance zatím neexistuje)

GameState::GameState() : currentPlayer(100, 10) // Privátní konstruktor [vytvoří nového hráče s defaultními hodnotami (100 HP, 10 síla)]
{

}

GameState* GameState::getInstance() // Statická metoda pro získání instance GameState (singleton pattern)
{
    if (instance == nullptr) // Pokud instance ještě neexistuje
    {
        instance = new GameState(); // Vytvoř novou instanci a ulož její ukazatel
    }
    return instance; // Vrátí ukazatel na existující instanci
}

void GameState::save() // funkce pro ukládání dat hry do paměti
{
    savedPlayer = currentPlayer;  // vytvoření kopie aktuálního stavu do (savedPlayer)
    //TODO přidat savedEnemies = currentEnemies; atd..
    hasSavedState = true; // nastaví status uložení na true
    std::cout << "Game saved." << std::endl;
}

void GameState::load()
{
    if (!hasSavedState) // pokud status uložení = false
    {
        std::cerr << "No save is available." << std::endl;
        return;
    }
    currentPlayer = savedPlayer;  // Načtení z úložky (savedPlayer)
    // TODO přidat currentEnemies = savedEnemies; atd..
    std::cout << "Game loaded." << std::endl;
}

Player& GameState::getCurrentPlayer()
{
    return currentPlayer;
}

void GameState::setCurrentPlayer(const Player& player) // Nastaví aktuálního hráče podle předaného objektu
{
    currentPlayer = player;
}

bool GameState::hasSave() const
{
    return hasSavedState;
}