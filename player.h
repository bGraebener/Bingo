#pragma once

#define ROW 3
#define COL_LONG 9
#define COL_SHORT 5

//declaration Player struct
typedef struct {

	char name[20];
	int displayCard[ROW][COL_LONG];			//cards with empty fields - for display only
	int shortCard[ROW][COL_SHORT];			//card used to determine winner

	int remaining[3];						//array used to keep track of remaining numbers per row

}Player;

//function prototypes
Player preparePlayer();
void generateCard(int [ROW][COL_LONG]);
void generateShortCard(int [ROW][COL_LONG], int [ROW][COL_SHORT]);
void sortCard(int [ROW][COL_LONG]);

