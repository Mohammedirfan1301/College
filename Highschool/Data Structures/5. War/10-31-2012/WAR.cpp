#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

int winner(char deck1[52][2], char deck2[52][2]);
void deal(char deck1[52][2], char deck2[52][2]);
void turn(char deck1[52][2], char deck2[52][2]);

main()
{
	char decks1[52][2] = {0};
	char decks2[52][2] = {0};
	int x = 0;
	
	deal(decks1, decks2);
	
	cout<<"Press a number please! \n";
	cout<<"-> ";
	cin>>x;
	
	return 0;
}

//THE FUNCTIONS!
//The Check win function
int winner(char deck1[52][2], char deck2[52][2])
{
	//if one of the decks has no cards and is completely equal to zero
	//then end the game and the opposite player has won!
	return 0;
}

//The deal function
void deal(char deck1[52][2], char deck2[52][2])
{
	//THERE IS A BUG / DIS CODE NO WORKS
	//why does 2 numbers print?
	//not in order!!
	
	int a, b = 0, x = 1, z = 0;
	int num = 0;				//number of cards pushed to shuffle
	int run = 0;
	char shuffle[51][2] = {0};	//contains a shuffled card deck after the following code is excuted
	int nums[51] = {-3};		//holds all the numbers that have been shuffled to the shuffle deck
	srand(time(NULL));		//random number using time as the seed for the random number
	
	do{
		run = 0;
		z = rand() % 10;	//generate a random #. % # means 0 - #-1. or rand() % 52 means random # between 0 and 51, or 52 cards.
		
		if(nums[z] == -3) 	//check to make sure it isn't in the used number array
			run = 0;		//this is done by comparing numbers:
		else				//-3 means a number has NOT been used
			run = -3;		//-1 means that a number HAS been used
		
		if(run == 0)
		{
			num++;
			switch(z)
			{
				case 0:	
					strcpy(shuffle[0],  "AC");
					cout<<shuffle[0]<<endl;
					nums[0] = -1;
					break;
				case 1:	
					strcpy(shuffle[1],  "2C");
					cout<<shuffle[1];
					nums[1] = -1;
					break;
				case 2:
					strcpy(shuffle[2],  "3C");
					cout<<shuffle[2]<<endl;
					nums[2] = -1;
					break;
				case 3:
					strcpy(shuffle[3],  "4C");
					cout<<shuffle[3]<<endl;
					nums[3] = -1;
					break;
				case 4:
					strcpy(shuffle[4],  "5C");
					cout<<shuffle[4]<<endl;
					nums[4] = -1;
					break;
				case 5:
					strcpy(shuffle[5],  "6C");
					cout<<shuffle[5]<<endl;
					nums[5] = -1;
					break;
				case 6:
					strcpy(shuffle[6],  "7C");
					cout<<shuffle[6]<<endl;
					nums[6] = -1;
					break;
				case 7:
					strcpy(shuffle[7],  "8C");
					cout<<shuffle[7]<<endl;
					nums[7] = -1;
					break;
				case 8:
					strcpy(shuffle[8],  "9C");
					cout<<shuffle[8]<<endl;
					nums[8] = -1;
					break;
				case 9:
					strcpy(shuffle[9],  "TC");
					cout<<shuffle[9]<<endl;
					nums[9] = -1;
					break;
				/*
				case 9:
				
				case 10:
				
				case 11:
				
				case 12:
				
				case 13:
				
				case 14:
			*/
				default:
						cout<<"ERROR!";
			}
			
		}
		
		if(num == 9)
		{
			x = 0;
			break;
		}
		
	}while(x == 1);
	
	//Clubs
/*
	strcpy(shuffle[1],  "2C");
	strcpy(shuffle[2],  "3C");
	strcpy(shuffle[3],  "4C");
	strcpy(shuffle[4],  "5C");
	strcpy(shuffle[5],  "6C");
	strcpy(shuffle[6],  "7C");
	strcpy(shuffle[7],  "8C");
	strcpy(shuffle[8],  "9C");
	strcpy(shuffle[9],  "TC");
	strcpy(shuffle[10], "JC");
	strcpy(shuffle[11], "QC");
	strcpy(shuffle[12], "KC");
	
	//Diamonds
	strcpy(shuffle[13], "AD");
	strcpy(shuffle[14], "2D");
	strcpy(shuffle[15], "3D");
	strcpy(shuffle[16], "4D");
	strcpy(shuffle[17], "5D");
	strcpy(shuffle[18], "6D");
	strcpy(shuffle[19], "7D");
	strcpy(shuffle[20], "8D");
	strcpy(shuffle[21], "9D");
	strcpy(shuffle[22], "TD");
	strcpy(shuffle[23], "JD");
	strcpy(shuffle[24], "QD");
	strcpy(shuffle[25], "KD");
	
	//Hearts
	strcpy(shuffle[26], "AH");
	strcpy(shuffle[27], "2H");
	strcpy(shuffle[28], "3H");
	strcpy(shuffle[29], "4H");
	strcpy(shuffle[30], "5H");
	strcpy(shuffle[31], "6H");
	strcpy(shuffle[32], "7H");
	strcpy(shuffle[33], "8H");
	strcpy(shuffle[34], "9H");
	strcpy(shuffle[35], "TH");
	strcpy(shuffle[36], "JH");
	strcpy(shuffle[37], "QH");
	strcpy(shuffle[38], "KH");
	
	//Spades
	strcpy(shuffle[39], "AS");
	strcpy(shuffle[40], "2S");
	strcpy(shuffle[41], "3S");
	strcpy(shuffle[42], "4S");
	strcpy(shuffle[43], "5S");
	strcpy(shuffle[44], "6S");
	strcpy(shuffle[45], "7S");
	strcpy(shuffle[46], "8S");
	strcpy(shuffle[47], "9S");
	strcpy(shuffle[48], "TS");
	strcpy(shuffle[49], "JS");
	strcpy(shuffle[50], "QS");
	strcpy(shuffle[51], "KS");
*/

	for(a = 0; a < 10; a++)
		cout<<shuffle[a]<<endl;
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
