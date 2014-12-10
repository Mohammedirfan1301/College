#ifndef COMPUTER_H
#define COMPUTER_H
#include <iostream>
using namespace std;

class Computer: public AbstractPlayer
{
public:
  virtual void selectPiece();
  virtual void move();
};

#endif
