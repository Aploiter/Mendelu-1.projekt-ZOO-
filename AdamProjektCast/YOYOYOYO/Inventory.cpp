//
// Created by ltopo on 09.12.2025.
//

#include "Inventory.h"
#include <iostream>
#include <algorithm> // Pro std::find_if
#include <sstream>

// Konstruktor - inicializace kapacity
Inventory::Inventory(int capacity) : m_capacityLimit(capacity) {}

// Metoda pro přidání předmětu s logikou stackování
bool Inventory::addItem(std::unique_ptr<Item> item) {
    if (!item) return false;

    // 1. Logika stackování: Hledáme, zda už stejný předmět máme a není plný
    if (item->getLimit() > 1) {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [&item](const std::unique_ptr<Item>& existing) {
                return existing->getItemID() == item->getItemID() &&
                       existing->getCount() < existing->getLimit();
            });

        if (it != m_items.end()) {
            (*it)->addCount(1); // Přidáme kus k existujícímu stohu
            return true;
        }
    }

    // 2. Kontrola kapacity (počet slotů)
    if (m_items.size() >= (size_t)m_capacityLimit) {
        std::cout << "Inventar je plny!" << std::endl;
        return false;
    }

    // 3. Přidání nového unikátního předmětu do vektoru (přesun vlastnictví)
    m_items.push_back(std::move(item));
    return true;
}

// Smazání předmětu podle ID
bool Inventory::deleteItem(int itemId) {
    auto it = std::find_if(m_items.begin(), m_items.end(),
        [itemId](const std::unique_ptr<Item>& item) {
            return item->getItemID() == itemId;
        });

    if (it != m_items.end()) {
        if ((*it)->getCount() > 1) {
            (*it)->removeCount(1); // Pokud je jich víc, jen jeden ubereme
        } else {
            m_items.erase(it); // Pokud je poslední, smažeme celý slot
        }
        return true;
    }
    return false;
}

// Výpis obsahu pro menu (vrací vektory stringů pro frontend)
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

// Pomocná metoda pro Adama (Player), aby mohl získat zbraň
Item* Inventory::getEquippedWeapon() const {
    // Tady by mohla být logika pro nalezení vybavené zbraně
    return nullptr;
}