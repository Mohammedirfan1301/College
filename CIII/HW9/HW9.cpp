/*
    Jason Downing, Copyright (C)2014
    12/8/2014
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

using namespace std;

class Game
{
public:
    void instructions();
    char askYesNo(string question);
    int askNumber(string question, int high, int low = 0);
    void announceWinner(char winner, char computer, char human);

    // constants
    const char X = 'X';
    const char O = 'O';
    const char EMPTY = ' ';
    const char TIE = 'T';
    const char NO_ONE = 'N';

private:
    char response;
    int number;
    char firstMove;

    vector<char> board;
    int move;
    Board Game_Board;
    AbstractPlayer Player;
    Computer CPU;
    Human The_Human;

};

class Board: public Game
{
public:
    bool isLegal(const vector<char>& board, int move);
    char winner(const vector<char>& board);
};


class AbstractPlayer
{
public:
    virtual void selectPiece();
    virtual void move();
};


class Computer: public AbstractPlayer
{
public:
    virtual void selectPiece();
    virtual void move();
};


class Human: public AbstractPlayer
{
public:
    virtual void selectPiece();
    virtual void move();
};


// main function
int main()
{


    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);

    instructions();
    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    displayBoard(board);

    while (winner(board) == NO_ONE)
    {
        if (turn == human) 
        {
            move = humanMove(board, human);
            board[move] = human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }

    announceWinner(winner(board), computer, human);

    return 0;
}


// functions
void Game::instructions()
{
    cout << "Welcome to tic-tac-toe.\n";
    cout << "This will be a friendly battle of human vs computer.\n\n";

    cout << "Make your move known by entering a number, 1 - 9.  The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";

    // I'm changing this because the original game was very counterintuitive
    cout << "       7 | 8 | 9\n";
    cout << "      -----------\n";
    cout << "       4 | 5 | 6\n";
    cout << "      -----------\n";
    cout << "       1 | 2 | 3\n\n";

    cout << "Prepare yourself.  The battle is about to begin.\n\n";
}


void Game::askYesNo(string question)
{
    do{
        cout << question << " (y/n): ";
        cin >> response;
    }while (response != 'y' && response != 'n');
}


void Game::askNumber(string question, int high, int low)
{
    do{
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    }while (number > high || number < low);
}


void AbstractPlayer::move()
{
    char go_first = askYesNo("Do you require the first move?");
    if(go_first == 'y')
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


void Board::displayBoard(void)
{
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
    cout << "\n\n";
}


char winner(void)
{
    // all possible winning rows
    const int WINNING_ROWS[8][3] = { {0, 1, 2},
                                     {3, 4, 5},
                                     {6, 7, 8},
                                     {0, 3, 6},
                                     {1, 4, 7},
                                     {2, 5, 8},
                                     {0, 4, 8},
                                     {2, 4, 6} };
    const int TOTAL_ROWS = 8;

    // if any winning row has three values that are the same (and not EMPTY),
    // then we have a winner
    for(int row = 0; row < TOTAL_ROWS; ++row)
    {
        if ( (board[WINNING_ROWS[row][0]] != EMPTY) &&
             (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
             (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) )
        {
            return board[WINNING_ROWS[row][0]];
        }
    }

    // since nobody has won, check for a tie (no empty squares left)
    if (count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;

    // since nobody has won and it isn't a tie, the game ain't over
    return NO_ONE;
}


inline bool isLegal(int move, const vector<char>& board)
{
    return (board[move] == EMPTY);
}


int Move(const vector<char>& board, char human)
{
    int move = askNumber("Where will you move?", (board.size() - 1));
    while (!isLegal(move, board))
    {
        cout << "\nThat square is already occupied, fool.\n";
        move = askNumber("Where will you move?", (board.size() - 1));
    }
    cout << "Fine...\n";
   
    cout << "I will take the number: ";

    // if computer can win on next move, make that move
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, board))
        {
            board[move] = computer;
            if (winner(board) == computer)
            {
                cout << move << endl;
                return move;
            }
            // done checking this move, undo it
            board[move] = EMPTY;
        }
    }

    // if human can win on next move, block that move
    char human = opponent(computer);
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, board))
        {
            board[move] = human;
            if (winner(board) == human)
            {
                cout << move << endl;
                return move;
            }
            // done checking this move, undo it
            board[move] = EMPTY;
        }
    }

    // the best moves to make, in order
    const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

    // since no one can win on next move, pick best open square
    for(int i = 0; i < board.size(); ++i)
    {
        int move = BEST_MOVES[i];
        if (isLegal(move, board))
        {
            cout << move << endl;
            return move;
        }
    }
}


void Game::announceWinner(int Winner)
{
    switch(Winner)
    {
        case 1:
            cout << winner << "'s won!\n";
            cout << "As I predicted, human, I am triumphant once more -- proof\n";
            cout << "that computers are superior to humans in all regards.\n";
            break;

        case 2:
            cout << winner << "'s won!\n";
            cout << "No, no!  It cannot be!  Somehow you tricked me, human.\n";
            cout << "But never again!  I, the computer, so swear it!\n";
            break;

        case 3:
            cout << "It's a tie.\n";
            cout << "You were most lucky, human, and somehow managed to tie me.\n";
            cout << "Celebrate... for this is the best you will ever achieve.\n";
            break
    }
}

