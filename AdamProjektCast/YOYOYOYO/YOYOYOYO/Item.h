//
// Created by ltopo on 09.12.2025.
//

#ifndef YOYOYOYO_ITEM_H
#define YOYOYOYO_ITEM_H
#include <string>

enum class Rarity {
    Common,
    Rare,
    Epic
};
class Item {
    int m_itemID;
    std::string m_name;
    std::string m_description;
    int m_limit;
    Rarity m_rarity;
    int m_count;
    public:
    Item(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity);
    virtual ~Item()=default;
    int getItemID() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    int getLimit() const;
    int getCount() const;
    void setCount(int count);
    void addCount(int amount);
    void removeCount(int amount);
    Rarity getRarity() const;
    virtual std::string getSpecificInfo() const=0; //const 0 je to ze je ciste virtualni a neda se implementovat v cpp
    virtual void Use(class Player& target) = 0; //Tohle ceka na adama aby vedel jak to pouzivat
    virtual std::string getDisplayString() const;
};


#endif //YOYOYOYO_ITEM_H