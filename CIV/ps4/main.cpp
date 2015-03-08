#include "ED.hpp"

int main(int argc, const char* argv[])
{
  // Read in two strings from stdin
  std::string string1, string2;
  std::cin >> string1 >> string2;

  std::cout << "String 1: " << string1 << "\n";
  std::cout << "String 2: " << string2 << "\n";

  // Declare a ED object
  ED ed_test(string1, string2);

  // Find the Edit Distance
  int distance = ed_test.OptDistance();

  // Get the string alignment
  std::string alignment = ed_test.Alignment();

//   // Test the penalty methods.
//   int pen = ed_test.penalty('A', 'A');
//   std::cout << "Penalty should be 0: " << pen << "\n";

//   // Test min method
//   int min = ed_test.min(4, 8, 5);
//   std::cout << "Min should be 4: " << min << "\n";

  // Debug the Matrix
  ed_test.PrintMatrix();

  // Print out the edit distance
  std::cout << "\nEdit Distance = " << distance << "\n";
  std::cout << alignment; // this should have newlines inside of it!

  return 0;
}