#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "patterns.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

// Struktura pro výběr dlaždice
struct TileOption {
    int index; // Pozice v balíčku pro pozdější smazání
    const Patterns::CellPattern* pattern;
};

// Barvy a znaky
static const char* RESET = "\033[0m";
static const char* LIGHT_GREEN = "\033[1;32m";
static const char* LIGHT_RED = "\033[1;31m";
static const char* BLUE = "\033[34m";
inline static const char* DARK_GRAY = "\033[90m";
#define PATH_CHAR ' '
const char PLAYER_CHAR = 'H';

class Map {
private:
    int playerRow;
    int playerCol;
    std::vector<std::vector<const Patterns::CellPattern*>> mapa;
    std::vector<std::vector<bool>> exploredCells;
    std::vector<const Patterns::CellPattern*> tileDeck;

    void initializeDeck();

public:
    Map();
    void printMap();
    bool movePlayer(Direction dir);
    bool isPathOpen(int r1, int c1, int r2, int c2) const;
    bool isPlayerAtExit() const;

    // Gettery pro GameController
    int getPlayerRow() const { return playerRow; }
    int getPlayerCol() const { return playerCol; }
    const Patterns::CellPattern* getTileAt(int r, int c) const;

    // Karak mechanika výběru
    std::vector<TileOption> getValidOptions(Direction dir);
    void placeTile(int r, int c, TileOption option);
    void printTileOptions(const std::vector<TileOption>& options);
    void placeBossTile(int r, int c);
};

#endif