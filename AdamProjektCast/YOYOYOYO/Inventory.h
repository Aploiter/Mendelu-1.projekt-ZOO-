//
// Created by ltopo on 09.12.2025.
//

#ifndef YOYOYOYO_INVENTORY_H
#define YOYOYOYO_INVENTORY_H
#include <vector>
#include <memory>       // Pro std::unique_ptr
#include <string>
#include "Item.h"
#include "../../Player/Player.h"

class Inventory {
        std::vector<std::unique_ptr<Item>> m_items; //mel by ukazovat na itemy co mi da adam
        int m_capacityLimit;
    public:
        Inventory(int capacity = 20);
        bool addItem(std::unique_ptr<Item> item);
        bool useItem(int itemId, class Player& target); //pro adama
        bool deleteItem(int itemID);
        std::vector<std::string> getInventoryContents() const;
        std::string getItemInfo(int itemId) const;
        Item* getEquippedWeapon() const;

};


#endif //YOYOYOYO_INVENTORY_H