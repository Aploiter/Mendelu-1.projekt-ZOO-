#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h" // player obsahuje Inventory jako member, proto musí znát jeho typ.

class Player
{
private:
    int m_health;
    int m_strength;
    Inventory m_inventory; // inventář hráče (kompozice: Player vlastní inventory).

public:
    Player(int health = 100, int strength = 10, int inventoryCapacity = 20); // konstruktor s default hodnotami.

    int getHealth() const; // getter pro (Health), const = nemění objekt.
    int getStrength() const; // getter pro (Strength).

    //TODO: pro pozdejší fight (hotovo)
    void heal(int amount); // přidá HP.
    void takeDamage(int amount); // ubere HP.

    Inventory& getInventory(); // vrátí referenci na inventář (umožní přidávat itemy).
    const Inventory& getInventory() const; // const verze getteru (pro čtení bez změn).

    Player clone() const; // vytvoří kopii hráče,enemy a inventáře (pro save/load.)
};

#endif //PLAYER_H