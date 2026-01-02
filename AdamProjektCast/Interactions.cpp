// Interactions.cpp
#include "Interactions.h"
#include <iostream>
#include <limits>
#include <cctype>

GameController::GameController() : isRunning(true), moveCount(0) {
    // GameMap je automaticky inicializována v hlavičkovém souboru
}

void GameController::handleInput(char input) {
    Direction dir;
    bool validKey = false;

    // 1. Převod klávesy na směr (8=nahoru, 2=dolů, 4=vlevo, 6=vpravo)
    switch (input) {
        case '8': dir = Direction::UP;    validKey = true; break;
        case '2': dir = Direction::DOWN;  validKey = true; break;
        case '4': dir = Direction::LEFT;  validKey = true; break;
        case '6': dir = Direction::RIGHT; validKey = true; break;
        case 'q': case 'Q':
            isRunning = false;
            std::cout << "Hra ukončena uživatelem.\n";
            return;
        default:
            std::cout << "Neplatná klávesa! Použij 8/2/4/6 pro pohyb nebo Q pro konec.\n";
            return;
    }

    // 2. Výpočet cílových souřadnic podle aktuální pozice hráče
    int tr = gameMap.getPlayerRow();
    int tc = gameMap.getPlayerCol();
    if (dir == Direction::UP) tr--;
    else if (dir == Direction::DOWN) tr++;
    else if (dir == Direction::LEFT) tc--;
    else if (dir == Direction::RIGHT) tc++;

    // 3. KARAK LOGIKA: Průzkum nebo pohyb
    const Patterns::CellPattern* targetTile = gameMap.getTileAt(tr, tc);

    if (targetTile == nullptr) {
        // Kontrola, zda je čas na Bosse (po 10 úspěšných tazích)
        if (moveCount >= 10) {
            std::cout << "\n\033[1;31m!!! VAROVÁNÍ: Temnota houstne a země se třese !!!\033[0m\n";
            std::cout << "\033[1;31mNarazil jsi na doupě BOSSE!\033[0m\n";
            gameMap.placeBossTile(tr, tc);
            gameMap.movePlayer(dir);
            moveCount = 0; // Reset počítadla po souboji
            return;
        }

        // Standardní výběr ze 3 dlaždic, které navazují na současnou chodbu
        auto options = gameMap.getValidOptions(dir);

        if (options.empty()) {
            std::cout << "Tímto směrem nelze položit žádnou chodbu (v balíčku není vhodný dílek).\n";
            return;
        }

        gameMap.printTileOptions(options);
        std::cout << "Vyber si dlaždici (1-" << options.size() << ") nebo 0 pro zrušení tahu: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        if (choice > 0 && choice <= (int)options.size()) {
            gameMap.placeTile(tr, tc, options[choice - 1]);
            if (gameMap.movePlayer(dir)) {
                moveCount++; // Úspěšné položení a pohyb zvýší počítadlo
            }
        }
    } else {
        // Pokud dlaždice už existuje, zkusíme se na ni pohnout (kontroluje zdi)
        if (gameMap.movePlayer(dir)) {
            moveCount++;
            std::cout << "Posunul jsi se chodbou. (Tah: " << moveCount << "/10 do Bosse)\n";
        } else {
            std::cout << "Cestu blokuje stěna!\n";
        }
    }

    // 4. Kontrola vítězství (pokud hráč vstoupil na Exit dlaždici)
    if (gameMap.isPlayerAtExit()) {
        gameMap.printMap();
        std::cout << "\n" << "\033[1;32m" << "VÍTĚZSTVÍ! Našel jsi cestu z labyrintu!" << "\033[0m" << "\n";
        isRunning = false;
    }
}

void GameController::runGameLoop() {
    std::cout << "--- START HRY KARAK ---\n";
    std::cout << "Ovládání: 8=nahoru, 2=dolů, 4=vlevo, 6=vpravo, Q=konec\n";
    std::cout << "Prozkoumej podzemí a najdi cestu ven!\n";

    while (isRunning) {
        std::cout << "\n=========================================\n";
        // Vykreslení aktuálního stavu mapy a "mlhy" (fog of war)
        gameMap.printMap();

        char input;
        std::cout << "Tvůj tah (8/4/6/2/Q): ";
        if (!(std::cin >> input)) {
            isRunning = false;
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        handleInput(input);
    }

    std::cout << "--- KONEC HRY ---\n";
}