#include <iostream> // konzole (cout/cin)
#include <limits> // pro ignore
#include <random> // pro RNG

#include "Fighting.h"
#include "Player.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Item.h"
#include "consumable.h"
#include "GameState.h"

namespace
{
    std::mt19937& rng() // funkce vrací referenci na globální RNG generátor
    {
        static std::mt19937 gen {std::random_device{}() }; // statický generátor se seedem (vytvoří se jen jednou)
        return gen; // vrací referenci na generátor
    }

    int randInt(int a, int b) // náhodné celé číslo v intervalu (a, b)
    {
        std::uniform_int_distribution<int> dist(a, b); // distribuce rovnoměrných celých čísel
        return dist(rng()); // vygeneruje číslo pomocí rng()
    }

    // vrací true s pravděpodobností (1-100%)
    bool chance(int percent)
    {
        return randInt(1, 100) <= percent; // vygeneruje 1-100 a porovná
    }

    void waitEnter() // zastaví program, dokud uživatel nedá (Enter)
    {
        std::cout << "\n(Press [Enter] to continue.)";
        getchar(); // čeká na (Enter)
        getchar();
    }

    bool getItemIdByIndex(const Inventory& inv, int index, int& outItemId) // převede index ve výpisu na itemID
    {
        const auto& items = inv.getItems(); // získá reference na vektor unique_ptr<Item>
        if (index < 0 || index >= static_cast<int>(items.size())) return false; // zkontroluje rozsahu indexu
        if (!items[index]) return false; // zkontroluje, že ukazatel není null
        outItemId = items[index]->getItemID(); // vytáhne itemID z itemu
        return true;
    }

    bool isConsumableById(const Inventory& inv, int itemId) // ověří, jestli item s tímto ID je consumable
    {
        for (const auto& it : inv.getItems()) // projde všechny itemy
        {
            if (it && it->getItemID() == itemId)  // pokud item existuje a má stejné ID
            {
                return dynamic_cast<consumable*>(it.get()) != nullptr; // zkusí přetypovat na consumable
            }
        }
        return false; // nenašel se = není consumable (isConsumableById = false)
    }

    void printFightHud(const Player& player, const Enemy& enemy) // zobrazí přehled HP/STR
    {
        std::cout << "<--- TURN BASED FIGHT --->\n";
        std::cout << "Player HP: " << player.getHealth()
                  << " | STR: " << player.getStrength() << "\n";
        std::cout << enemy.getName()
                  << " HP: " << enemy.getHealth()
                  << " | DMG: " << enemy.getStrength() << "\n\n";
    }

    void printInventoryForFight(const Inventory& inv) // zobrazí inventář
    {
        auto contents = inv.getInventoryContents(); // získá textové řádky inventáře
        if (contents.empty()) // pokud je prázdný
        {
            std::cout << "Inventory is empty.\n"; // vypíše, že inventář je prázdný
            return;
        }
        // jinak
        for (int i = 0; i < static_cast<int>(contents.size()); ++i) // projde všechny položky
        {
            std::cout << " [" << i << "] " << contents[i] << "\n"; // vypíše index + řádek
        }
    }
}

bool Fighting::fight(Player& player, Enemy& enemy) // Hlavní funkce boje (turn-based)
{
    std::cout << "Encounter: " << enemy.getName() << "\n"; // ohlásí, s kým bojuješ

    int round = 1; // počítá kola

    while (player.getHealth() > 0 && enemy.isAlive()) // dokud je hráč živý a enemy živý
    {
        //GameState::getInstance()->save();
        system("cls");
        printFightHud(player, enemy); // zobrazí HUD
        std::cout << "Round " << round << "\n";
        std::cout << "Actions:\n";
        std::cout << "  [a] Attack\n";
        std::cout << "  [i] Use item from inventory\n";
        std::cout << "  [r] Run (chance)\n";
        std::cout << "Choice: ";

        char choice;
        std::cin >> choice;

        std::cout << std::endl; // mezera

        // PLAYER TURN
        if (choice == 'a')
        {
            // miss 10%, crit 10%, dmg (rozptyl) -2+2
            if (chance(10)) // šance na miss
            {
                std::cout << "Player missed!\n";
            }
            else
            {
                int dmg = player.getStrength() + randInt(-2, 2); // damage = (strength) + rozptyl
                if (dmg < 0) dmg = 0; // damage nesmí být záporný

                bool crit = chance(10); // šance na critical
                if (crit) dmg *= 2; // critical zdvojnásobí dmg

                enemy.takeDamage(dmg); // odebere HP pro (Enemy)
                std::cout << "Player hits " << enemy.getName()
                          << " for " << dmg << " dmg"
                          << (crit ? " (CRIT!)" : "") << ".\n";
            }
        }
        else if (choice == 'i') // zobrazí staty pro (Player/Enemy) a inventář ze kterého si můžeme vybrat item
        {
            system("cls");

            std::cout << "Player HP: " << player.getHealth()
                  << " | STR: " << player.getStrength() << "\n";
            std::cout << enemy.getName()
                      << " HP: " << enemy.getHealth()
                      << " | DMG: " << enemy.getStrength() << "\n\n";

            Inventory& inv = player.getInventory(); // získá inventář hráče
            std::cout << "<--- INVENTORY --->\n";
            printInventoryForFight(inv); // vypíše položky v inventáři

            if (!inv.getItems().empty()) // pokud inventář není prázdný
            {
                std::cout << "\nSelected item: ";
                int idx; // index vybraného itemu
                std::cin >> idx; // načte index itemu

                if (idx != -1) // -1 se dá použít jako “storno”
                {
                    int itemId = -1; // uložíme itemID.
                    if (!getItemIdByIndex(inv, idx, itemId)) // převede index na itemID.
                    {
                        std::cout << "Invalid choice.\n"; // neplatný index
                    }
                    else // jinak máme platný itemID
                    {
                        // Použití itemu (heal potion atd.)
                        if (inv.useItem(itemId, player)) // zavolá polymorfní Use() na itemu
                        {
                            // když je to consumable, odeber 1 kus ze stacku/slotu
                            if (isConsumableById(inv, itemId))
                            {
                                inv.deleteItem(itemId);
                            }
                        }
                        else // pokud se nepodařilo použít
                        {
                            std::cout << "Item cannot be used.\n";
                        }
                    }
                }
            }
        }
        else if (choice == 'r')
        {
            // útěk: 35% šance
            if (chance(35))
            {
                std::cout << "You successfully ran away!\n";
                std::cout << "<--- (FIGHT ENDED) --->\n\n";
                GameState::getInstance()->save(); // Uloží stav hráče.
                waitEnter();
                return false;
            }
            std::cout << "Your attempt at running failed!\n";
        }
        else
        {
            std::cout << "Invalid choice (you lost a turn).\n";
        }

        // check po hráči
        if (!enemy.isAlive())
        {
            std::cout << enemy.getName() << " has been defeated!\n";
            std::cout << "<--- (YOU WON) --->\n\n";
            waitEnter();
            GameState::getInstance()->save(); // Uloží stav hráče.
            return true;
        }

        // ENEMY TURN
        // miss 12%, crit 8%, dmg (rozptyl) -1+1
        if (chance(12))
        {
            std::cout << enemy.getName() << " missed!\n";
        }
        else
        {
            int dmg = enemy.getStrength() + randInt(-1, 1); // enemy dmg = (strength) + rozptyl
            if (dmg < 0) dmg = 0;

            bool crit = chance(8); // 8% šance crit
            if (crit) dmg = static_cast<int>(dmg * 1.75); // menší crit než hráč

            player.takeDamage(dmg); // odebere HP hráči
            std::cout << enemy.getName() << " hits Player for "
                      << dmg << " dmg" << (crit ? " (CRIT!)" : "") << ".\n";
        }

        round++; // přičte kolo
        waitEnter();
    }

    if (player.getHealth() <= 0)
    {
        system("cls");
        std::cout << "Player has been defeated!\n";
        std::cout << "<--- (YOU LOST) --->\n\n";
        waitEnter();
        GameState::getInstance()->save(); // uloží stav
        return false;
    }

    if (!enemy.isAlive())
    {
        system("cls");
        std::cout << enemy.getName() << " has been defeated!\n";
        std::cout << "<--- (YOU WON) --->\n\n";
        waitEnter();
        GameState::getInstance()->save(); // uloží stav
        return true;
    }

    // fallback (nemělo by nastat)
    std::cout << "Fight ended.\n";
    GameState::getInstance()->save();
    return false;
}