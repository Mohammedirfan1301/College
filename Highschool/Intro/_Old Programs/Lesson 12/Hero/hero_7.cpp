#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

char movefunc(int, int, char[20][20]); //function for the switch, that moves the hero randomly.
char map[20][20];                      //2d character array for the map
int row = 0, col = 0;                  //global row/col variables - used both in the main/function
int rowmove = 0, colmove = 0;          //variables for moving the 'X'.

main()
{
	int a = 0, b = 0;        // row/col is for the map width/height. c controls when "*" appears in the map. d is used in a switch for random moves.
	int x = 1, y = 1;			 //x controls the main do/while. y controls the enter to continue
	int hero = 0, stop = 1;  //hero is for hero win/lose, stop is to stop the program when hero dies/lives
	srand(time(0));          //random number using time, used for switch(d) which does the random moves

	do{
	map[10][10] = 'X';
	stop = 1;

	do{
	cout<<"HERO: ESCAPE OR DEATH \n";
	cout<<"This program lets you watch the Hero escape... or die. \n";
	cout<<"=== is the safe zone, >> << is the moat, *** is the island and X is the Hero. \n";

	//fills the map
	for(row = 0; row < 20; row++)  //generates the numbers for map[a]
	{
		for(col = 0; col < 20; col++)  //numbers for map[b]
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

			if(a != 1 && map[row][col] != 'X') //fills the rest of the map with '*'s. (Island)
			{
				map[a][b] = '*';
			}

			a = 0;
		}
	}

//	b = rand()%8 + 1;  //randomly makes a number between 1 and 8.
	b = 1;

	switch(b)  //this moves X by one.
	{
		/*
		case 1: //moves X up by one.
			for(row=0;row<20;row++)
			{
				for(b=0;b<20;b++)
				{
					if(map[row][b] == 'X')
					{
						map[row-1][b] = 'X';
						map[row][b] = '*';
					}
				}
			}
			break;
		*/

		case 1: //moves X up by one.
			rowmove = -1;
			colmove = 0;
			map[20][20] = movefunc(rowmove, colmove, map[20][20]);
			break;
      	
		/*
		case 2: //moves X down by one.
			for(row=19;row>=0;a--)
			{
				for(b=19;b>=0;b--)
				{
					if(map[row][b] == 'X')
					{
						map[row+1][b] = 'X';
						map[row][b] = '*';
					}
				}
			}
			break;

		case 3: //moves X left by one.
			for(row=0;a<20;a++)
			{
				for(b=0;b<20;b++)
				{
					if(map[a][b] == 'X')
					{
						map[a][b-1] = 'X';
						map[a][b] = '*';
					}
				}
			}
			break;

		case 4: //moves X right by one.
			for(a=19;a>=0;a--)
			{
				for(b=19;b>=0;b--)
				{
					if(map[a][b] == 'X')
					{
						map[a][b+1] = 'X';
						map[a][b] = '*';
					}
				}
			}
			break;

		case 5: //moves X up left by one.
			for(a=0;a<20;a++)
			{
				for(b=0;b<20;b++)
				{
					if(map[a][b] == 'X')
					{
						map[a-1][b-1] = 'X';
						map[a][b] = '*';
					}
				}
			}
			break;

		case 6: //moves X up right by one.
			for(a=0;a<20;a++)
			{
				for(b=0;b<20;b++)
				{
					if(map[a][b] == 'X')
					{
						map[a-1][b+1] = 'X';
						map[a][b] = '*';
					}
				}
			}
			break;

		case 7: //moves X down left by one.
			for(a=19;a>=0;a--)
			{
				for(b=19;b>=0;b--)
				{
					if(map[a][b] == 'X')
					{
						map[a+1][b-1] = 'X';
						map[a][b] = '*';
					}
				}
			}
			break;

		case 8: //moves X down right by one.
			for(a=19;a>=0;a--)
			{
				for(b=19;b>=0;b--)
				{
					if(map[a][b] == 'X')
					{
						map[a+1][b+1] = 'X';
						map[a][b] = '*';
					}
				}
			}
		*/
	}

	//prints out the final map
	for(a = 0; a < 20; a++)
	{
		for(b = 0; b < 20; b++)
		{
			cout<<map[a][b];

			if(a==0 || a == 19)
			{
				if(map[a][b] == 'X')
				{
					hero = 1;
					stop = 0;
				}
			}

			if( (b==0 || b == 19) && a!= 0 && a!=19)
			{
				if(map[a][b] == 'X')
				{
					hero = 0;
					stop = 0;
				}
			}
		}
		cout<<endl;
	}

	do{
	cout<<"\nPress enter to continue the Hero's moves. ";
	y = getch();
	}while(y != 13);

	clrscr();

	}while(stop == 1);

	clrscr();

	cout<<"The HERO: ";

	if(hero == 1)
		cout<<"LIVED! \n";
	if(hero == 0)
		cout<<"DIED!! \n";

	do{
	cout<<"Do you want to play again or quit? \n";
   cout<<"Enter 1 to play again or 2 to quit the game. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

	clrscr();

	}while(x == 1);

	cout<<"Thanks for using the HERO program. \n";
	cout<<"The stats for all games of HERO: ";

	return 0;
}
//===================================================================================================================================================================
//Functions

char movefunc(int, int, char map[20][20])
{

	for(row = 0; row < 20; row++)
	{
		for(col = 0; col < 20; col++)
		{
			if(map[row][col] == 'X')
			{
				map[row][col] = '*';
				row += rowmove;
				col += colmove;
				map[rowmove][colmove] = 'X';
			}
		}
	}
	return map[20][20];
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