#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy
{
private:
    std::string m_name;
    int m_health;
    int m_strength;

public:
    Enemy(std::string name = "Enemy", int health = 30, int strength = 5); // Konstruktor s defaulty.
    // metody pro vracení dat
    const std::string& getName() const;
    int getHealth() const;
    int getStrength() const;

    void setHealth(int hp); // nastaví HP
    void takeDamage(int amount); // odečte HP
    bool isAlive() const; // kontrola

    Enemy clone() const; // Vytvoří kopii pro (Enemy), (podobně jako Player, ale bez inventáře).
};

#endif // ENEMY_H
