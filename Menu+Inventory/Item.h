#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

enum class Rarity
{
    Common,
    Rare,
    Epic
};

class Item
{
    int m_itemID;
    std::string m_name;
    std::string m_description;
    int m_limit;
    Rarity m_rarity;
    int m_count;

public:
    Item(int itemID, const std::string& name, const std::string& description, int limit, Rarity rarity);
    Item(const Item& other);  // Copy constructor

    virtual ~Item() = default;

    int getItemID() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    int getLimit() const;
    int getCount() const;
    void setCount(int count);
    void addCount(int amount);
    void removeCount(int amount);
    Rarity getRarity() const;

    virtual std::string getSpecificInfo() const = 0;
    virtual void Use(class Player& target) = 0;

    virtual std::unique_ptr<Item> clone() const = 0;

    virtual std::string getDisplayString() const;
};

#endif //ITEM_H