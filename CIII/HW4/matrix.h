// matrix.h
// Header file

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	public:

		// Member variables
		int e[3][3];		// nxn array of integers, where n is equal to 3.

		// Member functions
		Matrix();		// Default constructor, matrix elements = 0.
		Matrix(int d);	// Constructor making diagonal matrix. 
						// (d's on main diagonal, 0's everywhere else.)
		int det();		// Function which computes the determinant of a matrix.
						// Determinant for a 3x3 matrix is:
		/*
			A = [ a b c ]
				[ d e f ]
				[ g h i ]
			
			|A| = a(ei - fh) - b(di - fg) + c(dh - eg)

			Make sure to just apply the above formula.
		*/

		// Also need to do a bunch of overloaded functions.
		// Such as:
		/*

		<< and >> are operators for file/console I/O
		A==B if for all i,j: A.e[i][j]==B.e[i][j] 
		B=-A means that for all i,j: B.e[i][j]=-A.e[i][j];
		C=A+B means for all i,j: C.e[i][j]= A.e[i][j]+B.e[i][j];
		C=A-B means for all i,j: C.e[i][j]= A.e[i][j]-B.e[i][j];
		C=A*B means for all i,j: C.e[i][j]= i-th row of A * j-th column of B=sum for k of (A.e[i][k]*B.e[k][j]) for k from 0 to 2.

		*/
		/*
		friend Money operator +(const Money& amount1, const Money& amount2);
    	friend Money operator -(const Money& amount1, const Money& amount2);
    	friend Money operator -(const Money& amount);
    	friend bool operator ==(const Money& amount1, const Money& amount2);
		*/

/*
		istream& Matrix operator >>(istream& in, Matrix& trix);
		ostream& Matrix operator <<(ostream& out, Matrix& trix);
		bool operator ==(const Matrix& one, const Matrix& two);
		Matrix operator +(const Matrix& one, const Matrix& two);
		Matrix operator -(const Matrix& one, const Matrix& two);
		Matrix operator -(const Matrix& only);
		Matrix operator *(const Matrix& one, const Matrix& two);
*/

	private:

		// Does anything need to be private?

};

#endif