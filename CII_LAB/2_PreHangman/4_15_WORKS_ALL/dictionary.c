#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generic_vector.h"
#include "mystring.h"

/* 	NOTES
	In order to get the vector of mystring to work, I had to put some functions,
	such as mystring assignment and mystring destroyer, into the mystring.c file.
	
	Also, in a related note, to get the vector a vector part to work I had to do
	the same thing, except I put myvector_assignment and myvector_destroyer in
	the generic_vector.c file. 
	
	Made it less straight forward, but it seems to work!
*/

// File worker functions
void work_file(FILE* text, GENERIC_VECTOR hVectofVect);

// Tester function
void print_vector(GENERIC_VECTOR hVectofVect, int index);

// fTerminate function
int acceptLineInput(char ch, int * pbDiscardChar);

//	I use TRUE / FALSE in a few functions to represent "0" and "1"
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[])
{
	FILE* text;								// File pointer
	GENERIC_VECTOR hVectofVect = NULL;		// Vector of Vector handle
	int x;

//	Info
	printf("Dictionary Program\n");
	
//	Open the dictionary file in "read" mode
	text = fopen("dictionary.txt", "r");
	
//	Check the FILE pointer
	if(text == NULL)
	{
		printf("Error - failed to open dictionary.txt!\n");
		exit(1);
	}
	
//	Create a vector of a vector handle
	hVectofVect = make_vector_of_vector();
	
//	See if it succeeded or not.
	if(hVectofVect == NULL)
	{
		printf("Error - failed to create a vector of vectors!\n");
		exit(1);
	}	

//	Initialize the vect of vect with 29 vects of mystring
	hVectofVect = vector_of_vector_init_default(hVectofVect);
	
//	See if the initialize function worked
	if(hVectofVect == NULL)
	{
		printf("Error - failed to initialize vector of vector!\n");
		exit(1);
	}

//	Work on the file, by using the vector of vectors to store MYSTRINGS
	work_file(text, hVectofVect);

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
	

//	SUCCESS
	return 0;
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
					//	Prevent memory leaks - DESTROY THE LEFTOVER STRING!
					//mystring_destroy(&hString);
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
	GENERIC_VECTOR* temp;
	GENERIC_VECTOR  hVectofStr;
	MYSTRING* ptr;
	int i = 0;
	
	//	Get the MYSTRING vector from the VECTOR OF VECTOR
	temp = (GENERIC_VECTOR*)generic_vector_at(hVectofVect, index - 1);
				
	if(temp == NULL)
	{
		printf("Error - doesn't seem to be any MYSTRINGs of size %d!\n", index);
		return;
	}
	
	hVectofStr = (GENERIC_VECTOR) *temp;
	
	if(generic_vector_size(hVectofStr) < 1)
	{
		printf("Error - doesn't seem to be any MYSTRINGs of size %d!\n", index);
		return;
	}
	
//	Run through the vector, printing all the strings we find. 
//	This test should be words of length 4.
	for(i = 0; i < generic_vector_size(hVectofStr); i++)
	{
	//	Get a mystring object from the vector
		ptr = (MYSTRING*)generic_vector_at(hVectofStr, i);
		
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
