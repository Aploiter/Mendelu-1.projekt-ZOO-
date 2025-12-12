#include "TitleMenu.h"
#include <iostream>
#include <fstream> // (file)stream pro práci se soubory
#include <windows.h>
#include "IngameMenu.h"
#include "Player.h"
#include "GameState.h"

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
    /*
    // vytvoří proměnou SaveFile pro fstream.
    std::fstream SaveFile;

    // pokud neexistuje složka "SaveFile.txt" tak se sama vytvoří. možnosti ios(read=in, write=out(přepisuje data lze použít ofstream pro automatické vybrání write), append=app(připojí data))
    SaveFile.open("SaveFile.txt", std::ios::out);

    // ověření zda se soubor otevřel
    if (SaveFile.is_open())
    {
        //import textu do souboru
        // TODO make playerState
        SaveFile << "player health: " << player.getHealth()
        << "\nplayer strength: "<< player.getStrength() << std::endl;
    }

    // po otevnění souboru se musí zavřít aby se uvolnila paměť.
    SaveFile.close();*/
    //Map -> print // TODO spuštění hry
    SaveGame();     // uložení hry
    IngameMenu ingame;
    ingame.print();
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
}
