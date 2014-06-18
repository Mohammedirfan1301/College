#include <iostream.h>
#include "h:\Programming\Battleship\battle.cpp"
#include "h:\Programming\Battleship\battle.h"
//5-22-2012

main ()
{
	battleship x;
	int z = 1;

   do{
	x.intro();
	x.reset();
	x.fill();
	x.print();
	x.select();
	x.clear();
	x.print();
	}while(z == 1);

	return 0;
}

/*
Is it possible to change the
input from the player? to make
the input just arrow keys? or
is that too complicated?
take a lot into that...
ie

	cout<<"\t\t       YOUR BOMBS           YOUR NAVY    \n";
	cout<<"\t\t   0 1 . . . . . . . .   1 . . . . . . . . \n";
	cout<<"\t\t   1 2 . . . . . . . .   2 . . . . . . . . \n";
	cout<<"\t\t   2 3 . . . . . . . .   3 . . . . . . . . \n";
	cout<<"\t\t   3 4 . . . . . . . .   4 . . . . . . . . \n";
	cout<<"\t\t   4 5 . . . . . . . .   5 . . . . . . . . \n";
	cout<<"\t\t   5 6 . . . . . . . .   6 . . . . . . . . \n";
	cout<<"\t\t   6 7 . . . . . . . .   7 . . . . . . . . \n";
	cout<<"\t\t   7 8 . . . . . . . .   8 . . . . . . . . \n";
	cout<<"\t\t     A B C D E F G H     A B C D E F G H \n";
						 0 1 2 3 4 5 6 7

To Do:

2. Then make the computer randomly
	place their ships
3. Then allow the player to attack
4. Then allow the computer to attack
5. Loop this endlessly until all
	ships are destroyed.

Human VS Computer Battleship

1. Intro
2. Player places ships
	- Computer randomly places ships
3. Randomly choose who goes first
4A. Player goes first
4B. Computer goes first
5A. Player selects where to hit
5B. Computer selects where to hit
6A/B. If it hits go again
7A. If it doesn't hit go to Comp.
8A. If it doesn't hit go to Player.
9. Repeat A/B until someone's navy is completely
	destroyed.
10. Say who won/lost, allow the player to play again.
11. Repeat 2-10 until player quits
12. When player quits end the program.


*/