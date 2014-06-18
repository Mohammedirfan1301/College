#include <iostream.h>
#include "H:\Programming\L15\TicTacToe\print.cpp"
#include "H:\Programming\L15\TicTacToe\print.h"
//5-7-2012
//due on 5-28-2012

/*
	to do:

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
	 int z = 0;
	 printscreen x;

	 x.intro();
	 //x.menu();
	 x.cleargrid();

	 do{
	 {
	 //Player X moves
	 x.clearscreen();
	 x.intro();
	 x.map();
	 x.makemoveX();
	 x.test3();

	 //Player O moves
	 x.clearscreen();
	 x.intro();
	 x.map();
	 x.makemoveO();
	 x.test3();
	 }while(z != 1);

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
