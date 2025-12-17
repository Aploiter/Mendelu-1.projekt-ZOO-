// Map.h

#ifndef MAP_H
#define MAP_H

#include <vector>
#include "patterns.h"

// DEFINICE ENUMU DIRECTION (Pouze zde!)
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// ANSI Escape kódy pro barvy:
static const char* RESET = "\033[0m";
static const char* LIGHT_GREEN = "\033[1;32m";
static const char* LIGHT_RED = "\033[1;31m";
static const char* BLUE = "\033[34m";
inline static const char* DARK_GRAY = "\033[90m";

#define PATH_CHAR ' '
const char PLAYER_CHAR = 'H';

class Map {
private:
    int playerRow = 0; // Startovní souřadnice (0, 0)
    int playerCol = 0;
    std::vector<std::vector<bool>> exploredCells;
    std::vector<std::vector<const Patterns::CellPattern*>> mapa = {
        { &Patterns::H0D0L0R1, &Patterns::H0D1L1R0, &Patterns::H0D0L0R1, &Patterns::H0D1L1R1, &Patterns::H0D1L1R0 },
        { &Patterns::H0D1L0R1, &Patterns::H1D0L1R1, &Patterns::H0D0L1R1, &Patterns::H1D1L1R0, &Patterns::H1D1L0R0 },
        { &Patterns::H1D0L0R0, &Patterns::H0D1L0R1, &Patterns::H0D0L1R1, &Patterns::H1D0L1R1, &Patterns::H1D1L0R0 },
        { &Patterns::H0D0L0R1, &Patterns::H1D0L1R1, &Patterns::H0D0L1R1, &Patterns::H0D0L1R1, &Patterns::H0D0L1R1EXIT }
    };

public:
    Map();

    void printMap();
    void initializeExploration();
    bool movePlayer(Direction dir);
bool isPathOpen(int r1, int c1, int r2, int c2) const;
    bool isPlayerAtExit() const;
};

#endif // MAP_H