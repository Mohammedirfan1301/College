#include <iostream.h>
#include "h:\Programming\Battleship\battle.cpp"
#include "h:\Programming\Battleship\battle.h"
//#include "c:\Battle\battle.cpp"
//#include "c:\Battle\battle.h"
//5-31-2012

main ()
{
	battleship x;
	int y = 1, z = 1;

	do{
	x.intro();
	x.reset();
	x.fill();
	x.print();
	x.select();
	x.cselect();

	do{
	x.clear();
	x.intro();
	x.print();
	x.playhit();
	if(x.whowin() != 0)
		break;
	x.comphit();
	if(x.whowin() != 0)
		break;
	}while(y == 1);

	}while(z == 1);

	return 0;
}

/*
PROGRAM DONE!
HOWEVER: bug test and make sure it actually works
correctly!

1. Allow the player to place their ships. -> CHECK
2. Auto place ships for the computer.     -> CHECK
3. Player hits computer's ships.          -> CHECK
4. Auto hit the player's ships.           -> CHECK
5. Check to see if anyone won.            -> CHECK

	cout<<"\t\t       YOUR BOMBS           YOUR NAVY    \n";
	cout<<"\t\t   1 . . . . . . . .   1 . . . . . . . . \n";
	cout<<"\t\t   2 . . . . . . . .   2 . . . . . . . . \n";
	cout<<"\t\t   3 . . . . . . . .   3 . . . . . . . . \n";
	cout<<"\t\t   4 . . . . . . . .   4 . . . . . . . . \n";
	cout<<"\t\t   5 . . . . . . . .   5 . . . . . . . . \n";
	cout<<"\t\t   6 . . . . . . . .   6 . . . . . . . . \n";
	cout<<"\t\t   7 . . . . . . . .   7 . . . . . . . . \n";
	cout<<"\t\t   8 . . . . . . . .   8 . . . . . . . . \n";
	cout<<"\t\t     A B C D E F G H     A B C D E F G H

*/
