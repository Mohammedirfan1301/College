#ifndef MY_SET_H
#define MY_SET_H

#include <stdio.h>

typedef struct _MY_SET *MY_SET;

// Simple way to do TRUE/FALSE (FALSE = 0, TRUE = 1)
enum boolean {FALSE, TRUE};
typedef enum boolean Boolean;

// Simple way to do SUCCESS/FAILURE (FALSE = 0, TRUE = 1)
enum status {FAILURE, SUCCESS};
typedef enum status Status;

// Returns a handle to a default MY_SET
MY_SET my_set_init_default(void);	// NOTE: best practice to include VOID. I think, anyway. 
				// See Stackoverflow: http://stackoverflow.com/questions/693788/c-void-arguments 

// Returns TRUE if item is in the set; exit on error
Boolean my_set_is_element(MY_SET hMY_SET, int item);	

// Returns TRUE if the set is empty; exit on error
Boolean my_set_is_empty(MY_SET hMY_SET);		

// Returns the number of elements in the set; -1 on error
int my_set_size(MY_SET hMY_SET);			

// Call visit on each node in the set. (Inorder traversal)
Status my_set_traverse(MY_SET hMY_SET, void (*visit)(int));

// Adds item to the set if it is not already in it.
Status my_set_add(MY_SET hMY_SET, int item);		

// Find and remove item from the set if it is present. Otherwise ignore
Status my_set_remove(MY_SET hMY_SET, int item);		

// Destroy the data structure and set the handle pointed to by the arg to NULL
void my_set_destroy(MY_SET* p_hMY_SET);			

/* Return the height of the AVL Tree implementation.
  (An empty tree has height 0, a tree with one node has height 1)	*/
int my_set_height(MY_SET hMY_SET);			

#endif /*MY_SET*/

