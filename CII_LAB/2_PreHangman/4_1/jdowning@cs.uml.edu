#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "generic_vector.h"

//int make_vector_of_vector(void);
Generic_vector make_vector(void);
void work_file(FILE* text, Generic_vector* hVector);

// Assignment / Destroy functions
void* assign(void** hVector, void* hString);
void* destroy(void** hVector);

// fTerminate function
int acceptLineInput(char ch, int * pbDiscardChar);

// Index would be from 0 - 22, assuming completed vector of a vector code.
//int access_vector_of_vector(int index);	

int main(int argc, char* argv[])
{
	FILE* text;
	Generic_vector *hVector = NULL;

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
	//hVector = make_vector();

//	See if it succeeded or not.
	if(hVector == NULL)
	{
	// 	Something failed, quit with an error
		printf("Error - failed to init. vector!\n");
		return 0;
	}
	
// 	Otherwise, continue...
	work_file(text, hVector);
	
//	SUCCESS
	return 0;
}

GENERIC_VECTOR make_vector(void)
{
	Generic_vector *temp;
	temp = generic_vector_init_default
}

void work_file(FILE* text, Generic_vector* hVector)
{
	MyString_Status 	Code;
	MYSTRING hString = NULL;
	int (*fTerminate)(char, int*);
	fTerminate = &acceptLineInput;

	do{
		mystring_init_default(hString);
		
		if(hString != NULL)
		{
			Code = mystring_input(hString, text, 0, fTerminate);
			
			if(Code == MYSTRING_STATUS_SUCCESS)
			{
				// Add to generic vector
				
			}
			else{
				// Don't add - stop, we had a problem.
			}
		}
		else{
			mystring_destroy(hString);
			break;
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

void* assign(void** pVector, void* pString)
{
	
	return NULL;	
}

void* destroy(void** pString)
{
	MYSTRING hString;
	hString = (MYSTRING) pString;
	mystring_destroy(&hString);
}
