/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"


int main() {
  std::cout << "Text Generator Program V.1.\n\n";

  MarkovModel test("Hello", 5);

  // Testing methods.
  test.order();
  test.freq("Hello");
  test.freq("Hello", 'c');
  test.randk("Hello");
  test.gen("Hello", 5);
  std::cout << test << "\n";

  return 0;
}
