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

  else if(a != b)
  { // not equal and no spaces
    return 1;
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
  int N = _string_one.length();
  int M = _string_two.length();

  // Create the Matrix
  /*
   * Quick note - it seems the vector of a vector of ints actually runs
   * like this:
   * ------------------> this is one vector
   * ------------------> another vector
   * ------------------> etc
   *
   * So each column is a vector of ints.
   * And the entire vector is a vector of a vector of ints.
   * With each vector inside the large vector pointing to vectors,
   * which are technically the columns.
   *
   * This is important for some of the math down below, which follows Princeton's
   * site but can get confusing due to how the vectors seem to be making themselves.
   *
   */
  for(i = 0; i <= M; i++)
  {
    std::vector<int> tmp;
    _matrix.push_back(tmp);

    // Now push '0's back into the given vector
    for(j = 0; j <= N; j++)
    {
      _matrix.at(i).push_back(0);
    }
  }

  // Start by filling out the bottom row
  for(i = 0; i <= M; i++)
  {
    // Very bottom row
    _matrix[i][N] = 2 * (M - i);
  }

  // Now fill out the side row.
  for(j = 0; j <= N; j++)
  {
    // Very right most column
    _matrix[M][j] = 2 * (N - j);
  }

  // Now that we have the initial sides, we can go ahead and calculate the rest
  // of the sub problems.
  for(i = M - 1; i >= 0; i--)
  {
    for(j = N - 1; j >= 0; j--)
    {
      // Using Princeton's formula, we can just calculate every single row!
      /*
       * Note - min of 3 numbers, which we must get from using the penalty method.
       *
       */
      int opt1 = _matrix[i+1][j+1] + penalty(_string_one[j], _string_two[i]);
      int opt2 = _matrix[i+1][j] + 2;
      int opt3 = _matrix[i][j+1] + 2;

      _matrix[i][j] = min(opt1, opt2, opt3);
    }
  }

  return _matrix[0][0];
}


// This is a test method which will print out the matrix, so we can compare
// against Princeton's site to see if we're doing it right.
void ED::PrintMatrix()
{
  std::cout << "Printing out the Matrix for debug purposes: \n\n";

  std::vector< std::vector<int> >::iterator a;
  std::vector<int>::iterator b;
  for(a = _matrix.begin(); a != _matrix.end(); a++)
  {
    for(b = (*a).begin(); b != (*a).end(); b++)
    {
      // Using std::right and setw(3) to align numbers to the right.
      // See the following stackoverflow post for an example:
      // https://stackoverflow.com/questions/8750853/how-to-conveniently-align-numbers-centrally-in-c-cout
      std::cout << std::right << std::setw(3) << *b << " ";
    }
    std::cout << "\n";
  }
}


// Returns the alignment
std::string ED::Alignment()
{
  // Here we should trace the matrix and find the string that displays
  // the actual alignment.

  // Let's declare a stringstream object to hold the string we want to return.
  std::ostringstream return_string;

  // Get N & M for going through the Matrix
  int N = _string_one.length();
  int M = _string_two.length();

  int i = 0, j = 0;

  // A while loop will work here since we want to move either diagonally, down or right.
  while(i <= M && j <= N)
  {
    int pen =  penalty(_string_one[j], _string_two[i]);
    int opt1 = _matrix[i+1][j+1] + pen;
    int opt2 = _matrix[i+1][j] + 2;
    int opt3 = _matrix[i][j+1] + 2;

    // Move diagonally
    if(_matrix[i][j] == opt1)
    {
      return_string << _string_one[i] << " " << _string_two[j] << " "  >> pen;
      i++;
      j++;
    }

    // Move down
    else if(_matrix[i][j] == opt2)
    {
      return_string << _string_one[i] << " -" << " 2";
      i++;
    }

    // Move right
    else if(_matrix[i][j] == opt3)
    {
      return_string << "- " << _string_two[j] << " 2";
      j++;
    }
  }


  return "h - 2\n";
}

