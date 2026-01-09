#include "Map.h"
#include "patterns.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

using namespace Patterns;

// --- KONSTANTY PRO ASCII DLAŽDICE 5x5 ---
constexpr int TOP_WALL_LINE = 0;
constexpr int BOTTOM_WALL_LINE = 2;
constexpr int CENTER_PASS_POS = 2;
constexpr int LEFT_BORDER_POS = 0;
constexpr int RIGHT_BORDER_POS = 4;
constexpr int MAX_DISCOVERY_TILES = 10; // Maximální počet nových dlaždic

Map::Map() {
    // Inicializace herní plochy 15x15
    int size = 15;
    mapa.assign(size, std::vector<const CellPattern*>(size, nullptr));
    exploredCells.assign(size, std::vector<bool>(size, false));

    // Reset počítadla položených dlaždic
    tilesPlaced = 0;

    // Startovní pozice uprostřed mapy
    playerRow = size / 2;
    playerCol = size / 2;

    // Startovní dlaždice je křižovatka všech cest (nepočítá se do limitu objevování)
    mapa[playerRow][playerCol] = &Patterns::H1D1L1R1;
    exploredCells[playerRow][playerCol] = true;

    initializeDeck();
}

void Map::initializeDeck() {
    // Seznam dostupných vzorů dlaždic
    std::vector<const CellPattern*> types = {
        &Patterns::H1D1L1R1, &Patterns::H0D1L1R1, &Patterns::H1D0L1R1,
        &Patterns::H1D1L0R1, &Patterns::H1D1L1R0, &Patterns::H0D0L1R1,
        &Patterns::H0D1L0R1, &Patterns::H1D0L1R0, &Patterns::H0D0L0R1
    };

    // Naplnění balíčku
    for (int i = 0; i < 8; ++i) {
        for (auto type : types) {
            tileDeck.push_back(type);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tileDeck.begin(), tileDeck.end(), g);
}

const CellPattern* Map::getTileAt(int r, int c) const {
    if (r < 0 || r >= (int)mapa.size() || c < 0 || c >= (int)mapa[0].size()) return nullptr;
    return mapa[r][c];
}

bool Map::isPathOpen(int r1, int c1, int r2, int c2) const {
    if (r2 < 0 || r2 >= (int)mapa.size() || c2 < 0 || c2 >= (int)mapa[0].size()) return false;

    const CellPattern* p1 = mapa[r1][c1];
    const CellPattern* p2 = mapa[r2][c2];

    if (!p1 || !p2) return false;

    if (r1 > r2) { // Pohyb nahoru
        return (p1->lines[TOP_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR &&
                p2->lines[BOTTOM_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR);
    }
    if (r1 < r2) { // Pohyb dolů
        return (p1->lines[BOTTOM_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR &&
                p2->lines[TOP_WALL_LINE][CENTER_PASS_POS] == PATH_CHAR);
    }
    if (c1 > c2) { // Pohyb doleva
        return (p1->lines[1][LEFT_BORDER_POS] == PATH_CHAR &&
                p2->lines[1][RIGHT_BORDER_POS] == PATH_CHAR);
    }
    if (c1 < c2) { // Pohyb doprava
        return (p1->lines[1][RIGHT_BORDER_POS] == PATH_CHAR &&
                p2->lines[1][LEFT_BORDER_POS] == PATH_CHAR);
    }
    return false;
}

std::vector<TileOption> Map::getValidOptions(Direction dir) {
    std::vector<TileOption> options;

    // --- LOGIKA LIMITU OBJEVOVÁNÍ ---
    // Pokud hráč už položil 10 dlaždic, vracíme prázdný seznam (nelze dál stavět)
    if (tilesPlaced >= MAX_DISCOVERY_TILES) {
        return options;
    }

    int tr = playerRow, tc = playerCol;
    if (dir == Direction::UP) tr--;
    else if (dir == Direction::DOWN) tr++;
    else if (dir == Direction::LEFT) tc--;
    else if (dir == Direction::RIGHT) tc++;

    if (tr < 0 || tr >= (int)mapa.size() || tc < 0 || tc >= (int)mapa[0].size()) return options;

    // Pokud je políčko již obsazené, nové možnosti nenabízíme
    if (mapa[tr][tc] != nullptr) return options;

    for (int i = (int)tileDeck.size() - 1; i >= 0 && options.size() < 3; --i) {
        mapa[tr][tc] = tileDeck[i];
        if (isPathOpen(playerRow, playerCol, tr, tc)) {
            options.push_back({i, tileDeck[i]});
        }
        mapa[tr][tc] = nullptr;
    }
    return options;
}

void Map::placeTile(int r, int c, TileOption option) {
    if (r < 0 || r >= (int)mapa.size() || c < 0 || c >= (int)mapa[0].size()) return;

    mapa[r][c] = option.pattern;
    exploredCells[r][c] = true;

    // Zvýšíme počet položených dlaždic
    tilesPlaced++;

    if (option.index >= 0 && option.index < (int)tileDeck.size()) {
        tileDeck.erase(tileDeck.begin() + option.index);
    }
}

bool Map::movePlayer(Direction dir) {
    int tr = playerRow, tc = playerCol;
    if (dir == Direction::UP) tr--;
    else if (dir == Direction::DOWN) tr++;
    else if (dir == Direction::LEFT) tc--;
    else if (dir == Direction::RIGHT) tc++;

    if (isPathOpen(playerRow, playerCol, tr, tc)) {
        playerRow = tr;
        playerCol = tc;
        exploredCells[playerRow][playerCol] = true;
        return true;
    }
    return false;
}

void Map::printMap() {
    // Info o zbývajících tazích pro objevování
    std::cout << "Objevování: " << tilesPlaced << " / " << MAX_DISCOVERY_TILES << "\n";
    if (tilesPlaced >= MAX_DISCOVERY_TILES) {
        std::cout << LIGHT_RED << "POZOR: Balíček dlaždic je prázdný! Nemůžeš objevovat nové chodby.\n" << RESET;
    }

    for (int r = 0; r < (int)mapa.size(); ++r) {
        for (int line = 0; line < 3; ++line) {
            for (int c = 0; c < (int)mapa[0].size(); ++c) {
                const CellPattern* p = mapa[r][c];

                if (p == nullptr || !exploredCells[r][c]) {
                    std::cout << "     ";
                    continue;
                }

                bool isPlayer = (r == playerRow && c == playerCol);

                if (isPlayer) std::cout << LIGHT_GREEN;
                else if (p == &Patterns::H0D0L1R1EXIT) std::cout << LIGHT_RED;
                else std::cout << BLUE;

                std::string s = p->lines[line];
                if (isPlayer && line == 1) s[CENTER_PASS_POS] = PLAYER_CHAR;

                std::cout << s << RESET;
            }
            std::cout << "\n";
        }
    }
}

void Map::printTileOptions(const std::vector<TileOption>& options) {
    if (options.empty()) {
        std::cout << LIGHT_RED << "Žádné dostupné dlaždice (buď limit vyčerpán nebo slepá ulička)!\n" << RESET;
        return;
    }

    std::cout << "\nDOSTUPNÉ DLAŽDICE (Karak výběr):\n";
    for (int line = 0; line < 3; ++line) {
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << i + 1 << ": " << BLUE << options[i].pattern->lines[line] << RESET << "   ";
        }
        std::cout << "\n";
    }
}

void Map::placeBossTile(int r, int c) {
    if (r < 0 || r >= (int)mapa.size() || c < 0 || c >= (int)mapa[0].size()) return;

    mapa[r][c] = &Patterns::BOSS_TILE;
    exploredCells[r][c] = true;
    // Boss tile se do limitu 10 tahů obvykle nepočítá, ale pokud ano, přidej tilesPlaced++;
}

bool Map::isPlayerAtExit() const {
    if (mapa[playerRow][playerCol] == nullptr) return false;
    return mapa[playerRow][playerCol] == &Patterns::H0D0L1R1EXIT;
}