#include <iostream>
#include "LFSR.hpp"

// Testing the LFSR class

int main()
{
  LFSR test("01101000010", 8);

  std::cout << test << std::endl;

  test.step();

  test.generate(10);

  std::cout << test << std::endl;

  std::cout << "Main is done!\n";

  return 0;
}