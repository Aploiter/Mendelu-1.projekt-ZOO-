//
// Created by ltopo on 09.12.2025.
//

#ifndef YOYOYOYO_WEAPON_H
#define YOYOYOYO_WEAPON_H
#include <string>
#include "Item.h"

class Weapon : public Item {        //Pod trida neboli dedicnost na item
    int m_damage;
    std::string m_damageType;
    public:
    Weapon(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int damage, const std::string& damageType);
    ~Weapon() override=default;
    int getDamage() const;
    const std::string& getDamageType() const;
    std::string getSpecificInfo() const override;
    void Use(class Player& target)override;
};


#endif //YOYOYOYO_WEAPON_H