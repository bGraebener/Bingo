#pragma once
#include <time.h>
#include "caller_local.h"

//global variable
Caller caller;

void startGame() {
	srand(time(NULL));                                      //seed for the random number generator
	caller.roundCounter = -1;

	//initialise available numbers array
	for (int i = 0; i < 90; i++) {
		caller.available[i] = i + 1;
	}

	//set winner trackers to false
	caller.fourCornersWon = false;
	caller.oneRowWon = false;
	caller.twoRowsWon = false;

	//get number of players between 2 & 6
	do {
		displayTitle();
		printf("\n\n\t\t\t\tHow many player will be joining us today? (2 - 6)");
		printf("\n\n\t\t\t\tNumber of players: ");

		scanf("%d", &caller.numOfPlayers);
	} while (caller.numOfPlayers < 2 || caller.numOfPlayers > 6);

	caller.playerArray = malloc(sizeof(Player) * caller.numOfPlayers);								//get array to store players

	for (int i = 0; i < caller.numOfPlayers; i++) {													//prepare all the players
		caller.playerArray[i] = preparePlayer();													//generate player cards and display them
		displayPlayer(&caller.playerArray[i]);
		printf("\n\n\t\t\t\tPress key to continue...");
		_getch();
	}
	playGame();
}

//main game function
//displays all main options
void playGame() {

	int choice;
	do {
		displayMainOptions();
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	switch (choice) {
	case 4:
		exitHandler();
		break;

	case 3:
		displayStats(&caller);
		playGame();
		break;

	case 2:
		saveGame(caller);
		playGame();
		break;

	case 1:
		drawNumber();
		break;

	default:
		printf("Invalid option - please choose a different option!");
	}
}

//draw the next random number and store them in an array
void drawNumber() {

	int draw;
	int ranNum;

	do {
		ranNum = (rand() % 90);
		draw = caller.available[ranNum];							//get a random number from the pool of available numbers
	} while (draw == -1);

	caller.available[ranNum] = -1;									//mark drawn number as unavailable in pool of available numbers
	caller.drawn[++caller.roundCounter] = draw;						//update round counter and array of already frawn numbers

	displayTitle();
	printf("\n\n\t\t\t\tThe %d everybody! The %d was drawn!", draw, caller.drawn[caller.roundCounter]);

	printf("\n\n\t\t\t\tPress key to continue...");
	_getch();
	markCards();													//check all cards for the newly drawn number
}


//mark all player cards and check if there's a winner
void markCards() {
	boolean gameOver;

	for (int i = 0; i < caller.numOfPlayers; i++) {															//mark numbers on each card if found

		for (int row = 0; row < ROW; row++) {																//mark short card
			for (int col = 0; col < COL_SHORT; col++) {
				if (caller.playerArray[i].shortCard[row][col] == caller.drawn[caller.roundCounter]) {
					caller.playerArray[i].shortCard[row][col] = 0;											//matching numbers are marked zero
					caller.playerArray[i].remaining[row]--;													//track remaining numbers for each row
					break;
				}
			}
		}

		for (int row = 0; row < ROW; row++) {																//mark display card
			for (int col = 0; col < COL_LONG; col++) {
				if (caller.playerArray[i].displayCard[row][col] == caller.drawn[caller.roundCounter]) {
					caller.playerArray[i].displayCard[row][col] = 0;
					break;
				}
			}
		}
		gameOver = checkForWinner(&caller.playerArray[i]);													//check for all winning options

		if (gameOver) {
			break;
		}
	}

	if (!gameOver) {
		playGame();
	}
	else {
		endGame();
	}
}

//function to check for all winning options, returns whether someone got a full house
boolean checkForWinner(Player *player) {

	//check for Full House
	if (player->remaining[0] + player->remaining[1] + player->remaining[2] == 0) {
		displayTitle();
		printf("\n\n\t\t\t\t%s shouts Bingo! I have a Full House!", player->name);
		caller.winner = *player;
		printf("\n\n\t\t\t\tPress key to continue...");
		_getch();
		return true;
	}

	checkFourCorners(player);
	checkRows(player);
	return false;
}
//function that checks for the four corners winning option
void checkFourCorners(Player *player) {
	if (!caller.fourCornersWon) {																			//check four corners of the players card array
		if (player->shortCard[0][0] == 0 && player->shortCard[0][4] == 0 && player->shortCard[2][0] == 0 && player->shortCard[2][4] == 0) {
			displayTitle();
			caller.fourCornersWon = true;																	//option won't be checked again if once won
			printf("\n\n\t\t\t\t%s shouts Bingo! I have four corners!", player->name);
			printf("\n\n\t\t\t\tPress key to continue...");
			_getch();
		}
	}
}

//function that checks for the one and two row winnig options
void checkRows(Player *player) {
	if (!caller.oneRowWon) {																				//check for one row winner
		if (player->remaining[0] == 0 || player->remaining[1] == 0 || player->remaining[2] == 0) {
			caller.oneRowWon = true;																		//option won't be checked again if once won
			displayTitle();
			printf("\n\n\t\t\t\t%s shouts Bingo! I have completed one row!", player->name);
			printf("\n\n\t\t\t\tPress key to continue...");
			_getch();
		}
	}
	else {
		if (!caller.twoRowsWon) {																			//check for two row winner
			if ((player->remaining[0] == 0 && player->remaining[1] == 0) || (player->remaining[0] == 0 && player->remaining[2] == 0) || (player->remaining[2] == 0 && player->remaining[1] == 0)) {
				caller.twoRowsWon = true;																	//option won't be checked again if once won
				displayTitle();
				printf("\n\n\t\t\t\t%s shouts Bingo! I have completed two rows!", player->name);
				printf("\n\n\t\t\t\tPress key to continue...");
				_getch();
			}
		}
	}
}

//function to handle a finished game
void endGame() {
	int choice;
	do {
		displayTitle();

		printf("\n\n\t\t\t\t\t%s won this round of Bingo!", caller.winner.name);
		printf("\n\t\t\t\t\tWhat's your next move?");
		printf("\n\n\t\t\t\t\t1 - Play again");											//draw next number option unavailable
		printf("\n\t\t\t\t\t2 - Save Game");
		printf("\n\t\t\t\t\t3 - Show Game Status");
		printf("\n\t\t\t\t\t4 - Exit Game");
		printf("\n\n\t\t\t\t\tYour choice: ");

		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	switch (choice)
	{
	case 1:
		startGame();
		break;
	case 2:
		saveGame(caller);
		break;
	case 3:
		displayStats(&caller);
		endGame();
		break;
	case 4:
		exitHandler();
		break;
	default:
		break;
	}
}


//function that handles the loading of a saved game from the main function
void mainLoadHandler(int offset) {
	caller = loadGame(offset);
	displayStats(&caller);
	playGame();
}

//function that is called if the user wishes to exit the current game
void exitHandler() {
	int choice;

	do {
		displayExitOptions();

		scanf("%d", &choice);
	} while (choice < 1 || choice > 3);

	if (choice == 3) {
		free(caller.playerArray);                                       //release dynamically allocated heap space
		displayGoodbye();
	}
	else if (choice == 2) {
		int choice = chooseSaveGame();
		caller = loadGame(choice);
		displayStats(&caller);
		playGame();
	}
	else {
		startGame();
	}
}
