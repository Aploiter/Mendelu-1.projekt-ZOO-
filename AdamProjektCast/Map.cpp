// Map.cpp

#include "Map.h"
#include "patterns.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath> // Pro std::abs


using namespace Patterns;

// --- DŮLEŽITÉ KONSTANTY pro kontrolu ASCII 5x5 dlaždic ---
constexpr int TOP_WALL_LINE = 0;
constexpr int BOTTOM_WALL_LINE = 2;

// Pro horizontální stěny: Kontrolujeme střed (index 2)
constexpr int CENTER_PASS_POS = 2;

// Pro vertikální stěny: Kontrolujeme samotné HRANICE (index 0 a 4) na řádku 1
constexpr int LEFT_BORDER_POS = 0;
constexpr int RIGHT_BORDER_POS = 4;


// --------------------------------------------------------
// Konstruktor (zahrnuje inicializaci Fog of War)
// --------------------------------------------------------
Map::Map() {
    // Inicializace exploredCells probíhá hned, protože mapa je definována v Map.h.
    size_t rows = mapa.size();
    size_t cols = rows > 0 ? mapa[0].size() : 0;

    if (rows > 0 && cols > 0) {
        // Inicializace matice na všechny 'false' (nenavštíveno)
        exploredCells.assign(rows, std::vector<bool>(cols, false));

        // Hráčova startovní pozice je prozkoumaná (předpoklad: [0, 0])
        if (playerRow < rows && playerCol < cols) {
            exploredCells[playerRow][playerCol] = true;
        }
    }
}


/**
 * Pomocná funkce: Kontroluje, zda je průchod mezi dvěma SOUSIEDNÍMI buňkami volný.
 */
bool Map::isPathOpen(size_t r1, size_t c1, size_t r2, size_t c2) const {
    if (r1 >= mapa.size() || r2 >= mapa.size() || c1 >= mapa[0].size() || c2 >= mapa[0].size()) return false;

    // Zajištění, že se jedná o přímého souseda
    if ((std::abs((int)r1 - (int)r2) + std::abs((int)c1 - (int)c2)) != 1) return false;

    const CellPattern* pattern1 = mapa[r1][c1];
    const CellPattern* pattern2 = mapa[r2][c2];

    // Kontrola platnosti ukazatelů
    if (!pattern1 || !pattern2) return false;

    // 1. Horizontální kontrola (r1 pod r2 -> pohyb nahoru)
    if (r1 > r2) {
        return (pattern1->lines[TOP_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR &&
                pattern2->lines[BOTTOM_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR);
    }
    // 2. Horizontální kontrola (r1 nad r2 -> pohyb dolů)
    else if (r1 < r2) {
        return (pattern1->lines[BOTTOM_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR &&
                pattern2->lines[TOP_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR);
    }
    // 3. Vertikální kontrola (c1 vpravo od c2 -> pohyb doleva)
    else if (c1 > c2) {
        return (pattern1->lines[1][LEFT_BORDER_POS] == PATH_CHAR &&
                pattern2->lines[1][RIGHT_BORDER_POS] == PATH_CHAR);
    }
    // 4. Vertikální kontrola (c1 vlevo od c2 -> pohyb doprava)
    else if (c1 < c2) {
        return (pattern1->lines[1][RIGHT_BORDER_POS] == PATH_CHAR &&
                pattern2->lines[1][LEFT_BORDER_POS] == PATH_CHAR);
    }

    return false;
}


// --------------------------------------------------------
// Implementace pohybu a kolizí
// --------------------------------------------------------
bool Map::movePlayer(Direction dir) {
    size_t targetRow = playerRow;
    size_t targetCol = playerCol;

    // 1. Počítání cílové pozice a kontrola hranic
    switch (dir) {
        case Direction::UP:
            if (playerRow == 0) return false;
            targetRow--;
            break;
        case Direction::DOWN:
            if (playerRow == mapa.size() - 1) return false;
            targetRow++;
            break;
        case Direction::LEFT:
            if (playerCol == 0) return false;
            targetCol--;
            break;
        case Direction::RIGHT:
            if (playerCol == mapa[0].size() - 1) return false;
            targetCol++;
            break;
    }

    // 2. Kontrola kolize
    if (!isPathOpen(playerRow, playerCol, targetRow, targetCol)) {
        return false;
    }

    // 3. Pohyb je povolen
    playerRow = targetRow;
    playerCol = targetCol;

    // Označení cílové buňky jako prozkoumané
    exploredCells[playerRow][playerCol] = true;

    return true;
}

// --------------------------------------------------------
// Implementace kontroly cíle
// --------------------------------------------------------
bool Map::isPlayerAtExit() const {
    // Kontroluje, zda se hráč nachází na buňce EXIT.
    return mapa[playerRow][playerCol] == &Patterns::H0D0L1R1EXIT;
}


// --------------------------------------------------------
// Implementace tisku mapy (s "Fog of War" a opravenou pozicí hráče)
// --------------------------------------------------------
void Map::printMap() {
    if (mapa.empty() || mapa[0].empty() || exploredCells.empty()) {
        std::cerr << "CHYBA: Mapa nebo stav prozkoumání jsou prázdné.\n";
        return;
    }

    size_t rows = mapa.size();
    size_t cols = mapa[0].size();

    for (size_t r = 0; r < rows; ++r) {
        for (int line = 0; line < 3; ++line) {
            for (size_t c = 0; c < cols; ++c) {

                const CellPattern* patternPtr = mapa[r][c];
                bool isExplored = exploredCells[r][c];
                bool isVisible = (r == playerRow && c == playerCol);

                // Zjištění, zda je buňka bezprostřední a průchozí soused
                if (!isVisible && (std::abs((int)r - (int)playerRow) + std::abs((int)c - (int)playerCol) == 1)) {
                    if (isPathOpen(playerRow, playerCol, r, c)) {
                        isVisible = true;
                    }
                }

                // --- LOGIKA "FOG OF WAR" ---
                if (!isVisible && !isExplored) {
                    // Vykreslení neviditelného prázdného místa (5 mezer)
                    std::cout << RESET << "     ";
                    continue;
                }

                // --- KONTROLA NULLPTR ---
                if (patternPtr == nullptr) {
                    std::cout << RESET << "ERR";
                    continue;
                }

                // --- LOGIKA BAREV a TISKU ---

                const char* color_code = nullptr;

                // 1. Barevný kód: Zhasnutý stav
                if (isExplored && !isVisible) {
                    color_code = DARK_GRAY;
                }

                // 2. Hráč
                if (r == playerRow && c == playerCol) {
                    color_code = LIGHT_GREEN;
                }
                // 3. Cíl
                else if (patternPtr == &Patterns::H0D0L1R1EXIT) {
                    color_code = LIGHT_RED;
                }
                // 4. Viditelný soused
                else if (isVisible) {
                     color_code = BLUE;
                }

                // Aplikace barvy
                std::cout << RESET;
                if (color_code != nullptr)
                    std::cout << color_code;

                // Vykreslení segmentu DLAŽDICE
                std::string segment = patternPtr->lines[line];

                // Vykreslení hráče 'H' na STŘEDNÍ POZICI (index 2 pro šířku 5)
                if (r == playerRow && c == playerCol && line == 1 && segment.length() > CENTER_PASS_POS) {
                    segment[CENTER_PASS_POS] = PLAYER_CHAR; // CENTER_PASS_POS = 2
                }
                std::cout << segment;

                // Důležité: Reset po segmentu
                std::cout << RESET;
            }

            std::cout << "\n";
        }
    }
}