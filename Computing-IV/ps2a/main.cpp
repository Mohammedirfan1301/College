#include <iostream>
#include <string>
#include <sstream>
#include "LFSR.hpp"

// Testing the LFSR class

int main()
{
  LFSR test("01101000010", 8);

  std::cout << "Test case 1. \n";

  // Test case 1 from the princeton site.

  for(int i = 0; i < 10; i++)
  {
    int bit = test.step();
    std::cout << test << " " << bit << std::endl;
  }

  LFSR test2("01101000010", 8);
  std::cout << "\n\nTest case 2.\n";

  // Test case 2 from the princeton site.
  for(int i = 0; i < 10; i++)
  {
    int r = test2.generate(5);
    std::cout << test2 << " " << r << std::endl;
  }

  LFSR test3("0101", 2);
  int num = test3.generate(2);

  std::cout << test3 << " " << num <<  std::endl;

  LFSR test4("0011010010", 3);

  int num2 = test4.generate(4);

  std::cout << num2 << "\n";

  return 0;
}