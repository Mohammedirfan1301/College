#include <iostream.h>
#include "H:\Programming\L15\TicTacToe\print.cpp"
#include "H:\Programming\L15\TicTacToe\print.h"
//5-3-2012

/*
	to do:
	1. fix printing errors (lines off)
	2. reverse the num pad (b/c 1 is on top,
		but should be on the bottom...)
	3. make the program 2 player (humans)
	4. make the program detect 3-in-a-row
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
	 int d;
	 printscreen x;

	 x.intro();
	 //x.menu();
	 x.cleargrid();

	 for(d = 0; d < 10; d++)
	 {
	 x.clearscreen();
	 x.intro();
	 x.map();
	 x.makemove();
	 }

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
| * | * | * |
|---|---|---|
| * | * | * |
|---|---|---|
| * | * | * |
 --- --- ---

*/
