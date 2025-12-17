#ifndef ARMOR_H
#define ARMOR_H

#include <string>
#include <memory>

#include "Item.h"

class Armor : public Item
{
    int m_defense;
    std::string m_slot;

public:
    Armor(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int defense, std::string slot);
    Armor(const Armor& other);

    ~Armor() override = default;

    int getDefense() const;
    const std::string& getSlot() const;

    std::string getSpecificInfo() const override;
    void Use(class Player& target) override;

    std::unique_ptr<Item> clone() const override;
};

#endif //ARMOR_H