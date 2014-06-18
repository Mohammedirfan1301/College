#include <stdio.h>
#include <stdlib.h>
#include "my_set.h"

/*
	NOTES:
	Page 422 in DS&PD in C has helpful stuff on AVL trees
	See also page 384 for Binary Search Trees (Similar but helpful)
	
	FUNCTIONS TO IMPLEMENT:
	my_set_is_element	= DONE.
	my_set_size		= DONE.	
	my_set_add		= WORKS. But... not AVL. I think. Need rebalance.
	my_set_remove		= Started. Doesn't work at all... >_<
	my_set_height		= Started. Only works for heights 0 & 1. OR NOT. WHO KNOWS.
*/

void printNumber(int num)
{
	printf("%d\n", num);
	return;
}

int main(int argc, char * argv[])
{
	MY_SET hSet;
	Boolean test;
	int i;
	
	// Initialize a set
	hSet = my_set_init_default();
	
	// See if hSet initialized.
	if(hSet == FALSE)
	{
		printf("Something failed! OH N0!\n");
		return 0;
	}
	else
	{
		printf("hSet initialized fine.\n");
	}
	
	// Test the empty function
	test = my_set_is_empty(hSet);
	
	// See if the empty function failed.
	if(test == FALSE)
	{
		printf("my_set_is_empty function tis fine.\n");
	}
	if(test == TRUE)
	{
		printf("Derp, set should be EMPTY!\n");
	}
	
	// Test the add & search function
	for(i = 0; i < 5; i++)
	{
		test = my_set_add(hSet, i);			// Add
		test = my_set_is_element(hSet, i);		// Search
		if(test == TRUE)					
			printf("Found item %d!\n", i);	// Results
		else
			printf("Didn't find the item! :(\n");
	}
	
	// Make sure duplicate items aren't allowed.s
	test = my_set_add(hSet, 4);
	if(test == FALSE)
		printf("4 Ain't gonna be added yo.\n");
	
	test = my_set_is_element(hSet, 6);
	if(test == TRUE)
		printf("Found item %d!\n", 4);
	else
		printf("Didn't find the item! :(\n");
	
	// Test the remove function
	//test = my_set_remove(hSet, 1);
	
	// Test the size of the set function
	i = my_set_size(hSet);
	printf("\nSize of the set: %d\n", i);
	
	// Test the traverse function, and print each number in the tree.
	my_set_traverse(hSet, printNumber);

	// Find the height of the set (NOT DONE)
	i = my_set_height(hSet);
	printf("Height of the set: %d\n", i);

	// Destroy the tree to prevent memory leaks.
	my_set_destroy(&hSet);
	
	// Done testing.
	return 0;
}
