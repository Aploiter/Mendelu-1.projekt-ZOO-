#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <memory>
#include "Item.h"

class Weapon : public Item
{
    int m_damage;
    std::string m_damageType;

public:
    Weapon(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int damage, const std::string& damageType);
    Weapon(const Weapon& other);

    ~Weapon() override = default;

    int getDamage() const;
    const std::string& getDamageType() const;

    std::string getSpecificInfo() const override;
    void Use(class Player& target) override;

    std::unique_ptr<Item> clone() const override;
};

#endif //WEAPON_H