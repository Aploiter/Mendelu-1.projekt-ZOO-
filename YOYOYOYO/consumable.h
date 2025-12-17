//
// Created by ltopo on 09.12.2025.
//

#ifndef YOYOYOYO_CONSUMABLE_H
#define YOYOYOYO_CONSUMABLE_H
#include <string>
#include "Item.h"

class consumable : public Item {//Pod trida neboli dedicnost na item
    int m_healAmount;
    int m_effectId;
    public:
    consumable(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int healAmount, int effectId);
    ~consumable() override = default;
    int getHealAmount() const;
    int getEffectId() const;
    std::string getSpecificInfo() const override;
    void Use(class Player& target) override; //Hledání Inventář najde předmět podle ID
};


#endif //YOYOYOYO_CONSUMABLE_H