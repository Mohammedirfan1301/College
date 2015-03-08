#include "ED.hpp"

// Default constructor
ED::ED()
{

}


// Contructor with parameters
ED::ED(std::string string_one, std::string string_two)
{
  _string_one = string_one;
  _string_two = string_two;
}


// Destructor
ED::~ED()
{

}


// Returns the penalty of the two characters.
int ED::penalty(char a, char b)
{
  if(a == b)    // Equal characters
  {
    return 0;
  }

  else if(a != b && b != ' ')
  { // not equal and no spaces
    return 1;
  }

  else if(a != b && b == ' ')
  { // not equal and one is blank
    return 2;
  }

  // If something fails, return a -1.
  // We can check this for errors.
  return -1;
}


// Finds the minimum integer
int ED::min(int a, int b, int c)
{
  if(a < b && a < c)
  {
    return a;
  }

  else if(b < a && b < c)
  {
    return b;
  }

  else if(c < a && c < b)
  {
    return c;
  }

  // They are all equal if we get here.
  // So just return a cause w/e
  return a;
}


// Finds the optimal distance between the two strings
int ED::OptDistance()
{
  // This is where we should do some sort of loop and populate
  // the matrix. We should use the penalty and min methods as well.

  int i, j;
  int string1_end = _string_one.length();
  int string2_end = _string_two.length();

  // Need to count backwards for the rows
  j = 0;

  std::cout << "End of string 1: " << string1_end << "\n";
  std::cout << "End of string 2: " << string2_end << "\n";

  // Create the Matrix
  for(i = 0; i < string2_end + 1; i++)
  {
    std::vector<int> tmp;
    _matrix.push_back(tmp);

    // Now push '0's back into the given vector
    for(j = 0; j < string1_end + 1; j++)
    {
      _matrix.at(i).push_back(0);
    }
  }

  // Start by filling out the bottom row
  for(i = 0; i < string1_end + 1; i++)
  {
    // Very bottom row
    _matrix[i][string1_end] = 2 * (string2_end - i);
  }

  // Samething for the right most column, need to count backwards
  i = 0;

  // Now fill out the side row.
  for(j = 0; j < string2_end - 1; j++)
  {
    // Very right most column
    _matrix[string2_end][j] = 2 * (string1_end - j);
  }

  return 1;
}


// This is a test method which will print out the matrix, so we can compare
// against Princeton's site to see if we're doing it right.
void ED::PrintMatrix()
{
  std::vector< std::vector<int> >::iterator a;
  std::vector<int>::iterator b;
  for(a = _matrix.begin(); a != _matrix.end(); a++)
  {
    for(b = (*a).begin(); b != (*a).end(); b++)
    {
      std::cout << *b << " ";
    }
    std::cout << "\n";
  }

}


// Returns the alignment
std::string ED::Alignment()
{
  // Here we should trace the matrix and find the string that displays
  // the actual alignment.

  return "h - 2\ne - 2\nl - 2\nl - 2\no - 2\nw - 2\no - 2\nr - 2\nl - 2\nd - 2\n";
}