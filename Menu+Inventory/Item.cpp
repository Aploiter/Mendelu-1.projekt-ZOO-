#include <sstream>
#include "Item.h"
#include <iostream>
#include <ostream>

std::string RarityToString(Rarity rarity)
{
    switch (rarity)
    {
        case Rarity::Common: return "Common";
        case Rarity::Rare: return "Rare";
        case Rarity::Epic: return "Epic";
        default: return "Unknown";
    }
}

Item::Item(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity)
{
    m_itemID = itemID;
    m_name = name;
    m_description = description;
    m_rarity = rarity;
    m_limit = limit;
    m_count = 1;
}

Item::Item(const Item& other)
    : m_itemID(other.m_itemID), m_name(other.m_name), m_description(other.m_description),
      m_limit(other.m_limit), m_rarity(other.m_rarity), m_count(other.m_count)
{
    // Kopie jednoduchých členů
}

int Item::getItemID() const { return m_itemID; }
const std::string& Item::getName() const { return m_name; }
const std::string& Item::getDescription() const { return m_description; }
int Item::getLimit() const { return m_limit; }
Rarity Item::getRarity() const { return m_rarity; }
int Item::getCount() const { return m_count; }
void Item::setCount(int count) { m_count = count; }
void Item::addCount(int amount) { m_count += amount; }
void Item::removeCount(int amount) { m_count -= amount; }

std::string Item::getDisplayString() const
{
    std::stringstream ss;
    ss << "<---  Item  --->\n";
    ss << "Name: " << m_name << " (ID: " << m_itemID << ")\n";
    ss << "Rarity: " << RarityToString(m_rarity) << ", Stack: " << m_count << " / " << m_limit << " ks\n";
    ss << "Description: " << m_description << "\n";
    ss << getSpecificInfo();
    ss << "---------------\n";
    return ss.str();
}