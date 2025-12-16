//
// Created by ltopo on 09.12.2025.
//

#include "Weapon.h"
#include <sstream>
#include "Item.h"

Weapon::Weapon(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int damage,const std::string& damageType)
    :Item(itemID,name,description,limit,rarity)
{
    m_damage = damage;
    m_damageType = damageType;
}

int Weapon::getDamage() const { return m_damage; }
const std::string& Weapon::getDamageType() const { return m_damageType; }

std::string Weapon::getSpecificInfo() const {
    std::stringstream ss;
    ss << "SPECIFICKÉ INFO (Zbraň):\n";
    ss << "  Poskozeni: " << m_damage << "\n";
    ss << "  Typ poskozeni: " << m_damageType << "\n";
    return ss.str();
}