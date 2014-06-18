#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "h:\Programming\Battleship\battle.h"
//#include "c:\Battle\battle.h"
//5-31-2012

battleship::battleship()
{

}

void battleship::intro()   //introduction prompt - states program name, what it is and version #
{
	cout<<"\t\t\t      ********************** \n";
	cout<<"\t\t\t      *                    * \n";
	cout<<"\t\t\t      *  BATTLESHIP V1.5   * \n";
	cout<<"\t\t\t      *                    * \n";
	cout<<"\t\t\t      ********************** \n\n";

	cout<<"\t\t\t  This is a game of BATTLE SHIP. \n\n";
}

void battleship::reset()     //resets or clears the two character arrays
{
	memset(playnavy, '\0', 64);
	memset(compnavy, '\0', 64);
}

void battleship::clear() 	//clears the screen
{
	clrscr();
}

void battleship::fill()  //prefills the arrays with dots
{
	for(a = 0; a < 8; a++)
	{
		for(b = 0; b < 8; b++)
		{
			playnavy[a][b]	= '.';
			compnavy[a][b] = '.';
		}
	}

}

//PLAYER 1 selects where to place their ships on the map
void battleship::select()
{
	int num = 1;
	int ships = 0;
	cout<<"\nPLAYER 1: Please place your NAVY. To do so, enter the number and letter \n";
	cout<<"of the spot where you want to place your ship.            \n\n";

	do{

	do{
	cout<<num<<". Enter the number of your selection: ";
	cin>>col;
	}while(col != 1 && col != 2 && col != 3 && col != 4 && col != 5 && col != 6 && col != 7 && col != 8);
	col--;

	do{
	cout<<num<<". Enter the letter of your selection (NO CAPS): "; 
	cin>>rows;
	}while(rows != 'a' && rows != 'b' && rows != 'c' && rows != 'd' && rows != 'e' && rows != 'f' && rows != 'g' && rows != 'h');

	for(a = 0; a < 8; a++)
	{
		if(col == a)
		{
				if(rows == 'a')
					playnavy[a][0] = 'S';
				if(rows == 'b')
					playnavy[a][1] = 'S';
				if(rows == 'c')
					playnavy[a][2] = 'S';
				if(rows == 'd')
					playnavy[a][3] = 'S';
				if(rows == 'e')
					playnavy[a][4] = 'S';
				if(rows == 'f')
					playnavy[a][5] = 'S';
				if(rows == 'g')
					playnavy[a][6] = 'S';
				if(rows == 'h')
					playnavy[a][7] = 'S';
		}
	}

   num++;
	ships++;
	}while(ships != 5);

}

//COMPUTER automatically places its ships randomly.
void battleship::cselect()
{
	srand(time(0));
	int ships = 0;

	do{
	row = rand()%8;
	col = rand()%8;

	if(compnavy[row][col] == 'S')
	{
		ships--;
	}
	else if(compnavy[row][col] != 'S')
	{
		compnavy[row][col] = 'S';
	}

	ships++;

	}while(ships != 5);
}

//Function to print the two maps to the screen. note it doesn't show WHERE the computer's ships are, as this for
//PLAYER 1 ONLY. It shows where their own ships are, whether they have been hit or not, along with any misses.
//it only shows where they have hit or missed the computer's ships. the ships aren't printed as it is up to the
//player to guess where the ships are.
void battleship::print()
{
	int pship = 0, cship = 0;
	c = 1;

	cout<<"\t\t     YOUR NAVY: \t\t    YOUR BOMBS: \n";

	for(a = 0; a < 8; a++)
	{
		cout<<"\t\t"<<c<<" ";

		for(b = 0; b < 8; b++)
		{
			cout<<playnavy[a][b];
			cout<<" ";
			if(playnavy[a][b] == 'S')
				pship++; //for the count below
		}

		cout<<"\t\t"<<c<<" ";

		for(d = 0; d < 8; d++)
		{
				if(compnavy[a][d] != 'S')
				{
					cout<<compnavy[a][d];
					cout<<" ";
				}

				if(compnavy[a][d] == 'S') //masks the computer's ships from showing up on player 1's bomb screen
				{
					cout<<". ";
					cship++;
				}
		}

		cout<<endl;
		c++;
	}
	cout<<"\t\t  A B C D E F G H  		  A B C D E F G H \n";
	cout<<"\t\t   SHIPS LEFT: "<<pship<<"                   SHIPS LEFT: "<<cship<<"\n";


	/*
	cout<<"\t\t       YOUR BOMBS           YOUR NAVY    \n";
	cout<<"\t\t   1 . . . . . . . .   1 . . . . . . . . \n";
	cout<<"\t\t   2 . . . . . . . .   2 . . . . . . . . \n";
	cout<<"\t\t   3 . . . . . . . .   3 . . . . . . . . \n";
	cout<<"\t\t   4 . . . . . . . .   4 . . . . . . . . \n";
	cout<<"\t\t   5 . . . . . . . .   5 . . . . . . . . \n";
	cout<<"\t\t   6 . . . . . . . .   6 . . . . . . . . \n";
	cout<<"\t\t   7 . . . . . . . .   7 . . . . . . . . \n";
	cout<<"\t\t   8 . . . . . . . .   8 . . . . . . . . \n";
	cout<<"\t\t     A B C D E F G H     A B C D E F G H \n";
	*/
}

void battleship::playhit()
{
	int hit = 0;

	do{
	cout<<"\nPLAYER - Please choose where to hit your ENEMYs ships. \n";
	cout<<"Note: Look at the screen YOUR BOMBS to make your decision. Good luck. \n\n";

	do{
	cout<<"Enter the number of your selection: ";
	cin>>col;
	}while(col != 1 && col != 2 && col != 3 && col != 4 && col != 5 && col != 6 && col != 7 && col != 8);
	col--;

	do{
	cout<<"Enter the letter of your selection (NO CAPS): ";
	cin>>rows;
	}while(rows != 'a' && rows != 'b' && rows != 'c' && rows != 'd' && rows != 'e' && rows != 'f' && rows != 'g' && rows != 'h');

	for(a = 0; a < 8; a++)
	{
		if(col == a)            // a/0 b/1 c/2 d/3 e/4 f/5 g/6 h/7
		{
				if(rows == 'a')
				{
					if(compnavy[a][0] == '.')
					{
						compnavy[a][0] = 'M';
						hit = 1;
					}

					if(compnavy[a][0] == 'S')
					{
						compnavy[a][0] = 'H';
						hit = 1;
					}

					if(compnavy[a][0] == 'H')
						break;

					if(compnavy[a][0] == 'M')
						break;
				}

				if(rows == 'b')
				{
					if(compnavy[a][1] == '.')
					{
						compnavy[a][1] = 'M';
						hit = 1;
					}

					if(compnavy[a][1] == 'S')
					{
						compnavy[a][1] = 'H';
						hit = 1;
					}

					if(compnavy[a][1] == 'H')
						break;

					if(compnavy[a][1] == 'M')
						break;
				}

				if(rows == 'c')
				{
					if(compnavy[a][2] == '.')
					{
						compnavy[a][2] = 'M';
						hit = 1;
					}

					if(compnavy[a][2] == 'S')
					{
						compnavy[a][2] = 'H';
						hit = 1;
					}

					if(compnavy[a][2] == 'H')
						break;

					if(compnavy[a][2] == 'M')
						break;
				}

				if(rows == 'd')
				{
					if(compnavy[a][3] == '.')
					{
						compnavy[a][3] = 'M';
						hit = 1;
					}

					if(compnavy[a][3] == 'S')
					{
						compnavy[a][3] = 'H';
						hit = 1;
					}

					if(compnavy[a][3] == 'H')
						break;

					if(compnavy[a][3] == 'M')
						break;
				}

				if(rows == 'e')
								{
					if(compnavy[a][4] == '.')
					{
						compnavy[a][4] = 'M';
						hit = 1;
					}

					if(compnavy[a][4] == 'S')
					{
						compnavy[a][4] = 'H';
						hit = 1;
					}

					if(compnavy[a][4] == 'H')
						break;

					if(compnavy[a][4] == 'M')
						break;
				}

				if(rows == 'f')
				{
					if(compnavy[a][5] == '.')
					{
						compnavy[a][5] = 'M';
						hit = 1;
					}

					if(compnavy[a][5] == 'S')
					{
						compnavy[a][5] = 'H';
						hit = 1;
					}

					if(compnavy[a][5] == 'H')
						break;

					if(compnavy[a][5] == 'M')
						break;
				}

				if(rows == 'g')
				{
					if(compnavy[a][6] == '.')
					{
						compnavy[a][6] = 'M';
						hit = 1;
					}

					if(compnavy[a][6] == 'S')
					{
						compnavy[a][6] = 'H';
						hit = 1;
					}

					if(compnavy[a][6] == 'H')
						break;

					if(compnavy[a][6] == 'M')
						break;
				}

				if(rows == 'h')
				{
					if(compnavy[a][7] == '.')
					{
						compnavy[a][7] = 'M';
						hit = 1;
					}

					if(compnavy[a][7] == 'S')
					{
						compnavy[a][7] = 'H';
						hit = 1;
					}

					if(compnavy[a][7] == 'H')
						break;

					if(compnavy[a][7] == 'M')
						break;
				}

		}
	}

	}while(hit == 0);
}

void battleship::comphit()
{
	srand(time(0));
	int hit = 0;

	do{
	row = rand()%8;
	col = rand()%8;

	if(playnavy[row][col] == '.')
	{
		playnavy[row][col] = 'M';
		hit = 1;
	}

	if(playnavy[row][col] == 'S')
	{
		playnavy[row][col] = 'H';
		hit = 1;
	}

	}while(hit == 0);
}

int battleship::whowin()
{
	int playship = 0, compship = 0;
	winner = 0;

	for(a = 0; a < 8; a++)
	{
		for(b = 0; b < 8; b++)
		{
			if(playnavy[a][b] == 'S')
				playship++;
			if(compnavy[a][b] == 'S')
				compship++;
		}
	}

	if(playship == 0)
		winner = 1;
	if(compship == 0)
		winner = 2;

	return winner;
}
