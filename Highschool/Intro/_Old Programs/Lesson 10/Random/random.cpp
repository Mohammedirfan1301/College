#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

void coin();
void card();
void dice();

main()
{
	srand(time(0));
	int a = 0, x = 1;
	do{

	cout<<"Welcome to the 3 Games In One Program. \n";
	cout<<"This program will let you flip a coin, pick a card, \n";
	cout<<"or roll a dice. \n";

	cout<<"\nDo you want to flip a coin, pick a card or roll a dice? \n";
	cout<<"Flip a coin - Enter 1. \n";
	cout<<"Pick a card - Enter 2. \n";
	cout<<"Roll a dice - Enter 3. \n";
	cout<<"Enter your selection. -> ";
	cin>>a;

	switch(a)
	{
		case 1:
				coin();
				break;

		case 2:
				card();
				break;

		case 3:
				dice();
				break;

		default:
				cout<<"\nYou didn't enter a valid selection. Try entering \n";
				cout<<"numbers 1, 2 or 3. \n";
	}

	do{
	cout<<"\nTo stop the program, enter 0. To rerun the program, enter 1. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	cout<<endl;
	clrscr();
	}while((x != 1) && (x != 0));

	}while(x == 1);

	return 0;
}


void coin(void)
{
	int b;
	cout<<"\nFliping a coin...\n";

	b = 1 + rand()%2;

	switch(b)
	{
		case 1:
				cout<<"Heads. \n";
				break;
		case 2:
				cout<<"Tails. \n";
				break;
	}
}


void card(void)
{
	int c;
	cout<<"\nPicking a card... \n";

	c = rand()%13;

	switch(c)
	{
		case 1:
				cout<<"You got an Ace! \n";
				break;
		case 2:
				cout<<"You got a 2! \n";
				break;
		case 3:
				cout<<"You got a 3! \n";
				break;
		case 4:
				cout<<"You got a 4! \n";
				break;
		case 5:
				cout<<"You got a 5! \n";
				break;
		case 6:
				cout<<"You got a 6! \n";
				break;
		case 7:
				cout<<"You got a 7! \n";
				break;
		case 8:
				cout<<"You got a 8! \n";
				break;
		case 9:
				cout<<"You got a 9! \n";
				break;
		case 10:
				cout<<"You got a 10! \n";
				break;
		case 11:
				cout<<"You got a Jack! \n";
				break;
		case 12:
				cout<<"You got a Queen! \n";
				break;
		case 13:
				cout<<"You got a King! \n";
				break;

	}

}

void dice(void)
{
	int d;
	cout<<"\nRolling a dice...\n";

	d = rand()%6;

	switch (d)
	{
		case 1:
				cout<<"You rolled a 1! \n";
				break;
		case 2:
				cout<<"You rolled a 2! \n";
				break;
		case 3:
				cout<<"You rolled a 3! \n";
				break;
		case 4:
				cout<<"You rolled a 4! \n";
				break;
		case 5:
				cout<<"You rolled a 5! \n";
				break;
		case 6:
				cout<<"You rolled a 6! \n";
				break;
	}

}
