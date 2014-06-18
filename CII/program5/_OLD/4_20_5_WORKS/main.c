#include <stdio.h>
#include <stdlib.h>
#include "my_set.h"

/*
	NOTES:
	Page 422 in DS&PD in C has helpful stuff on AVL trees
	See also page 384 for Binary Search Trees (Similar but helpful)
	
	FUNCTIONS TO IMPLEMENT:
	my_set_remove		= Started. Doesn't work at all... >_<
*/

int isbalanced(MY_SET hMY_SET);	// -Wall was complaining about implicit declaration...

void newlinez(void)		//	NON-ESSENTIAL - merely lazyness to add a bunch of newlines.
{
	printf("\n\n");
}

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
	
	printf("PROGRAM 5 - Version #420 RETARD\n\n");
	
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
		printf("Derp, set should be EMPTY!\n");
	}
	
	// Rather then repeatedly typing shit in, let's just type it once!!
	
	// Test list RIGHT DELETE
	test = my_set_add(hSet, 10);
	test = my_set_add(hSet, 6);
	test = my_set_add(hSet, 4);
	test = my_set_add(hSet, 11);
	test = my_set_add(hSet, 3);
	test = my_set_add(hSet, 5);
	test = my_set_add(hSet, 8);
	
	// Test list LEFT DELETE
	/*
	test = my_set_add(hSet, 10);
	test = my_set_add(hSet, 6);
	test = my_set_add(hSet, 4);
	test = my_set_add(hSet, 3);
	*/
	//test = my_set_add(hSet, 5);
	
	//	RIGHT RIGHT RIGHT RIGHT
	/*
	test = my_set_add(hSet, 10);			// Add
	test = my_set_add(hSet, 20);			// Add
	test = my_set_add(hSet, 30);			// Add
	test = my_set_add(hSet, 40);			// Add
	test = my_set_add(hSet, 50);			// Add
	test = my_set_add(hSet, 25);			// Add		
	*/
	/*
	// TO THE LEFT LEFT LEFT LEFT
	test = my_set_add(hSet, 50);			// Add
	test = my_set_add(hSet, 40);			// Add
	test = my_set_add(hSet, 30);			// Add
	test = my_set_add(hSet, 20);			// Add
	test = my_set_add(hSet, 10);			// Add
*/

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
				newlinez();	// Add 2 newlines
				break;
			case 1:
				newlinez();	// Add 2 newlines
				test = my_set_is_empty(hSet);		// Test the empty function
				if(test == TRUE){
					printf("hSet is empty, sir!\n");	// EMPTY
				}
				else{
					printf("Derp, set no EMPTY!\n");	// NOT EMPTY
				}
				newlinez();	// Add 2 newlines
				break;
			case 2:
				// Test the is_element function
				newlinez();	// Add 2 newlines
				printf("Number to find in set: ");
				scanf("%d", &i);
				test = my_set_is_element(hSet, i);		// Search
				if(test == TRUE)					
					printf("Found item %d!\n", i);	// Results
				newlinez();	// Add 2 newlines
				break;
			case 3:
				// Test the size of the set function
				newlinez();	// Add 2 newlines
				i = my_set_size(hSet);
				printf("Size of the set: %d\n", i);
				newlinez();	// Add 2 newlines
				break;
			case 4:
				// Test the traverse function, and print each number in the tree.
				newlinez();	// Add 2 newlines
				my_set_traverse(hSet, printNumber);
				if(my_set_is_empty(hSet) == TRUE)
					printf(" ( EMPTY ) \n");
				newlinez();	// Add 2 newlines
				break;
			case 5:
				// Test the add function 
				newlinez();	// Add 2 newlines
				printf("Number to add to set: ");
				scanf("%d", &i);
				test = my_set_add(hSet, i);			// Add
				if(test == TRUE)
					printf("Added %d to set!\n", i);
				else
					printf("Failed to add %d to set!\n", i);
				newlinez();	// Add 2 newlines
				break;
			case 6:
				// Test the remove function
				newlinez();	// Add 2 newlines
				printf("Number to remove from set: ");
				scanf("%d", &i);
				test = my_set_remove(hSet, i);
				if(test == TRUE)
					printf("Removed %d from set!\n", i);
				else
					printf("Failed to remove %d from set!\n", i);
				newlinez();	// Add 2 newlines
				break;
			case 7:
				// Find the height of the set (NOT DONE)
				newlinez();	// Add 2 newlines
				if(isbalanced(hSet) == 1)
					printf("The AVL Tree is balanced! ^_^\n");
				else
					printf("The AVL Tree... IS NOT BALANCED! >_>\n");
				newlinez();	// Add 2 newlines
				break;
		}
	
	}while(x != -1);	// ONLY quit on -1!

	// Destroy the tree to prevent memory leaks.
	my_set_destroy(&hSet);
	
	// Done testing.
	return 0;
}
