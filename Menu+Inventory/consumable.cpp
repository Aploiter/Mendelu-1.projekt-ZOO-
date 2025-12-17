#include "consumable.h"
#include <sstream>
#include "Item.h"
#include <iostream>
#include "Player.h"

consumable::consumable(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int healAmount, int effectId)
    : Item(itemID, name, description, limit, rarity), m_healAmount(healAmount), m_effectId(effectId) {}

consumable::consumable(const consumable& other)
    : Item(other), m_healAmount(other.m_healAmount), m_effectId(other.m_effectId) {}

int consumable::getHealAmount() const { return m_healAmount; }
int consumable::getEffectId() const { return m_effectId; }

std::string consumable::getSpecificInfo() const
{
    std::stringstream ss;
    ss << "Specific info (consumer - Potion):\n";
    ss << "  Healing: " << m_healAmount << " HP\n";
    ss << "  Effect ID: " << m_effectId << "\n";
    return ss.str();
}

void consumable::Use(Player& target)
{
    target.heal(m_healAmount);
}

std::unique_ptr<Item> consumable::clone() const
{
    return std::make_unique<consumable>(*this);
}