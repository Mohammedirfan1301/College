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
  char winner(void);
  void askYesNo(void);
  inline bool isLegal(int move);
  void askNumber(void);
  void CPU(void);
  void announceWinner(void);
  friend class Game;
  friend class AbstractPlayer;
  friend class Computer;
  friend class Human;

protected:
  char firstMove;
  char response;
  char turn;
  char the_winner;
  int number;
  int move;
  int low, high;
  vector<char> board;
};


// Abstract Player Class. Child classes: Computer, Human.
class AbstractPlayer
{
public:
  //virtual void selectPiece();
  virtual void move();
  inline bool isLegal(Board& board, int move);
};


// Computer Class. Parent: AbstractPlayer
class Computer: public AbstractPlayer
{
public:
  //void selectPiece(Board& board);
  void move(Board& board);
};


// Human Class. Parent: AbstractPlayer
class Human: public AbstractPlayer
{
public:
  //void selectPiece(Board& board);
  void move(Board& board);
};


// Game Class. Uses the other classes
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
