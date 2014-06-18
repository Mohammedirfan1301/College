#include <iostream.h>
#include <conio.h>
#include "H:\Programming\L15\TicTacToe\print.h"
//5-18-2012

printscreen::printscreen()
{
	a = 0;
	b = 0;
	move = 0;
	stop = 0;
}

void printscreen::cleargrid()
{
	memset(grid, '\0', 9);
}

void printscreen::clearscreen()
{
	clrscr();
}

void printscreen::intro()
{
	cout<<"\t\t       =========================== \n";
	cout<<"\t\t       ||    TicTacToe V1.5     || \n";
	cout<<"\t\t       ||   Created by JASON    || \n";
	cout<<"\t\t       ||       4-17 to 5-18    || \n";
	cout<<"\t\t       =========================== \n\n";
}

/*
int printscreen::menu()
{
	cout<<"This game of TICTACTOE can be played in two ways: \n";
	cout<<"1. One Player (Human VS Computer)  \n";
	cout<<"2. Two Player (Human VS Human)     \n\n";
	cout<<"Which game type do you wish to play? \n";

	do{
	cout<<"Enter the number of your selection here. -> ";
	cin>>gametype;
	}while(gametype != 1 && gametype != 2);

	if(gametype == 1)
		cpu = 1;
	if(gametype == 2)
		cpu = 2;

	return cpu;
}
*/

//prints out the map
void printscreen::map()
{
	cout<<"\t  Using the NUM pad, enter the number where you wish \n";
	cout<<"\t  to place your pieces. Ex: Top Right = 7, Top Left = 9 \n\n";

	cout<<"\t\t\t      =============  \n";
	cout<<"\t\t\t      | ";
	cout<<grid[0][0];  //7
	cout<<" | ";
	cout<<grid[0][1];  //8
	cout<<" | ";
	cout<<grid[0][2];  //9
	cout<<" | \n";

	cout<<"\t\t\t      |===|===|===| \n";
	cout<<"\t\t\t      | ";
	cout<<grid[1][0];  //4
	cout<<" | ";
	cout<<grid[1][1];  //5
	cout<<" | ";
	cout<<grid[1][2];  //6
	cout<<" | \n";

	cout<<"\t\t\t      |===|===|===| \n";
	cout<<"\t\t\t      | ";
	cout<<grid[2][0];  //1
	cout<<" | ";
	cout<<grid[2][1];  //2
	cout<<" | ";
	cout<<grid[2][2];  //3
	cout<<" | \n";
	cout<<"\t\t\t      =============  \n";
}

//function for Player 1 (to make a move)
void printscreen::makemoveX()
{
    a = 0;
	 do{
	 do{
	 cout<<"Player 1's (X) turn. \n";
	 cout<<"Enter the number of your move -> ";
	 cin>>move;
	 cout<<endl;
	 }while(move != 1 && move != 2 && move != 3 && move != 4 && move != 5 && move != 6 && move != 7 && move != 8 && move != 9);

    if(move >= 1 && move <= 3)   //minus 1
	 {
		if(grid[2][move-1] != 'O' && grid[2][move-1] != 'X')
		{
			grid[2][move-1] = 'X';
			a = 1;
		}
	 }

	 if(move >= 4 && move <= 6)   //minus 4
	 {
		if(grid[1][move-4] != 'O' && grid[1][move-4] != 'X')
		{
			grid[1][move-4] = 'X';
			a = 1;
		}
	 }

	 if(move >= 7 && move <= 9)   //minus 7
	 {
		if(grid[0][move-7] != 'O' && grid[0][move-7] != 'X')
		{
			grid[0][move-7] = 'X';
			a = 1;
		}
	 }

	 }while(a == 0);

}

//function for Player 2 (to make a move)
void printscreen::makemoveO()
{
	 a = 0;
	 do{
	 do{
	 cout<<"Player 2's (O) turn. \n";
	 cout<<"Enter the number of your move -> ";
	 cin>>move;
	 cout<<endl;
	 }while(move != 1 && move != 2 && move != 3 && move != 4 && move != 5 && move != 6 && move != 7 && move != 8 && move != 9);

	 if(move >= 1 && move <= 3)   //minus 1
	 {
		if(grid[2][move-1] != 'O' && grid[2][move-1] != 'X')
		{
			grid[2][move-1] = 'O';
			a = 1;
		}
	 }

	 if(move >= 4 && move <= 6)   //minus 4
	 {
		if(grid[1][move-4] != 'O' && grid[1][move-4] != 'X')
		{
			grid[1][move-4] = 'O';
			a = 1;
		}
	 }

	 if(move >= 7 && move <= 9)   //minus 7
	 {
		if(grid[0][move-7] != 'O' && grid[0][move-7] != 'X')
		{
			grid[0][move-7] = 'O';
			a = 1;
		}
	 }

	 }while(a == 0);
}

//checks to see if theres three-in-a-row.
//also checks to see if all spots have been filled (tie game)
int printscreen::test3()
{
	stop = 0;

	//detects X across
	for(a = 0; a < 3; a++)
	{
		if(grid[a][0] == 'X' && grid[a][0] == grid[a][1])
		{
			if(grid[a][1] == 'X' && grid[a][1] == grid[a][2])
			{
				stop = 1;
			}
		}
	}

	//detects X down
	for(a = 0; a < 3; a++)
	{
		if(grid[0][a] == 'X' && grid[0][a] == grid[1][a])
		{
			if(grid[1][a] == 'X' && grid[1][a] == grid[2][a])
			{
				stop = 1;
			}
		}
	}

	//detects X diangle
	//753
	if(grid[0][0] == 'X' && grid[0][0] == grid[1][1])
	{
		if(grid[1][1] == 'X' && grid[1][1] == grid[2][2])
		{
			stop = 1;
		}
	}

	//159
	if(grid[0][2] == 'X' && grid[0][2] == grid[1][1])
	{
		if(grid[1][1] == 'X' && grid[1][1] == grid[2][0])
		{
			stop = 1;
		}
	}


	//detects O across
	for(a = 0; a < 3; a++)
	{
		if(grid[a][0] == 'O' && grid[a][0] == grid[a][1])
		{
			if(grid[a][1] == 'O' && grid[a][1] == grid[a][2])
			{
				stop = 2;
			}
		}
	}

	//detects O down
	for(a = 0; a < 3; a++)
	{
		if(grid[0][a] == 'O' && grid[0][a] == grid[1][a])
		{
			if(grid[1][a] == 'O' && grid[1][a] == grid[2][a])
			{
				stop = 2;
			}
		}
	}

	//detects O diangle
	//753
	if(grid[0][0] == 'O' && grid[0][0] == grid[1][1])
	{
		if(grid[1][1] == 'O' && grid[1][1] == grid[2][2])
		{
			stop = 2;
		}
	}

   //159
	if(grid[0][2] == 'O' && grid[0][2] == grid[1][1])
	{
		if(grid[1][1] == 'O' && grid[1][1] == grid[2][0])
		{
			stop = 2;
		}
	}

	return stop;
}

//prints out a winning messsage and a losing message.
void printscreen::endofgame()
{
	cout<<"PLAYER "<<" WON!  \n";
	cout<<"PLAYER "<<" LOST! \n";
	cout<<"Play again?";
}
