#include "Enemy.h"
#include <utility>

Enemy::Enemy(std::string name, int health, int strength) // konstruktor (Enemy)
{
    m_name = (std::move(name)); // přesune string name do m_name
    m_health = health;  // nastaví (m_health).
    m_strength = strength; // nastaví (m_strength).

    if (m_health < 0) m_health = 0; // zkontroluje, jestli nejsou (health) záporné
    if (m_strength < 0) m_strength = 0; // zkontroluje, jeslti (strength) není záporný
}

const std::string& Enemy::getName() const // getter pro (name).
{
    return m_name;
}

int Enemy::getHealth() const // getter pro (health).
{
    return m_health;
}

int Enemy::getStrength() const // getter pro (strength).
{
    return m_strength;
}

void Enemy::setHealth(int hp) // setter pro (health)
{
    m_health = hp; // nastaví (health)
    if (m_health < 0) m_health = 0; // omezí minimum na 0
}

void Enemy::takeDamage(int amount)
{
    if (amount < 0) amount = 0;
    m_health -= amount; // odečte damage od (m_health)
    if (m_health < 0) m_health = 0;
}

bool Enemy::isAlive() const
{
    return m_health > 0;
}

Enemy Enemy::clone() const // vytvoří kopii pro (Enemy).
{
    return Enemy(m_name, m_health, m_strength); // vrátí nový Enemy se stejnými hodnotami
}
