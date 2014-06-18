#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generic_vector.h"
#include "mystring.h"
#include "dictionary.h"

// Tester program for the dictionary.c code

int main(int argc, char* argv[])
{
	GENERIC_VECTOR hVectofVect = NULL;		// Vector of Vector handle
	int x;

//	Info
	printf("Dictionary Program\n");
	
/*	Make the vector of a vector, using vector_of_vector_dictionary function.	
	This function will both initialize the vector of a vector and fill it with
	words of varying sizes from the dictionary.txt file.	*/
	hVectofVect = vector_of_vector_dictionary();

//	TESTING FRAMEWORK
//	Make sure the vectors of MYSTRING actually have MYSTRING objects in them.
	do{
		printf("What size string to look for? (-1 to quit) -> ");
		scanf("%d", &x);
		
		// Print given size MYSTRINGs
		if(x > 1 && x < 30)
		{
			print_vector(hVectofVect, x);
		}
		else if(x == -1)
		{
			printf("Thanks for using the DICTIONARY.C program!\n");
		}
		else
		{
			printf("Error - no MYSTRINGs the size of %d!\n", x);
		}
		
	}while(x != -1);

//	Make sure to destroy the VECTOR OF MYSTRINGs, which in turn should destroy
//	each individual MYSTRING VECTOR
	generic_vector_destroy(&hVectofVect);

//	SUCCESS
	return 0;
}
