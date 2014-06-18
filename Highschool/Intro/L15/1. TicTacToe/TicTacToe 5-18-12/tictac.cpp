#include <iostream.h>
#include "H:\Programming\L15\TicTacToe\print.cpp"
#include "H:\Programming\L15\TicTacToe\print.h"
//5-7-2012
//due on 5-28-2012

/*
	to do:

	When this is done, fix bugs and make a
	scoring system which should keep track of
	wins - X won, O won.

	Also, what about ties? if none of the above
	comes out as true (ie 0 is returned)
	And the count is 9 for moves
	then a tie should have taken place since
	no one won.

	5. test the program, make sure it works
	6. add a scoring system

	8. once this is done (and anything else
		required or needed to be tweeked)
		Add a computer option
	9. Computer option will require:
		- Random moves
		- Additional Scoring (Reuse?)
		- Additional tweeks and such

*/

main()
{
	 int z = 1;
	 int e = 0;
	 int moves = 0;
	 int xwins = 0;
	 int owins = 0;
	 int ties = 0;
	 int totalgames = 0;
    float winper = 0;
	 printscreen x;

	 do{
	 x.intro();
	 //x.menu();
	 x.cleargrid();

	 do{
	 //Player X moves
	 x.clearscreen();
	 x.intro();
	 x.map();
	 x.makemoveX();
	 moves++;

	 if(x.test3() == 1)
	 {
		x.clearscreen();
		x.intro();
		x.map();
		xwins++;
		totalgames++;
		break;
	 }

	 if(moves == 9 && x.test3() == 0)
	 {
		x.clearscreen();
		x.intro();
		x.map();
		ties++;
		totalgames++;
		break;
	 }

	 //Player O moves
	 x.clearscreen();
	 x.intro();
	 x.map();
	 x.makemoveO();
	 moves++;

	 if(x.test3() == 2)
	 {
		x.clearscreen();
		x.intro();
		x.map();
		owins++;
		totalgames++;
		break;
	 }

	 if(moves == 9 && x.test3() == 0)
	 {
		x.clearscreen();
		x.intro();
      x.map();
		ties++;
      totalgames++;
		break;
	 }

	 }while(z == 1);

	 cout<<"Well done, ";
	 if(x.test3() == 0)
    	cout<<"but it's a TIE! \n";
	 if(x.test3() == 1)
		cout<<"X won! \n";
	 if(x.test3() == 2)
		cout<<"O won! \n";

	 cout<<"\nWin Percentages: \n";
	 cout<<"Player 1 (X) -> ";
	 winper = (xwins / totalgames) * 100;
	 cout<<winper<<"% \n";
	 cout<<"Player 2 (O) -> ";
	 winper = (owins / totalgames) * 100;
	 cout<<winper<<"% \n";
	 cout<<"        Ties -> ";
	 winper = (ties / totalgames) * 100;
    cout<<winper<<"% \n";

	 cout<<"\nPlay again? \n";
	 cout<<"Enter 1 for Yes or 2 for No -> ";
	 cin>>e;

	 if(e == 1)
	 {
		z = 1;
		moves = 0;
	 }

	 }while(e == 1);

	 x.clearscreen();
	 cout<<"\t\tTHANKS FOR PLAYING!";

	 return 0;
}

/*

Main Menu:

TicTacToe

Choose a game type:

1 Player
2 Player

Enter the # here ->

//loads into the game

 --- --- ---
| O | X | X |
|---|---|---|
| X | O | O |
|---|---|---|
| X | X | O |
 --- --- ---

*/
