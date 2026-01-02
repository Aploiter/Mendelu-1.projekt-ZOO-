#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include <string>
#include <memory>
#include "Item.h"

class consumable : public Item
{
    int m_healAmount;
    int m_effectId;

public:
    consumable(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity, int healAmount, int effectId);
    consumable(const consumable& other);

    ~consumable() override = default;

    int getHealAmount() const;
    int getEffectId() const;

    std::string getSpecificInfo() const override;
    void Use(class Player& target) override;

    std::unique_ptr<Item> clone() const override;
};

#endif //CONSUMABLE_H