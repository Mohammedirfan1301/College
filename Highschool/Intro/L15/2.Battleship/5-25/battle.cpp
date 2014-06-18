#include <iostream.h>
#include <conio.h>
#include "h:\Programming\Battleship\battle.h"
//5-22-2012

battleship::battleship()
{

}

void battleship::intro()
{
	cout<<"\t\t\t\t ********************** \n";
	cout<<"\t\t\t\t *                    * \n";
	cout<<"\t\t\t\t *  BATTLESHIP V1.02  * \n";
	cout<<"\t\t\t\t *                    * \n";
	cout<<"\t\t\t\t ********************** \n\n";

	cout<<"\t\t\t    This is a game of BATTLE SHIP. \n\n";
}

void battleship::reset()
{
	memset(playnavy, '\0', 64);
	memset(compnavy, '\0', 64);
}

void battleship::clear()
{
	clrscr();
}

void battleship::fill()
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

void battleship::select()
{
	cout<<"\nPlease place your NAVY. To do so, enter the number and letter of the \n";
	cout<<"spot where you want to place your ship.            \n\n";

	cout<<"Enter the number of your selection: ";   //add a do/while so #s
	cin>>col;                                       //must be 1 through 8
	col--;
	cout<<"Enter the Letter of your selection (NO CAPS): ";  //also a add do/while
	cin>>row;

   

	for(a = 0; a < 8; a++)
	{
		if(col == a)
		{
				if(row == 'a')
					playnavy[a][0] = 'S';
				if(row == 'b')
					playnavy[a][1] = 'S';
				if(row == 'c')
					playnavy[a][2] = 'S';
				if(row == 'd')
					playnavy[a][3] = 'S';
				if(row == 'e')
					playnavy[a][4] = 'S';
				if(row == 'f')
					playnavy[a][5] = 'S';
				if(row == 'g')
					playnavy[a][6] = 'S';
				if(row == 'h')
					playnavy[a][7] = 'S';
		}
	}

}

void battleship::print()
{
	c = 1;

	cout<<"\t\t     YOUR NAVY: \t\t    YOUR BOMBS: \n";

	for(a = 0; a < 8; a++)
	{
		cout<<"\t\t"<<c<<" ";

		for(b = 0; b < 8; b++)
		{
			cout<<playnavy[a][b];
			cout<<" ";
		}

		cout<<"\t\t"<<c<<" ";

		for(d = 0; d < 8; d++)
		{
			cout<<compnavy[a][d];
			cout<<" ";
		}

		cout<<endl;
		c++;
	}
	cout<<"\t\t  A B C D E F G H  		  A B C D E F G H \n";


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
