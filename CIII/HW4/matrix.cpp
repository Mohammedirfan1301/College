// matrix_app.cpp
// Application file
#include <iostream>
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
            in >> trix.e[i][x];        // This double for loop should do the job nicely.
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
        for(int x = 0; x < 3; x++)
        {
            out << trix.e[i][x];        // This double for loop should do the job nicely.
        }
        out<<"\n";
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
                cout<<"THE TWO MATRIXES ARE NOT EQUAL.\n\n";
                return false;
            }
        }

    }

    // If we get here, then matrix one is equal to matrix two.
    cout<<"THE TWO MATRIXES ARE EQUAL.\n\n";
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

    //return temp;
    return *this;       // Return the temp object. this  is just a pointer to the object we worked on.
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

    // Return the object.
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

    // Return this object.
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

    // Return this object.
    return temp;
}


// Multiple two matrixes
Matrix operator *(const Matrix& one, const Matrix& two)
{
    // Object to hold the addition.
    Matrix temp;

    // Multiply 3x3 matrixes. Using 3 loops we can do it.
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

    return temp;
}


int main()
{
    ifstream in_stream;
    ofstream out_stream;

    in_stream.open("inputfile.txt");
    if ( in_stream.fail() )
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    out_stream.open("outputfile.txt");
    if ( out_stream.fail() )
    {
        cout << "Output file opening failed.\n";
        exit(1);
    }


    /*
    Matrix Z - Matrix with all 0's, output this to the screen.
    Matrix E - diagonal matrix with 1 on the main diagonal, 0's everywhere else. Output E.
    Matrix D - diagonal matrix with 2 on the main diagonal, 0's everywhere else. Output D.
    Matrix A - elements inputted from a file, output A.
    Matrix B - a copy of A. Check that B == A using the == operator.
    */

    Matrix Z;
    cout<<"Z: \n"<<Z<<"\n";

    Matrix E(1);
    cout<<"E: \n"<<E<< "\n";

    Matrix D(2);
    cout<<"D: \n"<<D<< "\n";

    // A needs to be inputted from a file. Then output A.
    Matrix A;
    in_stream >> A;
    out_stream << A;             // Testing the output to a file function.
    cout<<"A: \n"<<A<< "\n";     // Also testing it via standard IO.

    // B needs to be a copy of A, and need to check that B == A using ==.
    Matrix B=A;
    B == A;

    cout<<"A: \n"<<A<<"\n";     // Also testing it via standard IO.
    cout<<"B: \n"<<B<<"\n";     // Also testing it via standard IO.

    // A+D
    cout<<"A+D:\n"<<A+D<<endl;
    
    // A-D
    cout<<"A-D:\n"<<A-D<<endl;

    // A*D
    cout<<"A*D:\n"<<A*D<<endl;

    // A-B==Z
    A-B==Z;

    // -A==Z-A
    -A==Z-A;

    // A+B==A*D
    A+B==A*D;

    // A*E==A
    A*E==A;

    // A*D==2*A
    A*D==2*A;

    // Compute the determinants of E and D
    cout<<"Computing determinants: \n";
    cout<<"E: "<<E.det()<<"\n";
    cout<<"D: "<<D.det()<<"\n\n";
    
    // Create C from inputed file.
    Matrix C;
    in_stream >> C;
    out_stream << C;
    cout<<"C: \n"<<C;

    cout<<"\nCHECK THE FOLLOWING DETERMINANT: \n";
    //cout<<"(A*C).det()==A.det()*C.det()"<<((A*C).det())==(A.det()*C.det());

    return 0;
}