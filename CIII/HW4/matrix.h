// matrix.h
// Header file

#ifndef MATRIX_H
#define MATRIX_H

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
		void output(ostream& outs) const;

	private:
		// Member variables
		const static int n = 3;		
		int e[n][n];				// nxn array of integers, where n is equal to 3.
};

#endif