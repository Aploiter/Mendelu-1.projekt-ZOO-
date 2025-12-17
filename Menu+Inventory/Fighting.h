#ifndef FIGHTING_H
#define FIGHTING_H

class Player;
class Enemy;

class Fighting
{
public:
    //Statická metoda (provede boj a vrátí výsledek)
    static bool fight(Player& player, Enemy& enemy); // Vrátí true = hráč vyhrál, false = hráč prohrál
};

#endif // FIGHTING_H
