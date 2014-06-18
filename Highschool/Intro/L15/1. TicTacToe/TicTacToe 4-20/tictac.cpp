#include <iostream.h>
#include "H:\TicTacToe\print.h"
#include "H:\TicTacToe\print.cpp"

main()
{
    printscreen x;
	 x.clear();
    x.intro();
	 x.map();
	 x.printmap();
	 x.stop();

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
