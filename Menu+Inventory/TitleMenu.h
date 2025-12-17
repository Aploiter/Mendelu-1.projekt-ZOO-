#ifndef TITLEMENU_H
#define TITLEMENU_H

class TitleMenu
{
public:
    TitleMenu(); // konstruktor (volá se při vytvoření objektu)
    //metody pro akce v menu
    void print();
    void newGame();
    void continueGame();
    void exitGame();
};

#endif //TITLEMENU_H