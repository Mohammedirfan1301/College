#include <iostream.h>
#include "H:\TicTacToe\print.h"

printscreen::printscreen()
{
	a = 0;
	b = 0;
}

void printscreen::map()
{
	for(a = 0; a < 3; a++)
	{
		for(b = 0; b < 3; b++)
		{
			grid[a][b]='#';
		}
	}
}

void printscreen::printmap()
{
	for(a = 0; a < 3; a++)
	{
		for(b = 0; b < 3; b++)
		{
			cout<<grid[a][b];
		}
	}
}

void printscreen::stop()
{
    do{
    cout<<"STOP! ENTER 1! ->";
    cin>>a;
    }while(a != 1);
}
