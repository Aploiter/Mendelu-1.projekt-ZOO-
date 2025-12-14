// Map.cpp

#include "Map.h"
#include "patterns.h"
#include <iostream>
#include <vector>
#include <string>

using namespace Patterns;

// --- Konstanty pro kolize ---
constexpr int TOP_WALL_LINE = 0;
constexpr int BOTTOM_WALL_LINE = 2;

// Pro horizontální stěny: Kontrolujeme střed (index 2), zda je volný pro průchod.
constexpr int CENTER_PASS_POS = 2;

// Pro vertikální stěny: Kontrolujeme samotné HRANICE (index 0 a 4) na řádku 1 (středním řádku), zda jsou volné pro průchod.
constexpr int LEFT_BORDER_POS = 0;
constexpr int RIGHT_BORDER_POS = 4;


Map::Map() {
    // Konstruktor je prázdný
}

// --------------------------------------------------------
// Implementace pohybu a kolizí
// --------------------------------------------------------
bool Map::movePlayer(Direction dir) {
    size_t targetRow = playerRow;
    size_t targetCol = playerCol;

    const CellPattern* currentPattern = mapa[playerRow][playerCol];
    const CellPattern* targetPattern = nullptr;

    // 1. Počítání cílové pozice a kontrola hranic
    switch (dir) {
        case Direction::UP:
            if (playerRow == 0) return false;
            targetRow--;
            targetPattern = mapa[targetRow][targetCol];
            break;
        case Direction::DOWN:
            if (playerRow == mapa.size() - 1) return false;
            targetRow++;
            targetPattern = mapa[targetRow][targetCol];
            break;
        case Direction::LEFT:
            if (playerCol == 0) return false;
            targetCol--;
            targetPattern = mapa[targetRow][targetCol];
            break;
        case Direction::RIGHT:
            if (playerCol == mapa[0].size() - 1) return false;
            targetCol++;
            targetPattern = mapa[targetRow][targetCol];
            break;
    }

    // 2. Kontrola kolize: Předpokládáme kolizi, dokud neprokážeme, že je volná cesta (' ').
    bool collision = true;

    switch (dir) {
        // Horizontální průchody (Nahoru/Dolů) - Kontrolujeme střed (index 2)
        case Direction::UP:
            // Musí být mezera (' ') ve středu nahoře (AKTUÁLNÍ) A mezera ve středu dole (CÍLOVÁ)
            if (currentPattern->lines[TOP_WALL_LINE][CENTER_PASS_POS] == ' ' &&
                targetPattern->lines[BOTTOM_WALL_LINE][CENTER_PASS_POS] == ' ') {
                collision = false;
            }
            break;

        case Direction::DOWN:
            // Musí být mezera (' ') ve středu dole (AKTUÁLNÍ) A mezera ve středu nahoře (CÍLOVÁ)
            if (currentPattern->lines[BOTTOM_WALL_LINE][CENTER_PASS_POS] == ' ' &&
                targetPattern->lines[TOP_WALL_LINE][CENTER_PASS_POS] == ' ') {
                collision = false;
            }
            break;

        // Vertikální průchody (Vlevo/Vpravo) - Kontrolujeme hranice (index 0 a 4)
        case Direction::LEFT:
            // Musí být mezera (' ') na levé HRANICI AKTUÁLNÍ buňky (index 0)
            // A mezera na pravé HRANICI CÍLOVÉ buňky (index 4)
            if (currentPattern->lines[1][LEFT_BORDER_POS] == ' ' &&
                targetPattern->lines[1][RIGHT_BORDER_POS] == ' ') {
                collision = false;
            }
            break;

        case Direction::RIGHT:
            // Musí být mezera (' ') na pravé HRANICI AKTUÁLNÍ buňky (index 4)
            // A mezera na levé HRANICI CÍLOVÉ buňky (index 0)
            if (currentPattern->lines[1][RIGHT_BORDER_POS] == ' ' &&
                targetPattern->lines[1][LEFT_BORDER_POS] == ' ') {
                collision = false;
            }
            break;
    }

    if (collision) {
        return false;
    }

    // 3. Pohyb je povolen
    playerRow = targetRow;
    playerCol = targetCol;

    return true;
}

// --------------------------------------------------------
// Implementace kontroly cíle
// --------------------------------------------------------
bool Map::isPlayerAtExit() const {
    // Kontroluje, zda se hráč nachází na buňce, která je definována jako EXIT
    return mapa[playerRow][playerCol] == &Patterns::H0D0L1R1EXIT;
}


// --------------------------------------------------------
// Implementace tisku mapy (s barvami a dynamickým hráčem)
// --------------------------------------------------------
void Map::printMap() {
    // V Map.cpp se netiskne úvodní zpráva, tu tiskne GameController
    if (mapa.empty() || mapa[0].empty()) {
        std::cerr << "CHYBA: Mapa je prázdná.\n";
        return;
    }

    size_t rows = mapa.size();
    size_t cols = mapa[0].size();
    size_t last_row = rows - 1;
    size_t last_col = cols - 1;

    for (size_t r = 0; r < rows; ++r)
    {
        for (int line = 0; line < 3; ++line)
        {
            for (size_t c = 0; c < cols; ++c)
            {
                const CellPattern* patternPtr = mapa[r][c];
                const char* color_code = nullptr;

                // Určení, zda je buňka cílová nebo je na ní hráč
                bool isPlayerCell = (r == playerRow && c == playerCol);
                bool isExitCell = (r == last_row && c == last_col);

                // --- LOGIKA BAREV: Zvýraznění buňky hráče ZELENĚ ---
                if (isPlayerCell) {
                    color_code = LIGHT_GREEN;
                }
                else if (isExitCell) {
                    color_code = LIGHT_RED;
                }

                // Aplikace barvy
                if (color_code != nullptr)
                    std::cout << color_code;

                if (patternPtr) {
                    std::string segment = patternPtr->lines[line];

                    // Vykreslení hráče 'H' na pozici 2 (střed)
                    if (isPlayerCell && line == 1 && segment.length() > 2) {
                        // Znak hráče je 'H' (z původní implementace),
                        // pokud chcete '@', stačí změnit na segment[2] = '@';
                        segment[2] = 'H';
                    }
                    std::cout << segment;
                }

                // Reset barvy po vytištění buňky
                if (color_code != nullptr)
                    std::cout << RESET;
            }

            std::cout << "\n";
        }
    }
}