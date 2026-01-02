#include "Player.h"
#include <iostream>

Player::Player(int health, int strength, int inventoryCapacity)
    : m_inventory(inventoryCapacity)
{
    m_health = health; // nastaví (m_health) na hodnotu z parametru (health).
    m_strength = strength; // nastaví (m_strength) na hodnotu z parametru (strength).
}

int Player::getHealth() const // vrací aktuální HP
{
    return m_health;
}

int Player::getStrength() const // vrací aktuální STR
{
    return m_strength;
}

void Player::heal(int amount)
{
    m_health += amount; // přičte amount k HP.
    std::cout << "Player has been healed: " << amount << " HP! (Current HP: " << m_health << ")\n";
}

void Player::takeDamage(int amount)
{
    m_health -= amount; // odečte amount od HP.
    if (m_health < 0) m_health = 0; // pokud je HP menší jak 0 nastaví se na 0 (aby nešlo do mínusových hodnot)
}

Inventory& Player::getInventory() // Vrátí inventář jako referenci.
{
    return m_inventory;
}

const Inventory& Player::getInventory() const // vrátí inventár jako referenci (const verze)
{
    return m_inventory;
}

Player Player::clone() const // kopie hráče/inventáře.
{
    Player copy(m_health, m_strength, m_inventory.getCapacityLimit()); // vytvoří kopii se stejnými staty a kapacitou.

    // kopie inventáře
    for (const auto& item : m_inventory.getItems()) // projde všechny itemy v inventáři (unique_ptr).
    {
        if (item) // kontrola, že ukazatel není null.
        {
            copy.getInventory().addItem(item->clone()); // přidá klon itemu do inventáře kopie.
        }
    }
    return copy;
}