#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generic_vector.h"
#include "mystring.h"
#include "dictionary.h"

//	I use TRUE / FALSE in a few functions to represent "0" and "1"
#define TRUE 1
#define FALSE 0


/* 	This function will return a vector of a vector of mystrings. It will have 29 such
	vectors of mystrings, each containing a bunch of words of a certain type.	 */
GENERIC_VECTOR vector_of_vector_dictionary(void)
{
	GENERIC_VECTOR hVectofVect = NULL;		// Vector of Vector handle
	FILE* text;								// File pointer
	
	//	Create a vector of a vector handle
	hVectofVect = make_vector_of_vector();

	//	See if it succeeded or not.
	if(hVectofVect == NULL)
	{
		printf("Error - failed to create a vector of vectors!\n");
		exit(1);
	}	
	
	//	Initialize the vect of vect with 29 (empty) vects of mystring
	hVectofVect = vector_of_vector_init_default(hVectofVect);
	
	//	See if the initialize function worked
	if(hVectofVect == NULL)
	{
		printf("Error - failed to initialize vector of vector!\n");
		exit(1);
	}
	
	//	Open the dictionary file in "read" mode
	text = fopen("dictionary.txt", "r");
	
	//	Check the FILE pointer
	if(text == NULL)
	{
		printf("Error - failed to open dictionary.txt!\n");
		exit(1);
	}
	
	//	Work on the file, by using the vector of vectors to store MYSTRINGS
	work_file(text, hVectofVect);
	
	//	Also - don't forget to close the dictionary file!
	fclose(text);
	
	// If we get here, we are set to simply start using the vector of a vector!
	return hVectofVect;
}


/*	This function will return a vector of a mystrings, of a certain size word that
	can be determined by the user. Ex: User calls this function with int size = 5,
	this function returns a vector of a mystring with size 5 words within it.	 */
GENERIC_VECTOR vector_of_mystring_at(GENERIC_VECTOR hVectofVect, int index)
{
	GENERIC_VECTOR* 		   temp = NULL;		// Used to hold error codes / test valid vectors
	GENERIC_VECTOR  hVectofMystring = NULL;		// Vector of Mystring handle
	
	//	Get the MYSTRING vector from the VECTOR OF VECTOR
	temp = (GENERIC_VECTOR*)generic_vector_at(hVectofVect, index - 1);
	
	//	Make sure its valid!
	if(temp == NULL)
	{
		printf("Error - doesn't seem to be any MYSTRINGs of size %d!\n", index);
		return NULL;
	}
	
	// Convert it to a usable format
	hVectofMystring = (GENERIC_VECTOR) *temp;
	
	// Again make sure its valid!
	if(generic_vector_size(hVectofMystring) < 1)
	{
		printf("Error - doesn't seem to be any MYSTRINGs of size %d!\n", index);
		return NULL;
	}
	
	// Return the given vector of MYSTRINGS
	return hVectofMystring;
}


void work_file(FILE* text, GENERIC_VECTOR hVectofVect)
{
	MyString_Status 	code;
	Status				test = SUCCESS;
	GENERIC_VECTOR* temp;
	GENERIC_VECTOR hVectofStr = NULL;
	MYSTRING hString = NULL;
	int (*fTerminate)(char, int*);
	fTerminate = &acceptLineInput;
	char c;
	int x, i = 0;

	do{
		hVectofStr = NULL;
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
				// Add to a generic vector. First find which one to add it to.
				for(x = 1; x < 30; x++)
				{
					if(mystring_size(hString) == x)
					{
					//	Find the vector of MYSTRINGS that contains x size words
						temp = (GENERIC_VECTOR*)generic_vector_at(hVectofVect, x - 1);
					
						if(temp == NULL)
						{
							printf("SOMETHING BAD HAPPENED!\n");
							exit(1);
						}
						
						hVectofStr = (GENERIC_VECTOR) *temp;
						
					
					//	Add hString to hVectofStr
						test = generic_vector_push_back(hVectofStr, hString);
			
					//	See if it worked.
						if(test == FAILURE)
						{
							printf("ERROR: failed to add MYSTRING to vect of MYSTRING...\n");
						}
					}
				}
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
	 
	 //	Prevent memory leaks - DESTROY THE LEFTOVER STRING!
		mystring_destroy(&hString);
	 
	 	i++;
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


void print_vector(GENERIC_VECTOR hVectofVect, int index)
{
	GENERIC_VECTOR  hVectofMystring;
	MYSTRING* ptr;
	int i = 0;
	
	hVectofMystring = vector_of_mystring_at(hVectofVect, index);
	
	if(hVectofMystring == NULL)
	{
		printf("Error - print_vector failed!\n");
		return;
	}
	
//	Run through the vector, printing all the strings we find. 
//	This test should be words of length 4.
	for(i = 0; i < generic_vector_size(hVectofMystring); i++)
	{
	//	Get a mystring object from the vector
		ptr = (MYSTRING*)generic_vector_at(hVectofMystring, i);
		
		if(ptr == NULL)
		{
			printf("Error - doesn't seem to be any MYSTRINGs of size %d!\n", index);
			return;
		}
		
	//	Print out the given mystring
		mystring_output(*ptr, stdout);
		
	//	Newlines
		printf("\n");
	}
	
	return;
}
