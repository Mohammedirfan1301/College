#include "game_includes"

void Board::displayBoard(void)
{
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\n";
}
