#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int m_health;
    int m_strength;
    // TODO přidat inventář
public:
    Player(int health = 100, int strength = 10);
    int getHealth() const;
    int getStrength() const;
    Player clone() const; // save/load (metoda pro kopírování objektů)
};

#endif