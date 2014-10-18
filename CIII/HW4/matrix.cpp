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

        // Default constructor, matrix elements = 0.
        Matrix();

        // Constructor making diagonal matrix. (d's on main diagonal, 0's everywhere else.)
        Matrix(int d);

        // Function which computes the determinant of a matrix.
        int det();

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
        const static int n = 3;
        int e[n][n];                // nxn array of integers, where n is equal to 3.
};


// Default constructor which puts 0's all throughout the matrix
Matrix::Matrix()
{
    // Put 0's throughout the matrix.
    for(int i = 0; i < n; i++)
    {
        for(int x = 0; x < n; x++)
        {
            e[i][x] = 0;        // This double for loop should do the job nicely.
        }
    }
}


// Constructor which creates a diagonal matrix with d's on the diagonal
// And 0's everywhere else.
Matrix::Matrix(int d)
{
    // Set the diagonals equal to d.
    for(int i = 0; i < n; i++)
    {
        for(int x = 0; x < n; x++)
        {
            if(i == x)  // When i equals x, it's a diagonal.
            {
                e[i][x] = d;
            }
            else        // When they aren't equal, make it 0.
            {
                e[i][x] = 0;
            }
        }
    }
}


// Function which computes the determinant of a matrix.
int Matrix::det()
{
    /*
    Since we are dealing with a 3x3 Matrix, this formula can be useful:

    |A| = a(ei - fh) - b(di - fg) + c(dh - eg)
    */

    // Long forumula that calculates the determinate.
    int A = ( e[0][0] * ( (e[1][1] * e[2][2]) - (e[1][2] * e[2][1]) ) );
    int B = ( e[0][1] * ( (e[1][0] * e[2][2]) - (e[1][2] * e[2][0]) ) );
    int C = ( e[0][2] * ( (e[1][0] * e[2][1]) - (e[1][1] * e[2][0]) ) );
    int determinant = A - B + C;

    // Return the final determinant result.
    return determinant;
}


// Input function from either a file or standard IO
istream& operator >>(istream& in, Matrix& trix)
{
    // Input the Matrix.
    for(int i = 0; i < 3; i++)
    {
        for(int x = 0; x < 3; x++)
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
    for(int i = 0; i < 3; i++)
    {
        out << "\t";                    // Tabs make output look pretty.

        for(int x = 0; x < 3; x++)
        {
            out << trix.e[i][x];        // << will redirect the output to the output stream.
            out << setw(4) << right << "\t";     // Make the output look pretty.
        }

        out<<"\n";                      // More pretty.
    }

    return out;
}


// Checks to see if two matrixes are equal to each other.
// Returns true if they are, otherwise it returns false.
bool operator ==(const Matrix& one, const Matrix& two)
{
    Matrix temp;

    for(int i = 0; i < temp.n; i++)
    {
        for(int x = 0; x < temp.n; x++)
        {
            // If one spot is not equal, then the
            // two matrixes are not equal to each other.
            if(one.e[i][x] != two.e[i][x])
            {
                cout<<"False.\n";
                return false;
            }
        }

    }

    // If we get here, then matrix one is equal to matrix two.
    cout<<"True.\n";
    return true;
}


// Copies a matrix
Matrix& Matrix::operator=(const Matrix& trix)
{
    Matrix temp;

    for(int i = 0; i < 3; i++)
    {
        for(int x = 0; x < 3; x++)
        {
            // Copy the right matrix into the left matrix.
            temp.e[i][x] = trix.e[i][x];
        }
    }

    // Return the temp object. this is just a pointer to the object we worked on.
    return *this;       
}


// Adds the two matrixes.
Matrix operator +(const Matrix& one, const Matrix& two)
{
    Matrix temp;

    for (int i = 0; i < 3; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            // Add all the matrix spots into temp's matrix e.
            temp.e[i][x] = one.e[i][x] + two.e[i][x];
        }

    }

    // Return a copy of this object.
    return temp;
}


// Binary "-" operator, subtracts two matrixes.
Matrix operator -(const Matrix& one, const Matrix& two)
{
    // Object to hold the addition.
    Matrix temp;

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
    Matrix temp;

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


// Multiple two matrixes
Matrix operator *(const Matrix& one, const Matrix& two)
{
    // Object to hold the addition.
    Matrix temp;

    // Multiply 3x3 matrixes. Using 3 loops will do it.
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


    // Testing class Matrix, its functions and its operators.
    Matrix Z;
    cout << "Z: \n" << Z << "\n";       
                                        
    Matrix E(1);
    cout << "E: \n" << E << "\n";

    Matrix D(2);
    cout << "D: \n" << D << "\n";

    Matrix A;
    in_stream >> A;
    out_stream << A;                    // Testing the output to a file function.
    cout << "A: \n" << A << "\n";       // Also testing it via standard IO.

    Matrix B=A;
    cout<<"A == B: ";
    B == A;

    cout << "\nA: \n" << A << "\n";       // Also testing it via standard IO.
    cout << "B: \n" << B << "\n";       // Also testing it via standard IO.


    // Compute and output to the screen the following matrices
    cout << "A+D:\n" << A+D << endl;
    cout << "A-D:\n" << A-D << endl;
    cout << "A*D:\n" << A*D << endl;


    // Checking the following with ==
    cout << "A - B == Z: ";
    A-B==Z;

    cout << "-A == Z - A: ";
    -A==Z-A;

    cout << "A + B == A * D: ";
    A+B==A*D;

    cout << "A * E == A: ";
    A*E==A;

    cout << "A * D == 2 * A: ";
    A*D==2*A;


    // Computing the determinants of E and D, 
    // where E should equal 1 and D should equal 8.
    cout << "\nComputing determinants for E & D: \n";
    cout << "Determinant of E: " << E.det() << "\n";
    cout << "Determinant of D: " << D.det() << "\n\n";
    

    // Create C from inputed file.
    Matrix C;
    in_stream >> C;
    out_stream << C;
    cout << "C: \n" << C;


    // Need to check the following property of the determinant.
    cout << "\nCHECK THE FOLLOWING DETERMINANT: \n";
    cout << "(A*C).det()==A.det()*C.det(): ";
    A*C.det()==A.det()*C.det();


    // Finally done. ^^
    return 0;
}