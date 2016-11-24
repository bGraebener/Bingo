//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


typedef struct {

	char name[20];
	int card[3][5];

}Player;


void generateCard(int[3][5], int sizeFirst, int sizeSecond);
void sortCard(int[3][5], int sizeFirst, int sizeSecond);

void main() {

	//declare variables 
	int numOfPlayers;

	/*printf("Welcome to Bingo!\nHow many players will be joining us today?");
	scanf("%d", &numOfPlayers);

	Player *playerArray = malloc(sizeof(Player) * numOfPlayers);
	*/

	Player player;

	generateCard(player.card, 3, 5);

	for (int i = 0; i < 3; i++) {
		printf("%d %d %d %d %d\n", player.card[i][0], player.card[i][1], player.card[i][2], player.card[i][3], player.card[i][4]);
	}


	getch();
}

void generateCard(int card[3][5], int sizeFirst, int sizeSecond) {

	srand(time(NULL));
	int ran, num;
	int allNums[90];

	//array to keep track of already assigned numbers
	for (int i = 0; i < 90; i++) {
		allNums[i] = i + 1;
	}

	//populate two-dimensional array
	for (int i = 0; i < sizeFirst; i++) {
		for (int j = 0; j < sizeSecond; j++) {
		NEWRAND:
			do {
				ran = (rand() % 90) + 1;				//generate a random number in the range 1 - 90
				num = allNums[ran];
			} while (num == -1);						//num -1 means num at index has been previously assigned

			for (int k = 0; k < 5; k++) {				//loop to check if the column is already populated
				if ((card[i][k] / 10) == (num / 10)) {
					goto NEWRAND;
				}
			}

			allNums[ran] = -1;
			card[i][j] = num;			
		}
	}

	sortCard(card, 3, 5);

	return card;
}

//sort every row from low to high
void sortCard(int card[3][5], int sizeFirst, int sizeSecond) {
	for (int i = 0; i < sizeFirst; i++) {

		for (int j = sizeSecond - 1; j > 0; j--) {

			for (int k = 0; k < j; k++) {
				if (card[i][k] > card[i][k + 1]) {
					int temp = card[i][k];
					card[i][k] = card[i][k + 1];
					card[i][k + 1] = temp;
				}
			}

		}

	}
}
