#include "GameState.h"
#include <fstream>
#include <iostream>
#include "IngameMenu.h"
#include "TitleMenu.h"

// globální hráč
Player CurrentPlayer(100, 10);
// vytvoření konstantní hodnoty int (seceretKey) pro ověřování zda byla data ve složce SaveFile.txt upravována
const int secretKey = 123456;

/*bool DoesSaveExist()
{
    std::ifstream Save("SaveFile.txt");
    return Save.is_open();
}*/

//TODO zašifrovat checksum pro ztížení upravy dat v SaveFile.txt
void SaveGame()
{
    std::ofstream Save("SaveFile.txt");
    if (Save.is_open())
    {
        int hp = CurrentPlayer.getHealth();
        int str = CurrentPlayer.getStrength();
        int checksum = hp + str + secretKey;
        Save << hp << " \n" << str << " \n" << checksum;
        std::cout << "Game saved." << std::endl;
    }
}

Player LoadGame()
{
    std::ifstream Save("SaveFile.txt");
    if (!Save.is_open())
    {
        std::cerr << "Save file not found." << std::endl;
        IngameMenu* menu;
        menu->print();
    }

    int hp, str, checksum;
    Save >> hp >> str >> checksum;

    if (Save.fail() || (hp + str + secretKey) != checksum)
    {
        std::cerr << "Save file is corrupted or has been manipulated!" << std::endl;
        getchar();
        getchar();
        TitleMenu* title;
        title->print();
    }

    // načtení uložených dat hráče
    return Player(hp, str);
}