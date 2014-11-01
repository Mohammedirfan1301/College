#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cctype>

using namespace std;

// Class for all the Matrix stuff
class Matrix
{
    public:

        // Default constructor, creates 3x3 matrix with elements = 0.
        Matrix();

        // Default constructor, creates n by m matrix with elements = 0.
        Matrix(int _m, int _n);

        // Constructor, creates n by m matrix with elements on the diagonal = d, elsewhere = 0.
        Matrix(int _m, int _n, int d);

        // Function which computes the determinant of a matrix. (EXTRA CREDIT)
        // int det();

        // Overloaded operators
        friend istream& operator >>(istream& in, Matrix& trix);
        friend ostream& operator <<(ostream& out, const Matrix& trix);
        friend bool operator ==(const Matrix& one, const Matrix& two);
        Matrix& operator=(const Matrix& trix);
        friend Matrix operator +(const Matrix& one, const Matrix& two);
        friend Matrix operator -(const Matrix& one, const Matrix& two);
        friend Matrix operator -(const Matrix& only);
        friend Matrix operator *(const Matrix& one, const Matrix& two);

    private:

        // Member variables
        int n, m;                   // Dimensions of the matrix
        int** e;                     // nxm array of integers, where n is equal to 3.
};


// Default constructor which puts 0's all throughout the matrix
Matrix::Matrix()
{
    m = 3;
    n = 3;
    e = new(nothrow) int*[m];       // Allocate the array of pointers.

    // Make sure the memory allocated! If it didn't, print an error.
    if(e == NULL) {
        cout << "Error: memory could not be allocated.\n";
        return;
    }

    for(int i = 0; i < m; i++)
    {
        e[i] = new(nothrow) int[n];     // This will allocate each individual array.

        // Make sure the memory allocated! If it didn't, print an error!
        if(e[i] == NULL) {
            cout << "Error: memory could not be allocated.\n";
            return;
        }
    }

    // Put 0's throughout the matrix.
    for(int i = 0; i < n; i++)
    {
        for(int x = 0; x < m; x++)
        {
            e[i][x] = 0;        // This double for loop should do the job nicely.
        }
    }
}


// Default constructor, creates n by m matrix with elements = 0.
Matrix::Matrix(int _m, int _n)
{
    n = _n;
    m = _m;
    e = new(nothrow) int*[m];       // Allocate the array of pointers.

    // Make sure the memory allocated! If it didn't, print an error.
    if(e == NULL) {
        cout << "Error: memory could not be allocated.\n";
        return;
    }

    for(int i = 0; i < m; i++)
    {
        e[i] = new(nothrow) int[n];     // This will allocate each individual array.

        // Make sure the memory allocated! If it didn't, print an error!
        if(e[i] == NULL) {
            cout << "Error: memory could not be allocated.\n";
            return;
        }
    }

    // Put 0's throughout the matrix.
    for(int i = 0; i < n; i++)
    {
        for(int x = 0; x < m; x++)
        {
            e[i][x] = 0;        // This double for loop should do the job nicely.
        }
    }
}


// Constructor, creates n by m matrix with elements on the diagonal = d, elsewhere = 0.
Matrix::Matrix(int _m, int _n, int d)
{
    n = _n;
    m = _m;
    e = new(nothrow) int*[m];       // Allocate the array of pointers.

    // Make sure the memory allocated! If it didn't, print an error.
    if(e == NULL) {
        cout << "Error: memory could not be allocated.\n";
        return;
    }

    for(int i = 0; i < m; i++)
    {
        e[i] = new(nothrow) int[n];     // This will allocate each individual array.

        // Make sure the memory allocated! If it didn't, print an error!
        if(e[i] == NULL) {
            cout << "Error: memory could not be allocated.\n";
            return;
        }
    }

    // Put 0's throughout the matrix, except for the diagonals.
    for(int i = 0; i < n; i++)
    {
        for(int x = 0; x < m; x++)
        {
            if(i == x) 
            {   // When i equals x, it's a diagonal.
                e[i][x] = d;
            }
            else        
            {   // When they aren't equal, make it 0.
                e[i][x] = 0;
            }
        }
    }
}


// Input function from either a file or standard IO
istream& operator >>(istream& in, Matrix& trix)
{
    // Input the Matrix.
    for(int i = 0; i < trix.n; i++)
    {
        for(int x = 0; x < trix.m; x++)
        {
            in >> trix.e[i][x];       // >> will redirect the input to the 3x3 array.
        }
    }

    return in;
}


// Output function to either a file or standard IO
ostream& operator <<(ostream& out, const Matrix& trix)
{
    // Output the Matrix.
    for(int i = 0; i < trix.n; i++)
    {
        out << "    ";                    // Tabs make output look pretty.

        for(int x = 0; x < trix.m; x++)
        {
            out << setw(6) << right;      // Make the output look pretty.
            out << trix.e[i][x];          // << will redirect the output to the output stream.
        }

        out << "\n";                      // More pretty.
    }

    return out;
}


// Checks to see if two matrices are equal to each other.
// Returns true if they are, otherwise it returns false.
bool operator ==(const Matrix& one, const Matrix& two)
{
    Matrix temp;

    // First make sure the two matrixes are the same size.
    // n and m should be the same for one and two
    if( (one.n != two.n) || (one.m != two.m) )
    {
        // Either n wasn't the same, m wasn't the same 
        // or both were not the same.
        // Therefor they are not equal matrixes.
        cout << "False.\n";
        return false;
    }

    for(int i = 0; i < one.n; i++)
    {
        for(int x = 0; x < one.m; x++)
        {
            // If one spot is not equal, then the
            // two matrices are not equal to each other.
            if(one.e[i][x] != two.e[i][x])
            {
                cout << "False.\n";
                return false;
            }
        }
    }

    // If we get here, then matrix one is equal to matrix two.
    cout << "True.\n";
    return true;
}


// Copies a matrix
Matrix& Matrix::operator=(const Matrix& trix)
{
    Matrix temp(trix.n, trix.m);        // Call the default construct with trix's dimensions.

    // Go through and copy every int over to temp.
    for(int i = 0; i < temp.n; i++)
    {
        for(int x = 0; x < temp.m; x++)
        {
            // Copy the right matrix into the left matrix.
            temp.e[i][x] = trix.e[i][x];
        }
    }

    // Return the temp object. this is just a pointer to the object we worked on.
    return *this;
}


// Adds the two matrices.
Matrix operator +(const Matrix& one, const Matrix& two)
{
    // First make sure the two matrixes are the same size.
    // n and m should be the same for one and two
    if( (one.n != two.n) || (one.m != two.m) )
    {
        // Either n wasn't the same, m wasn't the same 
        // or both were not the same.
        // Therefor they are not equal matrixes.
        cout << "Couldn't add the two matrixes, as they were not equal.\n";
        return one;
    }

    Matrix temp(one.n, one.m);        // Call the default construct with one's dimensions.

    for (int i = 0; i < temp.n; i++)
    {
        for (int x = 0; x < temp.m; x++)
        {
            // Add all the matrix spots into temp's matrix e.
            temp.e[i][x] = one.e[i][x] + two.e[i][x];
        }
    }

    // Return a copy of this object.
    return temp;
}


// Binary "-" operator, subtracts two matrices.
Matrix operator -(const Matrix& one, const Matrix& two)
{
    // First make sure the two matrixes are the same size.
    // n and m should be the same for one and two
    if( (one.n != two.n) || (one.m != two.m) )
    {
        // Either n wasn't the same, m wasn't the same 
        // or both were not the same.
        // Therefor they are not equal matrixes.
        cout << "Couldn't add the two matrixes, as they were not equal.\n";
        return one;
    }

    Matrix temp(one.n, one.m);        // Call the default construct with one's dimensions.

    for (int i = 0; i < temp.n; i++)
    {
        for (int x = 0; x < temp.n; x++)
        {
            // Subtract all the matrix spots into temp's matrix e.
            temp.e[i][x] = one.e[i][x] - two.e[i][x];
        }
    }

    // Return a copy of this object.
    return temp;
}


// Unary "-" operator, just negates whatever it is given.
Matrix operator -(const Matrix& only)
{
    // Object to hold the addition.
    Matrix temp(only.n, only.m);

    for (int i = 0; i < temp.n; i++)
    {
        for (int x = 0; x < temp.n; x++)
        {
            // Add all the matrix spots into temp's matrix e.
            temp.e[i][x] = -only.e[i][x];
        }
    }

    // Return a copy of this object.
    return temp;
}


// THIS ONE HASN'T BEEN STARTED, WILL DO LATER.
// Multiple two matrices
Matrix operator *(const Matrix& one, const Matrix& two)
{
    Matrix temp;

    // Multiply 3x3 matrices. Using 3 loops will do it.
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                   temp.e[i][j] += one.e[i][k] * two.e[k][j];
            }
        }
    }

    // Return a copy of this object.
    return temp;
}


int main()
{
    ifstream in_stream;
    ofstream out_stream;

    // Open up the file input and output streams.
    in_stream.open("inputfile.txt");
    if ( in_stream.fail() )
    {
        cout << "Input file opening failed.\n";     // Make sure to quit
        exit(1);                                    // if there is an error.
    }

    out_stream.open("outputfile.txt");
    if ( out_stream.fail() )
    {
        cout << "Output file opening failed.\n";    // Should also print out an
        exit(1);                                    // error message for the user.
    }

    // 3x3 Matrix with all zeroes, basically the default constructor with no parameters.
    Matrix Z3;      

    // Output it to the screen.
    cout << Z3;

    // Finally done. ^^
    return 0;
}