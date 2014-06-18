#include <iostream.h>

/*
	TO DO:
	1. Use classes?!?!
	2. Make it actually take in an input!
	3. Make a computer player!
*/

main()
{
	char grid[3][3];
	int a = 0, b = 0;

	memset(grid, '\0', 9);

	cout<<"\t\t =========================== \n";
	cout<<"\t\t ||    TicTacToe V1.01    || \n";
	cout<<"\t\t ||  Created by JASON D   || \n";
	cout<<"\t\t ||        4/17/2012      || \n";
	cout<<"\t\t =========================== \n";

	cout<<endl<<"\t   Use the number pad to select a space. \n";
	cout<<"\t   2 = Down, 4 = Left 6 = Right, 8 = Up \n\n";

	for(a = 0; a < 3; a++)
	{
		for(b = 0; b < 3; b++)
		{
			grid[a][b]='#';
		}
	}

	cout<<"\t\t\t   *********"<<endl;

	for(a = 0; a < 3; a++)
	{
		cout<<"\t\t\t   * ";
		for(b = 0; b < 3; b++)
		{
			cout<<grid[a][b]<<" ";
		}

		if(a != 2)
			cout<<"*"<<endl<<"\t\t\t   * \t   *"<<endl;
		if(a == 2)
      	cout<<"*";
	}

	cout<<endl<<"\t\t\t   *********"<<endl;

	return 0;
}