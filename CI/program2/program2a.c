/***********************************************************************************************
	Program:	program2a.c
	Author:		Jason Downing
	Date:		October 3rd, 2013
	Time Spent:	50 minutes
	Purpose:	The purpose of this program is to be able to play a two player game
				of rock-paper-scissors, using R/P/S for Rock/Paper/Scissors. The program
				lets the users play as many times as they want. It also gives the users
				a chance to re-enter a choice if they type something other than R/P/S or y/Y/n/N
				for the 'do you want to continue' prompt.
************************************************************************************************/
#include <stdio.h>

int main(int argc, char* argv[])
{
	/*	chars for the players choices. ans holds the answer to the 'do you want to continue' prompt.
	p1/p2 hold the responses to player1/player2		*/
	char ans = 'y', p1, p2;

	do{
		//	Introduction to the program - tell users what the program is and what to enter to use the program.
		printf("Welcome to the Rock, Paper, Scissors Program \n");
		printf("This program lets two players play a game of Rock, Paper, Scissors. \n");
		printf("Please use p/P for Paper, r/R for Rock and s/S for Scissors. \n\n");
	
		/*	The players then enter their choices and these are stored in p1 for Player 1 and p2 for Player 2
			The do while loop that surrounds these prompts forces the player to enter p/P/r/R/s/S.*/
		do{
			printf("Player 1 please enter your choice: ");
			scanf(" %c", &p1);
		}while(p1 != 'p' && p1 != 'P' && p1 != 'r' && p1 != 'R' && p1 != 's' && p1 != 'S');
		
		do{
			printf("\nPlayer 2 please enter your choice: ");
			scanf(" %c", &p2);
		}while(p2 != 'p' && p2 != 'P' && p2 != 'r' && p2 != 'R' && p2 != 's' && p2 != 'S');

		printf("\n");	//print out one new line to make the rest of the outputting look nicer.

		/*	This is the main code of the program. I use a main switch that detects what Player 1 entered.
		I then use ifs within the cases to print out what happened. ie if P1 = p, then the 'p' case will
		activate, and then one of those 3 ifs will print something out - so if P2 = p, then it will print out
		"You both entered paper, so it's a draw! \n"	*/
		switch(p1)
		{
			case 'p':
				if(p2 == 'p' || p2 == 'P')
					printf("You both entered Paper! It is a draw! No one wins! \n");
				else if(p2 == 'r' || p2 == 'R')	
					printf("Paper covers Rock! Player 1 wins! \n");
				else if(p2 == 's' || p2 == 'S')
					printf("Scissors cut Paper! Player 2 wins! \n");
				break;

			case 'P':
				if(p2 == 'p' || p2 == 'P')
					printf("You both entered Paper! It is a draw! No one wins! \n");
				if(p2 == 'r' || p2 == 'R')	
					printf("Paper covers Rock! Player 1 wins! \n");
				if(p2 == 's' || p2 == 'S')
					printf("Scissors cuts Paper! Player 2 wins! \n");
				break;

			case 'r':
				if(p2 == 'r' || p2 == 'R')
					printf("You both entered Rock! It is a draw! No one wins! \n");
				if(p2 == 'p' || p2 == 'P')
					printf("Paper covers Rock! Player 2 wins! \n");
				if(p2 == 's' || p2 == 'S')
					printf("Rock breaks	 Scissors! Player 1 wins!");
				break;	

			case 'R':				
				if(p2 == 'r' || p2 == 'R')
					printf("You both entered Rock! It is a draw! No one wins! \n");
				if(p2 == 'p' || p2 == 'P')
					printf("Paper covers Rock! Player 2 wins! \n");
				if(p2 == 's' || p2 == 'S')
					printf("Rock breaks Scissors! Player 1 wins!");
				break;

			case 's':
				if(p2 == 's' || p2 == 'S')
					printf("You both entered Scissors! It is a draw! No one wins! \n");
				if(p2 == 'p' || p2 == 'P')
					printf("Scissors cuts Paper! Player 1 wins! \n");
				if(p2 == 'r' || p2 == 'R')	
					printf("Rock breaks scissors! Player 2 wins! \n");
				break;

			case 'S':
				if(p2 == 's' || p2 == 'S')
					printf("You both entered Scissors! It is a draw! No one wins! \n");
				if(p2 == 'p' || p2 == 'P')
					printf("Scissors cuts Paper! Player 1 wins! \n");
				if(p2 == 'r' || p2 == 'R')	
					printf("Rock breaks scissors! Player 2 wins! \n");
				break;

			default:
				printf("\nYou didn't enter P, R or S. Please try again and enter one of those characters! \n");
				break;
		}	

		/*	This do while only allows the users to type y/Y/n/N. If they type anything else the condition is true, and runs a
		second time. Typing any of these characters: y,Y,n,N will cause the do/while to be FALSE and quit.	*/
		do{
			/*	This prompt asks if the user wants to continue the program or quit.
				It takes 'y'/'Y'/'n'/'N' as an answer.	*/
			printf("\nDo you want to continue running the program or quit? Enter y/n: ");
			scanf(" %c", &ans);
		}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');	
		
		//this printf 'clears' the screen - it just adds a bunch of spaces in between uses of the program.
		printf("\n\n\n\n\n\n\n\n\n\n\n");	
	}while(ans == 'y' || ans == 'Y');	//Continues for either y or Y.

	return 0;	//The program ends at this point.
}
