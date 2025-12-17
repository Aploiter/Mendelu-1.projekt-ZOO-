#include "IngameMenu.h"
#include <iostream>
#include <windows.h>
#include "GameState.h"
#include "TitleMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "Fighting.h"

Player& player = GameState::getInstance()->getCurrentPlayer();
Enemy enemy("Goblin", 40, 7);

IngameMenu::IngameMenu() // konstruktor
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
        if (GameState::getInstance()->hasSave()) // pokud existuje uložený stav v paměti (hasSavedState = true)
        {
            std::cout << "      [l] Load save\n"; // zobraz možnost pro načtení hry
        }
        std::cout << "      [s] Save game\n";
        std::cout << "      [i] Player info\n";
        std::cout << "      [v] View inventory\n";
        std::cout << "      [f] Engage in fight\n";
        std::cout << "      [e] Exit game\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 'r': returnToTitle(); exitLoop = true; break; // pokud input = 'r', načti metodu returnToTitle(), nastav exitLoop = true a breakni switch (ten exitLoop je asi zbytečnej, ale ani tam nijak neškodí)
            case 'l': // pokud input = 'l'
                if (GameState::getInstance()->hasSave()) // a existuje v paměti úložka
                {
                    loadSave(); // načti metodu loadSave()
                }
                else // jinak
                {
                    std::cerr << "No save is available!" << std::endl; // vypiš error msg
                    Sleep(1000); // podrž program na 1 sekundu
                }
                break;
            case 's':
                GameState::getInstance()->save(); // uloží aktuální stav do paměti
                Sleep(1000);
                break;
            case 'i': playerInfo(); break;
            case 'v': viewInventory(); break;
            case 'f': Fighting::fight(player, enemy); break; // volá statickou metodu (fight) z třídy Fighting (proto je tam :: a ne .)
                //té předá reference na player a enemy (ne kopie, takže se hodnoty mění i po návratu z funkce)
            case 'e': exitGame(); exitLoop = true; break;
            default: std::cerr << "Invalid choice." << std::endl; Sleep(1000); break;
        }
    }
}

void IngameMenu::returnToTitle()
{
    GameState::getInstance()->save();  // AUTOSAVE, když přecházíme z IngameMenu do TitleMenu
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
    Player& player = GameState::getInstance()->getCurrentPlayer(); // Získá referenci na aktuálního hráče.
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
    exit(0); // ukončí program s návratovým kódem 0 (úspěšné ukončení)
}

void IngameMenu::viewInventory()
{
    system("cls");
    Player& player = GameState::getInstance()->getCurrentPlayer(); // aktuální hráč.
    const Inventory& inv = player.getInventory(); // reference na jeho inventář.

    std::cout << "<---  |Player inventory|  --->\n\n";

    auto contents = inv.getInventoryContents(); // vytvoří vektor řádků pro zobrazení.
    if (contents.empty()) // pokud je prázdný
    {
        std::cout << "Inventory is empty.\n";
    }
    else
    {
        for (size_t i = 0; i < contents.size(); ++i) // projde všechny položky
        {
            std::cout << " [" << i << "] " << contents[i] << "\n"; // vypíše index + text
        }
    }

    std::cout << "\n(Press [Enter] to continue.)";
    std::cin.ignore(10000, '\n');
    getchar();
    getchar();
}
