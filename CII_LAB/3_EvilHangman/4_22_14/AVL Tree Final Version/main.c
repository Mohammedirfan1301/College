#include <stdio.h>
#include <stdlib.h>
#include "my_set.h"

// -Wall was complaining about implicit declaration...
int isbalanced(MY_SET hMY_SET);	
void other_traverse(MY_SET hMY_SET, void (*visit)(int));

void printNumber(int num)
{
	printf("%d\n", num);
	return;
}

int main(int argc, char * argv[])
{
	MY_SET hSet;
	Boolean test;
	int i = 0, x = 1;
	
	printf("PROGRAM 5 - Version 4/21/14\n\n");
	
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
	
	/*	THE ULIMATE TEST: 10,000 INTS, ADDING AND REMOVAL.	*/
	for(i = 0; i < 10000; i++)
	{
		printf("Adding item #%d\n", i);
		test = my_set_add(hSet, i);
		if(test == FALSE)
		{
			printf("SOMETHING FAILED!\n");
			break;
		}
	}
	
	for(i = 0; i < 1000; i++)
	{
		test = my_set_remove(hSet, i);
		if(test == TRUE)
			printf("succes.\n");
		else
			printf("fail.\n");
	}
	
	i = 0;
	x = 0;

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
				printf("Number to find in set: ");
				scanf("%d", &i);
				test = my_set_is_element(hSet, i);		// Search
				if(test == TRUE)					
					printf("Found item %d!\n", i);		// Results
				else
					printf("Did not find item %d!\n", i);
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
				my_set_traverse(hSet, printNumber);		// Call IN_ORDER
				 other_traverse(hSet, printNumber);		// Call two other order printouts
				printf("\n\n");
				break;
			case 5:
				// Test the add function 
				printf("\n\n");
				printf("Number to add to set: ");
				scanf("%d", &i);
				test = my_set_add(hSet, i);			// Add
				if(test == TRUE)
					printf("Added %d to set!\n", i);
				printf("\n\n");
				break;
			case 6:
				// Test the remove function
				printf("\n\n");
				printf("Number to remove from set: ");
				scanf("%d", &i);
				test = my_set_remove(hSet, i);
				if(test == TRUE)
					printf("Removed %d from set!\n", i);
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
		}
	
	}while(x != -1);	// ONLY quit on -1!

	// Destroy the tree to prevent memory leaks.
	my_set_destroy(&hSet);
	
	// Done testing.
	return 0;
}
