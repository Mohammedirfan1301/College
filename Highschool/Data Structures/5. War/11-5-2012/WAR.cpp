#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

/*
1. Some how shuffle the cards randomly? CHECK!
2. Then program the game
3. must go turn by turn, seeing who won
4. also must take into account ties
5. then must check after each turn to see if someone won yet.


*/

int winner(int deck1[52][2], int deck2[52][2]);
void deal(int deck1[52][2], int deck2[52][2]);
void turn(int deck1[52][2], int deck2[52][2]);

main()
{
	int decks1[52][2] = {0};
	int decks2[52][2] = {0};
	int x = 0;
	srand(time(0));		//random number using time as the seed for the random number
	
	deal(decks1, decks2);
	
	cout<<"Press a number please! \n";
	cout<<"-> ";
	cin>>x;
	
	return 0;
}

//THE FUNCTIONS!
//The Check win function
int winner(int deck1[52][2], int deck2[52][2])
{
	//if one of the decks has no cards and is completely equal to zero
	//then end the game and the opposite player has won!
	return 0;
}

//The deal function
void deal(int deck1[52][2], int deck2[52][2])
{
	//THERE IS A BUG / DIS CODE NO WORKS
	//why does 2 numbers print?
	//not in order!!
	
	int a, b = 0;				//loop variables/shuffle
	int len = 52, temp = 0;  	//variables for the shuffling 
	int num = 0;				//number of cards pushed to shuffle
	char shuffle[52][2] = {0};	//contains a shuffled card deck after the following code is excuted
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
	
	//throw the other half of nums into deck2
	for(a = 26; a < 52; a++)
		deck2[a] = nums[a];
}

//The turn function
void turn(int deck1[52][2], int deck2[52][2])
{
		//0 is the bottom of the queue, so check each player's decks and see who wins
		//if play1 wins, pop a[0] and make it zero. then move all his cards up.
		//if play2 loses, add play1s card to the back of the queue
		//and vice versa
		//if play1/play2 tie, then ??
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
