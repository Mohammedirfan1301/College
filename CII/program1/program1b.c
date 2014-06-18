#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//3049 last num for emirp program.

/*

# of wins by staying
---------------------
# of tries by staying

ie 6000/10000


*/

void run_experiment(void);
void always_switch(void);
//void never_switch(void);

int main(int argc, char* argv[])
{
	//Seed the random number generator
	srand(time(NULL));
	
	//Call the experiment function
	run_experiment();
	
	return 0;
}

void run_experiment(void)
{
	//Two tests to run: ALWAYS switching and NEVER switching
	always_switch();
		
	return;
}

void always_switch(void)
{
	int choices[3];
	int i, x, a, b, c, d;	//A Is the winning door. B is our choice. C is the other door, to be revealed.
	int count = 0, wins = 0, lose = 0;
	
	for(i = 0; i < 10000; i++)
	{
		a = rand() % 3;	//Random number 0 to 2
		choices[a] = 1;	//This is the WINNING door
		
		//Now set the non-winning doors
		if(choices[0] != 1)
			choices[0] = 0;
		if(choices[1] != 1)
			choices[1] = 0;
		if(choices[2] != 1)
			choices[2] = 0;
					
		//Now, doors are set. Pick what door to choose.
		b = rand() % 3;
		
		//Now to reveal the other door.
		do{
			c = rand() % 3;
		}while(choices[c] != 1 && c != b);	//This will pick the door that isn't the winner and the door that we did NOT pick.
		
		//Now we have the following situation:
		/*
			A is the winning door
			B is the door we picked
			C is the door that was revealed - it has nothing behind it.
			D is the door we will switch to
			
			Now, we will switch to the other door - it is either a WINNER or nothing.
			We will tally the number of wins by doing this in the variable wins.
			count will contain the total number of rounds (should be 10,000)
		*/
		
		for(x = 0; x < 2; x++)
		{
			if(choices[x] != b && choices[x] != c)
				d = x;
		}
		
		//Now detect whether we won or lost.
		if(choices[d] == 1)
		{	
			//WE WON!
			wins++;
		}
		else
			lose++;
			//we lost... ;(
		
		
		count++;
	
	}
	
	//Print out the number of wins, losses and total rounds.	
	printf(" 
	Wins: %d \n Losses: %d \n Rounds: %d \n", wins, lose, count);
}







