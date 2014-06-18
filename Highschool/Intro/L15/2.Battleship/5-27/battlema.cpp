#include <iostream.h>
//#include "h:\Programming\Battleship\battle.cpp"
//#include "h:\Programming\Battleship\battle.h"
#include "C:\Users\Jason\Documents\_Documents\Programming\_Programs\L15\2.Battleship\5-27\battle.cpp"
#include "C:\Users\Jason\Documents\_Documents\Programming\_Programs\L15\2.Battleship\5-27\battle.h"
//5-27-2012

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
