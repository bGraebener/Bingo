#pragma once

#include "player.h"
#include "caller.h"

void saveGame(Caller);
int chooseSaveGame();
Caller loadGame(int);