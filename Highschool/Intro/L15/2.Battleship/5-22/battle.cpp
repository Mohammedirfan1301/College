#include <iostream.h>
#include "h:\Programming\Battleship\battle.h"
//5-22-2012

battleship::battleship()
{

}

void battleship::intro()
{
	cout<<"********************** \n";
	cout<<"*                    * \n";
	cout<<"*  BATTLESHIP V1.00  * \n";
	cout<<"*                    * \n";
	cout<<"********************** \n\n\n";

	cout<<"This is the game of BATTLE SHIP. \n\n\n";
}

void battleship::print()
{

	cout<<"	PLAYER'S MAP       COMPUTER'S MAP   \n";
	cout<<"1 . . . . . . . .   1 . . . . . . . . \n";
	cout<<"2 . . . . . . . .   2 . . . . . . . . \n";
	cout<<"3 . . . . . . . .   3 . . . . . . . . \n";
	cout<<"4 . . . . . . . .   4 . . . . . . . . \n";
	cout<<"5 . . . . . . . .   5 . . . . . . . . \n";
	cout<<"6 . . . . . . . .   6 . . . . . . . . \n";
	cout<<"7 . . . . . . . .   7 . . . . . . . . \n";
	cout<<"8 . . . . . . . .   8 . . . . . . . . \n";
	cout<<"  A B C D E F G H     A B C D E F G H \n";

}
