#include <iostream.h>
#include "h:\Programming\Battleship\battle.cpp"
#include "h:\Programming\Battleship\battle.h"
//5-22-2012

main ()
{
	battleship x;
	x.intro();
	x.reset();
	x.fill();
   x.select();
	x.print();

	return 0;
}

/*
Is it possible to change the
input from the player? to make
the input just arrow keys? or
is that too complicated?
take a lot into that...
ie




To Do:

1. Need to accept an input from
	the player.
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