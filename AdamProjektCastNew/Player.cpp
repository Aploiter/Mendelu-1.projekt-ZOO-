#include "Player.h"

Player::Player(int health, int strength) // inicializuje zdraví a sílu hráče
{
    m_health = health;
    m_strength = strength;
}

int Player::getHealth() const
{
    return m_health;
}

int Player::getStrength() const
{
    return m_strength;
}

Player Player::clone() const // Vytvoří kopii hráče (pro bezpečné ukládání/načítání stavu hráče)
{
    return Player(m_health, m_strength);  // Vrátí nový objekt Player se stejnýma hodnotama
    // TODO přidat inventář
}