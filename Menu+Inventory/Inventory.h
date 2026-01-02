#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>
#include <string>
#include "Item.h"

class Player; // Forward deklarace

class Inventory {
    std::vector<std::unique_ptr<Item>> m_items;
    int m_capacityLimit;

public:
    Inventory(int capacity = 20);
    bool addItem(std::unique_ptr<Item> item);
    bool useItem(int itemId, Player& target);
    bool deleteItem(int itemId);
    std::vector<std::string> getInventoryContents() const;
    std::string getItemInfo(int itemId) const;
    Item* getEquippedWeapon() const;

    const std::vector<std::unique_ptr<Item>>& getItems() const { return m_items; }
    int getCapacityLimit() const { return m_capacityLimit; }
};

#endif //INVENTORY_H