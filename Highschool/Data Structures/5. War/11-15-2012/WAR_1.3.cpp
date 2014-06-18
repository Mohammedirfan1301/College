#include <iostream>
#include <iomanip>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

int winner(int deck1[52], int deck2[52]);	//checks to see if either player has won (is one deck[0] == -1?)
void deal(int deck1[52], int deck2[52]);	//deals the cards, by shuffling them and spliting the deck into two arrays (deck1/deck2)
void turn(int deck1[52], int deck2[52]);	//runs through a turn of WAR!
int turnwin(int deck1[52], int deck2[52], int bot1, int bot2, int pos);	//Used for checking which player has won the turn
void p1win(int deck1[52], int deck2[52], int bot1);				//if Player 1 wins, this goes through the necessary processes (enqueueing, dequeueing, etc)
void p2win(int deck1[52], int deck2[52], int bot2);				//same as above but reversed for Player 2

int main()
{
	int decks1[52] = {-1};	//Deck of cards for Player 1
	int decks2[52] = {-1};	//Deck of cards for Player 2
	int win1 = 0, win2 = 0;			//Keeps track of the wins (win1 is P1's wins, win2 is P2's wins)
	int turns, totalturn = 0;	//Keeps track of the turns needed for each win and the total turns completed for all games.
	char c;	//used for 'press enter to continue'
	int win = 0, a = 0, x = 0;	//used for detecting wins and in the do/while loops
	srand(time(0));		//random number using time as the seed for the random number
	
	do{
		deal(decks1, decks2);	//deal the cards
		turns = 1;
		
		cout<<" ###       #       ###     ###       ########   ### \n";
 		cout<<"  ###     ###     ###     #####      ###   ##   ### \n";
  		cout<<"   ###   #####   ###     ### ###     ###   ##   ### \n";
   		cout<<"    ### ### ### ###     ###   ###    ########   ### \n";
    	cout<<"     #####   #####     ###########   ###  ###       \n";
      	cout<<"      ###     ###     ###       ###  ###   ###  ### \n\n";                  
		
		cout<<"\tTo start a game of WAR! Press Enter! -> ";
		
		do{
        	c = getch();
   	 	}while(c != 13);
   	 	
		system("cls");	//clear the screen
		
		do{
			cout<<"TURN: "<<turns<<'\n';
			turn(decks1, decks2);	//a round of war starts
		
    		cout<<"\nPress enter to continue. -> ";
    		
			do{
        		c = getch();
   	 		}while(c != 13);
			
			win = winner(decks1, decks2);
			
			system("cls");	//clear the screen
			turns++;
			
		}while(win == 0);	//run until there is a winner!
	
	if(win == 1)
	{
		cout<<"CONGRATZ PLAYER 2! YOU WIN! \n";
		cout<<"Your army crushed the enemy Player 2! \n\n";
		
		cout<<"PLAYER 1 - you failed. Your entire army was completely destroyed. \n";
		cout<<"Better luck next time Player 1. \n\n";
		
		cout<<"Turns taken to win the game: "<<turns<<"\n\n";
		win1++;
		totalturn += turns;
	}
	if(win == 2)
	{
		cout<<"CONGRATZ PLAYER 1! YOU WIN! \n";
		cout<<"Your army crushed the enemy Player 1! \n\n";
		
		cout<<"PLAYER 2 - you failed. Your entire army was completely destroyed. \n";
		cout<<"Better luck next time Player 2. \n\n";
		
		cout<<"Turns taken to win the game: "<<turns<<"\n\n";			
		win2++;
		totalturn += turns;
	}
	
	cout<<"Do you wish to play again? \n";
	cout<<"Enter 1 to continue playing or 2 to quit. -> ";
	cin>>x;
	
	system("cls");	//clear the screen
	
	}while(x == 1);
	
	cout<<"THANKS FOR PLAYING WAR! \n";
	cout<<"Total turns completed: "<<totalturn<<'\n';
	cout<<"Total games played: ";
	x = win1 + win2;
	cout<<x<<'\n';
	cout<<"Average turns per game: ";
	a = totalturn / x;
	cout<<a;
	
	cout<<"\n\nPress Enter to quit. -> ";
		
	do{
        c = getch();
   	}while(c != 13);
	
	return 0;
}

//THE FUNCTIONS!
//The Check win function
int winner(int deck1[52], int deck2[52])
{
	if(deck1[0] == -1)		//if one of the decks has no cards and is completely equal to zero
		return 1;			//then end the game and the opposite player has won!
	if(deck2[0] == -1)
		return 2;
	else
		return 0;
}

//The deal function
void deal(int deck1[52], int deck2[52])
{
	int a = 0, b = 0, x = 0;	//loop variables/shuffle
	int len = 52, temp = 0;  	//variables for the shuffling 
	int num = 0;				//number of cards pushed to shuffle
	int nums[52] = {0};			//holds all the numbers that have been shuffled to the shuffle deck
	
	/*My shuffling works like this:
	1. Shuffle an array of numbers (0-51) representing all of the cards in a 52 card deck
	2. Use that shuffled array to put the cards in the char array 'shuffle'
	3. Split this array into two, for the deck1 and deck2 arrays
	4. From here, the turn/win functions take over as deal is done.
	
	ALSO: I use int arrays - I didn't feel like using chars when I could use use a few divisions/modulas to find what suit/value the card has
	*/

	for(a = 0; a < 52; a++)		//set nums array equal to 0-51
	{
		nums[a] = num;
		num++;	
	}
	
	for(x = 0; x < 1000; x++)	//shuffle the array, using a shuffling algorithm (found info on wikipedia - Fisher-Yates Shuffle)
	{							//the more times it runs, the 'more' random it gets. I figured 1000 would make it pretty random.
		a = rand()%51;			//makes two random numbers between 0 and 51
		b = rand()%51;
		temp = nums[a];			//shuffles by moving them around - temp holds nums[a], which nums[a] is then set equal to nums[b] and
		nums[a] = nums[b];		//nums[b] is then set equal to temp.
		nums[b] = temp;			//since a/b are both random numbers, the process is random - numbers move to different spots randomly.
	}

	for(a = 0; a < 26; a++)		//split half of nums array in to deck1
		deck1[a] = nums[a];
	
	temp = 26;	//used for the second half of the array.
	
	for(a = 0; a < 26; a++)		//throw the other half of nums into deck2
	{
		deck2[a] = nums[temp];
		temp++;
	}
	
	for(a = 26; a < 52; a++)	//make sure all the empty spots are equal to -1 - makes it easier to error check in the future.
	{
		deck1[a] = -1;
		deck2[a] = -1;
	}
}

//The turn function
void turn(int deck1[52], int deck2[52])
{
		int a, b;						//loop variables
		int cards1 = 0, cards2 = 0;		//number of cards in each deck
		int pos = 0;					//pos allows the tie part to work - it starts at 0 and increases by 3 for each tie.
		int bot1 = 0, bot2 = 0;			//bottom of the queue for each deck
		int win = 0, tie = 0, tienum = 1;			//win is for the outcome of the turn (P1 wins, P2 wins, P1/P2 tie) and tie is to rerun the tie check until ties are done.
										//ie tie lets the program check for ties within a tie.
		
		//see how many cards each deck has
		for(a = 0; a < 52; a++)		//deck1:
		{
			if(deck1[a] == -1)
			{
				cards1 = a;
				bot1 = a;
				break;
			}
		}	

		for(a = 0; a < 52; a++)		//deck2:
		{
			if(deck2[a] == -1)
			{
				cards2 = a;
				bot2 = a;
				break;
			}
		}
		
		cout<<"\n*** Number of Cards in each Player's Deck *** \n";
		cout<<"Player 1: "<<cards1<<" cards \nPlayer 2: "<<cards2<<" cards\n\n";
		cout<<"*** Card each Player has *** \n";
		cout<<right<<"Player 1 "<<setw(20)<<"Player 2    \n";
		
		win = turnwin(deck1, deck2, bot1, bot2, pos);	//See who wins the given round:
		
		if(win == 1)
		{
			p1win(deck1, deck2, bot1);				//P1win is the function that handles
			cout<<"PLAYER 1 WINS THIS ROUND! \n";
		}
		
		if(win == 2)
		{
			p2win(deck1, deck2, bot2);
			cout<<"PLAYER 2 WINS THIS ROUND! \n";
		}
		
		if(win == 3)
		{
			do{
				cout<<"TIE! \n\n";
				cout<<"   ##    \t   ##	   \n";
				cout<<"   ##    \t   ##      \n";
				cout<<"   ##    \t   ##      \n";
				
				pos += 4;
				
				win = turnwin(deck1, deck2, bot1, bot2, pos);
				
				if(win == 1)
				{
					for(a = tienum; a > 0; a--)
					{
						p1win(deck1, deck2, bot1);
						bot1++;
						p1win(deck1, deck2, bot1);
						bot1++;
						p1win(deck1, deck2, bot1);
						bot1++;
						p1win(deck1, deck2, bot1);
						bot1++;
						p1win(deck1, deck2, bot1);
						bot1++;
					}
					tie = 1;
					cout<<"PLAYER 1 WINS THIS ROUND! \n";
					break;
				}
		
				if(win == 2)
				{
					for(a = tienum; a > 0; a--)
					{
						p2win(deck1, deck2, bot2);
						bot2++;
						p2win(deck1, deck2, bot2);
						bot2++;
						p2win(deck1, deck2, bot2);
						bot2++;
						p2win(deck1, deck2, bot2);
						bot2++;
						p2win(deck1, deck2, bot2);
						bot2++;
					}
					tie = 1;
					cout<<"PLAYER 2 WINS THIS ROUND! \n";
					break;
				}
				tienum++;
			}while(tie == 0);
		}
}

int turnwin(int deck1[52], int deck2[52], int bot1, int bot2, int pos)
{
		int val1, val2;					//value of each card for the turn
		int suit1, suit2;				//suit for the given cards
		
		val1 = deck1[pos] % 13 + 1;
		val2 = deck2[pos] % 13 + 1;
		suit1 = deck1[pos] / 13;
		suit2 = deck2[pos] / 13;

		cout<<setw(4);
		
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
		
		cout<<setw(15);
		
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
		
		//The below part returns different numbers for different outcomes of the cards:
		if(val1 > val2)	//Player 1 Wins = return a #1
			return 1;
		if(val1 < val2)	//Player 2 Wins = return a #2
			return 2;
		if(val1 == val2)//The Players tie = return a #3
			return 3;
}

void p1win(int deck1[52], int deck2[52], int bot1)
{
	int a = 0;
	
	//What must happen:
	//	1. Move deck1[0] to the back of the queue.
	//	2. Pop deck2[0] to the back of deck1.
	//	3. Move all queues forward 1.
			
	deck1[bot1] = deck1[0];			// 1. (see 1.)
	deck1[bot1 + 1] = deck2[0];		//Part of 2., its popped in the below 'move forward' steps (3.)

	for(a = 0; a <= 51; a++)		//move Player 1's deck forward 1.	(3.1)
	{
		if(a > 0)
			deck1[a-1] = deck1[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
	}
	
	deck1[51] = -1;					//make sure the last number is -1 since everything got moved forward 1.
			
	for(a = 0; a <= 51; a++) 		//move Player 2's deck forward 1.	(3.2)
	{
		if(a > 0)
			deck2[a-1] = deck2[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			
		if(deck2[a] == -1)			//this makes sure to pop the value of the losing card from the deck.
			deck2[a-1] = -1;
	}		
}

void p2win(int deck1[52], int deck2[52], int bot2)
{
	int a = 0;
	
	//What must happen:
	//	1. Move deck2[0] to the back of the queue.
	//	2. Pop deck1[0] to the back of deck1.
	//	3. Move all queues forward 1.
			
	deck2[bot2] = deck2[0];			// 1. (see 1.)
	deck2[bot2 + 1] = deck1[0];		//Part of 2., its popped in the below 'move forward' steps (3.)
			
	for(a = 0; a <= 51; a++)		//move Player 1's deck forward 1.	(3.1)
	{
		if(a > 0)
			deck2[a-1] = deck2[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
	}
	
	deck2[51] = -1;					//make sure the last number is -1 since everything got moved forward 1.
			
	for(a = 0; a <= 51; a++)		//move Player 2's deck forward 1.	(3.2)
	{
		if(a > 0)
			deck1[a-1] = deck1[a];	//nums[0] = nums[1], nums[1] = nums[2], nums[2] = nums[3], etc.
			
		if(deck1[a] == -1)			//this makes sure to pop the value of the losing card from the deck.
			deck1[a-1] = -1;
	}
}

/*	
	HELPFUL LINKS:
	http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
	http://cboard.cprogramming.com/c-programming/147721-shuffle-deal-cards-c.html
	http://www.pagat.com/war/war.html
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088(v=vs.85).aspx#_win32_character_attributes
*/
