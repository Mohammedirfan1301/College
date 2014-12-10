#ifndef BOARD_H
#define BOARD_H
#include <iostream>
using namespace std;

class Board: public Game
{
public:
  void displayBoard(void);
  bool isLegal(const vector<char>& board);
  char winner(const vector<char>& board);
protected:

};

#endif
