//
// Created by ltopo on 09.12.2025.
//

#include "Inventory.h"
#include <iostream>
#include <algorithm> // Pro std::find_if
#include <sstream>


Inventory::Inventory(int capacity) : m_capacityLimit(capacity) {}

// Metoda pro přidání předmětu s logikou stackování pro vice itemu
bool Inventory::addItem(std::unique_ptr<Item> item) {
    if (!item) return false;

    // Hledáme zda už stejný předmět máme a není plný
    if (item->getLimit() > 1) {
        auto it = std::find_if(m_items.begin(), m_items.end(), //find if neco jako for cyklus projede cely items kde je find if musi byt i it a existing
            [&item](const std::unique_ptr<Item>& existing) {    //it existuje jen v jednom bloku proto se nemusi deklarovat a existing funguje na principu bool
                return existing->getItemID() == item->getItemID() &&
                       existing->getCount() < existing->getLimit();
            });

        if (it != m_items.end()) {
            (*it)->addCount(1); //tohle se rovna unique ptr neukazuje na nej
            return true;
        }
    }

    //jednoducha kontrola kapacity
    if (m_items.size() >= m_capacityLimit) {
        return false;
    }

    //pro presun itemu
    m_items.push_back(std::move(item)); //move nezanmena ze se presouva ale stava se nullptr
    return true;                        // std::move umozni presun vlastnictvi unique_ptr, item pak zustane prazdny
}

// Smazání předmětu podle ID
bool Inventory::deleteItem(int itemId) {
    auto it = std::find_if(m_items.begin(), m_items.end(),
        [itemId](const std::unique_ptr<Item>& item) {
            return item->getItemID() == itemId;
        });

    if (it != m_items.end()) {
        if ((*it)->getCount() > 1) {
            (*it)->removeCount(1); // Pokud je jich víc, jen jeden ubereme pricemz pouzivame ukazatel it ketry existuje zase jenom v tomhle bloku
        } else {
            m_items.erase(it); // Pokud je poslední, smažeme celý slot
        }
        return true;
    }
    return false;
}

// Výpis obsahu pro menu
    std::vector<std::string> Inventory::getInventoryContents() const {
    std::vector<std::string> contents;
    for (const auto& item : m_items) {
        std::stringstream ss;
        ss << item->getName() << " [" << item->getCount() << "x]";
        contents.push_back(ss.str());
    }
    return contents;
}

// Detailní info o konkrétním předmětu
std::string Inventory::getItemInfo(int itemId) const {
    for (const auto& item : m_items) {
        if (item->getItemID() == itemId) {
            return item->getDisplayString(); // Polymorfní volání
        }
    }
    return "Predmet nenalezen.";
}

// Pomocná metoda pro Adama (Player), aby mohl získat zbraň nemusi se pouzivat
Item* Inventory::getEquippedWeapon() const {
    // Tady by mohla být logika pro nalezení vybavené zbraně
    return nullptr;
}
bool Inventory::useItem(int itemId, Player& target) {
    for (auto& item : m_items) {
        if (item->getItemID() == itemId) {
            item->Use(target); // Tady se spustí tvá logika lektvaru/zbraně
            return true;
        }
    }
    return false;
}