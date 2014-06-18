#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generic_vector.h"
#include "mystring.h"

// Initialize functions
//GENERIC_VECTOR make_vector_of_vector(void);
GENERIC_VECTOR make_vector_of_mystring(void);

// File worker functions
void work_file(FILE* text, GENERIC_VECTOR hVector);

// Tester function
void print_vector(GENERIC_VECTOR hVectofStr);

// Assignment / Destroy functions
void assign_vector_of_vector(void** hVectVect, void* hVector);
void destroy_vector_of_vector(void** hVector);
void destroy_vector_of_mystring(void** hVectString);

// Assignment/Destroy functions which are located in mystring.c
void assign_vector_of_mystring(void** left, void* right);
void mystring_destroyer(void** hString);

// fTerminate function
int acceptLineInput(char ch, int * pbDiscardChar);

// Index would be from 0 - 22, assuming completed vector of a vector code.
//int access_vector_of_vector(int index);	

//	I use TRUE / FALSE in a few functions to represent "0" and "1"
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[])
{
	FILE* text;
	GENERIC_VECTOR hVectofStr = NULL;

	printf("Dictionary Program\n");
	
//	Open the dictionary file in "read" mode
	text = fopen("dictionary.txt", "r");
	
//	Check the FILE pointer
	if(text == NULL)
	{
		printf("Error - failed to open dictionary.txt!\n");
		return 0;
	}
	
/*	FUTURE: 
	create a vector of vectors.
	
	
*/	
	
//	Start by only looking for words of length 4.
	printf("Finding words of length 4 as a test: \n");
	
//	Initialize a vector of mystrings.
	hVectofStr = make_vector_of_mystring();

//	See if it succeeded or not.
	if(hVectofStr == NULL)
	{
	// 	Something failed, quit with an error
		printf("Error - failed to init. vector!\n");
		return 0;
	}
	
// 	Otherwise, continue...
	work_file(text, hVectofStr);
	
//	Test what we got from work_file - see if there are strings stored in the vector!
	print_vector(hVectofStr);
	
//	Close the file	
	fclose(text);
	
//	Destroy the vector of mystrings
//	Call vector destroy, which should go through and destroy any MYSTRING objects.
//   destroy_vector_of_vector( ... );
//	

//	SUCCESS
	return 0;
}

GENERIC_VECTOR make_vector_of_mystring(void)
{
	GENERIC_VECTOR temp;				// temp ptr to GEN VECTOR
	Generic_vector_functions functions;	// ptr to functions struct
		
	// Set the function pointers equal to their respected functions.
	functions.assignment = mystring_assignment;
	functions.destructor = mystring_destroyer;
	
	// Initialize the Vector, send it the functions ptr as well!
	temp = generic_vector_init_default(functions);
	
	// Check to see it initialized!
	if(temp == NULL)
		return NULL;
	
	// Return the pointer to the vector if it exists.
	return temp;
}


void work_file(FILE* text, GENERIC_VECTOR hVector)
{
	MyString_Status 	code;
	Status			test;
	MYSTRING hString = NULL;
	int (*fTerminate)(char, int*);
	fTerminate = &acceptLineInput;
	char c;

	do{
		hString = mystring_init_default();
		
	//	See if hString initialized.
		if(hString != NULL)
		{
		//	Get one char from the file & put it back. This is to test for EOF.
			c = fgetc(text);
			ungetc(c, text);
			
		//	Call input using a MS obj, text (FP), and fTerminate (newline)
			code = mystring_input(hString, text, 0, fTerminate);
			
			if(code == MYSTRING_STATUS_SUCCESS)
			{
				// Add to generic vector. First test - only 4 char words.
				if(mystring_size(hString) == 4)
				{
				//	Add hString to hVector
					test = generic_vector_push_back(hVector, hString);
					
				//	See if it worked.
					if(test == FAILURE)
					{
						printf("ERROR: failed to add MYSTRING to vect of MYSTRING...\n");
					}
				}
				
				// Other wise don't (YET)
			}
			else{
				// Don't add - stop, we had a problem.
				printf("Error - couldn't get success from mystring_input!\n");
				return;
			}
		}
		else{
		//	Something failed when allocating the mystring object.
			printf("Error - failed to initialize mystring!\n");
			return;
		}
		
	}while(c != EOF);
	
	return;
}


int acceptLineInput(char ch, int * pbDiscardChar)
{
//	See if we have a newline
	if(ch == '\n')
	{
	//	Yes, we do. Discard the character
		*pbDiscardChar = TRUE;

	//	Also, terminate input.
		return TRUE;	
	}
//	See if we get a space
	if(isspace(ch))
	{
	//	We do, so discard it
		*pbDiscardChar = TRUE;

	//	And signal to terminate input.
		return TRUE;
	}

//	If we don't have a newline:
//	 don't discard & don't terminate input.
	*pbDiscardChar = FALSE;
	return FALSE;
}


void print_vector(GENERIC_VECTOR hVectofStr)
{
	int i = 0;
	MYSTRING* ptr;
	
//	Run through the vector, printing all the strings we find. 
//	This test should be words of length 4.
	for(i = 0; i < generic_vector_size(hVectofStr); i++)
	{
	//	Get a mystring object from the vector
		ptr = (MYSTRING*)generic_vector_at(hVectofStr, i);
		
	//	Print out the given mystring
		mystring_output(*ptr, stdout);
		
	//	Newlines
		printf("\n");
	}
	
	return;
}


void assign_vector_of_vector(void** hVectVect, void* hVector)
{
		
	
	return;
}

/*
	I THINK THESE TWO CAN BE COMBINED? OR SOMETHING?
*/
void destroy_vector_of_vector(void** hVector)
{
	int i;
	
	// Run through the vector of a vector, destroying all vector of mystrings.
	for(i = 0; ((GENERIC_VECTOR*)hVector != NULL); i++)
	{	
		destroy_vector_of_mystring(&hVector[i]);
	}

	return;
}


void destroy_vector_of_mystring(void** hVectString)
{
//	Destroy the vector of mystrings. Go through and call destroy_mystring
//	for every single item.
	int i;
	for(i = 0; (GENERIC_VECTOR*)hVectString != NULL; i++)
	{
		//destroy_mystring(&hVectString[i]);
	}
	//free(hVectString->data);		// Free the malloc'd array
	free(hVectString);			// Free the structure
	return;
}
