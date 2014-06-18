#include <iostream>
#include <windows.h>
using namespace std;

main()
{
	int deck1[52] = {0};
	int deck2[52] = {0};
	
	HANDLE hConsole;
	hConsole = GetStdHandle (STD_OUTPUT_HANDLE);

	//FOREGROUND_GREEN
	//FOREGROUND_BLUE

    SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    	cout<<"Ace of Hearts \n";
	
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE);
    	cout<<"Ace of Diamonds \n";
	
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    	cout<<"Ace of Clubs \n";
	
	cout<<"Å  \n";
	Sleep(5000);
	/*
	First thing to do is to deal the cards (26 to each, random, only use 52 cards)
	Then look at the top most of each person's deck and determine who wins
	Then pop the enqueue the loser's card, pop that card off the loser and move everything forward 1.
	
	black = spades
	red = hearts
	blue = diamonds
	green = clubs
	
	*/
		
	return 0;
}
