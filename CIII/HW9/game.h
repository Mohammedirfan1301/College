#ifndef GAME_H
#define GAME_H
#include <iostream>
using namespace std;

class Game
{
public:
  Game();
  void instructions();
  void askYesNo(void);
  void askNumber(void);
  void announceWinner(int Winner);

  // Declared as points so compiler won't complain.
  Board* Game_Board;
  AbstractPlayer* Player;
  Computer* CPU;
  Human* The_Human;

protected:
  char response;
  int number;
  char firstMove;
  int move;
  int low, high;
  vector<char> board;
};

#endif
