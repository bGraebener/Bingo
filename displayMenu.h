#pragma once

#include "player.h"
#include "caller.h"

void displayStartMenu();
void displayTitle();
void displayMainOptions();

void displayExitOptions();
void displayGoodbye();

void displayPlayer(Player*);
void displayRemaining(Player*);

void displayStats(Caller*);