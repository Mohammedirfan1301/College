#include <iostream>
#include "LFSR.hpp"

// Implemenation file for the LFSR class


// Constructor
LFSR::LFSR(std::string seed, int t)
{
  // Constructor
  std::cout << "Hello world.\n";

  bits = seed;
  tap = t;
}


// simulates one step
int LFSR::step()
{
  std::cout << "One step.\n";
  return 1;
}


// simulates k steps
int LFSR::generate(int k)
{
  std::cout << k << " number of steps.\n";
  return 1;
}


// returns a string rep. of the LFSR
std::ostream& operator<< (std::ostream &out, LFSR &cLFSR)
{
  out << cLFSR.bits;
  return out;
}