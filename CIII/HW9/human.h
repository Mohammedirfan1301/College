#ifndef HUMAN_H
#define HUMAN_H
#include <iostream>
using namespace std;

class Human: public AbstractPlayer
{
public:
  virtual void selectPiece();
  virtual void move();
};

#endif
