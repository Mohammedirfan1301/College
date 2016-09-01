/**********************************************************************
Program: Program1B
Author: Jason Downing
Date: 2/2/2014
Time spent: 3 Hours
Purpose: The purpose of this program is stimulate 10,000 games
	 of chance, where the winner has a chance to win $1M.
	 3 "doors" are reprented in an integer array of size 3.
	 One door is at random chosen as the 'winning door' and one
	 door is chosen as the choice of the constant. One more door
	 is then revealed to have one of the lesser prizes behind it.
	 There are two options at this point - switch or stay. This 
	 program notes how many times the constant wins if they
	 switch vs how many times they win if they stay.

From the results of several runs of this program, it is very clear
to me that on this particular game show it is a good idea to switch
your choice. This is because you have a roughly 66% chance of winning
if you switch vs a 33% chance of winning if you stay. (This was 
determined in numerous runs of this program)
Since switching has the higher chance of winning, I'd always switch so 
that I could win the million dollars. ^_^
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>		//srand uses stdlib
#include <time.h>		//time(NULL) uses this

/*
	 Pre-condition: srand has been called in main. Nothing else has been done.
	Post-condition: 10k games have been simulated entirely, 
					with wins recorded and printed to the screen.
*/
void run_experiment(void);

/*
	 Pre-condition: outcome of the game is unknown.
	Post-condition: outcome of the game is determined and recorded in the
					'outcome' variable within run_experiment
*/
int determine_outcome(int doors[], int chosen_door);

/*
	 Pre-condition: Doors array is filled with 0s or 1s
	Post-condition: Doors array is filled ONLY with 0s for use in
					next game.
*/
void clear_array(int arr[]);

int main(int argc, char* argv[])
{
	int i = 0;

	//Seed the random number generator
	srand(time(NULL));
	
	do{
		printf("GAME SHOW SIMULATOR 3000 \n");

		//Call the experiment function
		run_experiment();
	
		//Hold the window open
		printf("\nDo you wish to continue? -> ");
		scanf("%d", &i);
		printf("\n\n");

	}while(i != 1);		//1 will end the program, other wise any other number will
						//continue to call the experiment function, stimulating 10k games
	return 0;
}

void run_experiment(void)
{
	int doors[3] = {0};											//Holds the door's values
	int x, winning_door, chosen_door, revealed_door, outcome;	//Doors
	int count = 0, stay = 0, switched = 0;						//Counters
	
	for(count = 0; count < 10000; count++)	//10k games
	{
		//Set the winning door
		winning_door = rand() % 3;	//Random number 0 to 2
		doors[winning_door] = 1;	//This is the WINNING door (1 represents win)
		
		//Now set the non-winning doors
		for(x = 0; x <= 2; x++)		//0 to 2
			if(doors[x] != 1)		//Not the winning door
				doors[x] = 0;		//Set equal to 0 for 'loser prize'
					
		//Pick what door the person chooses.
		chosen_door = rand() % 3;		//Any random # 0 to 2 will do.
		
		//Now reveal the other door.
		for(revealed_door = 0; revealed_door <= 2; revealed_door++)				//Another 0-2 range.
			if(revealed_door != winning_door && revealed_door != chosen_door)	//This will pick the door that 
				break;															//isn't the winner or the door that they pick.

		outcome = determine_outcome(doors, chosen_door);	
		
		if(outcome == 1)
			stay++;
		else if(outcome == -1)
			switched++;

		//RESET THE ARRAY EACH ROUND! OTHERWISE YOU'LL ALWAYS WIN!
		clear_array(&doors[0]);
	}
	
	//Print out the number of wins, losses and total rounds.	
	printf("Switched Wins: %d \n  Stayed Wins: %d \n       Rounds: %d \n", switched, stay, count);
}

int determine_outcome(int doors[], int chosen_door)
{
	//Now randomly determine whether they win by switching or staying
	if(doors[chosen_door] == 1)
	{
		//They win if they stay!
		return 1;
	}
	else if(doors[chosen_door] != 1)
	{
		//If they switch, then they should win.
		//This is b/c there's 2 doors now - two doors that is
		//And if they don't stick with their door, there's only one other door to pick!
		return -1;
	}
}

void clear_array(int arr[])
{
	int x;

	for(x = 0; x <= 2; x++)		//0 to 2
		arr[x] = 0;				//Clear the array by putting 0s in each index

	return;
}
