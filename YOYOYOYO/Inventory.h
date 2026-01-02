//
// Created by ltopo on 09.12.2025.
//

#ifndef YOYOYOYO_INVENTORY_H
#define YOYOYOYO_INVENTORY_H

#include <vector>
#include <memory>
#include <string>
#include "Item.h"

class Player; // Forward deklarace - říkáme "Player existuje", aniž bychom vkládali celý Player.h

class Inventory {
    std::vector<std::unique_ptr<Item>> m_items; //string ktery ukazuje na item dulezite pro celou deklaraci unique aby se to mohlo lepe mazat a pridavat
    int m_capacityLimit;
public:
    Inventory(int capacity = 20);
    bool addItem(std::unique_ptr<Item> m_item); //ukazuje na items
    bool useItem(int itemId, Player& target); // Důležité pro propojení s Adamem
    bool deleteItem(int itemId);
    std::vector<std::string> getInventoryContents() const;
    std::string getItemInfo(int itemId) const;
    Item* getEquippedWeapon() const;// Tady bys musel mít způsob, jak poznat, že je to zbraň a že je vybavená
                                    //jenom zkouska pro propojeni

};

#endif //YOYOYOYO_INVENTORY_H