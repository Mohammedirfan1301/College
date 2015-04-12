/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"


int main() {
  std::cout << "Text Generator Program V.1.\n\n";

  MarkovModel test("hello", 5);

  // Testing methods.
  test.order();
  test.freq("hello");
  test.freq("hello", 'c');
  test.randk("hello");
  test.gen("hello", 5);
  std::cout << test << "\n";

  return 0;
}
