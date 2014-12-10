#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include "tictac_header.h"

using namespace std;

// global constants
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

/*************************************************************
// Game Functions
*************************************************************/
// Default Constructor
Game::Game()
{
	// There isn't anything really to set so I left it empty.
}

// This function will have all the game related stuff.
void Game::PlayGame(void)
{
	// Show the user how to play.
	instructions();

	// Now time to set up the game.
	Game_Board.askYesNo();

	Game_Board.displayBoard();

	// Loop through the game now until we find a winner.
	while(Game_Board.winner() == NO_ONE)
	{
		if(Game_Board.turn == 'H')
		{
			// Human goes
			human.move(Game_Board);
		}
		else
		{
			// CPU goes
			computer.move(Game_Board);
		}
		Game_Board.displayBoard();				// Display the board after each turn.
	}
	// We got a winner, so call that function.
	Game_Board.announceWinner();
}


void Game::instructions()
{
	cout << "Welcome to tic-tac-toe.\n";
	cout << "This will be a friendly battle of human vs computer.\n\n";

	cout << "Make your move by entering a number, 1 - 9.  The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";

	// I'm changing this because the original game was very counterintuitive
	cout << "       7 | 8 | 9\n";
	cout << "      -----------\n";
	cout << "       4 | 5 | 6\n";
	cout << "      -----------\n";
	cout << "       1 | 2 | 3\n\n";

	cout << "Prepare yourself.  The battle is about to begin.\n\n";
}


/*************************************************************
// Board Functions
*************************************************************/
// Default Constructor
Board::Board()
{
	// Preset all the variables for safety.
	firstMove = EMPTY;
	response = EMPTY;
	turn = EMPTY;
	the_winner = EMPTY;

	// These need to be set, especially low / high.
	number = 0;
	move = 0;
	low = 1;
	high = 9;

	// Make vector size 9 and have every space equal to ' '.
	for(int i = 0; i < 9; i ++)
	{
		board.push_back(EMPTY);
	}
}


// Small function to get the size of the vector. Used in Human/Computer classes.
int Board::getSize(void)
{
	return board.size();
}


void Board::askYesNo(void)
{
	notYN except;

	do{
		cout << "Do you want to make the first move? (y/n): ";
		cin >> response;

		try{
			if(response == 'y' || response == 'Y' || response == 'n' || response == 'N')
			{
				// Don't throw an exception, we're good.
			}
			else{
				// throw one, the user didn't follow instructions.
				throw except;
			}
		}
		catch(exception& e)
		{
			cout << endl << e.what() << endl << endl;
		}
	}while(response != 'y' && response != 'n');

	if(response == 'y')
	{
		cout << "\nPlease feel free to take a number.\n";
		firstMove = 'H';
		turn = 'H';
	}
	else
	{
		cout << "\nI will go first.\n";
		firstMove = 'C';
		turn = 'C';
	}
}


char Board::winner(void)
{
	// All possible winning rows
	const int WIN[8][3] = {{0, 1, 2}, {3, 4, 5},{6, 7, 8},{0, 3, 6},{1, 4, 7},{2, 5, 8},{0, 4, 8},{2, 4, 6} };
	const int TOTAL_ROWS = 8;

	// If any winning row has three values that are the same (and not EMPTY),
	// then we have a winner
	for(int row = 0; row < TOTAL_ROWS; ++row)
	{
		if( (board[WIN[row][0]] != ' ') && (board[WIN[row][0]] == board[WIN[row][1]]) &&
			  (board[WIN[row][1]] == board[WIN[row][2]]) )
		{

			the_winner = board[WIN[row][0]];
			return board[WIN[row][0]];
		}
	}

	// Since nobody has won, check for a tie (no empty squares left)
	if (count(board.begin(), board.end(), EMPTY) == 0)
	{
		the_winner = 'T';
		return 'T';
	}

	// Since nobody has won and it isn't a tie, the game ain't over
	the_winner = 'N';
	return 'N';
}


void Board::announceWinner(void)
{
	if(the_winner == 'X' && firstMove == 'C' || the_winner == 'O' && firstMove == 'H')
	{
		cout << "The Computer won!\n";
		cout << "As I predicted, human, I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
		return;
	}
	else if(the_winner == 'X' && firstMove == 'H' || the_winner == 'O' && firstMove == 'C')
	{														// Note: Human cannot win the way this program is
		cout << "You won!\n";			// programmed.
		cout << "No, no!  It cannot be!  Somehow you tricked me, human.\n";
		cout << "But never again!  I, the computer, so swear it!\n";
		return;
	}

	cout << "It's a tie.\n";
	cout << "You were most lucky, human, and somehow managed to tie me.\n";
	cout << "Celebrate... for this is the best you will ever achieve.\n";
}


void Board::displayBoard(void)
{
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\n";
}


/*************************************************************
// AbstractPlayer Functions
*************************************************************/
AbstractPlayer::AbstractPlayer()
{
	// Empty because there are no member variables to set.
}

void AbstractPlayer::move()
{
  // Left empty
}

char AbstractPlayer::selectPiece(Board& board)
{
	// Left empty
}


inline bool AbstractPlayer::isLegal(Board& board, int move)
{
    return (board.board[move] == EMPTY);
}


// Human really only needs one function, since it inherits the default constructor
// and the isLegal function.
void Human::move(Board& board)
{
	int x = 0;
	do{
		do{
			cout << "Where will you move? -> ";
			cin >> board.number;
		}while(board.number > board.high || board.number < board.low);

		// Only let the player continue if the move is legal.
		// Basically if the move is on an empty spot.
		if(isLegal(board, board.number - 1) == true)
		{
			board.board[board.number - 1] = selectPiece(board);
			x = 1;
			board.turn = 'C';
		}
	}while(x == 0);
}

char Human::selectPiece(Board& board)
{
	if(board.firstMove == 'H')
	{
		return X;
	}
	else{
		return O;
	}
}


// Same as Human, requires just one function since it inherits from AbstractPlayer.
void Computer::move(Board& board)
{
	char human;
  cout << "I will take the number: ";

	// I combined the two for loops in to one, since that made more logical sense.
  for(int move = 0; move < board.getSize(); ++move)
  {
		// if computer can win on next move, make that move
		if (isLegal(board, move))
		{
		    board.board[move] = selectPiece(board);
		    if (board.winner() == selectPiece(board))
		    {
		        cout << move << endl;
		        board.board[move] = selectPiece(board);
		        board.turn = 'H';
		        return;
		    }
		    // done checking this move, undo it
		    board.board[move] = EMPTY;
		}

		// if human can win on next move, block that move
		if (isLegal(board, move))
		{
			char computer = selectPiece(board);
			if(computer == 'X')
			{
				human = 'O';
			}
			else{
				human = 'X';
			}
			board.board[move] = human;

			if (board.winner() == human)
			{
				cout << move << endl;
				board.board[move] = computer;
				board.turn = 'H';
				return;
			}
			// done checking this move, undo it
			board.board[move] = EMPTY;
		}
  }


  // the best moves to make, in order
  const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

  // since no one can win on next move, pick best open square
  for(int i = 0; i < board.getSize(); ++i)
  {
      int move = BEST_MOVES[i];
      if (isLegal(board,move))
      {
          cout << move << endl;
          board.board[move] = selectPiece(board);
          board.turn = 'H';
          return;
      }
  }
}

char Computer::selectPiece(Board& board)
{
	if(board.firstMove == 'C')
	{
		return X;
	}
	else{
		return O;
	}
}
