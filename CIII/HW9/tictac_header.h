#ifndef TICTAC_HEADER_H
#define TICTAC_HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

using namespace std;

// Board Class.
class Board
{
  public:
    Board();
    void displayBoard(void);
    void askYesNo(void);
    void askNumber(void);
    inline bool isLegal(int move);
    int getSize(void);
    char winner(void);
    void announceWinner(void);

    // Made these friends so that they can access Board's variables.
    friend class Game;
    friend class AbstractPlayer;
    friend class Computer;
    friend class Human;

  protected:
    // Variables used in the class
    char firstMove, response, turn, the_winner;
    int number, move, low, high;
    vector<char> board;
};


// Abstract Player Class. Child classes: Computer, Human.
class AbstractPlayer
{
public:
  AbstractPlayer();
  virtual void move();
  inline bool isLegal(Board& board, int move);
};


// Computer Class. Parent: AbstractPlayer
class Computer: public AbstractPlayer
{
public:
  void move(Board& board);
};


// Human Class. Parent: AbstractPlayer
class Human: public AbstractPlayer
{
public:
  void move(Board& board);
};


// Game Class. Uses the other classes to play a game of TicTacToe
class Game
{
public:
  void instructions(void);
  void PlayGame(void);

protected:
  Board Game_Board;
  Human human;
  Computer computer;
};


#endif
