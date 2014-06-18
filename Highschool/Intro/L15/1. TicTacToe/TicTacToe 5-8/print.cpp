#include <iostream.h>
#include <conio.h>
#include "H:\Programming\L15\TicTacToe\print.h"
//5-7-2012

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
	cout<<"\t\t =========================== \n";
	cout<<"\t\t ||    TicTacToe V1.0     || \n";
	cout<<"\t\t ||   Created by JASON    || \n";
	cout<<"\t\t ||       4-17 to 5-7     || \n";
	cout<<"\t\t =========================== \n";

}

/*
void printscreen::menu()
{
	cout<<"This game of TICTACTOE can be player in two ways: \n";
	cout<<"1. One Player (Computer VS Human)  \n";
	cout<<"2. Two Player (Human VS Human)     \n\n";
	cout<<"Which game type do you wish to play? \n";
	do{
	cout<<"Enter the number of your selection here. -> ";
	cin>>gametype;
	}while(gametype != 1 && gametype != 2);

	if(gametype == 1)
		cpu = 0;
	if(gametype == 2)
		cpu = 1;
}
*/

//prints out the map
void printscreen::map()
{
	cout<<"\n\t\t      =================  \n";
	cout<<"\t\t      || ";
	cout<<grid[0][0];
	cout<<" || ";
	cout<<grid[0][1];
	cout<<" || ";
	cout<<grid[0][2];
	cout<<" || \n";

	cout<<"\t\t      ||===||===||===|| \n";
	cout<<"\t\t      || ";
	cout<<grid[1][0];
	cout<<" || ";
	cout<<grid[1][1];
	cout<<" || ";
	cout<<grid[1][2];
	cout<<" || \n";

	cout<<"\t\t      ||===||===||===|| \n";
	cout<<"\t\t      || ";
	cout<<grid[2][0];
	cout<<" || ";
	cout<<grid[2][1];
	cout<<" || ";
	cout<<grid[2][2];
	cout<<" || \n";
	cout<<"\t\t      =================  \n\n";

	cout<<"\t  Using the NUM pad, enter the number where you wish \n";
	cout<<"\t  to place your pieces. Ex: Top Right = 7, Top Left = 9 \n\n";
}

//function for Player 1 (to make a move)
void printscreen::makemoveX()
{
    a = 0;
	 do{
	 do{
	 cout<<"Player 1 - MAKE YOUR MOVE! \n";
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
	 cout<<"Player 2 - MAKE YOUR MOVE! \n";
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
void printscreen::test3()
{
	stop = 0;
	/*
	needs to detect:
	7-8-9
	4-5-6
	1-2-3 CHECK

	7-4-1
	8-5-2
	9-6-3

	7-5-3
	1-5-9

	*/

	//loop this? count up from 0 - grid[a][0]
	//or grid[0][0], grid[1][0], grid[2][0]...
	if(grid[2][0] == grid[2][1] && grid[2][1] == grid[2][2])
		stop = 1;

	if(stop = 1)



}

//prints out a winning messsage and a losing message.
void printscreen::endofgame()
{

	cout<<"PLAYER "<<" WON!  \n";
	cout<<"PLAYER "<<" LOST! \n";

   cout<<"Play again?";

}
