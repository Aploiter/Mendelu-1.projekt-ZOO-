//
// Created by ltopo on 09.12.2025.
//

#ifndef YOYOYOYO_ARMOR_H
#define YOYOYOYO_ARMOR_H
#include <string>
#include "Item.h"

class Armor : public Item {
    int m_defense;
    std::string m_slot; // Slot pro nošení (např. "Head", "Body", "Legs")
    public:
    Armor(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity,int defense,std::string slot);
    ~Armor() override = default;
    int getDefense() const;
    const std::string& getSlot() const;
    std::string getSpecificInfo() const override;
    void Use(class Player& target) override;
};


#endif //YOYOYOYO_ARMOR_H