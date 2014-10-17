// matrix.cpp
// Implementation file
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include "matrix.h"

using namespace std;

// Default constructor which puts 0's all throughout the matrix
Matrix::Matrix()
{
	// Put 0's throughout the matrix.
	for(int i = 0; i < 3; i++)
	{
		for(int x = 0; x < 3; x++)
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
	e[1][1] = d;
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
	
	00 01 02
	10 11 12
	20 21 22

	A = [ [0][0] [0][1] [0][2] ]
		[ [1][0] [1][1] [1][2] ]
		[ [2][0] [2][1] [2][2] ]

	|A| = a(ei - fh) - b(di - fg) + c(dh - eg)
	
	*/

	// Long forumula that calculates the determinate.
	int A = ( e[0][0] * ( (e[1][1] * e[2][2]) - (e[1][2] * e[2][1]) ) );
	int B = ( e[0][1] * ( (e[1][0] * e[2][2]) - (e[1][2] * e[2][0]) ) );
	int C = ( e[0][2] * ( (e[1][0] * e[2][1]) - (e[1][1] * e[2][0]) ) );
	int final = A - B + C;

	// Return the final determinant result.
	return final;
}

Matrix operator >>(istream& in, Matrix& trix)
{


}

Matrix operator <<(ostream& out, Matrix& trix)
{
	// Output the Matrix.
	for(int i = 0; i < 3; i++)
	{
		for(int x = 0; x < 3; x++)
		{
			outs << e[i][x];		// This double for loop should do the job nicely.
		}
		outs<<"\n";
	}
}


bool operator ==(const Matrix& one, const Matrix& two)
{


}


Matrix operator +(const Matrix& one, const Matrix& two)
{


}


Matrix operator -(const Matrix& one, const Matrix& two)
{


}


Matrix operator -(const Matrix& only)
{


}


Matrix operator *(const Matrix& one, const Matrix& two)
{


}
