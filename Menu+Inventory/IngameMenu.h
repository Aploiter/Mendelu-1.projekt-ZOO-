#ifndef INGAMEMENU_H
#define INGAMEMENU_H

class IngameMenu
{
public:
    IngameMenu(); // konstruktor
    //metody pro akce v menu
    void print();
    void loadSave();
    void returnToTitle();
    void exitGame();
    void playerInfo();
    void viewInventory();
};

#endif //INGAMEMENU_H