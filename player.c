#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "displayMenu.h"
#include "player.h"

//initialise a player before the game starts
Player preparePlayer() {

	displayTitle();
	Player player;
	printf("\n\n\t\t\t\tPlease enter the players name: ");
	scanf("%s", player.name);

	generateCard(player.displayCard);

	generateShortCard(player.displayCard, player.shortCard);		

	player.remaining[0] = 5;										//
	player.remaining[1] = 5;										//initialise tracker for remaining numbers 
	player.remaining[2] = 5;										//

	return player;
}

//generate the card with empty fields 
void generateCard(int card[ROW][COL_LONG]) {
	//seed for RNG
	srand(time(NULL));

	int ran;

	//numbers 1 - 90 in ranges of 10th 
	int availableNums[9][10];
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 10; col++) {
			availableNums[row][col] = (row * 10) + col + 1;
		}
	}

	//fill card with 27 numbers
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL_LONG; col++) {

			do {
				ran = (rand() % 10);
			} while (availableNums[col][ran] == -1);					//check if number has already been taken

			card[row][col] = availableNums[col][ran];
			availableNums[col][ran] = -1;								//mark number as taken to avoid duplicates
		}
	}

	sortCard(card);

	//delete 4 random numbers in each row
	for (int row = 0; row < ROW; row++) {
		for (int j = 0; j < 4; j++) {

			do {
				ran = rand() % 9;
			} while (card[row][ran] == -1);

			card[row][ran] = -1;									//-1 == empty field in card
		}
	}	
}


//sort columns with bubble sort
void sortCard(int card[ROW][COL_LONG]) {

	for (int col = 0; col < COL_LONG; col++) {

		for (int row = ROW - 1; row > 0; row--) {
			for (int k = 0; k < row; k++) {
				if (card[k][col] > card[k + 1][col]) {
					int temp = card[k][col];
					card[k][col] = card[k + 1][col];
					card[k + 1][col] = temp;
				}
			}
		}
	}
}


//generate the card used to determine winner
void generateShortCard(int card[ROW][COL_LONG], int shortCard[ROW][COL_SHORT]) {

	for (int row = 0; row < ROW; row++) {
		int shortCol = 0;
		for (int col = 0; col < COL_LONG; col++) {
			if (card[row][col] != -1) {
				shortCard[row][shortCol++] = card[row][col];
			}			
		}
	}
}

