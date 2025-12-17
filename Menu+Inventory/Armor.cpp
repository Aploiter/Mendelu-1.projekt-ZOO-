#include <sstream>
#include <iostream>
#include <ostream>
#include "Armor.h"
#include "Item.h"

Armor::Armor(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int defense, std::string slot)
    : Item(itemID, name, description, limit, rarity), m_defense(defense), m_slot(slot) {}

Armor::Armor(const Armor& other)
    : Item(other), m_defense(other.m_defense), m_slot(other.m_slot) {}

int Armor::getDefense() const { return m_defense; }
const std::string& Armor::getSlot() const { return m_slot; }

std::string Armor::getSpecificInfo() const
{
    std::stringstream ss;
    ss << "Specific info (Armor):\n";
    ss << "  Defense: " << m_defense << "\n";
    ss << "  Item slot: " << m_slot << "\n";
    return ss.str();
}

void Armor::Use(Player& target)
{
    std::cout << "Armor cannot be equiped.\n";
}

std::unique_ptr<Item> Armor::clone() const
{
    return std::make_unique<Armor>(*this);
}