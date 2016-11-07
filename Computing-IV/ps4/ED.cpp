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
  std::cout << "\n\nPrinting out the Matrix for debug purposes: \n\n";

  // Iterator the large vector
  std::vector< std::vector<int> >::iterator a;

  // Iterator to each vector of integers.
  std::vector<int>::iterator b;

  for(a = _matrix.begin(); a != _matrix.end(); a++)
  {
    for(b = (*a).begin(); b != (*a).end(); b++)
    {
      // Using std::right and setw(3) to align numbers to the right.
      // See the stackoverflow post in the README for an example
      std::cout << std::right << std::setw(3) << *b << " ";
    }
    std::cout << "\n";
  }
}


// Returns the alignment
// Here we should trace the matrix and find the string that displays the actual alignment.
std::string ED::Alignment()
{
  // Let's declare a stringstream object to hold the string we want to return.
  std::ostringstream return_string;

  // Get M & N for going through the Matrix
  // NOTE: I use standard MxN Matrix notation - that is,
  // M is the number of rows, N is the number of columns.
  int M = _string_two.length();
  int N = _string_one.length();

  // I left in some debugging stuff for future reference.
  // NOTE: Rows are represented by the first vector "of vectors",
  // while columns are the vectors of ints inside the main vector.
//   std::cout << "M = " << M << "\n";
//   std::cout << "N = " << N << "\n";
//
//   std::cout << "Row = " << _matrix.size() << "\n";
//   std::cout << "Col = " << _matrix.at(0).size() << "\n";

  int i = 0, j = 0;
  int pen, opt1, opt2, opt3;
  std::string ret_str;

  // More debug stuff to check where the code is heading.
//   std::cout << "We want: " << _matrix[M-1][N-1] << "\n";

  // A while loop will work here since we want to move either diagonally, down or right.
  while(i < M || j < N) // Need to run until we hit the far bottom right corner!
  {
    // More test stuff.
//     std::cout << "i = " << i << "\nj = " << j << "\n";
//     std::cout << "mat is: " << _matrix[i][j] << "\n";

    // Checking vector bounds with try/catch
    try{
      pen =  penalty(_string_one[j], _string_two[i]);
      opt1 = _matrix.at(i+1).at(j+1) + pen;
    }
    catch(const std::out_of_range& error)
    {
      // out of range
      opt1 = -1;
    }
    try{
      opt2 = _matrix.at(i+1).at(j) + 2;
    }catch(const std::out_of_range& error)
    {
      // out of range
      opt2 = -1;
    }
    try{
      opt3 = _matrix.at(i).at(j+1) + 2;
    }catch(const std::out_of_range& error)
    {
      // out of range
      opt3 = -1;
    }

    // Move diagonally
    if(_matrix[i][j] == opt1)
    {
      return_string << _string_one[j] << " " <<  _string_two[i] << " "  << pen << "\n";
      i++;
      j++;
    }

    // Move down
    else if(_matrix[i][j] == opt2)
    {
      return_string << "- " << _string_two[i] << " 2\n";
      i++;
    }

    // Move right
    else if(_matrix[i][j] == opt3)
    {
      return_string << _string_one[j] << " -" << " 2\n";
      j++;
    }
  }

  // Get the string from the ostringstream object & return it.
  ret_str = return_string.str();
  return ret_str;
}
