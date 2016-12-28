//Bingo - Bastian Graebener - 02.12.2016
//C Programming Project 2016 - Implementation of a Bingo Game

#include <stdio.h>
#include <conio.h>

#include "persistance.h"
#include "displayMenu.h"
#include "caller.h"

void main() {

	int choice;

	do {
		displayStartMenu();
		scanf("%d", &choice);
	} while (choice < 1 || choice > 3);

	if (choice == 3) {
		displayGoodbye();
	}
	else if (choice == 2) {
		int choice = chooseSaveGame();
		mainLoadHandler(choice);
	}
	else {
		startGame();
	}
	_getch();
}
