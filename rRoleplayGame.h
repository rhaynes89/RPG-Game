/*======================================
* Programer:Richard Haynes III
* Date: 3/1/17
* Class: C Programming
* Assignment: RolePlaying Game
========================================*/

#define _CRT_SECURE_NO_WARNINGS
#define PAUSE system("pause")
#define CLS system("cls")
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structs here
typedef struct CHARACTER
{
	char name[20];
	int lives;
	int money;
	int strength;
	int bodyArmor;
	int agility;
}CHARACTER;

typedef struct GAME
{
	int numWins;
	int numLosses;
	int winStreak;
	int lossStreak;
	int bestWinStreak;
	int bestLossStreak;
}GAME;

typedef struct HIGHSCORES
{
	char name[20];
	int money;
}HIGHSCORES;

//functions here
void buyHealthAndStrengthMenu(CHARACTER *player, GAME *gamePlay);
void displayMenu();
void displayHighScores(HIGHSCORES scores, int gamesSaved);//NOT DONE
void initalizeGame(CHARACTER *player, GAME *gamePlay);
void playGame(HIGHSCORES scores[], int *gamesSaved);
void readHighScores(HIGHSCORES scores[], int gamesSaved);
void rulesOfFightClub();
void showPlayerInfo(CHARACTER player, GAME gamePlay);
void simBattle(CHARACTER *player, GAME *gamePlay);
void sortHighScores(HIGHSCORES scores[]);
void storeMenu();
char userChoice();
void winLossResults(GAME gamePlay, CHARACTER player);
void writeHighScores(HIGHSCORES scores[], int gamesSaved);



/*======================================
* Function: buyHealthAndStrengthMenu
* Date: 3/1/17
* Data Needed: CHARACTER *player, GAME *gamePLay
* Data Returned: nothing
* Purpose: Menu for option B in main
menu. This function lets the user
purchase lives and strength.
========================================*/
void buyHealthAndStrengthMenu(CHARACTER *player, GAME *gamePlay)
{
	char choice;
	int totalMoney;
	do
	{
		CLS;
		showPlayerInfo(*player, *gamePlay);
		storeMenu();
		choice = userChoice();

		switch (choice)
		{
		case 'A'://buy strength
			if (player->money < 50)
			{
				printf("\n\n\t\t\t\t\t=================== \n \t\t\t\t\t==You broke fool!== \n\t\t\t\t\t===================\n\n");
				PAUSE;
			}
			else
			{
				printf("\n\n\t\t\t\t=============================================\n \t\t\t\t== Your strength has grown by 5 points! ==\n\t\t\t\t=============================================\n\n");
				PAUSE;
				player->strength = player->strength + 5;
				player->money = player->money - 50;
			}
			break;

		case 'B'://buy Health
			if (player->money < 100)
			{
				printf("\n\n\t\t\t\t\t=================== \n \t\t\t\t\t==You broke fool!== \n\t\t\t\t\t===================\n\n");
				PAUSE;
			}
			else
			{
				printf("\nn\t\t\t\t\t=============================\n \t\t\t\t\t==You have gained one life!==\n\t\t\t\t\t=============================\n\n");
				PAUSE;
				player->money = player->money - 100;
				player->lives = player->lives + 1;

			}
			break;

		case 'C':
			if (player->money < 200)
			{
				printf("\n\n\t\t\t\t\t=================== \n \t\t\t\t\t==You broke fool!== \n\t\t\t\t\t===================\n\n");
				PAUSE;
			}
			else if (player->bodyArmor < 100)
			{
				printf("\n\n\t\t\t\t\t=========================\n \t\t\t\t\t==You have body armor!==\n\t\t\t\t\t=========================\n\n");
				PAUSE;
				player->money = player->money - 200;
				player->bodyArmor = player->bodyArmor + 100;
			}
			if (player->bodyArmor > 100)
			{
				printf("\n\n\t\t\t\t\t================================\n \t\t\t\t\t==You already have body armor!==\n\t\t\t\t\t================================\n\n");
				PAUSE;
			}
			break;

		case 'D':
			if (player->money < 700)
			{
				printf("\n\n\t\t\t\t\t=================== \n \t\t\t\t\t==You broke fool!== \n\t\t\t\t\t===================\n\n");
				PAUSE;
			}
			else
			{
				printf("\n\n\t\t\t\t\t=============================\n \t\t\t\t\t==You now have sneakers!==\n\t\t\t\t\t=============================\n\n");
				PAUSE;
				player->money = player->money - 700;
				player->agility = player->agility + 10;
			}
			break;
		case 'Q'://Return to main menu
			CLS;
			printf("\n\n\t\t\t\t===================================== \n \t\t\t\t ==Thanks for shopping at Walmart!==\n \t\t\t\t=====================================\n\n");
			PAUSE;
			break;

		default:
			printf("\n\nPlease pick a valid option!\n\n");
			PAUSE;
			break;
		}
	} while (choice != 'Q');



}//end of buying menu

 /*======================================
 * Function: displayMenu
 * Date: 3/1/17
 * Data Needed: none
 * Data Returned: nothing
 * Purpose: Shows user main menu.
 ========================================*/
void displayMenu()
{

	printf("\t\t\t\t\t   ==================\n\t\t\t\t\t    == FIGHT CLUB ==\n\t\t\t\t\t   ==================\n");
	printf("\n\t\t\t\t\t================================\n");
	printf("\t\t\t\t\t A. Rules of Fight Club.\n");
	printf("\t\t\t\t\t B. Start a battle.\n");
	printf("\t\t\t\t\t C. Buy player attributes.\n");
	printf("\t\t\t\t\t D. Display current results (wins/losses).\n");
	printf("\t\t\t\t\t E. Display top 10 scores.\n");
	printf("\t\t\t\t\t Q. Save and Quit");
	printf("\n\t\t\t\t\t================================\n\n");

	printf("\nSelect your choice: ");


} // end displayMenu

  /*======================================
  * Function: displayHighScores
  * Date: 3/1/17
  * Data Needed: HIGHSCORES scores
  * Data returned: none
  * Purpose: This function displays the
  top ten high scores to the user.
  ========================================*/
void displayHighScores(HIGHSCORES scores[], int *gamesSaved)
{
	char count;

	CLS;
	printf("\n\n\t\t\t\t\t===================\n \t\t\t\t\t== TOP 10 SCORES ==\n\t\t\t\t\t===================\n\n ");
	for (count = 0; count < *gamesSaved; count++)
	{
		printf("%i. %s: $%i\n\n", count + 1, scores[count].name, scores[count].money);
	}

	if (*gamesSaved == 0)
	{
		CLS;
		printf("\n\n\t\t\t\t\t ===========================\n \t\t\t\t\t   == No highscores yet!==\n\t\t\t\t\t ===========================\n\n");
		
	}


}//end of display highscores


  /*======================================
  * Function: initalizeGame
  * Date: 3/1/17
  * Data Needed: CHARACTER *player, GAME *gamePlay
  * Data Returned: none
  * Purpose: This function starts all current
  win/lose streaks to zero. Allows user to
  enter a characters name.
  ========================================*/
void initalizeGame(CHARACTER *player, GAME *gamePlay)
{
	printf("Enter character's name:\t\n");
	scanf("%[^\n]s", &player->name);
	getc(stdin);
	player->lives = 4;
	player->money = 0;
	player->strength = 0;
	player->bodyArmor = 0;
	player->agility = 0;
	gamePlay->numWins = 0;
	gamePlay->numLosses = 0;
	gamePlay->winStreak = 0;
	gamePlay->lossStreak = 0;
	gamePlay->bestWinStreak = 0;
	gamePlay->bestLossStreak = 0;
}//end of initalizeGame

 /*======================================
 * Function: playGame
 * Date: 3/2/17
 * Data Needed: CHARACTER *player, GAME *gamePlay,
 HIGHSCORES *scores
 * Data Returned: none
 * Purpose: This function is the game itself.
 ========================================*/
void playGame(HIGHSCORES scores[], int *gamesSaved)
{
	char choice;
	CHARACTER player;
	GAME gamePlay;
	
	

	initalizeGame(&player, &gamePlay);
	do
	{
		CLS;
		showPlayerInfo(player, gamePlay);
		displayMenu();
		choice = userChoice();

		switch (choice)
		{
		case 'A'://rules of fight club
			rulesOfFightClub();
			PAUSE;
			break;
		case 'B'://battle
			simBattle(&player, &gamePlay);
			PAUSE;
			break;
		case 'C'://store
			buyHealthAndStrengthMenu(&player, &gamePlay);
			PAUSE;
			break;
		case 'D'://current record
			winLossResults(gamePlay, player);
			PAUSE;
			break;
		case 'E'://top 10 scores
			displayHighScores(scores, gamesSaved);
			PAUSE;
			break;
		case 'Q'://save and quit
			CLS;
			
			printf("\n\n\t\t\t\t================================= \n \t\t\t\t   == Thank you for playing! ==\n \t\t\t\t=================================\n\n");
			printf("\n\n\n\n");
			break;
		default:
			printf("\n \t\t\t\t================================== \n \t\t\t\t ==Please pick a valid option! ==\n \t\t\t\t==================================\n\n\n\n");
			PAUSE;
			break;
		}
		if (player.lives == 0)
		{

			winLossResults(gamePlay, player);
			printf("\n\n\t\t\t\t     ===================== \n \t\t\t\t       == GAME OVER! ==\n \t\t\t\t     =====================\n\n");
			printf("\n\n");
			choice = 'Q';
			printf("\n\n\n\n");
			PAUSE;
		}

	} while (choice != 'Q');

	if (*gamesSaved < 10)
	{
		strcpy(scores[*gamesSaved].name, player.name);
		scores[*gamesSaved].money = player.money;
		(*gamesSaved)++;
	}
	else if (scores[*gamesSaved - 1].money < player.money)
	{
		strcpy(scores[*gamesSaved - 1].name, player.name);
		scores[*gamesSaved - 1].money = player.money;
	}
	sortHighScores(scores, gamesSaved);
	writeHighScores(scores, gamesSaved);

}

/*======================================
* Function: readHighScores
* Date: 3/1/17
* Data Needed: HIGHSCORES scores
* Data Returned: none
* Purpose: To read the bin file to pull
highscores into game.
========================================*/
void readHighScores(HIGHSCORES scores[], int *gamesSaved)
{
	FILE* scoresPtr;
	scoresPtr = fopen("highscore.bin", "rb");

	if (scoresPtr == NULL)
	{
		printf("\n Error! \n");
		PAUSE;
		exit(-1);
	}

	fread(gamesSaved, sizeof (int), 1, scoresPtr);
	fread(scores, sizeof (HIGHSCORES), (*gamesSaved), scoresPtr);
	fclose(scoresPtr);


}//end redHighScores

/*======================================
* Function: rulesOfFightClub
* Date: 3/1/17
* Data Needed: none
* Data Returned: none
* Purpose: This displays the rules of
fight club.
========================================*/
void rulesOfFightClub()
{
	CLS;
	printf("\n\n\t\t\t\t\t=========================\n \t\t\t\t\t== RULES OF FIGHT CLUB ==\n\t\t\t\t\t=========================\n\n");
	printf("\t\t     ===============================================================================");
	printf("\n\t\t\t1.The first rule of fight club is: you dont talk about fight club.\n\n");
	printf("\t\t\t2.The second rule of fight club is: you DO NOT talk about fight club.\n\n");
	printf("\t\t\t3.The third of fight club: if someone yells 'STOP', goes limp, or taps out,\n"
		"\t\t\t  the fight is over.\n\n");
	printf("\t\t\t4.The fourth rule is: only two guys to a fight!\n");
	printf("\t\t     ===============================================================================\n\n");
}//end of rules

 /*======================================
 * Function: showPlayerInfo
 * Date: 3/1/17
 * Data Needed: CHARACTER player, GAME gamePlay
 * Data Returned: none
 * Purpose: This function will show the
 information for the player at all times.
 ========================================*/
void showPlayerInfo(CHARACTER player, GAME gamePlay)
{
	printf("======================\n == PLAYER INFO == \n======================\n");
	printf("======================\n");
	printf("Name: %s\n", player.name);
	printf("Lives: %i\n", player.lives);
	printf("Money: $%i\n", player.money);
	printf("Strength: %i\n", player.strength);
	printf("Agility: %i\n", player.agility);
	printf("Body Armor: %i\n", player.bodyArmor);
	printf("======================\n");
}//end of showPlayerInfo

/*======================================
* Function: simBattle
* Date: 3/1/17
* Data Needed: CHARACTER *player, GAME *gamePLay
* Data Returned: nothing
* Purpose: Simulates battle and decides
wins and loses. Also adds and subtracts
money, lifes, and strength.
========================================*/
void simBattle(CHARACTER *player, GAME *gamePlay)
{
	int randValue = 0;

	randValue = rand() % 100;
	randValue++;

	if (randValue <= 20 || randValue + player->strength <= 50)
	{
		CLS;
		showPlayerInfo(*player, *gamePlay);
		printf("\n\n\t\t\t\t\t========================\n \t\t\t\t\t==You loss the battle!==\n\t\t\t\t\t=========================\n\n\n\n"); //loss here
		player->lives = player->lives - 1;
		if (player->strength > 0 && player->bodyArmor == 0)
		{
			player->strength = player->strength - 5;
		}
		else if (player->bodyArmor > 0)
		{
			player->bodyArmor = player->bodyArmor - 5;
		}

		gamePlay->numLosses++;
		gamePlay->lossStreak++;
		gamePlay->winStreak = 0;

		if (gamePlay->lossStreak > gamePlay->bestLossStreak)
		{
			gamePlay->bestLossStreak = gamePlay->lossStreak;
		}

	}
	else
	{
		CLS;
		showPlayerInfo(*player, *gamePlay);
		printf("\n\n\t\t\t\t\t========================\n \t\t\t\t\t==You won the battle!==\n\t\t\t\t\t=========================\n\n\n\n");// win here
		player->strength = player->strength + 5;
		player->agility = player->agility + 10;
		player->money = player->money + 50;
		gamePlay->numWins++;
		gamePlay->winStreak++;
		gamePlay->lossStreak = 0;

		if (gamePlay->bestWinStreak >= 3)
		{
			player->money = player->money * 1.5;
		}

		if (gamePlay->bestWinStreak < gamePlay->winStreak)
		{
			gamePlay->bestWinStreak = gamePlay->winStreak;
		}
	}


}//end simBattle

 /*======================================
 * Function: sortHighScores
 * Date: 3/1/17
 * Data Needed: HIGHSCORES scores
 * Data Returned: none
 * Purpose: This function keeps track
 of the top 10 scores. Score is based
 on the amount of money gained while
 playing the game.
 ========================================*/
void sortHighScores(HIGHSCORES scores[], int *scoreNum)
{
	char swap;
	HIGHSCORES temp;
	int count;

	do
	{
		swap = 'N';

		for (count = 0; count < (*scoreNum - 1); count++)
		{
			if (scores[count].money < scores[count + 1].money)
			{
				temp = scores[count + 1];
				scores[count + 1] = scores[count];
				scores[count] = temp;
				swap = 'Y';
			}//end of bubble sort
		}
	} while (swap == 'Y');

	return;
}//end of sortHighScores


  /*======================================
  * Function: storeMenu
  * Date: 3/1/17
  * Data Needed: none
  * Data Returned: none
  * Purpose: This displays the menu to the
  user for buying strength and health.
  ========================================*/
void storeMenu()

{
	printf("\t\t\t\t\t\t=============\n\t\t\t\t\t\t== WALMART ==\n\t\t\t\t\t\t=============\n");
	printf("\t\t\t\t===============================================\n");
	printf("\t\t\t\t A. Buy strength($50 for 5 strength points.\n");
	printf("\t\t\t\t B. Buy lives ($100 for one life).\n");
	printf("\t\t\t\t C. Buy body armor ($200 for armor).\n");
	printf("\t\t\t\t D. Buy sneakers (one pair $700).\n");
	printf("\t\t\t\t Q. Return to main menu.\n");
	printf("\t\t\t\t===============================================\n");

	printf("\nSelect your choice: ");
}//end of store menu

 /*======================================
 * Function: useChoice
 * Date: 3/1/17
 * Data Needed: none
 * Data Returned: char
 * Purpose: To gather users choice.
 ========================================*/
char userChoice()
{
	char result;
	scanf(" %c", &result); getc(stdin);
	return toupper(result);

}// end userChoice

 /*======================================
 * Function: winLossResults
 * Date: 3/1/17
 * Data Needed: CHARACTER player, GAME gamePlay
 * Data Returned: none
 * Purpose: This function shows the user
 all win and lose results.
 ========================================*/
void winLossResults(GAME gamePlay, CHARACTER player)
{
	CLS;
	printf("\n\t\t\t\t  =========================== \n\t\t\t\t       == GAME STATS ==\n\t\t\t\t  ===========================");
	printf("\n\t\t\t\t===================================\n");
	printf("\t\t\t\t    Number of wins: %i\n", gamePlay.numWins);
	printf("\t\t\t\t    Number of losses: %i\n", gamePlay.numLosses);
	printf("\t\t\t\t    Current winning streak: %i\n", gamePlay.winStreak);
	printf("\t\t\t\t    Current lossing streak: %i\n", gamePlay.lossStreak);
	printf("\t\t\t\t    Best winning streak: %i\n", gamePlay.bestWinStreak);
	printf("\t\t\t\t    Best lossing streak: %i\n", gamePlay.bestLossStreak);
	printf("\t\t\t\t===================================\n\n\n");
}//end of showing all results (wins/losses)

 /*======================================
 * Function: writeHighScores
 * Date: 3/1/17
 * Data Needed: HIGHSCORES score
 * Data Returned: none
 * Purpose: This function writes the top
 ten high scores to the bin file.
 ========================================*/
 void writeHighScores(HIGHSCORES scores[], int gamesSaved)
 {
	 FILE* scoresPtr;
	 scoresPtr = fopen("highscore.bin", "wb");

	 if (scoresPtr == NULL)
	 {
		 printf("\n Error! \n");
		 PAUSE;
		 exit(-1);
	 }

	 fwrite(&gamesSaved, sizeof(int), 1, scoresPtr);
	 fwrite(scores, sizeof(HIGHSCORES), gamesSaved, scoresPtr);

	 fclose(scoresPtr);
	 return;
 }


