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
  bool isLegal(void);
  char winner(void);
  void askYesNo(void);
  void askNumber(void);
  void announceWinner(void);
  friend class Game;

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
class AbstractPlayer: public Board
{
public:
  virtual void selectPiece();
  virtual void move();
};


// Computer Class. Parent: AbstractPlayer
class Computer: public AbstractPlayer
{
public:
  virtual void selectPiece();
  virtual void move();
};


// Human Class. Parent: AbstractPlayer
class Human: public AbstractPlayer
{
public:
  virtual void selectPiece();
  virtual void move();
};


// Game Class. Main class that the others derive from.
class Game
{
public:
  void instructions(void);
  void PlayGame(void);

protected:
  Board Game_Board;
  
};


#endif
