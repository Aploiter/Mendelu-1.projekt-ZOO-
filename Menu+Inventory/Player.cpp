#include "Player.h"
#include <iostream>

Player::Player(int health, int strength, int inventoryCapacity)
    : m_inventory(inventoryCapacity)
{
    m_health = health;
    m_strength = strength;
}

int Player::getHealth() const { return m_health; }
int Player::getStrength() const { return m_strength; }

void Player::heal(int amount)
{
    m_health += amount;
    std::cout << "Player has been healed: " << amount << " HP! (Current HP: " << m_health << ")\n";
}

void Player::takeDamage(int amount)
{
    m_health -= amount;
    if (m_health < 0) m_health = 0;
    std::cout << "Player has been dealt: " << amount << " damage! (Current HP: " << m_health << ")\n";
}

Inventory& Player::getInventory() { return m_inventory; }
const Inventory& Player::getInventory() const { return m_inventory; }

Player Player::clone() const
{
    Player copy(m_health, m_strength, m_inventory.getCapacityLimit());

    // Hluboká kopie inventáře
    for (const auto& item : m_inventory.getItems())
    {
        if (item)
        {  // Bezpečnostní check
            copy.getInventory().addItem(item->clone());
        }
    }

    return copy;
}