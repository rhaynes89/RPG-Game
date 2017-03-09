/*======================================
* Programer:Richard Haynes III
* Date: 3/1/17
* Class: C Programming
* Assignment: RolePlaying Game
========================================*/

#include"rRoleplayGame.h"

main()
{
	srand(time(NULL));

	char playAgain;
	HIGHSCORES scores[10];
	
	int gamesSaved = 0;

	
	do {
		
		playGame(scores, &gamesSaved);
		CLS;
		printf("\n\n\t\t\t\t   ======================= \n \t\t\t\t   == PLAY AGAIN? (Y/N) ==\n \t\t\t\t   =======================\n\n");
		scanf("%c", &playAgain);
		getc(stdin);
		playAgain = toupper(playAgain);
		CLS;

	} while (playAgain != 'N');


	PAUSE;
}//end main