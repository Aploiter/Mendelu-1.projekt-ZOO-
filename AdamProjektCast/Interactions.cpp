// Interactions.cpp

#include "Interactions.h"
#include <limits> // pro std::numeric_limits


GameController::GameController() : isRunning(true) {
    // GameMap je automaticky inicializována.
}

void GameController::handleInput(char input) {
    Direction dir;
    bool moved = false;

    // Vstup je znak, takže kontrolujeme znaky '8', '2', '4', '6' a 'q'.
    switch (std::tolower(input)) {
        case '8': // Nahoru
            dir = Direction::UP;
            moved = gameMap.movePlayer(dir);
            break;
        case '2': // Dolů
            dir = Direction::DOWN;
            moved = gameMap.movePlayer(dir);
            break;
        case '4': // Vlevo
            dir = Direction::LEFT;
            moved = gameMap.movePlayer(dir);
            break;
        case '6': // Vpravo
            dir = Direction::RIGHT;
            moved = gameMap.movePlayer(dir);
            break;
        case 'q':
            isRunning = false;
            std::cout << "\nHra ukončena uživatelem.\n";
            return;
        default:
            std::cout << "Neplatný vstup. Použijte 8/2/4/6 pro pohyb nebo Q pro ukončení.\n";
            return;
    }

    // Dodatečná kontrola pro ukončení hry po úspěšném pohybu
    if (moved && gameMap.isPlayerAtExit()) {
        gameMap.printMap();
        std::cout << "\n" << LIGHT_GREEN << "VÍTĚZSTVÍ! Úspěšně jste se dostali ven!" << RESET << "\n";
        isRunning = false;
    }
}

void GameController::runGameLoop() {
    std::cout << "--- START HRY ---\n";
    std::cout << "Použijte 8/6/4/2 pro pohyb, Q pro ukončení.\n";

    while (isRunning) {
        // Vyčistit obrazovku (optional, složitější na multi-platform)
        std::cout << "\n=========================================\n";

        // Vykreslení mapy
        gameMap.printMap();

        // Přijetí vstupu
        char input;
        std::cout << "Váš tah (8/6/4/2/Q): ";

        // Používáme std::cin >> input
        if (!(std::cin >> input)) {
            // Chyba vstupu (např. EOF), ukončení smyčky
            isRunning = false;
            break;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Zpracování vstupu a logiky
        handleInput(input);

    }

    std::cout << "--- KONEC HRY ---\n";
}