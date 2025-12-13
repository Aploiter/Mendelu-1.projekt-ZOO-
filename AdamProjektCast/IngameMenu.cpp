#include "IngameMenu.h"
#include <iostream>
#include <fstream>
#include <windows.h>

#include "GameState.h"
#include "TitleMenu.h"
#include "Player.h"

IngameMenu::IngameMenu()
{

}

void IngameMenu::print()
{
    bool exitLoop = false;
    while (!exitLoop)
    {
        system("cls");
        //vytvoření bool proměnné na ověření zda jde otevřít "SaveFile.txt" pro použítí v podmínkách
        bool saveExists = false;
        {

            std::ifstream Save("SaveFile.txt");
            saveExists = Save.is_open();
        }
        char choice;
        std::cout << "<---  |Ingame-Menu|  --->\n";
        std::cout << "      [r] Return to title\n";
        //pokud jde otevřít soubor savefile/existuje přidat možnost continue
        if (saveExists) {std::cout << "      [l] Load save\n";}
        std::cout << "      [i] Player info\n";
        std::cout << "      [e] Exit game\n";
        std::cout << "\nChoice: "; std::cin >> choice;

        {
            switch (choice)
            {
                case 'r': returnToTitle(); exitLoop = true;break;
                case 'l': if (saveExists) {loadSave(); exitLoop = true;} else {std::cerr << "Invalid choice!" << std::endl; Sleep(1000);} break;
                case 'i': playerInfo(); exitLoop = true; break;
                case 'e': exitGame(); exitLoop = true; break;
                default: std::cerr << "Invalid choice!" << std::endl; Sleep(1000); break;
            }
        }
    }
}

void IngameMenu::loadSave()
{
    // TODO načíst data z SaveFile.txt souboru (HOTOVO)
    std::cout << "Save file loaded.\n";
    CurrentPlayer = LoadGame();
    std::cout << "Player info: " << "\nHealth: " << CurrentPlayer.getHealth()
    << "\nStrenght: " << CurrentPlayer.getStrength() << std::endl;
    getchar();
    getchar();
}

void IngameMenu::returnToTitle()
{
    TitleMenu titleMenu;
    titleMenu.print();
}

void IngameMenu::exitGame()
{
    std::cout << "Exiting game..." << std::endl;
    Sleep(1500);
    exit(0);
}

void IngameMenu::playerInfo()
{
    std::cout << "Player health: " << CurrentPlayer.getHealth()
    << "\nPlayer strength: " << CurrentPlayer.getStrength() << "\n";
    getchar(); getchar();
    IngameMenu menu;
    menu.print();
}