#pragma once

#include <stdio.h>

void displayTitle() {
	system("cls");
	//printf("\n\n\n\t*********************************************************************************************************\n");
	printf("\n\n\n\n\n\t\t\t\t**********************************************");
	printf("\n\t\t\t\t*\t\tWelcome to Bingo!\t     *");
	printf("\n\t\t\t\t**********************************************");
}

void displayStartMenu() {
	displayTitle();
	printf("\n\n\t\t\t\t\t1 - Start a new game of Bingo?");
	printf("\n\t\t\t\t\t2 - Load an old Game?");
	printf("\n\t\t\t\t\t3 - Exit?");
	printf("\n\n\t\t\t\t\tYour choice: ");
}


void displayMainOptions() {

	
		displayTitle();

		printf("\n\n\t\t\t\t\tWhat's your next move?");
		printf("\n\n\t\t\t\t\t1 - Draw a number");
		printf("\n\t\t\t\t\t2 - Save Game");
		printf("\n\t\t\t\t\t3 - Show Game Status");
		printf("\n\t\t\t\t\t4 - Exit Game Without Saving");
		printf("\n\n\t\t\t\t\tYour choice: ");
		
}



void displayExitOptions() {

		displayTitle();

		printf("\n\n\t\t\t\t\tLeave Bingo?");
		printf("\n\n\t\t\t\t\t1 - Start a new Game");
		printf("\n\t\t\t\t\t2 - Load Game");
		printf("\n\t\t\t\t\t3 - Exit Game Without Saving");
		printf("\n\n\t\t\t\t\tYour choice: ");

}

void displayGoodbye() {
	displayTitle();
	printf("\n\n\t\t\t\t\tGoodbye - See you next time!");
}