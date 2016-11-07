/***********************************************************************************************
	Program:	program1a.c
	Author:		Jason Downing
	Date:		September 22, 2013
	Time Spent:	1 hour
	Purpose:	The purpose of this program is to determine whether a meeting room is
				below, at or above the maximum room capacity. The user enters both the 
				number of people in the room and the maximum number of people allowed,
				and the program then determines whether the meeting is legal or not. 
				It then prints to the screen how many more people can be in the room or 
				how many people must leave the room for the meeting to be held.
************************************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
	char ans = 'y';			//char 'ans' for the main do/while loop
	int max = 0, curr = 0;	//ints for the two questions

	do{
		/*
		This first part is just an introduction to the program. 
		It tells the user what program it is, and what the program can do.
		*/
		printf("Welcome to the room capacity program. \n");
		printf("This program will allow you to calculate how many people \n");
		printf("may legally be in a room for a meeting. \n\n");

		/*
		The next part of the program asks the user two questions and records the responses
		to those questions in integer variables.
		*/
		printf("How many people will be attending the next meeting? -> ");
		scanf(" %d", &curr);
		printf("What is the legal limit for the room? -> ");
		scanf(" %d", &max);

		/*
		Now the program will perform two calculations:
		1. Is the meeting legal? Y/N
		2A. If legal, how many more people may attend the meeting?
		2B. If illegal, how many people must not attend for the meeting to be legal?
		*/

		if(curr <= max)	//legal to hold the meeting (at or below the room capacity)
		{
			printf("\nIt is legal to hold the meeting! \n");
			printf("%d more people can attend the meeting!", max-curr);
		}
		else //illegal to hold the meeting (over the room capacity)
		{
			printf("\nIt is illegal to hold the meeting! \n");
			printf("%d people must not attend the meeting for it to be legal! \n", curr-max);
		}

		/*
		Finally the program concludes with a prompt to see if the user wishes to continue and perform more calculations or if the user wants to end the program.
		It takes a "y" / "Y" for yes and a "n" / "N" for no.
		The do while loop forces the user to enter y/Y or n/N.
		This is so the user cannot enter 'l' or 'z' (if they entered those it would just end) - they must enter yes or no.
		*/

		do{		
			printf("\n\nDo you wish to continue or exit the program? -> ");	//Prompt for the user to enter yes or no
			scanf(" %c", &ans);
		}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');	//Run while any other letter/number is entered - only quit if y/Y/n/N is entered.

		printf("\n\n\n\n\n\n\n\n\n\n\n");	//this printf 'clears' the screen - it just adds a bunch of spaces in between uses of the program.

	}while(ans == 'y' || ans == 'Y');	//this do while loop is true while the character variable 'ans' holds a y or a 'Y'.
										//it runs until the user wants to quit.
	return 0;	//end of the program at this point.
}