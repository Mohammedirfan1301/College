#include "game_includes"

void AbstractPlayer::move()
{
	askYesNo();

	if(response == 'y')
	{
		cout << "\nPlease feel free to take a number.\n";
		firstMove = 'X';
	}
	else
	{
		cout << "\nI will go first.\n";
		firstMove = 'O';
	}
}
