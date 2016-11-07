#include "ED.hpp"

int main(int argc, const char* argv[])
{
  // Time calculations
  sf::Clock clock;
  sf::Time t;

  // Read in two strings from stdin
  std::string string1, string2;
  std::cin >> string1 >> string2;

  // Check stdin
//   std::cout << "String 1: " << string1 << "\n";
//   std::cout << "String 2: " << string2 << "\n";

  // Declare a ED object
  ED ed_test(string1, string2);

  // Find the Edit Distance
  int distance = ed_test.OptDistance();

  // Get the string alignment
  std::string alignment = ed_test.Alignment();

  // Print out the edit distance
  std::cout << "Edit distance = " << distance << "\n";
  std::cout << alignment; // this should have newlines inside of it!

  // Debug the Matrix
  ed_test.PrintMatrix();

  // I'm printing this out again to make it easier when running tests for the README.
  std::cout << "\nEdit distance = " << distance;
  t = clock.getElapsedTime();
  std::cout << "\nExecution time is " << t.asSeconds() << " seconds \n";

  return 0;
}
