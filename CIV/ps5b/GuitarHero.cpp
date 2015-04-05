/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <vector>
#include "GuitarString.hpp"

int main(int argc, char* argv[]) {
  // Testing the GuitarString
  std::vector<sf::Int16> vec;

  vec.push_back((sf::Int16)3);

  GuitarString test(50.0);
  GuitarString test2(vec);

  test.pluck();
  test.tic();
  test.sample();
  test.time();

  return 0;
}
