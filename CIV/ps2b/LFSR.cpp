#include <iostream>
#include <string>
#include <sstream>
#include "LFSR.hpp"

// Implemenation file for the LFSR class


// Constructor
LFSR::LFSR(std::string seed, int t)
{
  // Sets inital seed / tap position
  bits = seed;
  tap = t;
}


// simulates one step
int LFSR::step()
{
  /*
   * We need to XOR the left most position with the tap position.
   * The left most position is just bits[0] - the very left most bit.
   *
   * The tap position can be found using the following formula:
   * tap position = size() - tap - 1
   *
   * It works by converting the tap position value into array indexes
   *
   */

  // Find the index of the tap position.
  int tap_pos = bits.length() - tap - 1;

  // XOR the tap position with the left most bit
  int res = bits[0] ^ bits[tap_pos];

  // We need to go through and shift all bits left now.
  std::string::size_type i;
  std::ostringstream ostring;   // Using string streams to append the
                                // the XOR result

  // Now shift everything left.
  for(i = 0; (unsigned)i < bits.length() - 1; i++)
  {
    ostring << bits[i + 1];
  }

  // Append the XOR result
  ostring << res;

  // Save the updated string - ostring.str() converts a string stream
  // back into a string
  bits = ostring.str();

  // Return the XOR result bit
  return res;
}


// simulates k steps
int LFSR::generate(int k)
{
  // Intialize variable to zero.
  int x = 0;

  for(int i = 0; i < k; i++)
  {
    x = (x * 2) + step();
  }

  return x;
}


// returns a string rep. of the LFSR
std::ostream& operator<< (std::ostream &out, LFSR &cLFSR)
{
  out << cLFSR.bits;
  return out;
}