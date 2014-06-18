#include <iostream.h>
#include "H:\TicTacToe\print.h"

printscreen::printscreen()
{
	a = 0;
	b = 0;
}

void printscreen::clear()
{
	memset(grid, '\0', 9);
}

void printscreen::intro()
{
	cout<<"\t\t =========================== \n";
	cout<<"\t\t ||    TicTacToe V1.01    || \n";
	cout<<"\t\t ||  Created by JASON D   || \n";
	cout<<"\t\t ||        4/17/2012      || \n";
	cout<<"\t\t =========================== \n";

	cout<<"\n\n\t\t Use the NUM Pad to play this game. \n";
	cout<<"\t\t 1 is the bottom left corner \n";
	cout<<"\t\t 2 is the bottom middle \n";
	cout<<"\t\t 3 is the bottom right corner \n";
   cout<<"\t\t and such. \n";
}

void printscreen::map()
{
	cout<<"=================  \n";
	cout<<"|| * || * || * || \n";
	cout<<"||===||===||===|| \n";
	cout<<"|| * || * || * || \n";
	cout<<"||===||===||===|| \n";
	cout<<"|| * || * || * || \n";
	cout<<"=================  \n";
}

void printscreen::printmap()
{
	//???
}

void printscreen::stop()
{
	 do{
	 cout<<"Enter the next move -> ";
	 cin>>move;
	 }while(move != 1 && move != 2 && move != 3 && move != 4 && move != 5 && move != 6 && move != 7 && move != 8 && move != 9);
}
