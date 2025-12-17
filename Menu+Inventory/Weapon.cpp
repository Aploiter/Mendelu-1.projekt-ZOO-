#include "Weapon.h"
#include <sstream>
#include "Item.h"
#include <iostream>

Weapon::Weapon(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int damage, const std::string& damageType)
    : Item(itemID, name, description, limit, rarity), m_damage(damage), m_damageType(damageType) {}

Weapon::Weapon(const Weapon& other)
    : Item(other), m_damage(other.m_damage), m_damageType(other.m_damageType) {}

int Weapon::getDamage() const { return m_damage; }
const std::string& Weapon::getDamageType() const { return m_damageType; }

std::string Weapon::getSpecificInfo() const
{
    std::stringstream ss;
    ss << "Specific info (Weapon):\n";
    ss << "  Damage: " << m_damage << "\n";
    ss << "  Type of damage: " << m_damageType << "\n";
    return ss.str();
}

void Weapon::Use(Player& target)
{
    std::cout << "Weapon cannot be equiped.\n";
}

std::unique_ptr<Item> Weapon::clone() const
{
    return std::make_unique<Weapon>(*this);
}