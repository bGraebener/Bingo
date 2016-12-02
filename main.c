//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "displayMenu.h"
#include "caller.h"

void startGame();

void main() {
	
	int choice;

	do {
		displayStartMenu();
		scanf("%d", &choice);
	} while (choice < 1 || choice > 3);

	if (choice == 3) {
		displayGoodbye();
		getch();
		return;
	}
	else if (choice == 2) {
		loadGame(0);
	}
	else {
		startGame();
	}


	getch();
	
}



