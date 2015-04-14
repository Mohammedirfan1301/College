/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"


int main(int argc, const char* argv[]) {
  // Make sure the user knows how to use our amazing TextGenerator program.
  if(argc != 3) {
    std::cout << "Usage: ./TextGenerator (int K) (int T)\n";
    return 0;
  }

  // For some weird reason, need to use a string to please -fpermissive
  // Can't just cast to int with getting:
  // error: cast from ‘const char*’ to ‘int’ loses precision [-fpermissive]
  std::string str_k(argv[1]);
  std::string str_t(argv[2]);

  // Get the command line arguments as ints.
  int k = std::stoi(str_k);
  int t = std::stoi(str_t);

  // Check the arguments for santity
//   std::cout << "k is: " << k << "\n";
//   std::cout << "t is: " << t << "\n";

  // Now take input from standard IO.
  std::string input;

  while (std::getline(std::cin, input)) {
    // This loop is magical and I love stackoverflow for help in cases
    // like this.
  }
  // I figured we should output the user's input for sanity checking.
  std::cout << "ORIGINAL INPUT TEXT BELOW THIS LINE.\n\n";
  std::cout << input;

  // Whenever stand IO hits a newline, we've finished taking input and
  // can actually do fun text generating stuff!

  // First make a final output string to use.
  std::string output_string;

  // We also need to use a MarkovModel object! Give it the int k as the
  // order. Also, the input text will be our string that we pass to the
  // constructor.
  MarkovModel amazing(input, k);

  // Now let's run from t - k transitions like Princeton tells us to!
  for (int a = 0; a < t - k; a++) {
    output_string += amazing.gen(input.substr(a, k), t);
  }

  // We're done! Just output the text to standard IO for the user to see. ^_^
  std::cout << "\n\nFINAL OUTPUT TEXT BELOW THIS LINE.\n\n";

  std::cout << output_string << "\n";

  // Original main below left here for testing purposes in the future.
  /*
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
  MarkovModel test2("Hello World. This is merely a test of stuff.", 1);
  std::cout << test2 << "\n";

  // Testing the randk function
  char temp = test2.randk("t");

  std::cout << "Random character is: " << temp << "\n";

  // Testing the generate function
  std::cout << "\n\n\n";

  MarkovModel test3("Hello World. This is merely a test of stuff.", 2);
  std::string final_str = test3.gen("Th", 4);

  std::cout << "My logic says this should be, well, \"This\": " << final_str;
  std::cout << "\nAm I right?\n";
*/
  return 0;
}
