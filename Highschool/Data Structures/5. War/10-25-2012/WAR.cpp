#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

//DEAL IS WRONG! EACH PLAYER STARTS WITH 26 CARDS !!!!!!!!!

int winner(char deck1[52][3], char deck2[52][3]);
//void deal(char deck1[52][3], char deck2[52][3]);
void turn(char deck1[52][3], char deck2[52][3]);

main()
{
	char decks1[52][3] = {0};
	char decks2[52][3] = {0};
	int x = 0;
	
	deal(decks1, decks2);
	
	cout<<"Press a number please! \n";
	cout<<"-> ";
	cin>>x;
	
	return 0;
}

//THE FUNCTIONS!
//The Check win function
int winner(char deck1[52][3], char deck2[52][3])
{
	//if one of the decks has no cards and is completely equal to zero
	//then end the game and the opposite player has won!
	return 0;
}

//The deal function
void deal(char deck1[52][3], char deck2[52][3])
{
	int a, b = 0;
	int num = 2;
	
	//make both decks in the same order:
	//CA
	//C1
	//C2
	//etc
	//then randomize the order!
	
	strcpy(deck1[0], "AC");
	
	//copy 2-9 for
	for(a = 1; a < 9; a++)
	{
		itoa(num, &deck1[a][0], 10);
		strcpy(&deck1[a][1], "C");
		num++;
	}
	
	strcpy(deck1[9], "TC");
	strcpy(deck1[10], "JC");
	strcpy(deck1[11], "QC");
	strcpy(deck1[12], "KC");
	
	num = 2;
	strcpy(deck1[13], "AD");
	
	for(a = 14; a < 22; a++)
	{
		itoa(num, &deck1[a][0], 10);
		strcpy(&deck1[a][1], "D");
		num++;
	}
	
	strcpy(deck1[22], "JD");
	strcpy(deck1[23], "QD");
	strcpy(deck1[24], "KD");
	
		num = 2;
	strcpy(deck1[25], "AH");
	
	for(a = 26; a < 34; a++)
	{
		itoa(num, &deck1[a][0], 10);
		strcpy(&deck1[a][1], "H");
		num++;
	}
	
	strcpy(deck1[34], "JH");
	strcpy(deck1[35], "QH");
	strcpy(deck1[36], "KH");
	
			num = 2;
	strcpy(deck1[37], "AS");
	
	for(a = 38; a < 46; a++)
	{
		itoa(num, &deck1[a][0], 10);
		strcpy(&deck1[a][1], "S");
		num++;
	}
	
	strcpy(deck1[46], "JS");
	strcpy(deck1[47], "QS");
	strcpy(deck1[48], "KS");
	
	for(a = 0; a < 52; a++)
		cout<<deck1[a]<<endl;
}

//The turn function
void turn(int deck1[52][3], int deck2[52][3])
{
		//0 is the bottom of the queue, so check each player's decks and see who wins
		//if play1 wins, pop a[0] and make it zero. then move all his cards up.
		//if play2 loses, add play1s card to the back of the queue
		//and vice versa
		//if play1/play2 tie, then ??
}

/*
	First thing to do is to deal the cards (26 to each, random, only use 52 cards)
	Then look at the top most of each person's deck and determine who wins
	Then pop the enqueue the loser's card, pop that card off the loser and move everything forward 1.
	
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088(v=vs.85).aspx#_win32_character_attributes
	
	black = spades
	red = hearts
	blue = diamonds
	green = clubs
	
	FOREGROUND_GREEN
	FOREGROUND_BLUE
	FOREGROUND_RED
	
	*/
		
	/*
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
