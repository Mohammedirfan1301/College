#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "generic_vector.h"


GENERIC_VECTOR make_vector_of_mystring(void);
//GENERIC_VECTOR make_vector_of_vector(void);
void work_file(FILE* text, GENERIC_VECTOR hVector);

// Assignment / Destroy functions
void assign(void** hVector, void* hString);
void destroy(void** hVector);

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
	GENERIC_VECTOR *hVector = NULL;

	printf("Dictionary Program\n");
	
//	Open the dictionary file in "read" mode
	text = fopen("dictionary.txt", "r");
	
//	Check the FILE pointer
	if(text == NULL)
	{
		printf("Error - failed to open dictionary.txt!\n");
		return 0;
	}
	
//	Start by only looking for words of length 4.
	printf("Finding words of length 4 as a test: \n");
	
//	Initialize a vector.
	*hVector = make_vector_of_mystring();

//	See if it succeeded or not.
	if(hVector == NULL)
	{
	// 	Something failed, quit with an error
		printf("Error - failed to init. vector!\n");
		return 0;
	}
	
// 	Otherwise, continue...
	work_file(text, *hVector);
	
//	Close the file	
	fclose(text);

//	SUCCESS
	return 0;
}

GENERIC_VECTOR make_vector_of_mystring(void)
{
	GENERIC_VECTOR temp;
	Generic_vector_functions functions;
	
	functions.assignment = &assign;
	functions.destructor = &destroy;
	temp = generic_vector_init_default(functions);
	return temp;
}


void work_file(FILE* text, GENERIC_VECTOR hVector)
{
	MyString_Status 	Code;
	MYSTRING hString = NULL;
	int (*fTerminate)(char, int*);
	fTerminate = &acceptLineInput;

	do{
		hString = mystring_init_default();
		
	//	See if hString initialized.
		if(hString != NULL)
		{
		//	Call input using a MS obj, text (FP), and fTerminate (newline)
			Code = mystring_input(hString, text, 0, fTerminate);
			
			if(Code == MYSTRING_STATUS_SUCCESS)
			{
				// Add to generic vector. First test - only 4 char words.
				if(mystring_size(hString) == 4)
				{
				//	Add hString to hVector
					//...
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
		
	}while(text != NULL);

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

//	If we don't have a newline:
//	 don't discard & don't terminate input.
	*pbDiscardChar = FALSE;
	return FALSE;
}

void assign(void** hVector, void* hString)
{
//	We were given a vector of mystrings. Need to put a mystring into the
//	vector!

	

	return;	
} 

void destroy(void** pString)
{
	MYSTRING hString;
	hString = (MYSTRING) pString;
	mystring_destroy(&hString);
	return;
}
