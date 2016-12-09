
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "persistance.h"


//function to save game
void saveGame(Caller caller) {
	//open file to append
	FILE *output = fopen("savegame.txt", "a");

	if (output == NULL) {
		printf("Couldn't open file!");
		return;
	}

	fprintf(output, "%d ", caller.numOfPlayers);										//save number of players
	fprintf(output, "%d ", caller.roundCounter);										//save number of rounds

	//save players
	for (int i = 0; i < caller.numOfPlayers; i++) {
		fprintf(output, "%s ", caller.playerArray[i].name);								//save player name

		//save remaining rows
		fprintf(output, "%d %d %d ", caller.playerArray[i].remaining[0], caller.playerArray[i].remaining[1], caller.playerArray[i].remaining[2]);
				
		for (int row = 0; row < ROW; row++) {											//save players card
			for (int col = 0; col < COL_LONG; col++) {
				fprintf(output, "%d ", caller.playerArray[i].displayCard[row][col]);
			}
		}
	}//end save players

	//save drawn numbers array
	for (int i = 0; i <= caller.roundCounter; i++) {
		fprintf(output, "%d ", caller.drawn[i]);
	}

	fprintf(output, ";\n");
	fclose(output);

	printf("\n\n\t\t\t\tGame saved...");
	printf("\n\n\t\t\t\tPress key to continue...");
	getch();
}

//find the number of save games and let the user choose one
int chooseSaveGame() {

	int userChoice;
	char buffer[1024];
	int counter = 0;
	int result;
	int offset = 0;

	FILE *input;
	input = fopen("savegame.txt", "r");

	if (input == NULL) {
		printf("Couldn't open file!");
		return 2;
	}
	
	//scan the file by line and count their amount
	while (!feof(input)) {
		result = fgets(buffer, 1024, input);
		if (result > 0) {
			counter++;
		}
	}

	printf("\n\n\t\t\t\tFound %d savegames", counter);
	printf("\n\t\t\t\tChoose a savegame: ");

	do {
		scanf("%d", &userChoice);
	} while (userChoice < 1 || userChoice > counter);								//let the user choose a savegame
		

	//find the offset of the chosen savegame	
	fseek(input, 0, SEEK_SET);														//go back to the start of the file
	counter = 0;

	while (counter != userChoice - 1) {												//loop until one less than the users choice
		result = fgets(buffer, 1024, input);
		if (result > 0) {
			counter++;																//count line numbers
		}
		offset = ftell(input);														//store the position of the pointer 
	}

	fclose(input);
	return offset;
}

//load a previously saved game, store it in a caller struct and return it to the main game
Caller loadGame(int offset) {
	srand(time(NULL));

	//initialise a new caller struct
	Caller caller;
	caller.fourCornersWon = false;
	caller.oneRowWon = false;
	caller.twoRowsWon = false;

	//open save game file
	FILE *input = fopen("savegame.txt", "r");

	if (input == NULL) {
		printf("Couldn't open file!");
		return;
	}
	
	fseek(input, offset, SEEK_SET);													//set scan pointer to the start of the chosen savegame

	fscanf(input, "%d", &caller.numOfPlayers);										//load number of players
	fscanf(input, "%d", &caller.roundCounter);										//load number of rounds played

	caller.playerArray = (Player*)malloc(sizeof(Player) * caller.numOfPlayers);		//initialise player array

	//load players
	for (int i = 0; i <caller.numOfPlayers; i++) {
		fscanf(input, "%s", caller.playerArray[i].name);							//load player name
																					
		for (int j = 0; j < 3; j++) {												//load remaining tracker array
			fscanf(input, "%d", &caller.playerArray[i].remaining[j]);
		}
				
		for (int row = 0; row < ROW; row++) {										//load players card
			for (int col = 0; col < COL_LONG; col++) {
				fscanf(input, "%2d ", &caller.playerArray[i].displayCard[row][col]);
			}
		}

		generateShortCard(caller.playerArray[i].displayCard, caller.playerArray[i].shortCard);

	}//end load players
	
	for (int i = 0; i <= caller.roundCounter; i++) {								//load drawn numbers array
		fscanf(input, "%d ", &caller.drawn[i]);
	}
		
	for (int i = 0; i < 90; i++) {													//set up available numbers array
		caller.available[i] = i + 1;
	}
	
	for (int i = 0; i <= caller.roundCounter; i++) {								//mark numbers as unavailable
		for (int j = 0; j < 90; j++) {
			if (caller.drawn[i] == caller.available[j]) {
				caller.available[j] = -1;
				break;
			}
		}
	}

	fclose(input);
	return caller;
}
