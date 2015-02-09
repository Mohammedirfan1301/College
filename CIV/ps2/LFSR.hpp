#ifndef LFSR_HPP
#define LFSR_HPP

#include <iostream>

class LFSR {
public:
  LFSR(std::string seed, int t);    // Constructor
  int step();                       // simulates one step
  int generate(int k);              // simulates k steps

  // Overloaded << operator
  friend std::ostream& operator<< (std::ostream &out, LFSR &cLFSR);

private:
  std::string bits;                 // holds the LFSR
  int tap;
};

#endif