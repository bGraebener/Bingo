#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "player.h"
#include "caller.h"
#include "displayMenu.h"

typedef int boolean;
#define true 1;
#define false 0;

//local function prototypes
void playGame();
void drawNumber();
void markCards();
boolean checkForWinner(Player);
void displayStats();
void displayRemaining(Player);
void endGame(Player);
void saveGame();
void loadGame(int);

//global variables
int roundCounter = -1;
int numOfPlayers;
boolean fourCornersWon = false;
boolean oneRowWon = false;
boolean twoRowsWon = false;

int available[90];
int drawn[90];
Player *playerArray;
Player winner;


void startGame() {
	srand(time(NULL));

	roundCounter = -1;
	//initialise available numbers array
	for (int i = 0; i < 90; i++) {
		available[i] = i + 1;
	}

	do {
		displayTitle();
		printf("\n\n\t\t\t\tHow many player will be joining us today? (2 - 6)");
		printf("\n\n\t\t\t\tNumber of players: ");

		scanf("%d", &numOfPlayers);
	} while (numOfPlayers < 2 || numOfPlayers > 6);

	playerArray = malloc(sizeof(Player) * numOfPlayers);

	//prepare all the players
	for (int i = 0; i < numOfPlayers; i++) {

		playerArray[i] = preparePlayer();

		displayPlayer(playerArray[i]);

		printf("\n\n\t\t\t\tPress key to continue...");
		getch();
	}

	playGame();

}


void playGame() {

	int choice;
	do {
		displayMainOptions();

		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	switch (choice) {
	case 4:
		do {
			displayExitOptions();

			scanf("%d", &choice);
		} while (choice < 1 || choice > 3);
		
		if (choice == 3) {
			displayGoodbye();
		}
		else if (choice == 2) {
			loadGame(0);
		}
		else {
			startGame();
		}
		break;

	case 3:
		displayStats();
		playGame();
		break;

	case 2:
		saveGame();
		break;

	case 1:
		drawNumber();
		break;

	default:
		printf("Invalid option - please choose a different option!");
	}
}


void drawNumber() {

	int draw;
	int ranNum;

	do {
		ranNum = (rand() % 89) + 1;
		draw = available[ranNum];
	} while (draw == -1);

	available[ranNum] = -1;
	drawn[++roundCounter] = draw;

	displayTitle();
	printf("\n\n\t\t\t\tThe %d everybody! The %d was drawn!", draw, drawn[roundCounter]);

	printf("\n\n\t\t\t\tPress key to continue...");
	getch();
	markCards();
}

//mark all player cards and check if there's a winner
void markCards() {
	boolean gameOver;
	//mark numbers on each card if found
	for (int i = 0; i < numOfPlayers; i++) {

		//mark on the short card
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL_SHORT; col++) {
				if (playerArray[i].shortCard[row][col] == drawn[roundCounter]) {
					playerArray[i].shortCard[row][col] = 0;
					playerArray[i].remaining[row]--;									//track remaining numbers for each row
					break;
				}
			}
		}

		//mark display card
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL_LONG; col++) {
				if (playerArray[i].displayCard[row][col] == drawn[roundCounter]) {
					playerArray[i].displayCard[row][col] = 0;
					break;
				}
			}
		}
		gameOver = checkForWinner(playerArray[i]);

		if (gameOver) {
			break;
		}

	}
	if (!gameOver) {
		playGame();
	}
	else {
		endGame(winner);
	}

}

//function to check for all winning options, returns whether someone got a full house and the game is over
boolean checkForWinner(Player player) {

	//check for Full House
	if (player.remaining[0] + player.remaining[1] + player.remaining[2] == 0) {
		displayTitle();
		printf("\n\n\t\t\t\t%s shouts Bingo! I have a Full House!", player.name);
		winner = player;
		printf("\n\n\t\t\t\tPress key to continue...");
		getch();
		return true;
	}

	//check four corners of the players card array
	if (!fourCornersWon) {
		if (player.shortCard[0][0] == 0 && player.shortCard[0][4] == 0 && player.shortCard[2][0] == 0 && player.shortCard[2][4] == 0) {
			displayTitle();
			printf("\n\n\t\t\t\t%s shouts Bingo! I have four corners!", player.name);
			fourCornersWon = true;
			printf("\n\n\t\t\t\tPress key to continue...");
			getch();
		}
	}
	if (!oneRowWon) {
		//get remaining for rows
		if (player.remaining[0] == 0 || player.remaining[1] == 0 || player.remaining[2] == 0) {
			displayTitle();
			printf("\n\n\t\t\t\t%s shouts Bingo! I have completed one row!", player.name);
			oneRowWon = true;
			printf("\n\n\t\t\t\tPress key to continue...");
			getch();
		}
	}
	else {
		if (!twoRowsWon) {
			if ((player.remaining[0] == 0 && player.remaining[1] == 0) || (player.remaining[0] == 0 && player.remaining[2] == 0) || (player.remaining[2] == 0 && player.remaining[1] == 0)) {
				displayTitle();
				printf("\n\n\t\t\t\t%s shouts Bingo! I have completed two rows!", player.name);
				twoRowsWon = true;
				printf("\n\n\t\t\t\tPress key to continue...");
				getch();
			}
		}
	}
	return false;
}


void endGame(Player winner) {
	int choice;
	do {
		displayTitle();

		printf("\n\n\t\t\t\t\t%s won this round of Bingo!", winner.name);
		printf("\n\t\t\t\t\tWhat's your next move?");
		printf("\n\n\t\t\t\t\t1 - Play again");
		printf("\n\t\t\t\t\t2 - Save Game");
		printf("\n\t\t\t\t\t3 - Show Game Status");
		printf("\n\t\t\t\t\t4 - Exit Game Without Saving");
		printf("\n\n\t\t\t\t\tYour choice: ");

		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	switch (choice)
	{
	case 1:
		startGame();
		break;
	case 2:
		//saveGame();
		break;
	case 3:
		displayStats();
		endGame(winner);
		break;
	case 4:
		do {
			displayExitOptions();

			scanf("%d", &choice);
		} while (choice < 1 || choice > 3);

		if (choice == 3) {
			displayGoodbye();
		}
		else if (choice == 2) {
			loadGame(0);
		}
		else {
			startGame();
		}
		break;
	default:
		break;
	}

}

void displayStats() {

	displayTitle();
	printf("\n\n\t\t\t\tCurrent stats: ");
	printf("\n\n\t\t\t\t%d rounds played so far!", roundCounter + 1);

	//display already drawn numbers
	printf("\n\t\t\t\tDrawn numbers:");
	printf("\n\t\t\t\t");
	for (int i = 0; i <= roundCounter; i++) {
		printf("%2d ", drawn[i]);
		if (i > 0 && i % 10 == 0) {
			printf("\n\t\t\t\t");
		}
	}

	//display player cards and remaining numbers
	for (int i = 0; i < numOfPlayers; i++) {
		printf("\n");
		displayPlayer(playerArray[i]);
		displayRemaining(playerArray[i]);
	}

	printf("\n\n\t\t\t\tPress key to continue...");
	getch();
}

//display remaining numbers for all winning options
void displayRemaining(Player player) {

	//remaining for four corners
	int fourCourners = 4;
	if (player.shortCard[0][0] == 0) {
		fourCourners--;
	}
	if (player.shortCard[0][4] == 0) {
		fourCourners--;
	}
	if (player.shortCard[2][0] == 0) {
		fourCourners--;
	}
	if (player.shortCard[2][4] == 0) {
		fourCourners--;
	}


	//remaining for rows
	int leastNumbers[3];

	for (int i = 0; i < 3; i++) {
		leastNumbers[i] = player.remaining[i];
	}

	for (int i = 2; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (leastNumbers[j] > leastNumbers[j + 1]) {
				int temp = leastNumbers[j];
				leastNumbers[j] = leastNumbers[j + 1];
				leastNumbers[j + 1] = temp;
			}
		}
	}

	printf("\n\n\t\t\t\tNumbers needed to complete four courners: %2d", fourCourners);
	printf("\n\t\t\t\tNumbers needed to complete a row: %2d", leastNumbers[0]);
	printf("\n\t\t\t\tNumbers needed to complete two rows: %2d", leastNumbers[0] + leastNumbers[1]);
	printf("\n\t\t\t\tNumbers needed to complete Full House: %2d", leastNumbers[0] + leastNumbers[1] + leastNumbers[2]);

}

void saveGame() {

	FILE *output;

	output = fopen("savegame.txt", "a");

	if (output == NULL) {
		printf("Couldn't open file!");
		return;
	}

	//save number of players
	fprintf(output, "%d\n", numOfPlayers);

	//save available number array
	for (int i = 0; i < 90; i++) {
		fprintf(output, "%d ", available[i]);
	}
	fprintf(output, "\n");

	//save drawn numbers array
	for (int i = 0; i < 90; i++) {
		fprintf(output, "%d ", drawn[i]);
	}
	fprintf(output, "\n");

	//save players
	for (int i = 0; i < numOfPlayers; i++) {
		//save player name
		fprintf(output, "%s \n", playerArray[i].name);

		//save remaining rows
		fprintf(output, "%d %d %d \n", playerArray[i].remaining[0], playerArray[i].remaining[1], playerArray[i].remaining[2]);

		//save players card
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL_LONG; col++) {
				fprintf(output, "%d ", playerArray[i].displayCard[row][col]);
			}
		}
		fprintf(output, "\n");
	}


	fclose(output);
}

void loadGame(int start) {
	srand(time(NULL));

	//open save game file
	FILE *input;
	input = fopen("savegame.txt", "r");

	if (input == NULL) {
		printf("Couldn't open file!");
		return;
	}

	roundCounter = -1;

	fscanf(input, "%d", &numOfPlayers);

	//initialise player array
	playerArray = malloc(sizeof(Player) * numOfPlayers);

	//load available numbers array
	for (int i = 0; i < 90; i++) {
		fscanf(input, "%d ", &available[i]);
	}

	//load drawn numbers array
	for (int i = 0; i < 90; i++) {
		fscanf(input, "%d ", &drawn[i]);
		if (drawn[i] != 0) {
			roundCounter++;
		}
	}

	//load players
	for (int i = 0; i < numOfPlayers; i++) {
		//load player name
		fscanf(input, "%s ", playerArray[i].name);
		fscanf(input, "%d %d %d", &playerArray[i].remaining[0], &playerArray[i].remaining[1], &playerArray[i].remaining[2]);

		//save players card
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL_LONG; col++) {
				fscanf(input, "%d ", &playerArray[i].displayCard[row][col]);
			}
		}
		generateShortCard(playerArray[i].displayCard, playerArray[i].shortCard);
	}
	fclose(input);


	//markCards();
	displayStats();
	playGame();
}