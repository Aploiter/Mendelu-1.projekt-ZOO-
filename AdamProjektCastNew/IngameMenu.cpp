#include "IngameMenu.h"
#include <iostream>
#include <windows.h>
#include "GameState.h"
#include "TitleMenu.h"
#include "Player.h"

IngameMenu::IngameMenu()
{

}

void IngameMenu::print() // funkce pro komunikaci s uživatelem (výpis/zápis)
{
    bool exitLoop = false;
    while (!exitLoop)
    {
        system("cls");
        char choice;
        std::cout << "<---  |Ingame-Menu|  --->\n";
        std::cout << "      [r] Return to title\n";
        if (GameState::getInstance()->hasSave()) // pokud hasSave = true tak se zobrazí možnost Load save
        {
            std::cout << "      [l] Load save\n";
        }
        std::cout << "      [s] Save game\n";
        std::cout << "      [i] Player info\n";
        std::cout << "      [e] Exit game\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 'r': returnToTitle(); exitLoop = true; break;
            case 'l':
                if (GameState::getInstance()->hasSave())
                {
                    loadSave();
                }
                else
                {
                    std::cerr << "No save is available!" << std::endl;
                    Sleep(1000);
                }
                break;
            case 's':
                GameState::getInstance()->save();
                Sleep(1000);
                break;
            case 'i': playerInfo(); break;
            case 'e': exitGame(); exitLoop = true; break;
            default: std::cerr << "Invalid choice." << std::endl; Sleep(1000); break;
        }
    }
}

void IngameMenu::returnToTitle()
{
    TitleMenu titleMenu;
    titleMenu.print();
}

void IngameMenu::loadSave()
{
    GameState::getInstance()->load(); // Načte uložený stav hráče z paměti a přepíše aktuální stav
    playerInfo();
}

void IngameMenu::playerInfo()
{
    Player& player = GameState::getInstance()->getCurrentPlayer(); // Získá referenci na aktuálního hráče ze singletonu GameState
    std::cout << "<---  |Player info|  --->\n";
    std::cout << "      Player health [" << player.getHealth() << "]\n"
              << "      Player strength [" << player.getStrength() << "]" << std::endl;
    getchar();
    getchar();
}

void IngameMenu::exitGame()
{
    std::cout << "Exiting game..." << std::endl;
    Sleep(1500);
    exit(0); // Okamžitě ukončí program s návratovým kódem 0 (úspěšné ukončení)
}
