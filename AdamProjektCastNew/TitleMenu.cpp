#include "TitleMenu.h"
#include <iostream>
#include <windows.h>
#include "IngameMenu.h"
#include "Player.h"
#include "GameState.h"

TitleMenu::TitleMenu()
{

}

void TitleMenu::print()
{
    bool exitLoop = false;
    while (!exitLoop)
    {
        system("cls");
        char choice;
        std::cout << "<---  |Title-Menu|  --->\n";
        std::cout << "      [n] New game\n";

        if (GameState::getInstance()->hasSave()) // pokud hasSave = true
        {
            std::cout << "      [c] Continue game\n";
        }

        std::cout << "      [e] Exit game\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 'n': newGame(); exitLoop = true; break;
            case 'c':
                if (GameState::getInstance()->hasSave()) //poznámka
                {
                    continueGame();
                    exitLoop = true;
                }
                else
                {
                    std::cerr << "Invalid choice." << std::endl;
                    Sleep(1000);
                }
                break;
            case 'e': exitGame(); exitLoop = true; break;
            default: std::cerr << "Invalid choice." << std::endl; Sleep(1000); break;
        }
    }
}

void TitleMenu::newGame()
{
    GameState::getInstance()->setCurrentPlayer(Player(100, 10));  // Nastaví nového hráče s výchozíma hodnotama (100 HP, 10 síla)
    std::cout << "Starting new game." << std::endl;
    GameState::getInstance()->save();  // Uloží aktuální stav hry (defaultní hráč) do paměti jako save
    IngameMenu ingame; // Vytvoří novou instanci herního menu
    ingame.print(); // návrat do IngameMenu (print)
}

void TitleMenu::continueGame()
{
    if (!GameState::getInstance()->hasSave()) // pokud hasSave = false
    {
        std::cerr << "No save is available!" << std::endl;
        return;
    }
    GameState::getInstance()->load(); // Načte uložený stav hráče z paměti a nastaví ho jako aktuální
    IngameMenu ingame; // Vytvoří novou instanci herního menu
    ingame.print(); // návrat do IngameMenu (print)
}

void TitleMenu::exitGame() // funkce pro ukončení programu
{
    std::cout << "Exiting game..." << std::endl;
    Sleep(1500);
    exit(0); // Okamžitě ukončí program s návratovým kódem 0 (úspěšné ukončení)
}