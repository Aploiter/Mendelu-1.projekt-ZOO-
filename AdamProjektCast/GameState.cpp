#include "GameState.h"
#include <fstream>
#include <iostream>

Player CurrentPlayer(100, 10);  // deklarace statů hráče

bool DoesSaveExist()
{
    std::ifstream f("SaveFile.txt");
    return f.is_open();
}

void SaveGame()
{
    std::ofstream file("SaveFile.txt");
    if (file.is_open())
    {
        file << CurrentPlayer.getHealth() << '\n';
        file << CurrentPlayer.getStrength() << '\n';
        std::cout << "Game saved." << std::endl;
    }
}

Player LoadGame()
{
    std::ifstream file("SaveFile.txt");
    if (!file.is_open())
    {
        std::cerr << "Save file not found." << std::endl;
        //return Player(100, 10);
    }

    int hp, str;
    file >> hp >> str;

    if (file.fail())
    {
        std::cerr << "Save file is corrupted!" << std::endl;
        //return Player(100, 10);
    }

    //std::cout << "Game loaded." << std::endl;
    return Player(hp, str);
}