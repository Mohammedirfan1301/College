/***********************************************************************************************
	Program:	program2b.c
	Author:		Jason Downing
	Date:		October 3rd, 2013
	Time Spent:	1 hour 30 minutes
	Purpose:	
				The purpose of thise program is to calculate how large a population
				of green crud will be after x number of days. The program takes the users
				input on how large the initial population of green crud is and how many days 
				the user wants the program to calculate out to. 
************************************************************************************************/
#include <stdio.h>

void wipe_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	/*	Variables used in the program. Ans for answer. greencrud holds the initial population and days holds the number of days to calculate out.
		firstfib holds the 1st Fibonacci number and secondfib holds the 2nd one. X is used in a while loop. Count is used to count every 5 days.	*/
	char ans;
	int greencrud = 0, days = 0, increases = 0;
	int firstfib = 0, secondfib = 0, x = 0;

	do{
		//Introduction prompt to the program.
		printf("Welcome to the Green Crud Population Calculator. \n");
		printf("This program will calculate the size of a population of Green Crud \n");
		printf("given a number of days to calculate out to. \n\n");

		//Now the program prompts for the initial size and the number of days to calculate out to.
		printf("Enter the initial size of the Green Crud Population: ");
		scanf(" %d", &greencrud);
		wipe_keyboard_buffer();

		printf("Enter the number of days to calculate out to: ");
		scanf(" %d", &days);
		wipe_keyboard_buffer();

		increases = days/5;		//This finds how many times to increase the population, which is on a 5 day cycle for increases.
		firstfib = 0;			//Initilize these numbers for use in the while loop.
		secondfib = greencrud;	//This basically makes sure the first green crud calculation is correct
								//as green crud = f1 + f2 and the first one should equal 0 + itself = itself

		for(x = 0; x < increases; x++)	//Calculate out to the number of days requested.
		{	
				greencrud = firstfib + secondfib;		//increase greencrud by adding the last two numbers
				firstfib = secondfib;					//previous holds the last number
				secondfib = greencrud;					//current holds the current number
		}	
		

		//Print out the final size after x amount of days.
		printf("\nThe final size of the Green Crud Population after %d days is: %d \n\n", days, greencrud);

		/*	This do while only allows the users to type y/Y/n/N. If they type anything else the condition is true, and runs a
		second time. Typing any of these characters: y,Y,n,N will cause the do/while to be FALSE and quit.	*/
		do{
			/*	This prompt asks if the user wants to continue the program or quit.
				It takes 'y'/'Y'/'n'/'N' as an answer.	*/
			printf("Do you want to continue running the program or quit? Enter y/n: ");
			scanf(" %c", &ans);
			wipe_keyboard_buffer();
		}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');	
		
		//this printf 'clears' the screen - it just adds a bunch of spaces in between uses of the program.
		printf("\n\n\n\n\n");	

	}while(ans == 'y' || ans == 'Y');

	return 0;
}

void wipe_keyboard_buffer(void)
{
	char next;

	scanf("%c", &next);	//wipe the first character

	while(next != '\n') //wipe until the newline
	{
		//keep wiping characters
		scanf("%c", &next);
	}
	return;
}