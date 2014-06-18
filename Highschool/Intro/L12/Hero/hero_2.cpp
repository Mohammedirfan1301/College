#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

main()
{
	int a = 0, b = 0, c = 0, d = 0, x = 0, y = 0;
	char map[20][20];
	srand(time(0));
	int exit = 0;

	do{
	do{
	cout<<"HERO: ESCAPE OR DEATH \n";
	cout<<"This program lets you watch the Hero escape... or die. \n\n";

	d = rand()%9;

	for(a = 0; a < 20; a++)
	{
		for(b = 0; b < 20; b++)
		{
			if(a == 10 && b == 10)
			{
				map[a][b] = 'X';
				c = 1;
			}

			if(a == 0 || a == 19)
			{
				map[a][b] = '=';
				c = 1;
			}

			if(b == 0 && a != 0 && a != 19)
			{
				map[a][b] = '>';
				c = 1;
			}

			if(b == 19 && a != 0 && a != 19)
			{
				map[a][b] = '<';
				c = 1;
			}

			if(c != 1)
			{
				map[a][b] = '*';
			}

			c = 0;
		}
	}

	switch(d)
	{
		case 1:
			for(a=0;a<20;a++)
			{
				for(b=0;b<20;b++)
				{
					if(map[a][b] == 'X')
					{
                  map[a+1][b+1] == 'X';
						//somehow move x up one...
					}
				}
			}
			//moves up
			break;

		case 2:
			if(map[a][b] == 'X')
			{

			}
			//moves down
			break;

		case 3:
			if(map[a][b] == 'X')
			{

			}
			//moves left
			break;

		case 4:
			if(map[a][b] == 'X')
			{

			}
			//moves right
			break;

		case 5:
			if(map[a][b] == 'X')
			{

			}
			//moves up left
			break;

		case 6:
			if(map[a][b] == 'X')
			{

			}
			//moves up right
			break;

		case 7:
			if(map[a][b] == 'X')
			{

			}
			//moves down left
			break;

		case 8:
			if(map[a][b] == 'X')
			{

         }
			//moves down right
         break;
	}

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

	}while(y == 13);

	do{
	cout<<"\nPress 1 to continue, press 2 to quit. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

	clrscr();

	}while(x == 1);

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