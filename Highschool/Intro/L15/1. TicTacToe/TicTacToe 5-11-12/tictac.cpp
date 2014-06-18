#include <iostream.h>
#include "H:\Programming\L15\TicTacToe\print.cpp"
#include "H:\Programming\L15\TicTacToe\print.h"
//5-7-2012
//due on 5-28-2012

/*
	to do:

	OK so X should be all set
	Make function to detect if O has 3inarow
	just copy/paste but change X to O
	or find a way to reuse both of them...
   (probably not possible)

	- It can detect to some degree 3 in a row
	- Must expand this to check whether X won
	- or O won.

	* also detects X across 3inArow
	ie 123 or 456 or 789
	need to expand to up and down
	ie 741 or 852 or 963
	also diangle
	ie 753 or 159

	then after X is done, copy and paste,
	but for O. Same thing - across, up and down
	and diangle.

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
	7. make the game replayable (best 2/3 etc)
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
	 if(x.test3() == 1)
	 {
      x.clearscreen();
		x.intro();
		x.map();
		break;
	 }

	 //Player O moves
	 x.clearscreen();
	 x.intro();
	 x.map();
	 x.makemoveO();
	 x.test3();

	 if(x.test3() == 1)
	 {
		x.clearscreen();
		x.intro();
		x.map();
		break;
	 }

	 }while(z == 1);

	 cout<<"Well done, ";
	 if(x.test3() == 1)
		cout<<"X";
	 //if(stop == 2)
		//cout<<"O";

	 cout<<" won! \n";
	 cout<<"Play again? \n";
	 cout<<"Enter 1 for Yes or 2 for No -> ";
	 cin>>e;
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
