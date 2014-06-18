#include <iostream.h>
#include <conio.h>
#include "H:\TicTacToe\print.h"
//5-3-2012

printscreen::printscreen()
{
	a = 0;
	b = 0;
	move = 0;
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
	cout<<"\t\t ||       4-17 to 5-3		 || \n";
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

void printscreen::map()
{
	cout<<"\t =================  \n";
	cout<<"\t || ";
	cout<<grid[0][0];
	cout<<" || ";
	cout<<grid[0][1];
	cout<<" || ";
	cout<<grid[0][2];
	cout<<" || \n";

	cout<<"\t ||===||===||===|| \n";
	cout<<"\t || ";
	cout<<grid[1][0];
	cout<<" || ";
	cout<<grid[1][1];
	cout<<" || ";
	cout<<grid[1][2];
	cout<<" || \n";

	cout<<"\t ||===||===||===|| \n";
	cout<<"\t || ";
	cout<<grid[2][0];
	cout<<" || ";
	cout<<grid[2][1];
	cout<<" || ";
	cout<<grid[2][2];
	cout<<" || \n";
	cout<<"\t =================  \n";
}

void printscreen::makemove()
{
	 do{
	 cout<<"Using the NUM pad, enter the number where you wish \n";
	 cout<<"to place your pieces. Ex: Top Right = 7, Top Left = 9 \n";
	 cout<<"Enter the number of your move -> ";
	 cin>>move;
	 }while(move != 1 && move != 2 && move != 3 && move != 4 && move != 5 && move != 6 && move != 7 && move != 8 && move != 9);

	 if(move >= 1 && move <= 3)   //minus 1
	 {
		if(grid[0][move-1] != 'X')
			grid[0][move - 1] = 'X';
		//else
			//stop++;
	 }

	 if(move >= 4 && move <= 6)   //minus 4
	 {
		if(grid[1][move-4] != 'X')
			grid[1][move-4] = 'X';
		//else
			//stop++;
	 }

	 if(move >= 7 && move <= 9)   //minus 7
	 {
		if(grid[2][move-7] != 'X')
			grid[2][move-7] = 'X';
		//else
			//stop++;
	 }
}
