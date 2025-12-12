#pragma once
#include "Player.h"

extern Player CurrentPlayer;               // globální hráč (všude dostupný)

void SaveGame();
Player LoadGame();                        // vrátí uloženého hráče (nebo defaultního)
bool DoesSaveExist();