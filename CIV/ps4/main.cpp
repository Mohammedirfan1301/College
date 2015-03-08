#include "ED.hpp"

int main()
{
  // Read in two strings from stdin
  std::string string1, string2;
  std::cin >> string1 >> string2;

  // Declare a ED object
  ED ed_test(string1, string2);

  // Find the Edit Distance
  int distance = ed_test.OptDistance();

  // Get the string alignment
  std::string alignment = ed_test.Alignment();

//   // Test the penalty methods.
//   int pen = ed_test.penalty('A', 'A');
//   std::cout << "Penalty should be 0: " << pen << "\n";
//
//   pen = ed_test.penalty('A', 'B');
//   std::cout << "Penalty should be 1: " << pen << "\n";
//
//   pen = ed_test.penalty('A', ' ');
//   std::cout << "Penalty should be 2: " << pen << "\n";
//
//   // Test min method
//   int min = ed_test.min(1, 2, 3);
//   std::cout << "Min should be 1: " << min << "\n";
//
//   min = ed_test.min(3, 2, 1);
//   std::cout << "Min should be 1: " << min << "\n";
//
//   min = ed_test.min(3, 3, 3);
//   std::cout << "Min should be 3: " << min << "\n";

  // Print out the edit distance
  std::cout << "Edit Distance = " << distance << "\n";
  std::cout << alignment; // this should have newlines inside of it!

  return 0;
}