//
// Created by ltopo on 09.12.2025.
//
#include <sstream>
#include <iostream>
#include <ostream>
#include "Armor.h"
#include "Item.h"

Armor::Armor(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity,int defense,std::string slot)
:Item(itemID,name,description,limit,rarity)
{
    m_defense=defense;
    m_slot=slot;
}

int Armor::getDefense() const { return m_defense; }
const std::string& Armor::getSlot() const { return m_slot; }

std::string Armor::getSpecificInfo() const{
    std::stringstream ss;
    ss << "SPECIFICKÉ INFO (Brnění):\n";
    ss << "  Obrana: " << m_defense << "\n";
    ss << "  Slot pro noseni: " << m_slot << "\n";

    return ss.str();
}