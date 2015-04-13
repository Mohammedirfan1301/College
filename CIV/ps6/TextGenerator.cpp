/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"


int main() {
  std::cout << "Text Generator Program V1.1.\n\n";

  // Testing Order 0.
  MarkovModel test("gagggagaggcgagaaa", 0);

  // Testing methods.
  std::cout << "Order is: " << test.order() << "\n";
  std::cout << "Freq of \"\": " << test.freq("") << "\n";
  std::cout << "Freq of \"\" followed by 'a': " << test.freq("", 'a') << "\n";
  std::cout << "Freq of \"\" followed by 'c': " << test.freq("", 'c') << "\n";
  std::cout << "Freq of \"\" followed by 'g': " << test.freq("", 'g') << "\n";
  std::cout << "Freq of \"\" followed by 'z': " << test.freq("", 'z') << "\n";

  // Output the object for testing purposes.
  std::cout << test << "\n";

  // Testing Order 1.
  MarkovModel test1("Hello World. This is merely a test of stuff.", 1);
  std::cout << test1 << "\n";

  // Testing Order 2.
  MarkovModel test2("Hello World. This is merely a test of stuff.", 2);
  std::cout << test2 << "\n";

  // Testing the randk function
  char temp = test2.randk("is");

  std::cout << "Random character is: " << temp << "\n";

  // Testing the generate function


  return 0;
}
