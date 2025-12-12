#include "Player.h"

#include <iostream>
#include <ostream>

Player::Player(int health, int strength)
{
    m_player_health = health;
    m_player_strength = strength;
}

int Player::getHealth()
{
    return m_player_health;
}

int Player::getStrength()
{
    return m_player_strength;
}

