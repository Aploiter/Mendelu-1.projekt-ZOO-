//
// Created by ltopo on 09.12.2025.
//
#include <sstream> //pro lepsi stringy
#include "Item.h"
#include <iostream>
#include <ostream>
std::string RarityToString(Rarity rarity) {
    switch (rarity) {
        case Rarity::Common: return "Common";
        case Rarity::Rare: return "Rare";
        case Rarity::Epic: return "Epic";
        default: return "Neznámá";
    }
}
Item::Item(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity) {
    m_itemID = itemID;
    m_name = name;
    m_description = description;
    m_rarity = rarity;
    m_limit = limit;
    m_count=1;
}
int Item::getItemID() const{return m_itemID;}
const std::string& Item::getName() const{return m_name;}
const std::string& Item::getDescription() const{return m_description;}
int Item::getLimit() const{return m_limit;}
Rarity Item::getRarity() const { return m_rarity; }
virtual void Use(class Player& target) = 0; //Tohle ceka na adama aby vedel jak to pouzivat
int Item::getCount() const { return m_count; }
void Item::setCount(int count) { m_count = count; }
void Item::addCount(int amount) { m_count += amount; }
void Item::removeCount(int amount) { m_count -= amount; }
std::string Item::getDisplayString() const {
    std::stringstream ss;
    ss << "---- Predmet ----\n";
    ss << "Nazev: " << m_name << " (ID: " << m_itemID << ")\n";
    ss << "Vzácnost: " << RarityToString(m_rarity) << ", Stack: " << m_count << " / " << m_limit << " ks\n";
    ss << "Popis: " << m_description << "\n";
    ss << getSpecificInfo();
    ss << "---------------\n";
    return ss.str();
}