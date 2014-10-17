// matrix_app.cpp
// Application file
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
//#include "matrix.h"

using namespace std;

// Class for all the Matrix stuff
class Matrix
{
	public:
		// Member functions

		// Default constructor, matrix elements = 0.
		Matrix();		

		// Constructor making diagonal matrix. (d's on main diagonal, 0's everywhere else.)
		Matrix(int d);	
						
		// Function which computes the determinant of a matrix.
		int det();		
						
		// Overloaded operators
		//friend istream& Matrix operator >>(istream& in, Matrix& trix);
		//friend ostream& Matrix operator <<(ostream& out, Matrix& trix);
		friend bool operator ==(const Matrix& one, const Matrix& two);
		friend Matrix operator +(const Matrix& one, const Matrix& two);
		friend Matrix operator -(const Matrix& one, const Matrix& two);
		friend Matrix operator -(const Matrix& only);
		friend Matrix operator *(const Matrix& one, const Matrix& two);

		// Test function!
		void output();

	private:
		// Member variables
		const static int n = 3;		
		int e[n][n];				// nxn array of integers, where n is equal to 3.
};


// Default constructor which puts 0's all throughout the matrix
Matrix::Matrix()
{
	// Put 0's throughout the matrix.
	for(int i = 0; i < n; i++)
	{
		for(int x = 0; x < n; x++)
		{
			e[i][x] = 0;		// This double for loop should do the job nicely.
		}
	}
}

// Constructor which creates a diagonal matrix with d's on the diagonal
// And 0's everywhere else.
Matrix::Matrix(int d)
{
	/*
		1 0 0
		0 1 0
		0 0 1
	*/

	// Set the diagonals equal to d.
	e[0][0] = d;
	e[0][1] = 0;
	e[0][2] = 0;
	e[1][0] = 0;
	e[1][1] = d;
	e[1][2] = 0;
	e[2][0] = 0;
	e[2][1] = 0;
	e[2][2] = d;
}


// Function which computes the determinant of a matrix.
int Matrix::det()
{
	// Since we are dealing with a 3x3 Matrix, this formula can be useful:
	/* 

			A = [ a b c ]
				[ d e f ]
				[ g h i ]

	it could also be written like:
	
	[ 00 01 02 ]
	[ 10 11 12 ]
	[ 20 21 22 ]

	A = [ [0][0] [0][1] [0][2] ]
		[ [1][0] [1][1] [1][2] ]
		[ [2][0] [2][1] [2][2] ]

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

/*
Matrix operator >>(istream& in, Matrix& trix)
{
	;

}

Matrix operator <<(ostream& out, Matrix& trix)
{
	/*
	// Output the Matrix.
	for(int i = 0; i < 3; i++)
	{
		for(int x = 0; x < 3; x++)
		{
			outs << e[i][x];		// This double for loop should do the job nicely.
		}
		outs<<"\n";
	}
	*/
//}


// Temp output function
void Matrix::output()
{
	// Output all the values in the matrix.
	for(int i = 0; i < n; i++)
	{
		for(int x = 0; x < n; x++)
		{
			cout<<e[i][x];		// This double for loop should do the job nicely.

			//cout<<"i is "<<i<<endl;
			//cout<<"x is "<<x<<endl;
		}
		cout<<"\n";
	}
}


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
				return false;
			}
		}

	}

	// If we get here, then matrix one is equal to matrix two.
	return true;
}


Matrix operator +(const Matrix& one, const Matrix& two)
{
	// Object to hold the addition.
	Matrix temp;

	for (int i = 0; i < temp.n; i++)
	{
		for (int x = 0; x < temp.n; x++)
		{
			// Add all the matrix spots into temp's matrix e.
			temp.e[i][x] = one.e[i][x] + two.e[i][x];
		}

	}

	// Return this object.
	return temp;
}


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


Matrix operator *(const Matrix& one, const Matrix& two)
{
	// Object to hold the addition.
	Matrix temp;

	//temp.e[i][j] = one.e[i][k] * two.e[k][j]; 	// From k = 0 to 2.

	/* 

	0, 1, 2 for i
	0, 1, 2 for j
	0, 1, 2 for k

	
	

	*/

	for (int i = 0; i < temp.n; i++)
	{
		for (int x = 0; x < temp.n; x++)
		{

			// Multiply all the matrix spots into temp's matrix e.
			temp.e[i][x] = one.e[i][x] * two.e[i][x];
		}

	}

	// Return this object.
	return temp;
}


int main()
{
	
	// Need to test a bunch of stuff:

	/*
	Matrix Z - Matrix with all 0's, output this to the screen.
	Matrix E - diagonal matrix with 1 on the main diagonal, 0's everywhere else. Output E.
	Matrix D - diagonal matrix with 2 on the main diagonal, 0's everywhere else. Output D.
	Matrix A - elements inputted from a file, output A.
	Matrix B - a copy of A. Check that B == A using the == operator.

	Compute and output the following to the screen:
	A + D
	A - D
	A * D

	Check with == that
	A-B == Z
	-A == Z-A
	A+B == A*D
	A*E = A
	A*D = 2*A

	Compute the determinants of E and D (should = 1 and 8?)

	Create C with the elements inputted from file (uh, what? Again? Ok...)

	check the following property of the determinant: 
	(A*C).det() == A.det()*C.det()

	THEN YOU ARE DONE AND CAN SUBMIT THIS STUFF.

	*/

	Matrix Z(1);

	cout<<"OUTPUTTING THE DIAGONAL FUNCTION: \n";
	Z.output();

	Matrix a;

	cout<<"\n\nOUTPUTTING JUST THE DEFAULT CONSTRUCTOR: \n";
	a.output();


	//ifstream in_stream;
	//ofstream out_stream;

	// Output this to screen.
	//cout << Z;


	return 0;
}