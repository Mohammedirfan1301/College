#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

/*	1. Some how shuffle the cards randomly? CHECK!
	2. Then program the game
	3. must go turn by turn, seeing who won
	4. also must take into account ties
	5. then must check after each turn to see if someone won yet. */

int winner(int deck1[52], int deck2[52]);
void deal(int deck1[52], int deck2[52]);
void turn(int deck1[52], int deck2[52]);

int main()
{
	int decks1[52] = {-1};
	int decks2[52] = {-1};
	char c;
	int win = 0, x = 0;
	srand(time(0));		//random number using time as the seed for the random number
	
	do{
		deal(decks1, decks2);	//deal the cards
		
		cout<<"__                __      ___        _____     _    \n";
		cout<<"\ \      /\      / /     / _ \      |  __ \   | |   \n";
		cout<<" \ \    /  \    / /     / / \ \     | |__) |  | |   \n";
		cout<<"  \ \  / /\ \  / /     / /___\ \    |  _  /   |_|   \n";
		cout<<"   \ \/ /  \ \/ /     / /-----\ \   | | \ \    _    \n";
		cout<<"    \__/    \__/     /_/       \_\  |_|  \_\  |_|   \n";
		        
		cout<<" ###      #       ###     ###       ########   ### \n";
 		cout<<"  ###	 ###     ###     #####      ###  ###   ### \n";
  		cout<<"   ###	#####   ###     ### ###     ###  ###   ### \n";
   		cout<<"    ### ### ### ###     ###   ###    ########   ### \n";
    	cout<<"     #####   #####     ###########   ###  ###       \n";
      	cout<<"      ###     ###     ###       ###  ###   ###  ### \n";

		
		do{
			turn(decks1, decks2);	//a round of war starts
		
    		cout<<"Press enter to continue. -> ";
    		
			do{
        		c = getch();
   	 		}while(c != 13);
			
			win = winner(decks1, decks2);
			
			system("cls");	//clear the screen
			
		}while(win == 0);	//run until there is a winner!
	
	if(win == 1)
	{
		cout<<"CONGRATZ PLAYER 2! YOU WIN! \n";
		cout<<"Your army crushed the enemy Player 2! \n";
		cout<<"PLAYER 1 - you failed. Your entire army was completely destroyed. \n";
		cout<<"Better luck next time Player 1. \n";
	
	}
	if(win == 2)
	{
		cout<<"CONGRATZ PLAYER 1! YOU WIN! \n";
		cout<<"Your army crushed the enemy Player 1! \n";
		cout<<"PLAYER 2 - you failed. Your entire army was completely destroyed. \n";
		cout<<"Better luck next time Player 2. \n\n";			
	}
	
	cout<<"Do you wish to play again? \n";
	cout<<"Enter 1 to continue playing or 2 to quit. -> ";
	cin>>x;
	
	}while(x == 1);
	
	cout<<"THANKS FOR PLAYING WAR! \n";
	
		do{
        	c = getch();
   	 	}while(c != 13);
	
	return 0;
}

//THE FUNCTIONS!
//The Check win function
int winner(int deck1[52], int deck2[52])
{
	//if one of the decks has no cards and is completely equal to zero
	//then end the game and the opposite player has won!
	if(deck1[0] == -1)
		return 1;
	if(deck2[0] == -1)
		return 2;
	else
		return 0;
}

//The deal function
void deal(int deck1[52], int deck2[52])
{
	int a = 0, b = 0, x = 0;				//loop variables/shuffle
	int len = 52, temp = 0;  	//variables for the shuffling 
	int num = 0;				//number of cards pushed to shuffle
	int nums[52] = {0};		//holds all the numbers that have been shuffled to the shuffle deck
	
	/*My shuffling works like this:
	1. Shuffle an array of numbers (0-51) representing all of the cards in a 52 card deck
	2. Use that shuffled array to put the cards in the char array 'shuffle'
	3. Split this array into two, for the deck1 and deck2 arrays
	4. From here, the turn/win functions take over as deal is done.
	
	ALSO: I use int arrays - I didn't feel like using chars when I could use use a few divisions/modulas to find what suit/value the card has
	*/
	
	//set nums array equal to 0-51
	for(a = 0; a < 52; a++)
	{
		nums[a] = num;
		num++;	
	}
	
	//shuffle the array, using a shuffling algorithm (found info on wikipedia - Fisher-Yates Shuffle)
	for(x = 0; x < 1000; x++)	//the more times it runs, the 'more' random it gets. I figured 1000 would make it pretty random.
	{
		a = rand()%51;			//makes two random numbers between 0 and 51
		b = rand()%51;
		temp = nums[a];			//shuffles by moving them around - temp holds nums[a], which nums[a] is then set equal to nums[b] and
		nums[a] = nums[b];		//nums[b] is then set equal to temp.
		nums[b] = temp;			//since a/b are both random numbers, the process is random - numbers move to different spots randomly.
	}

	
	//split half of nums array in to deck1
	for(a = 0; a < 26; a++)
		deck1[a] = nums[a];
	
	temp = 26;
	
	//throw the other half of nums into deck2
	for(a = 0; a < 26; a++)
	{
		deck2[a] = nums[temp];
		temp++;
	}
	
	//make sure all the empty spots are equal to -1 - makes it easier to error check in the future.
	for(a = 26; a < 52; a++)
	{
		deck1[a] = -1;
		deck2[a] = -1;
	}
	
	/*	//FOR TESTING PURPOSES:
	for(a=0;a<52;a++)
		cout<<deck1[a]<<'\n'<<deck2[a]<<'\n';
		
	cout<<"Works? \n";
	cin>>a;
	*/
}

//The turn function
void turn(int deck1[52], int deck2[52])
{
		//0 is the bottom of the queue, so check each player's decks and see who wins
		//if play1 wins, pop a[0] and make it zero. then move all his cards up.
		//if play2 loses, add play1s card to the back of the queue
		//and vice versa
		//if play1/play2 tie, then ??
		//top is 0 and bottom is the last card in the queue (26 or such)

		int a, b;						//loop variables
		int cards1 = 0, cards2 = 0;		//number of cards in each deck
		int bot1 = 0, bot2 = 0;			//bottom of the queue for each deck
		int temp = 0;					//temp variable
		int val1, val2;					//value of each card for the turn
		int suit1, suit2;				//suit for the given cards
		
		//see how many cards each deck has
		//deck1:
		for(a = 0; a < 52; a++)
		{
			if(deck1[a] == -1)
			{
				cards1 = a;
				bot1 = a;
				break;
			}
		}
				
		//deck2:
		for(a = 0; a < 52; a++)
		{
			if(deck2[a] == -1)
			{
				cards2 = a;
				bot2 = a;
				break;
			}
		}
		
		cout<<"*** Number of Cards in each Player's Deck *** \n";
		cout<<"Player 1: "<<cards1<<'\n';
		cout<<"Player 2: "<<cards2<<"\n";
		
		//Now see who wins the given round:
		val1 = deck1[0] % 13 + 1;
		val2 = deck2[0] % 13 + 1;
		suit1 = deck1[0] / 13;
		suit2 = deck2[0] / 13;
		
		cout<<"\n* Card each Player has * \n";
		
		cout<<"PLAYER 1: ";
			if(val1 == 1)
			{
				val1 = 14;
				cout<<"A";
			}
			if(val1 <= 9 && val1 > 1)
				cout<<val1;
			if(val1 > 9)
			{
				if(val1 == 10)
					cout<<"T";
				if(val1 == 11)
					cout<<"J";
				if(val1 == 12)
					cout<<"Q";
				if(val1 == 13)
					cout<<"K";
			}
			
		if(suit1 == 0)
			cout<<"C";
		if(suit1 == 1)
			cout<<"D";
		if(suit1 == 2)
			cout<<"H";
		if(suit1 == 3)
			cout<<"S";
		
		cout<<"\nPLAYER 2: ";
			if(val2 == 1)
			{
				val2 = 14;
				cout<<"A";
			}
			if(val2 <= 9 && val2 > 1)
				cout<<val2;
			if(val2 > 9)
			{
				if(val2 == 10)
					cout<<"T";
				if(val2 == 11)
					cout<<"J";
				if(val2 == 12)
					cout<<"Q";
				if(val2 == 13)
					cout<<"K";
			}
			
		if(suit2 == 0)
			cout<<"C";
		if(suit2 == 1)
			cout<<"D";
		if(suit2 == 2)
			cout<<"H";
		if(suit2 == 3)
			cout<<"S";
			
		cout<<"\n\n";
		
		if(val1 > val2)
		{
			cout<<"PLAYER 1 WINS THIS ROUND! \n";
			
			//What must happen:
			//	1. Move deck1[0] to the back of the queue.
			//	2. Pop deck2[0] to the back of deck1.
			//	3. Move all queues forward 1.
			
			deck1[bot1] = deck1[0];	// 1. (see 1.)
			deck1[bot1 + 1] = deck2[0];	//Part of 2., its popped in the below 'move forward' steps (3.)
			
			//move Player 1's deck forward 1.	(3.1)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck1[a-1] = deck1[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			}
			deck1[51] = -1;	//make sure the last number is -1 since everything got moved forward 1.
			
			//move Player 2's deck forward 1.	(3.2)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck2[a-1] = deck2[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			
				if(deck2[a] == -1)		//this makes sure to pop the value of the losing card from the deck.
					deck2[a-1] = -1;
			}	
		}
		
		if(val1 < val2)
		{
			cout<<"PLAYER 2 WINS THIS ROUND! \n";
			
			//What must happen:
			//	1. Move deck1[0] to the back of the queue.
			//	2. Pop deck2[0] to the back of deck1.
			//	3. Move all queues forward 1.
			
			deck2[bot2] = deck2[0];	// 1. (see 1.)
			deck2[bot2 + 1] = deck1[0];	//Part of 2., its popped in the below 'move forward' steps (3.)
			
			//move Player 1's deck forward 1.	(3.1)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck2[a-1] = deck2[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			}
			deck2[51] = -1;	//make sure the last number is -1 since everything got moved forward 1.
			
			//move Player 2's deck forward 1.	(3.2)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck1[a-1] = deck1[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			
				if(deck1[a] == -1)		//this makes sure to pop the value of the losing card from the deck.
					deck1[a-1] = -1;
			}
		}
		
		if(val1 == val2)
		{
			cout<<"TIE! \n";
			
			cout<<"Player 1\tPlayer 2  \n";
			cout<<"   #    \t   #	   \n";
			cout<<"   #    \t   #      \n";
			cout<<"   #    \t   #      \n";
			
			//Think about making a function for the below since its used in the original turn area way above. A ton of code too!!
			
			val1 = deck1[3] % 13 + 1;
			val2 = deck2[3] % 13 + 1;
			suit1 = deck1[3] / 13;
			suit2 = deck2[3] / 13;
			
			cout<<"   ";
			
			if(val1 == 1)
			{
				val1 = 14;
				cout<<"A";
			}
			if(val1 <= 9 && val1 > 1)
				cout<<val1;
			if(val1 > 9)
			{
				if(val1 == 10)
					cout<<"T";
				if(val1 == 11)
					cout<<"J";
				if(val1 == 12)
					cout<<"Q";
				if(val1 == 13)
					cout<<"K";
			}
			
			if(suit1 == 0)
				cout<<"C";
			if(suit1 == 1)
				cout<<"D";
			if(suit1 == 2)
				cout<<"H";
			if(suit1 == 3)
				cout<<"S";
		
			cout<<"     \t   ";
		
			if(val2 == 1)
			{
				val2 = 14;
				cout<<"A";
			}
			if(val2 <= 9 && val2 > 1)
				cout<<val2;
			if(val2 > 9)
			{
				if(val2 == 10)
					cout<<"T";
				if(val2 == 11)
					cout<<"J";
				if(val2 == 12)
					cout<<"Q";
				if(val2 == 13)
					cout<<"K";
			}
			
			if(suit2 == 0)
				cout<<"C";
			if(suit2 == 1)
				cout<<"D";
			if(suit2 == 2)
				cout<<"H";
			if(suit2 == 3)
				cout<<"S";
			
			cout<<"\n\n";
			
			//THESE SHOULD BE FUNCTIONS!!!
			if(val1 > val2)
			{
				cout<<"PLAYER 1 WINS THIS ROUND! \n";
			
			//What must happen:
			//	1. Move deck1[0] to the back of the queue.
			//	2. Pop deck2[0] to the back of deck1.
			//	3. Move all queues forward 1.
			
			deck1[bot1] = deck1[0];	// 1. (see 1.)
			deck1[bot1 + 1] = deck2[0];	//Part of 2., its popped in the below 'move forward' steps (3.)
			
			//move Player 1's deck forward 1.	(3.1)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck1[a-1] = deck1[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			}
			deck1[51] = -1;	//make sure the last number is -1 since everything got moved forward 1.
			
			//move Player 2's deck forward 1.	(3.2)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck2[a-1] = deck2[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			
				if(deck2[a] == -1)		//this makes sure to pop the value of the losing card from the deck.
					deck2[a-1] = -1;
			}	
			cout<<'\n';	
			}
			
			//TURN THESE INTO FUNCTIONS! EEK!
			if(val1 < val2)
			{
				cout<<"PLAYER 2 WINS THIS ROUND! \n";
			
			//What must happen:
			//	1. Move deck1[0] to the back of the queue.
			//	2. Pop deck2[0] to the back of deck1.
			//	3. Move all queues forward 1.
			
			deck2[bot2] = deck2[0];	// 1. (see 1.)
			deck2[bot2 + 1] = deck1[0];	//Part of 2., its popped in the below 'move forward' steps (3.)
			
			//move Player 1's deck forward 1.	(3.1)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck2[a-1] = deck2[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			}
			deck2[51] = -1;	//make sure the last number is -1 since everything got moved forward 1.
			
			//move Player 2's deck forward 1.	(3.2)
			for(a = 0; a <= 51; a++)
			{
				if(a > 0)
					deck1[a-1] = deck1[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			
				if(deck1[a] == -1)		//this makes sure to pop the value of the losing card from the deck.
					deck1[a-1] = -1;
			}
			cout<<'\n';		
			}
		}
}

/*
	HELPFUL LINKS:
	http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
	http://cboard.cprogramming.com/c-programming/147721-shuffle-deal-cards-c.html
	http://www.pagat.com/war/war.html
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088(v=vs.85).aspx#_win32_character_attributes
	
	HOW TO PROCEED:
	First thing to do is to deal the cards (26 to each, random, only use 52 cards)
	Then look at the top most of each person's deck and determine who wins
	Then pop the enqueue the loser's card, pop that card off the loser and move everything forward 1.

	COLORS!!:
	black = spades
	red = hearts
	blue = diamonds
	green = clubs
	
	FOREGROUND_GREEN
	FOREGROUND_BLUE
	FOREGROUND_RED
	
	HANDLE hConsole;
	hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    	cout<<"Ace of Clubs \n";

	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    	cout<<"Ace of Diamonds \n";

    SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    	cout<<"Ace of Hearts \n";
	
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_INTENSITY);
    	cout<<"Ace of Spades \n";
	
		for(a = 0; a < 10; a++)
		cout<<deck1[a]<<endl;
	*/
