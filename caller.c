#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

	//get number of players between 2 & 6
	do {
		displayTitle();
		printf("\n\n\t\t\t\tHow many player will be joining us today? (2 - 6)");
		printf("\n\n\t\t\t\tNumber of players: ");

		scanf("%d", &numOfPlayers);
	} while (numOfPlayers < 2 || numOfPlayers > 6);

	//get array to store players
	playerArray = malloc(sizeof(Player) * numOfPlayers);

	//prepare all the players
	for (int i = 0; i < numOfPlayers; i++) {

		//generate player cards and display them
		playerArray[i] = preparePlayer();
		displayPlayer(playerArray[i]);
		printf("\n\n\t\t\t\tPress key to continue...");
		getch();
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
		do {
			displayExitOptions();

			scanf("%d", &choice);
		} while (choice < 1 || choice > 3);

		if (choice == 3) {
			displayGoodbye();
		}
		else if (choice == 2) {
			int choice = chooseSaveGame();
			loadGame(choice);
		
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
		ranNum = (rand() % 89) + 1;
		draw = available[ranNum];							//get a number from the pool of available numbers
	} while (draw == -1);

	available[ranNum] = -1;									//mark drawn number as unavailable
	drawn[++roundCounter] = draw;							//update round counter 

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

		//mark short card
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
			fourCornersWon = true;																	//option won't be checked again if once won
			printf("\n\n\t\t\t\tPress key to continue...");
			getch();
		}
	}

	//check for row winners
	if (!oneRowWon) {
		if (player.remaining[0] == 0 || player.remaining[1] == 0 || player.remaining[2] == 0) {
			displayTitle();
			printf("\n\n\t\t\t\t%s shouts Bingo! I have completed one row!", player.name);
			oneRowWon = true;																		//option won't be checked again if once won
			printf("\n\n\t\t\t\tPress key to continue...");
			getch();
		}
	}
	else {
		if (!twoRowsWon) {
			if ((player.remaining[0] == 0 && player.remaining[1] == 0) || (player.remaining[0] == 0 && player.remaining[2] == 0) || (player.remaining[2] == 0 && player.remaining[1] == 0)) {
				displayTitle();
				printf("\n\n\t\t\t\t%s shouts Bingo! I have completed two rows!", player.name);
				twoRowsWon = true;																	//option won't be checked again if once won
				printf("\n\n\t\t\t\tPress key to continue...");
				getch();
			}
		}
	}
	return false;
}

//function to handle a finished game
void endGame(Player winner) {
	int choice;
	do {
		displayTitle();

		printf("\n\n\t\t\t\t\t%s won this round of Bingo!", winner.name);
		printf("\n\t\t\t\t\tWhat's your next move?");
		printf("\n\n\t\t\t\t\t1 - Play again");											//draw next number option unavailable
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
		saveGame();
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
			int choice = chooseSaveGame();
			loadGame(choice);			
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

//function to save game
void saveGame() {
	//open file to append 
	FILE *output = fopen("savegame.txt", "a");

	if (output == NULL) {
		printf("Couldn't open file!");
		return;
	}

	//save number of players
	fprintf(output, "%d ", numOfPlayers);

	//save number of rounds
	fprintf(output, "%d ", roundCounter);

	//save players
	for (int i = 0; i < numOfPlayers; i++) {
		//save player name
		fprintf(output, "%s ", playerArray[i].name);

		//save remaining rows
		fprintf(output, "%d %d %d ", playerArray[i].remaining[0], playerArray[i].remaining[1], playerArray[i].remaining[2]);

		//save players card
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL_LONG; col++) {
				fprintf(output, "%d ", playerArray[i].displayCard[row][col]);
			}
		}
	}

	//save drawn numbers array
	for (int i = 0; i <= roundCounter; i++) {
		fprintf(output, "%d ", drawn[i]);
	}

	fprintf(output, "\n");
	fclose(output);
}

//find the number of save games and let the user choose one
int chooseSaveGame() {

	FILE *input;
	input = fopen("savegame.txt", "r");

	if (input == NULL) {
		printf("Couldn't open file!");
		return;
	}

	//savegames are delimited by a newline char \n
	//scan the file for \n and count their occurences
	char tok = '0';
	int counter = 0;

	while (!feof(input)) {
		fscanf(input, "%c", &tok);
		if (tok == 10) {
			counter++;
		}
	}

	//feof adds one \n so subtract one
	printf("\n\n\t\t\t\tFound %d savegames", counter - 1);

	printf("\n\t\t\t\tChoose a savegame: ");

	int savegame;

	do {
		scanf("%d", &savegame);
	} while (savegame < 1 || savegame >(counter - 1));

	return savegame;
}


void loadGame(int savegame) {
	srand(time(NULL));

	//open save game file
	FILE *input;
	input = fopen("savegame.txt", "r");

	if (input == NULL) {
		printf("Couldn't open file!");
		return;
	}

	//find the offset of the chosen savegame
	char tok = '0';
	int counter = 0;
	int offset = 0;

	while (counter != savegame - 1) {			//count the /n until one less than the users choice
		fscanf(input,"%c", &tok);
		if (tok == 10) {
			counter++;							//count newline occurences 
		}
		offset++;								//count the offset to start of the savegame
	}

	fseek(input, offset, 0);					//set scan pointer to the start of the chosen savegame

	//load number of players
	fscanf(input, "%d", &numOfPlayers);
	
	//load number of rounds played
	fscanf(input, "%d", &roundCounter);
	
	//initialise player array
	playerArray = malloc(sizeof(Player) * numOfPlayers);


	//load players
	for (int i = 0; i < numOfPlayers; i++) {
		//load player name
		fscanf(input, "%s%n", playerArray[i].name);
	
		//bytes_consumed += strlen(playerArray[i].name);

		//load status tracker array
		for (int j = 0; j < 3; j++) {
			fscanf(input, "%d%n", &playerArray[i].remaining[j]);			
		}

		//load players card
		for (int row = 0; row < ROW; row++) {
			for (int col = 0; col < COL_LONG; col++) {
				fscanf(input, "%2d ", &playerArray[i].displayCard[row][col]);
			}
		}

		generateShortCard(playerArray[i].displayCard, playerArray[i].shortCard);
	}

	//load drawn numbers array
	for (int i = 0; i <= roundCounter; i++) {
		fscanf(input, "%d ", &drawn[i]);
	}

	//set up available numbers array
	for (int i = 0; i < 90; i++) {
		available[i] = i + 1;
	}

	//mark numbers as unavailable
	for (int i = 0; i <= roundCounter; i++) {
		for (int j = 0; j < 90; j++) {
			if (drawn[i] == available[j]) {
				available[j] = -1;
				break;
			}
		}
	}


	fclose(input);

	displayStats();
	playGame();
}