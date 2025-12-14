#include "TitleMenu.h"
#include <iostream>
#include <fstream> // (file)stream pro práci se soubory
#include <windows.h>
#include "IngameMenu.h"
#include "Player.h"
#include "GameState.h"
#include "Interactions.h"

TitleMenu::TitleMenu()
{

}

void TitleMenu::print()
{
    bool exitLoop = false;
    while (!exitLoop)
    {
        system("cls");
        //vytvoření bool proměnné na ověření zda jde otevřít "SaveFile.txt" pro použítí v podmínkách
        bool saveExists = false;
        {
            std::ifstream save("SaveFile.txt");
            saveExists = save.is_open();
        }
        char choice;
        std::cout << "<---  |Title-Menu|  --->\n";
        std::cout << "      [n] New game\n";
        //pokud jde otevřít soubor savefile/existuje přidat možnost continue
        if (saveExists) {std::cout << "      [c] Continue game\n";}
        std::cout << "      [e] Exit game\n";
        std::cout << "\nChoice: "; std::cin >> choice;

        switch (choice)
        {
            case 'n': newGame(); exitLoop = true; break;
            case 'c': if (saveExists) {continueGame(); exitLoop = true;} else {std::cerr << "Invalid choice!" << std::endl; Sleep(1000);} break;
            case 'e': exitGame(); exitLoop = true; break;
            default: std::cerr << "Invalid choice!" << std:: endl; Sleep(1000); break;
        }
    }
}

void TitleMenu::newGame()
{
    // globální hráč
    CurrentPlayer = Player(100, 10);
    std::cout << "Starting new game." << std::endl;

    // Zde je třeba odstranit starý komentář a zavolat GameController.
    // Původní kód: //Map -> print // TODO spuštění hry

    // Ukládání by mělo probíhat, až se hra skutečně hraje nebo skončí,
    // ale ponecháme SaveGame() pro zachování původní logiky.
    SaveGame();     // uložení hry

    // NOVÁ LOGIKA: Spuštění herního kontroleru
    GameController game;
    game.runGameLoop();

    // Po ukončení game.runGameLoop() (buď vítězství, nebo Q) se vracíme na TitleMenu.
    // Zde by měla být další kontrola stavu, ale prozatím ukončíme smyčku TitleMenu.

    // Původní volání IngameMenu už není potřeba, pokud GameController řídí hru
    // IngameMenu ingame;
    // ingame.print();
}

void TitleMenu::continueGame()
{
    // jiná možnost
    /*std::cout << "checking save files" << std::endl;

    std::ifstream SaveFile("SaveFile.txt");

    if (SaveFile.is_open())
    {
        std::cout << "save file found, loading game." << std::endl;
        return;
    }
    std::cerr << "unable to find save file." << std::endl;*/

    //vybraná možnost
    //std::cout << "continuing game" << std::endl;
    //Sleep(1500);

    CurrentPlayer = LoadGame();     // načtení dat ze souboru
    IngameMenu ingame;
    ingame.print();
}

void TitleMenu::exitGame()
{
    std::cout << "Exiting game..." << std::endl;
    Sleep(1500);
    exit(0);
}
