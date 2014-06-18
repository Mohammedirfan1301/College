#include <iostream.h>
#include "h:\Programming\Battleship\battle.h"
//5-22-2012

battleship::battleship()
{

}

void battleship::intro()
{
	cout<<"\t\t\t ********************** \n";
	cout<<"\t\t\t *                    * \n";
	cout<<"\t\t\t *  BATTLESHIP V1.01  * \n";
	cout<<"\t\t\t *                    * \n";
	cout<<"\t\t\t ********************** \n\n\n";

	cout<<"\t\t    This is the game of BATTLE SHIP. \n\n\n";
}

void battleship::reset()
{
	memset(playnavy, '\0', 64);
	memset(compnavy, '\0', 64);
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
	c = 1;

	for(a = 0; a < 8; a++)
	{
		cout<<c<<" ";

		for(b = 0; b < 8; b++)
		{
			cout<<playnavy[a][b];
			cout<<" ";
		}
		cout<<endl;
		c++;
	}
	cout<<"  A B C D E F G H \n";

	cout<<"\n Please place your NAVY. To do so, enter \n";
	cout<<"the number and letter of the spot where \n";
	cout<<"you want to place your ship.            \n\n";

	cout<<"Enter the # of your selection: ";
	cin>>col;
	cout<<"Enter the Letter of your selection: ";
	cin>>row;

   

	for(a = 0; a < 8; a++)
	{
      if(a == col)
				if(row == 'a')
					playnavy[a][b] = 'S';

		for(b = 0; b < 8; b++)
		{

		}

	}

}

void battleship::print()
{
	c = 1;

	for(a = 0; a < 8; a++)
	{
		cout<<c<<" ";

		for(b = 0; b < 8; b++)
		{
			cout<<playnavy[a][b];
			cout<<" ";
		}
		cout<<endl;
		c++;
	}
	cout<<"  A B C D E F G H \n";


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
