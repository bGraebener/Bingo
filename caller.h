#pragma once
#include "player.h"

typedef int boolean;
#define true 1;
#define false 0;

typedef struct {

	int roundCounter;
	int numOfPlayers;
	boolean fourCornersWon;
	boolean oneRowWon;
	boolean twoRowsWon;

	int available[90];
	int drawn[90];
	Player *playerArray;
	Player winner;

}Caller;

void startGame();
void mainLoadHandler(int savegame);