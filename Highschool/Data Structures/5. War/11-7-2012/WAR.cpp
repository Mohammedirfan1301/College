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

int winner(int deck1[26], int deck2[26]);
void deal(int deck1[26], int deck2[26]);
void turn(int deck1[26], int deck2[26]);

int main()
{
	int decks1[26] = {0};
	int decks2[26] = {0};
	char c;
	int x = 0;
	srand(time(0));		//random number using time as the seed for the random number
	
	do{
		deal(decks1, decks2);	//deal the cards
		
		do{
			turn(decks1, decks2);	//a round of war starts
		
    		cout<<"Press enter to continue. -> ";
    		
			do{
        		c = getch();
   	 		}while(c != 13);
			
			system("cls");	//clear the screen
			
		}while(winner(decks1, decks2) == 0);	//run until there is a winner!
	
	}while(x == 1);
	
	return 0;
}

//THE FUNCTIONS!
//The Check win function
int winner(int deck1[26], int deck2[26])
{
	//if one of the decks has no cards and is completely equal to zero
	//then end the game and the opposite player has won!
	
	return 0;
}

//The deal function
void deal(int deck1[26], int deck2[26])
{
	int a, b = 0;				//loop variables/shuffle
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
	
	//shuffle the array, using the Fisher-Yates Shuffle algorithm (found info on wikipedia)
	do{
		b = rand()%(a+1);
		temp = nums[a];
		nums[a] = nums[b];
		nums[b] = temp;
		b--;
	}while(b > 0);
	
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
}

//The turn function
void turn(int deck1[26], int deck2[26])
{
		//0 is the bottom of the queue, so check each player's decks and see who wins
		//if play1 wins, pop a[0] and make it zero. then move all his cards up.
		//if play2 loses, add play1s card to the back of the queue
		//and vice versa
		//if play1/play2 tie, then ??

		int a, b;						//loop variables
		int cards1 = 0, cards2 = 0;		//number of cards in each deck
		int temp = 0;					//temp variable
		int val1, val2;					//value of each card for the turn
		int suit1, suit2;				//suit for the given cards
		
		//see how many cards each deck has
		//deck1:
		for(a = 0; a < 26; a++)
		{
			if(deck1[a] == -1)
			{
				cards1 = a + 1;
				break;
			}

			if(a == 25 && deck1[a] != -1)
			{
				cards1 = 26;
				break;
			}
		}
				
		//deck2:
		for(a = 0; a < 26; a++)
		{
			if(deck2[a] == -1)
			{
				cards2 = a + 1;
				break;
			}

			if(a == 25 && deck2[a] != -1)
			{
				cards2 = 26;
				break;
			}
		}
		
		cout<<"*** Number of Cards in each Player's Deck *** \n";
		cout<<"Player 1: "<<cards1<<'\n';
		cout<<"Player 2: "<<cards2<<"\n\n";
		
		//Now see who wins the given round:
		val1 = deck1[cards1-1] % 13 + 1;
		val2 = deck2[cards2-1] % 13 + 1;
		suit1 = deck1[cards1-1] / 13;
		suit2 = deck2[cards2-1] / 13;
		
		cout<<"PLAYER 1: ";
			if(val1 <= 9)
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
		
		cout<<"\nPLAYER 2: ";
			if(val1 <= 9)
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
		cout<<'\n';
		if(val1 > val2)
			cout<<"PLAYER 1 WINS THIS ROUND! \n";
		
		if(val1 < val2)
			cout<<"PLAYER 2 WINS THIS ROUND! \n";
		
		if(val1 == val2)
		{
			cout<<"TIE! SUDDEN DEATH: \n";
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
