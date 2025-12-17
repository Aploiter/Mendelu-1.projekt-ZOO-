//
// Created by ltopo on 09.12.2025.
//

#include "consumable.h"
#include <sstream>
#include "Item.h"
#include <iostream>
consumable::consumable(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int healAmount, int effectId)
    :Item(itemID,name,description,limit,rarity)
{
    m_healAmount = healAmount;
    m_effectId = effectId;
}
int consumable::getHealAmount() const {
    return m_healAmount;
}

int consumable::getEffectId() const {
    return m_effectId;
}
std::string consumable::getSpecificInfo() const {
    std::stringstream ss;
    ss << "SPECIFICKÉ INFO (Spotřební - Lektvar):\n";
    ss << "  Léčení: " << m_healAmount << " HP\n";
    ss << "  ID Efektu: " << m_effectId << "\n";

    return ss.str(); // Vrátíme výsledný string.
}