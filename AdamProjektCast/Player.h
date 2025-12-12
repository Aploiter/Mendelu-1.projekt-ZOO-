#ifndef ADAMPROJEKTCAST_PLAYER_H
#define ADAMPROJEKTCAST_PLAYER_H


class Player
{
private:
    int m_player_health;
    int m_player_strength;
public:
    Player(int health, int strength);
    int getHealth();
    int getStrength();
};


#endif //ADAMPROJEKTCAST_PLAYER_H