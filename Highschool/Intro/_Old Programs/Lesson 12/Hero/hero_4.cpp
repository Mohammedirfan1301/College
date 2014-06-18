#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

main()
{
	int a = 0, b = 0, c = 0, d = 0, x = 0, y = 0;  /* a/b used for nested for loops. c controls when "*" appears in the map. d.
										e controls when "X" is first put in the map. x controls the main do/while. y controls the enter to continue  */
	int hero = 0, stop = 1;
	char map[20][20];
	srand(time(0));

	do{
	map[10][10] = 'X';
	do{
	cout<<"HERO: ESCAPE OR DEATH \n";
	cout<<"This program lets you watch the Hero escape... or die. \n";
	cout<<"=== is the safe zone, >> << is the moat, *** is the island and X is the Hero. \n";

	//fills the map
	for(a = 0; a < 20; a++)  //generates the numbers for map[a]
	{
		for(b = 0; b < 20; b++)  //numbers for map[b]
		{
			if(a == 0 || a == 19) //controls the safe zone.
			{
				map[a][b] = '=';
				c = 1;
			}

			if(b == 0 && a != 0 && a != 19) //controls the left side of the dead zone.
			{
				map[a][b] = '>';
				c = 1;
			}

			if(b == 19 && a != 0 && a != 19) //controls the right side of the dead zone.
			{
				map[a][b] = '<';
				c = 1;
			}

			if(c != 1 && map[a][b] != 'X') //fills the rest of the map with '*'s.
			{
				map[a][b] = '*';
			}

			c = 0;
		}
	}

	d = rand()%8 + 1;  //randomly makes a number between 1 and 8.

	switch(d)  //this moves X by one.
	{
		case 1: //moves X up by one.
			for(a=0;a<20;a++)
			{
				for(b=0;b<20;b++)
				{
					if(map[a][b] == 'X')
					{
						map[a-1][b] = 'X';
						map[a][b] = '*';
					}
				}
			}
			break;

		case 2: //moves X down by one.
			for(a=19;a>=0;a--)
			{
				for(b=19;b>=0;b--)
				{
					if(map[a][b] == 'X')
					{
						map[a+1][b] = 'X';
						map[a][b] = '*';
					}
				}
			}
			break;

		case 3: //moves X left by one.
			for(a=0;a<20;a++)
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
	}

	for(a = 0; a < 20; a++)
	{
		for(b = 0; b < 20; b++)
		{
			if(b == 0 || b == 19)
			{
				if(map[a][b] == 'X');
				{
					stop = 0;
				}
			}
		}
	}

	//prints out the final map
	for(a = 0; a < 20; a++)
	{
		for(b = 0; b < 20; b++)
		{
			cout<<map[a][b];
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

/*
KEY:
=== is the safe zone
>/< are the crocodiles
*** is the water
H   is the hero

======================
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>********************<
>*********H**********<
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