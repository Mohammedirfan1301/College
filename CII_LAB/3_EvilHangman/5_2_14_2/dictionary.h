#include "status.h"
#include "generic_vector.h"
#include "mystring.h"

#ifndef DICTIONARY_H
#define DICTIONARY_H

/* 	This function will return a vector of a vector of mystrings. It will have 29 such
	vectors of mystrings, each containing a bunch of words of a certain type.	 */
GENERIC_VECTOR vector_of_vector_dictionary(void);

/*	This function will return a vector of a mystrings, of a certain size word that
	can be determined by the user. Ex: User calls this function with int size = 5,
	this function returns a vector of a mystring with size 5 words within it.	 */
GENERIC_VECTOR vector_of_mystring_at(GENERIC_VECTOR hVectofVect, int index);

// File worker functions
void work_file(FILE* text, GENERIC_VECTOR hVectofVect);

// Tester function
void print_vector(GENERIC_VECTOR hVectofVect, int index);

// fTerminate function
int acceptLineInput(char ch, int * pbDiscardChar);

#endif
