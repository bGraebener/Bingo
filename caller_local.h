#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "caller.h"
#include "persistance.h"
#include "displayMenu.h"

//local function prototypes
void playGame();
void drawNumber();
void markCards();
boolean checkForWinner(Player*);
void checkFourCorners(Player*);
void checkRows(Player*);
void displayStats();
void endGame();
void exitHandler();
