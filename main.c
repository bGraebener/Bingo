//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


typedef struct {

	char name[20];
	int card[3][5];

}Player;


void generateCard(int[3][5], int size);

void main() {

	//declare variables 
	int numOfPlayers;

	//printf("Welcome to Bingo!\nHow many players will be joining us today?");
	//scanf("%d", &numOfPlayers);

	Player player;
	
	generateCard(player.card, 3);

	for (int i = 0; i < 3; i++) {
		printf("%d %d %d %d %d\n", player.card[0], player.card[1], player.card[2], player.card[3], player.card[4]);
	}


	getch();
}

void generateCard(int card[3][5], int size) {

	srand(time(NULL));
	int ran, num;
	int allNums[90];

	for (int i = 0; i < 90; i++) {
		allNums[i] = i + 1;
	}

	for (int i = 0; i < size; i++) {
		SAME: for (int j = 0; j < 5; j++) {
			
			do {
				ran = (rand() % 90) + 1;
				num = allNums[ran];
			} while (num == -1);

			for (int k = 0; k < 5; k++) {
				if ((card[i][k] / 10) == (num / 10)) {
					j--;
					goto SAME;
				}
			}

			allNums[ran] = -1;
			card[i][j] = num;
			printf("%d", card[i][j]);
		}
	}


}