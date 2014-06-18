#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

main()
{
	char map[20][20];             //2d character array for the map
	int row = 0, col = 0;         //used to fill the char array
	int rowmove = 0, colmove = 0; //variables for moving the 'X'.
	int a = 0, b = 0, x = 1, y = 1; //a controls when "*" appears in the map. b is used in a switch for random moves. x for the main do/while, y for the enter.
	int up = 0, down = 0;	        //counts up or down
	int hero = 0, stop = 1;         //hero is for hero win/lose. stop controls one of the do/whiles
	float moves = 0, allmoves = 0, allwins = 0, allloses = 0, allgames = 0;
   float avgmoves = 0, success = 0;
	srand(time(0));               //random number using time, used for switch(d) which does the random moves

	do{ //x variable controls this
   map[10][10] = 'X';
	stop = 1, moves = 0;

	cout<<"HERO: ESCAPE OR DEATH \n";
	cout<<"This program lets you watch the Hero escape... or die. \n";

	cout<<"\nKEY: \n";
	cout<<"======= is the safe zone \n";
	cout<<">>> <<< is the moat   \n";
	cout<<"******* is the island \n";
	cout<<"X is the Hero. \n\n";

	do{
	//fills the map
	cout<<"HERO (Scroll up for Intro/Key) \n\n";

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
	up = 0;
	down = 0;

	switch(b)  //uses b to choose a random option.
	{
		case 1: //moves X up by one.
			rowmove = -1;
			colmove = 0;
			up = 1;
			break;

		case 2: //moves X down by one.
			rowmove = 1;
			colmove = 0;
			down = 1;
			break;

		case 3: //moves X left by one.
			rowmove = 0;
			colmove = -1;
			up = 1;
			break;

		case 4: //moves X right by one.
			rowmove = 0;
			colmove = 1;
			down = 1;
			break;

		case 5: //moves X up left by one.
			rowmove = -1;
			colmove = -1;
			up = 1;
			break;

		case 6: //moves X up right by one.
			rowmove = -1;
			colmove = 1;
			up = 1;
			break;

		case 7: //moves X down left by one.
			rowmove = 1;
			colmove = -1;
			down = 1;
			break;

		case 8: //moves X down right by one.
			rowmove = 1;
			colmove = 1;
         down = 1;
         break;
	}

	//moves the Hero ("X") (used for case 1,3,5,6)
	if(up == 1)
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
	if(down == 1)
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

			if(row == 0 || row == 19)   //if the Hero is at one of the two escape bridges, he lives.
			{                           //the Hero variable is set equal to 1 and stop = 0, to stop the do/while loop.
				if(map[row][col] == 'X')
				{
					hero = 1;
					stop = 0;
				}
			}

			if( (col == 0 || col == 19) && row != 0 && row != 19)
			{                            //if the Hero is in one of the two moats, he dies.
				if(map[row][col] == 'X')  //the Hero variable is then set equal to 0 and stop = 0 to stop the do/while loop.
				{
					hero = 0;
					stop = 0;
				}
			}
		}
		cout<<endl;
	}

	moves++;   //counts the # of moves for each play through.

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
		cout<<"LIVED! Yay! \n";
		allwins++;
	}
	if(hero == 0)
	{
		cout<<"DIED! Oh no! \n";
		allloses++;
	}

	cout<<"The Hero moved "<<moves<<" times. \n";
	allmoves += moves;

	do{
	cout<<"\nDo you want to play again or quit? \n";
   cout<<"Enter 1 to play again or 2 to quit the game. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

	clrscr();
    
	}while(x == 1);

	allgames = allwins + allloses;
	avgmoves = allmoves / allgames;
	success = (allwins / allgames) * 100;

	cout<<"Thanks for using the HERO program. \n";

	cout<<"\nThe stats for all games of HERO: \n";
	cout<<"The Hero moved "<<allmoves<<" spaces. \n";
	cout<<"Which is an average of "<<setprecision(2)<<avgmoves<<" moves per game. \n";
	cout<<"The Hero survived "<<allwins<<" times. \n";
	cout<<"Which means the Hero's rate of survival is: "<<setprecision(4)<<success<<"%";

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
