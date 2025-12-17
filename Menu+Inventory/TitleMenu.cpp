#include "TitleMenu.h"
#include <iostream>
#include <windows.h>
#include "IngameMenu.h"
#include "Player.h"
#include "GameState.h"
#include "consumable.h"
#include "Armor.h"
#include "Weapon.h"

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
    Player newPlayer(100, 10, 20);

    // Testovací itemy
    auto potion = std::make_unique<consumable>(1, "Heal potion", "Regained 30 HP", 99, Rarity::Common, 30, 0);
    newPlayer.getInventory().addItem(std::move(potion));

    auto sword = std::make_unique<Weapon>(2, "Iron sword", "Basic weapon", 1, Rarity::Rare, 15, "Slashing");
    newPlayer.getInventory().addItem(std::move(sword));

    auto armor = std::make_unique<Armor>(3, "Leather vest", "Basic defence", 1, Rarity::Common, 10, "Body");
    newPlayer.getInventory().addItem(std::move(armor));

    GameState::getInstance()->setCurrentPlayer(newPlayer);

    system("cls");
    std::cout << "Starting new game." << std::endl;
    Sleep(1000);
    GameState::getInstance()->save();
    IngameMenu ingame;
    ingame.print();
}

void TitleMenu::continueGame()
{
    if (!GameState::getInstance()->hasSave()) // pokud hasSave = false
    {
        system("cls");
        std::cerr << "No save is available!" << std::endl;
        Sleep(1000);
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