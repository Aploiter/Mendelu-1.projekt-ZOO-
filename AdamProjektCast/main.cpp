#include <iostream>
#include "IngameMenu.h"
#include "TitleMenu.h"
#include "Player.h"
#include "Map.h"
#include <windows.h>
#include <cstdio>
#include "Interactions.h"


void enable_ansi_color_support() {
    // Používá Windows API k povolení režimu Virtual Terminal Processing
    // pro standardní výstup (stdout).
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
}

int main() {
    enable_ansi_color_support(); // Zapne barvy hned na startu programu

    TitleMenu titleMenu;
    titleMenu.print();
    return 0;
}
