#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assocarray.h"
#include "mystring.h"

// -Wall was complaining about implicit declaration...
int isbalanced(MY_SET hMY_SET);	
void other_traverse(MY_SET hMY_SET, void (*visit)(MYSTRING, GENERIC_VECTOR));
int acceptLineIn(char ch, int * pbDiscardChar);

void printStrings(MYSTRING hString, GENERIC_VECTOR hVect)
{
	MYSTRING* ptr;
	int i;	
	
	// Output the MYSTRING object
	printf("Given key: ");
	mystring_output(hString, stdout);
	printf("\n\n");
	
	printf("Size of the generic_vector at this node: %d\n", generic_vector_size(hVect));
	printf("Printing this node's generic_vector: \n");
	for(i = 0; i < generic_vector_size(hVect); i++)
	{
	//	Get a mystring object from the vector
		ptr = (MYSTRING*)generic_vector_at(hVect, i);
		
		if(ptr == NULL)
		{
			printf("Error - something failed when printing hVector!\n");
			return;
		}
		
	//	Print out the given mystring
		mystring_output(*ptr, stdout);
		
	//	Newlines
		printf("\n");
	}
	
	printf("\n");
	return;
}

int main(int argc, char * argv[])
{
	MY_SET hSet;
	Boolean test = FALSE;
	MyString_Status code;
	int i = 0, x = 1;
	MYSTRING take_input = NULL;
	MYSTRING word 		= NULL;
	
	printf("PROGRAM 5 - Version 4/30/14\n\n");
	
	// Initialize a set
	hSet = my_set_init_default();
	
	// See if hSet initialized.
	if(hSet == FALSE){
		printf("Something failed! OH N0!\n");
		return 0;
	}
	
	// Test the empty function
	test = my_set_is_empty(hSet);
	
	// See if the empty function failed.
	if(test != TRUE){
		printf("Set should be EMPTY!\n");
	}
	
	i = 0;
	x = 0;
	
	take_input = mystring_init_default();
	mystring_concatenate_c_string(take_input, "---\n");
	word = mystring_init_default();
	mystring_concatenate_c_string(word, "Hey\n");
	my_set_add(hSet, take_input, word);

	mystring_destroy(&take_input);
	mystring_destroy(&word);

	take_input = mystring_init_default();
	mystring_concatenate_c_string(take_input, "---\n");
	word = mystring_init_default();
	mystring_concatenate_c_string(word, "Heh\n");
	my_set_add(hSet, take_input, word);
	
	mystring_destroy(&take_input);
	mystring_destroy(&word);
	
	take_input = mystring_init_default();
	mystring_concatenate_c_string(take_input, "---\n");
	word = mystring_init_default();
	mystring_concatenate_c_string(word, "hex\n");
	my_set_add(hSet, take_input, word);
	
	mystring_destroy(&take_input);
	mystring_destroy(&word);

	do{
		printf("The following choices are possible: \n");
		printf("1: Check empty\n");
		printf("2: Find item\n");
		printf("3: Check size\n");
		printf("4: Traverse set (PRINT)\n");
		printf("5: Add to set\n");
		printf("6: Remove from set\n");
		printf("7: Find height of set\n");
		printf("TO QUIT - ENTER -1\n");
		
		printf("Enter a number: ");
		do{
			scanf("%d", &x);
		}while(x < -1 && x > 7);		// ONLY	USER ENTER -1 TO 7
	
		take_input = mystring_init_default();
			  word = mystring_init_default();
	
		switch(x)
		{
			case -1:
				// 	QUITTING!
				printf("\n\n");
				break;
			case 1:
				printf("\n\n");
				test = my_set_is_empty(hSet);		// Test the empty function
				
				if(test == TRUE){
					printf("hSet is empty!\n");	// EMPTY
				}
				else{
					printf("hSet is not empty!\n");	// NOT EMPTY
				}
				
				printf("\n\n");
				break;
			case 2:
				// Test the is_element function
				printf("\n\n");
				printf("String to find in set: ");
				code = mystring_input(take_input, stdin, 1, acceptLineIn);
				
				if(code == MYSTRING_STATUS_ERROR)
					printf("Failed to take mystring_input!\n");
				
				test = my_set_is_element(hSet, take_input);	// Search
				if(test == TRUE)
				{		
					printf("Found the item: ");
					mystring_output(take_input, stdout);
				}
				printf("\n\n");
				break;
			case 3:
				// Test the size of the set function
				printf("\n\n");
				i = my_set_size(hSet);
				printf("Size of the set: %d\n", i);
				printf("\n\n");
				break;
			case 4:
				// Test the traverse function, and print each number in the tree.
				printf("\n\n");
				
				my_set_traverse(hSet, printStrings);	// Call IN_ORDER
				 other_traverse(hSet, printStrings);	// Call POST & PRE ORDER
				
				printf("\n\n");
				break;
			case 5:
				// Test the add function 
				printf("\n\n");
				printf("Key to add to set: ");
				code = mystring_input(take_input, stdin, 1, acceptLineIn);
				
				if(code == MYSTRING_STATUS_ERROR)
					printf("Failed to take mystring_input of key!\n");
				
				printf("Word to add to set: ");
				code = mystring_input(word, stdin, 1, acceptLineIn);
				
				if(code == MYSTRING_STATUS_ERROR)
					printf("Failed to take mystring_input of word!\n");
				
				test = my_set_add(hSet, take_input, word);	// Add
				if(test == TRUE || test == FALSE)
				{
					printf("Added ");
					mystring_output(take_input, stdout);	
					printf(" to the set!\n");
				}
				printf("\n\n");
				break;
			case 6:
				// Test the remove function
				printf("\n\n");
				printf("Key to remove from set: ");
				mystring_input(take_input, stdin, 1, acceptLineIn);
				
				if(code == MYSTRING_STATUS_ERROR)
					printf("Failed to take mystring_input!\n");
				
				test = my_set_remove(hSet, take_input);
				if(test == TRUE)
				{
					printf("Removed ");
					mystring_output(take_input, stdout);	
					printf(" from set!\n");
				}
				printf("\n\n");
				break;
			case 7:
				// Find the height of the set (NOT DONE)
				printf("\n\n");
				i = isbalanced(hSet);
				
				if(i == -1)
					printf("The AVL Tree is EMPTY! ;)\n");
				else if(i == 0)
					printf("The AVL Tree... IS NOT BALANCED! >_>\n");
				else if(i == 1)
					printf("The AVL Tree is balanced! ^_^\n");
				
				printf("\n\n");
				break;
			default:
				printf("\n\nYou entered a number that isn't valid!\n");
				printf("Please enter a number between 1 and 7!\n\n\n");
				break;
		}
	
		mystring_destroy(&take_input);
		mystring_destroy(&word);
	
	}while(x != -1);	// ONLY quit on -1!

	// Destroy the tree to prevent memory leaks.
	my_set_destroy(&hSet);
	
	// Done testing.
	return 0;
}


int acceptLineIn(char ch, int * pbDiscardChar)
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
//	don't discard & don't terminate input.
	*pbDiscardChar = FALSE;
	return FALSE;
}
