#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"

class Player
{
private:
    int m_health;
    int m_strength;
    Inventory m_inventory;

public:
    Player(int health = 100, int strength = 10, int inventoryCapacity = 20);

    int getHealth() const;
    int getStrength() const;

    void heal(int amount);
    void takeDamage(int amount); // TODO: Pro pozdější boj

    Inventory& getInventory();
    const Inventory& getInventory() const;

    Player clone() const; // Pro save/load
};

#endif //PLAYER_H