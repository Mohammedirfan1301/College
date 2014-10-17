// matrix.cpp
// Implementation file
#include <iostream>
#include "matrix.h"

using namespace std;

// Default constructor which puts 0's all throughout the matrix
void Matrix::Matrix()
{
	// Put 0's throughout the matrix.
	for(int i = 0; i < 3; i++)
	{
		for(x = 0; x < 3; x++)
		{
			e[i][x] = 0;		// This double for loop should do the job nicely.
		}
	}
}

// Constructor which creates a diagonal matrix with d's on the diagonal
// And 0's everywhere else.
void Matrix::Matrix(int d)
{

}

// Function which computes the determinant of a matrix.
int Matrix::Det()
{
	// Since we are dealing with a 3x3 Matrix, this formula can be useful:
	/* 

			A = [ a b c ]
				[ d e f ]
				[ g h i ]

	it could also be written like:

	A = [ 0 1 2 ]
		[ 1 2 3 ]
		[ 2 3 4 ]

	|A| = a(ei - fh) - b(di - fg) + c(dh - eg)
	
	*/


}