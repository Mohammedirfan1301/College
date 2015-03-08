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
  int string1_end = _string_one.length() + 1;
  int string2_end = _string_two.length() + 1;

  // Reserve space in the matrix
  

  // Need to count backwards for the rows
  j = string2_end;

  // Start by filling out the bottom row
  for(i = 0; i < string1_end; i++)
  {
    // Very bottom row
    _matrix[string1_end][i] = j * (string2_end + 1);
    j--;
  }

  // Samething for the right most column, need to count backwards
  i = string1_end;

  // Now fill out the side row.
  for(j = 0; j < string2_end; j++)
  {
    // Very right most column
    _matrix[j][string2_end] = i * (string1_end + 1);
    i--;
  }

  return 1;
}


// This is a test method which will print out the matrix, so we can compare
// against Princeton's site to see if we're doing it right.
void ED::PrintMatrix()
{
  std::vector< std::vector<std::string> >::iterator a;
  std::vector<std::string>::iterator b;
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