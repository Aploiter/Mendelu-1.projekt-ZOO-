#include <iostream> // std:: fuknce
#include <windows.h> // funkce jako system("cls"); atd..
//odkazy na jednotlivé třídy
#include "TitleMenu.h"
#include "IngameMenu.h"
#include "Player.h"
#include "GameState.h"
#include "consumable.h"
#include "Armor.h"
#include "Weapon.h"
#include "Enemy.h"

TitleMenu::TitleMenu() // konstruktor
{

}

void TitleMenu::print() // metoda (print)
{
    bool exitLoop = false; // řídí kdy bude ukončen loop v menu
    while (!exitLoop) // dokud exitLoop = false
    {
        system("cls"); // vyčistí konzoli
        char choice;
        std::cout << "<---  |Title-Menu|  --->\n";
        std::cout << "      [n] New game\n";

        if (GameState::getInstance()->hasSave()) // pokud existuje uložený stav v paměti (hasSavedState = true)
        {
            std::cout << "      [c] Continue game\n"; // zobraz možnost pro načtení hry
        }

        std::cout << "      [e] Exit game\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 'n': newGame(); exitLoop = true; break; // pokud input = 'n', tak nastav exitLoop -> true a breakni switch
            case 'c': // pokud input = 'c'
                if (GameState::getInstance()->hasSave()) // ověří že existuje úložka v paměti
                {
                    continueGame(); // načte uložený stav
                    exitLoop = true; // ukončí loop
                }
                else
                {
                    std::cerr << "Invalid choice." << std::endl; // vypíše error msg
                    Sleep(1000); // podrží program na 1 sekundu
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
    auto potion = std::make_unique<consumable> // vytvoří unikátní ukazatel na (healing potion)
    (1, "Heal potion", "Regained 30 HP", 99, Rarity::Common, 30, 0); // nastaví hodnoty pro item
    newPlayer.getInventory().addItem(std::move(potion)); // přidá item do inventáře

    auto sword = std::make_unique<Weapon> // vytvoří unikátní ukazatel na (Iron sword)
    (2, "Iron sword", "Basic weapon", 1, Rarity::Rare, 15, "Slashing"); // nastaví hodnoty pro item
    newPlayer.getInventory().addItem(std::move(sword)); // přidá item do inventáře

    auto armor = std::make_unique<Armor> // vytvoří unikátní ukazatel na (Leather vest)
    (3, "Leather vest", "Basic defence", 1, Rarity::Common, 10, "Body"); // nastaví hodnoty pro item
    newPlayer.getInventory().addItem(std::move(armor)); // přidá item do inventáře

    GameState::getInstance()->setCurrentPlayer(newPlayer); // nastaví nového (Player), jako aktuálního v GameState.

    system("cls");
    std::cout << "Starting new game." << std::endl;
    Sleep(1000);
    GameState::getInstance()->save(); // Uloží stav (savedPlayer = clone current..).
    IngameMenu ingame; // vytvoří (IngameMenu) objekt
    ingame.print(); // spustí print v ingame objektu.
}

void TitleMenu::continueGame()
{
    if (!GameState::getInstance()->hasSave()) // Pokud neexistuje žádný uložený stav
    {
        system("cls"); // vyčisti konzoli
        std::cerr << "No save is available!" << std::endl; // vypiš error msg
        Sleep(1000);
        return;
    }
    GameState::getInstance()->load(); // Načte uložený stav hráče z paměti a nastaví ho jako aktuální
    IngameMenu ingame; // vytvoří (IngameMenu) objekt
    ingame.print(); // spustí print v ingame objektu
}

void TitleMenu::exitGame() // funkce pro ukončení programu
{
    std::cout << "Exiting game..." << std::endl;
    Sleep(1500);
    exit(0); // ukončí program s návratovým kódem 0 (úspěšné ukončení)
}