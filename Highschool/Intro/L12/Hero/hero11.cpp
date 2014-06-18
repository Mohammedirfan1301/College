#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

main()
{
	char map[20][20];             //2d character array for the map
	int row = 0, col = 0;         //row/col variables - used both in the main/function
	int rowmove = 0, colmove = 0; //variables for moving the 'X'.
	int a = 0, b = 0;       //a controls when "*" appears in the map. b is used in a switch for random moves.
	int c = 0, d = 0;			//c/d for the moving of X (whether it should count up or down)
	int x = 1, y = 1;			//x controls the main do/while. y controls the enter to continue
	int hero = 0, stop = 1; //hero is for hero win/lose, stop is to stop the program when hero dies/lives
	int moves = 0, allmoves = 0, allwins = 0, allloses = 0; //various counters used to display the average moves/wins/loses
	srand(time(0));         //random number using time, used for switch(d) which does the random moves

	do{
   map[10][10] = 'X';
	stop = 1;

	cout<<"HERO: ESCAPE OR DEATH \n";
	cout<<"This program lets you watch the Hero escape... or die. \n";

	cout<<"\nKEY: \n";
	cout<<"======= is the safe zone \n";
	cout<<">>> <<< is the moat   \n";
	cout<<"******* is the island \n";
	cout<<"X is the Hero. \n\n";

	do{
	//fills the map
	cout<<"HERO \n\n";

	for(row = 0; row < 20; row++)  //rows
	{
		for(col = 0; col < 20; col++) //columns
		{
			if(row == 0 || row == 19) //controls the safe zone. (Escape Bridges)
			{
				map[row][col] = '=';
				a = 1;
			}

			if(col == 0 && row != 0 && row != 19) //controls the left side of the dead zone. (Moat)
			{
				map[row][col] = '>';
				a = 1;
			}

			if(col == 19 && row != 0 && row != 19) //controls the right side of the dead zone. (Moat)
			{
				map[row][col] = '<';
				a = 1;
			}

			if(a != 1) //fills the rest of the map with '*'s. (Island)
			{
				if(map[row][col] != 'X')
				{
					map[row][col] = '*';
				}
			}

			a = 0;
		}
	}

	b = rand()%9;  //randomly makes a number between 1 and 8.

	rowmove = 0;
	colmove = 0;
	c = 0;
	d = 0;

	switch(b)  //uses b to choose a random option.
	{
		case 1: //moves X up by one.
			rowmove = -1;
			colmove = 0;
			c = 1;
			break;

		case 2: //moves X down by one.
			rowmove = 1;
			colmove = 0;
			d = 1;
			break;

		case 3: //moves X left by one.
			rowmove = 0;
			colmove = -1;
			c = 1;
			break;

		case 4: //moves X right by one.
			rowmove = 0;
			colmove = 1;
			d = 1;
			break;

		case 5: //moves X up left by one.
			rowmove = -1;
			colmove = -1;
			c = 1;
			break;

		case 6: //moves X up right by one.
			rowmove = -1;
			colmove = 1;
			c = 1;
			break;

		case 7: //moves X down left by one.
			rowmove = 1;
			colmove = -1;
			d = 1;
			break;

		case 8: //moves X down right by one.
			rowmove = 1;
			colmove = 1;
         d = 1;
         break;
	}

	//moves the Hero ("X") (used for case 1,3,5,6)
	if(c == 1)
	{
		for(row = 0; row < 20; row++)
		{
			for(col = 0; col < 20; col++)
			{
				if(map[row][col] == 'X')
				{
					rowmove = row + rowmove;
					colmove = col + colmove;

					map[rowmove][colmove] = 'X';
					map[row][col] = '*';
				}
			}
		}
	}

	//moves the Hero ("X") (used for case 2,4,7,8)
	if(d == 1)
	{
		for(row = 19; row >= 0; row--)
		{
			for(col = 19; col >= 0; col--)
			{
				if(map[row][col] == 'X')
				{
					rowmove = row + rowmove;
					colmove = col + colmove;

					map[rowmove][colmove] = 'X';
					map[row][col] = '*';
				}
			}
		}
	}

	//prints out the final map
	for(row = 0; row < 20; row++)
	{
		for(col = 0; col < 20; col++)
		{
			cout<<map[row][col];

			if(row == 0 || row == 19)
			{
				if(map[row][col] == 'X')
				{
					hero = 1;
					stop = 0;
				}
			}

			if( (col == 0 || col == 19) && row != 0 && row != 19)
			{
				if(map[row][col] == 'X')
				{
					hero = 0;
					stop = 0;
				}
			}
		}
		cout<<endl;
	}

	moves++;

	do{
	cout<<"\nPress enter to continue the Hero's moves. ";
	y = getch();
	}while(y != 13);

	clrscr();

	}while(stop == 1);

	clrscr();

	cout<<"The HERO: ";

	if(hero == 1)
	{
		cout<<"LIVED! Huray! \n";
		allwins++;
	}
	if(hero == 0)
	{
		cout<<"DIED! Oh no! \n";
		allloses++;
	}

	cout<<"The Hero moved "<<moves<<" times. ";
	allmoves += moves;

	do{
	cout<<"Do you want to play again or quit? \n";
   cout<<"Enter 1 to play again or 2 to quit the game. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

	clrscr();

	}while(x == 1);

	cout<<"Thanks for using the HERO program. \n";
	cout<<"The stats for all games of HERO: ";
	cout<<"The Hero moved "<<allmoves<<"

	return 0;
}

//===================================================================================================================================================================
/*
MISC. NOTES

KEY:
=== is the safe zone
>/< are the crocodiles
*** is the water
X   is the hero

======================
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>*********X**********<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
======================


*/