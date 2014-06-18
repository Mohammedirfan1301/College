#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "generic_vector.h"
#include "assocarray.h"

typedef struct node Node;

// TREE STRUCTURE.
struct node
{
	/* 	Data (KEY) will act as the locater for each generic_vector. 
		Each vector holds separate lists of words, depending on which 
		key is attached to that node.		*/

	MYSTRING data;				// data = KEY 	
	GENERIC_VECTOR hVector;		// vector holds a generic_vector pointer
	Node *left;					
	Node *right;				
	int number;
	int height;					// Keep track of the height of each node.
};

struct my_set					// MY_SET holds the root pointer.
{
	Node *root;	
};

typedef struct my_set My_set;


/*		Helper Functions		*/
void in_order_traverse(Node* root, void (*visit)(MYSTRING, GENERIC_VECTOR));
void           destroy(Node* root);
void     SearchTree(Node *head, MYSTRING item, Boolean *test);
int           FindSize(Node *temp, Node *numb);
Node*              Add(Node *next, Node *temp, Boolean *InSet, MYSTRING item, MYSTRING word);
Node*           Remove(Node *next, MYSTRING item, Boolean *InList);
GENERIC_VECTOR* 	max_vector_node(MY_SET hMY_SET, MYSTRING* key);
Node* 			FindMaxNode(Node *head, Node *max_node, Node *numb);

//	Functions for TESTING - UPDATE THE VISIT FUNCTION!
void other_traverse(MY_SET hMY_SET, void (*visit)(MYSTRING, GENERIC_VECTOR));
void pre_order_traverse(Node* root, void(*visit)(MYSTRING, GENERIC_VECTOR));
void post_order_traverse(Node* root, void(*visit)(MYSTRING, GENERIC_VECTOR));

// Helpers for the size function - THESE ARE ALL FINE
int isbalanced(MY_SET hMY_SET);
int balanced(Node* temp);
int height(Node* node);
int max(int a, int b);

// Rotating Functions - THESE ARE ALL FINE
int getBF(Node* temp);
Node* RotateLeft(Node* ptr);
Node* RotateRight(Node* ptr);	

/*
	Given a MY_SET handle and an int pointer, this function will run through the tree
	and see which node contains the largest generic_vector. It will return a pointer
	to that generic_vector and also its size and key (using pass by reference). 
	Thus this function will be critical to the hangman game - after the word list is 
	sorted by key, this function will get the "new" word list and also the "new" key.	
*/
GENERIC_VECTOR* max_vector_node(MY_SET hMY_SET, MYSTRING* key)
{
	My_set *pSet 	= (My_set*)hMY_SET;
	Node *head 		= pSet->root;
	Node *max_node  = NULL;
	Node *numb 		= (Node*) malloc(sizeof(Node));
	numb->number 	= 0;
	
	// If the handle isn't valid, we can't continue!
	if(hMY_SET == NULL)
	{
		printf("Error: hMY_SET is not valid!\n");
		return NULL;
	}

	// Also if the head is NULL we can't do anything!
	if(head == NULL)
	{
		printf("Error: head of the tree is NULL!\n");
		return NULL;
	}
	
	// Use a helper function to find the maximium node
	max_node = FindMaxNode(head, max_node, numb);
	
	// See if something failed.
	if(max_node == NULL)
	{
		printf("Find max vector node failed!\n");
		exit(1);
	}
	
	// Prevent memory leaks
	free(numb);
	
	// Return the max node!
	*key = max_node->data;
	return &max_node->hVector;
}


// Helper function for the max_vector_node function
Node* FindMaxNode(Node *head, Node *max_node, Node *numb)
{
	if(head != NULL)
	{
		// If we found a new max
		if(numb->number < generic_vector_size(head->hVector))		
		{
			// Then save this node!
			max_node = head;
		}
		
		FindMaxNode(head->right, max_node, numb);	// Search right
		FindMaxNode(head->left, max_node, numb);		// Search left
	}
	
	// Return the node with the largest vector
	return max_node;

}


// Takes no arguments; returns a handle to a default MY_SET
MY_SET my_set_init_default(void)
{
	My_set *temp;	
	temp  = (My_set*)malloc(sizeof(My_set));	// Alloc space for a MY_SET
	
	// See if the malloc failed:
	if(temp == NULL)
	{
		printf("Error - failed to malloc default MY_SET object!\n");
		return NULL;
	}
	
	// If it succeded, then we are free to set root to NULL
	if(temp != NULL)
	{
		temp->root = NULL;
	}
	
	// And return a handle to the MY_SET object!
	return (MY_SET)temp;
}


// Returns TRUE if item is in the set; exit on error
Boolean my_set_is_element(MY_SET hMY_SET, MYSTRING item)	
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;
	Boolean test = FALSE;
	
	// First see if the list is empty.
	if(head == NULL)
	{
		printf("Error: can't find an item in an empty list!\n");
		return FALSE;
	}
			
	// Other wise run through the list until we find the item!
	if(head != NULL)
	{
		// Call Search tree to do this for us.
		SearchTree(head, item, &test);
	}

//	FOUND THE ITEM!
	if(test == TRUE)
		return TRUE;

//	Failed to find the item!
	return FALSE;
}


// Returns TRUE if an item is in the set. False if it is not.
void SearchTree(Node *head, MYSTRING item, Boolean *test)
{
	// Run through the list until we find the item!
	if(head != NULL)
	{
		if(mystring_compare(head->data, item) == 0)   // Uses MYSTRING_COMPARE
		{						// to see if these two MYSTRINGS are the same.
			*test = TRUE;
			return;
		}
		SearchTree(head->left, item, test);	// Search  left side
		SearchTree(head->right, item, test);	// Search right side
	}
	
	// If we get here, return FALSE - we didn't find the item.
	return;
}


// Returns TRUE if the set is empty; exit on error
Boolean my_set_is_empty(MY_SET hMY_SET)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;

//	If MY_SET is NULL, there is no set.
	if(hMY_SET == NULL)
	{
		return TRUE;
	}
	
//	If the head pointer points to NULL, there is no set.
	if(head == NULL)
	{
		return TRUE;
	}
	
//	If it isn't NULL, there is some sort of a list.
	return FALSE;
}


// Returns the number of elements in the set; -1 on error
int my_set_size(MY_SET hMY_SET)			
{
	int number_of_nodes = 0;
	My_set *pSet = (My_set*)hMY_SET;
	Node *temp = pSet->root;
	Node *numb = (Node*) malloc(sizeof(Node));
	numb->number = 0;
		
	// Verify that hMY_SET exists.
	if(hMY_SET == NULL)
		return -1;	// Return error if it doesn't.
	
	/* 	  
		  Assuming we have at least one node, run through the tree. (Using pre-order)
		  NOTE: using recursion, so needed a good way to get the ACTUAL
		  number of nodes in the set. numb is ONLY used for its data, as it
		  should not be modified by recursion.
	*/
	number_of_nodes = FindSize(temp, numb);
	
	free(numb);		// Prevent memory leaks.
	
	return number_of_nodes;
}


int FindSize(Node *temp, Node *numb)
{
	if(temp != NULL)
	{
		numb->number++;;				// Increase n for each node we find.
		FindSize(temp->right, numb);	// Search right
		FindSize(temp->left, numb);		// Search left
	}
	
	// Return the number of nodes.
	return numb->number;
}


// Call visit on each node in the set. (Inorder traversal)
Boolean my_set_traverse(MY_SET hMY_SET, void (*visit)(MYSTRING, GENERIC_VECTOR))
{
	My_set *pSet = (My_set*) hMY_SET;
	Node *temp = pSet->root;

	if(temp != NULL) 				// Make sure the set isn't empty!
	{
		printf("IN_ORDER\n");
		in_order_traverse(temp, visit);	// First in_order (REQUIRED)
		printf("\n\n");
		return TRUE;
	}
	else{
		printf("IN_ORDER\n\n");
		printf(" ( EMPTY ) \n\n");
	}

	return FALSE;		// If temp was NULL, must return a FAILURE. 
}


void other_traverse(MY_SET hMY_SET, void (*visit)(MYSTRING, GENERIC_VECTOR))
{
	My_set *pSet = (My_set*) hMY_SET;
	Node *temp = pSet->root;
	
	if(temp != NULL)
	{
		printf("PRE_ORDER\n");
		pre_order_traverse(temp, visit);	// Then pre_order (NOT REQUIRED)
		printf("\n\n");
		printf("POST_ORDER\n");
		post_order_traverse(temp, visit);	// Finally post_order (NOT REQUIRED)
	}
	else{
		printf("PRE_ORDER\n\n");
		printf(" ( EMPTY ) \n\n");
		printf("POST_ORDER\n\n");
		printf(" ( EMPTY ) \n");
	}
	
	return;
}


// Traverse the list in order of the Nodes.
void in_order_traverse(Node* root, void (*visit)(MYSTRING, GENERIC_VECTOR))
{
	if(root == NULL)	// Can't traverse an empty set!
	{
		return;
	}
	else
	{
		in_order_traverse(root->left, visit);	// Traverse left side.
		visit(root->data, root->hVector);		// Then visit root.
		in_order_traverse(root->right, visit);	// Traverse right side.
		return;
	}
}


void pre_order_traverse(Node* root, void(*visit)(MYSTRING, GENERIC_VECTOR))
{
	if(root == NULL)	// Can't traverse an empty set!
	{
		return;
	}
	else
	{
		visit(root->data, root->hVector);						// Then visit root.
		pre_order_traverse(root->left, visit);	// Traverse left side.
		pre_order_traverse(root->right, visit);	// Traverse right side.
		return;
	}

}


void post_order_traverse(Node* root, void(*visit)(MYSTRING, GENERIC_VECTOR))
{
	if(root == NULL)	// Can't traverse an empty set!
	{
		return;
	}
	else
	{
		post_order_traverse(root->left, visit);	// Traverse left side.
		post_order_traverse(root->right, visit);	// Traverse right side.
		visit(root->data, root->hVector);						// Then visit root.
		return;
	}

}


// Adds item to the set if it is not already in it.
Boolean my_set_add(MY_SET hMY_SET, MYSTRING item, MYSTRING word)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;
	Node *node = NULL;
	Boolean InSet   = TRUE;		// Used to indicate if a node is in the set or not.
	MyString_Status code;
	
	// If the handle isn't valid, we can't continue!
	if(hMY_SET == NULL)
	{
		printf("Error: hMY_SET is not valid!\n");
		return FAILURE;
	}
	
	// Make a new node function?
	node = (Node*) malloc(sizeof(Node));
	
	if(node == NULL)
	{
		printf("Error: failed to malloc node!\n");
		return FAILURE;
	}
	
	// Store the MYSTRING object in the node
	node->data = mystring_init_default();
	
	if(node->data == NULL)
	{
		printf("Failed to initialize MYSTRING object for the given node!\n");
		exit(1);
	}
	
	code = mystring_concatenate_mystring(node->data, item);
	
	if(code == MYSTRING_STATUS_ERROR)
	{
		printf("Failed to concatenate mystring object in the current node!\n");
		exit(1);
	}
	
	// Create a generic_vector object for use later
	node->hVector = make_vector_of_mystring();
	
	if(node->hVector == NULL)
	{
		printf("Failed to initialize hVector for the given node!\n");
		exit(1);
	}
	
	// Initialize the other members in the node
	node->left   = NULL;				// Make left/right NULL
	node->right  = NULL;
	node->number = 0;
	node->height = 1;					// Starts as a leaf at first.
	
	// Other wise we can just see if there's room somewhere,
	// by looking left / right etc.
	head = Add(head, node, &InSet, item, word);
	
	// If InList did not change to FALSE, then we added a new key!
	if(InSet == TRUE)
	{
		pSet->root = head;	// Updated pSet (hMY_SET) to include the new head.
		return TRUE;
	}
	
	// Prevent memory leaks if the tree wasn't enlarged
	destroy(node);
	
	return TRUE;		// The given key was already in the set if we get here.
}						// which perfectly fine for an associative array!


Node* Add(Node *next, Node *temp, Boolean *InSet, MYSTRING item, MYSTRING word)
{
	int bf;
	// First do the standard BST insertion

	//	We found a spot to put the node. Push the word back to the generic_vector at temp.
	if(next == NULL)
	{
		generic_vector_push_back(temp->hVector, word);
		return temp;
	}
	
	// In the case of keys, we CAN have the same key twice!
	// So don't do anything special in that case - just push word back to the generic_vector
	if(mystring_compare(next->data, item) == 0)
	{
	//	In the case of the same key being found,
	//	we just need to push the word back into the generic_vector.
		generic_vector_push_back(next->hVector, word);
		*InSet = FALSE;		// Note that the key was already in here - all we had to do
		return next;		// was push a word back to the vector!
	}
	
	// Look to the left side
	if(mystring_compare(item, next->data) == -1)
	{
		next->left = Add(next->left, temp, InSet, item, word);
	}
	
	// Look to the right side
	else if(mystring_compare(item, next->data) == 1)
	{
		next->right = Add(next->right, temp, InSet, item, word);
	}
	
	// Next update the height of the node that was just inserted
	next->height = max(height(next->left), height(next->right)) + 1;

	/* Finally, get the balance factor of the node to see if it made the
	   set unbalanced.	*/
	bf = getBF(next);

	// If the tree is unbalanced, then we have a few cases to test
	// Left Left		
	if (bf > 1 && ( (mystring_compare(item, next->left->data) ) == -1) )
	{
	    next = RotateRight(next);
	    return next;
	}

	// Right Right		mystring_compare(item, next->right->data)
	if (bf < -1 && ( (mystring_compare(item, next->right->data) ) == 1) )
	{
		next = RotateLeft(next);
	    return next;
	}

	// Left Right		( (mystring_compare(item, next->left->data) ) == 1)
	if (bf > 1 && ( (mystring_compare(item, next->left->data) ) == 1) )
	{
	    next->left =  RotateLeft(next->left);
	    next = RotateRight(next);
	    return next;
	}

	// Right Left	(mystring_compare(item, next->right->data) ) == 1)
	if (bf < -1 && ( (mystring_compare(item, next->right->data) ) == -1) )
	{
	    next->right = RotateRight(next->right);
	    next = RotateLeft(next);
	    return next;
	}
	
	// Return the given node.
	return next;
}


// Find and remove item from the set if it is present. Otherwise ignore.
Boolean my_set_remove(MY_SET hMY_SET, MYSTRING item)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;
	Node *next = head;
	Boolean InSet   = TRUE;		// Used to indicate if a node is in the set or not.
	
	// If the set isn't initialized, don't bother searching!
	if(hMY_SET == NULL)
	{
		printf("Error: hMY_SET is not initialized!\n");
		return FAILURE;
	}
	
	// If the set contains no nodes, don't bother searching!
	if(head == NULL)
	{
		printf("Error: cannot remove from an empty list!\n");
		return FAILURE;
	}
	
	// Other wise go through the list and try to find the item.
	next = Remove(next, item, &InSet);
	
	// If InList did not change to FALSE, then we removed the Node!
	if(InSet == TRUE)
	{
		pSet->root = next;	// Updated pSet (hMY_SET) to include the new head.
		return TRUE;
	}
	
	return FALSE;		// Something failed...
}


Node* Remove(Node *next, MYSTRING item, Boolean *InSet)
{
	Node *temp;
	int bf;
	MyString_Status code;

	// FIRST STEP: Perform the usual BST Delete
	
	// We found the end of a subtree, which means we didn't find the item!
	if(next == NULL)
	{
		printf("Error: ");
		mystring_output(item, stdout);
		printf(" is not in the list! Failed to remove it!\n");
		*InSet = FALSE;		// Signal to my_set_remove that we failed. :(
		return NULL;
	}	
	
	// If item is less than the current Node we are testing, go to the left subtree
	if(mystring_compare(item, next->data) == -1)				
	{
		next->left = Remove(next->left, item, InSet);
	}
	
	// Otherwise, go to the right subtree 
	else if(mystring_compare(item, next->data) == 1)			
	{
		next->right = Remove(next->right, item, InSet);
	}
	
	// WE FOUND THE ITEM! Now we have a few cases to run through
	else if(mystring_compare(next->data, item) == 0)			
	{		
		// NO sub children
		if(next->left == NULL && next->right == NULL)
		{
			free(next);
			next = NULL;
			return NULL;
		}
		
		// ONE sub child - on the LEFT
		if(next->left != NULL && next->right == NULL)
		{
			// Just relink it!
			temp = next->left;
			free(next);
			return temp;
		}	
			
		// ONE sub child - on the RIGHT
		if(next->left == NULL && next->right != NULL)
		{
			// Just relink it!
			temp = next->right;
			free(next);
			return temp;
		}

		// TWO sub children
		if(next->right != NULL && next->right != NULL)
		{
			// Get the inorder successor, which is the smallest node in the right subtree
			temp = next->right;
			
			// Go as far left as possible
			while(temp->left != NULL)
			{
			 	temp = temp->left;
			}
			
			// Now copy the successor into the current node			
			// First destroy the current mystring object located in next
			mystring_destroy(&(next->data));
			
			// Now re-initialize next->data
			next->data = mystring_init_default();
	
			// See if the re-initialize failed
			if(next->data == NULL)
			{
				printf("Failed to initialize MYSTRING object for the given node!\n");
				exit(1);
			}
			
			// Now copy the successor's data into the current node!
			code = mystring_concatenate_mystring(next->data, temp->data);
	
			if(code == MYSTRING_STATUS_ERROR)
			{
				printf("Failed to concatenate mystring object in the current node!\n");
				exit(1);
			}
			
			// Now delete the successor
			next->right = Remove(next->right, temp->data, InSet);
			
			return next;
		}
	}	

	// If this was a tree with one node, simply return.
	if(next == NULL)
		return next;
		
	// Next update the height of the current node
	next->height = max(height(next->left), height(next->right)) + 1;

	/* Finally, get the balance factor of the node to see if we made the
	   set unbalanced.	*/
	bf = getBF(next);
	
	// If the tree is unbalanced, then we have a few cases to test
	// Left Left
	if (bf > 1 && getBF(next->left) >= 0)
	{
        next = RotateRight(next);
        return next;
	}
	
	// Right Right
	if (bf < -1 && getBF(next->right) <= 0)
	{
		next = RotateLeft(next);
        return next;
	}
	
	// Left Right
	if (bf > 1 && getBF(next->left) < 0)
    {
        next->left =  RotateLeft(next->left);
        next = RotateRight(next);
        return next;
    }
	
	// Right Left
	if (bf < -1 && getBF(next->right) > 0)
    {
        next->right = RotateRight(next->right);
        next = RotateLeft(next);
        return next;
    }
    
    // At the very end return the node.
    return next;
}


// Rotating Functions
Node* RotateLeft(Node* ptr)
{
	Node* rightchild = ptr;

	if(ptr == NULL)		// Check to see if the tree exists.
	{
		printf("Error: Cannot rotate an empty tree!\n");
		return NULL;
	}
	else if(ptr -> right == NULL)		// Check to see if the subtree exists.
	{
		printf("Error: cannot make an empty tree the head in RotateLeft!\n");
		return NULL;
	}
	else		// If a tree & subtree exist, we are free to rotate to the left!
	{
		        rightchild =        ptr -> right;
	 	      ptr -> right = rightchild -> left;
		rightchild -> left =        ptr;
	}

	return rightchild;
}


Node* RotateRight(Node* ptr)
{
	Node* leftchild = ptr;

	if(ptr == NULL)		// Check to see if the tree exists.
	{
		printf("Error: Cannot rotate an empty tree!\n");
		return NULL;
	}
	else if(ptr -> left == NULL)		// Check to see if the subtree exists.
	{
		printf("Error: cannot make an empty tree the head in RotateLeft!\n");
		return NULL;
	}
	else		// If a tree & subtree exist, we are free to rotate to the left!
	{
		         leftchild =        ptr -> left;
	 	      ptr ->  left = leftchild -> right;
		leftchild -> right =        ptr;
	}

	return leftchild;
}


// Destroy the data structure and set the handle pointed to by the arg to NULL.
void my_set_destroy(MY_SET* p_hMY_SET)			
{
	My_set *temp = (My_set*)*p_hMY_SET;

	if(temp != NULL)
	{
		destroy(temp->root);
		free(temp);
	}

	*p_hMY_SET = NULL;
	return;
}

// Function called by my_set_destroy
void destroy(Node* root)
{
	if(root == NULL)
	{
		return;
	}
	else
	{
		destroy(root->left);
		destroy(root->right);
		// BEFORE FREEING THE NODE - FREE THE MYSTRING OBJECT AND THE VECTOR!
		mystring_destroy(&(root->data));
		generic_vector_destroy(&(root->hVector));
		free(root);
	}
}


/* Return the height of the AVL Tree implementation.
  (An empty tree has height 0, a tree with one node has height 1)	*/
int isbalanced(MY_SET hMY_SET)		
{	
	int lheight = 0;
	int rheight = 0;
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;

	// If the set pointer is NULL, well the list is empty!
	if(head == NULL)
	{				
		return -1;
	}
	
	// Otherwise, search through the list level by level.
	// Once we hit the max level, we can return the # of levels.
	if(head->left == NULL && head->right == NULL)
	{
		printf("Only one node! Height = 1\n");
		return 1;	// Only one node, so height 1. Thus balanced.
	}
	
	// If it isn't height 0 or 1, then we'll have to search the tree.
	// First get the heights of the left side and the right side
	lheight =  height(head -> left);
	rheight =  height(head -> right);
	printf("LEFT: %d\nRIGHT: %d\n", lheight, rheight);
	
	// See if the difference in height is 1 or less. For a balanced AVL tree 
	// it should be 0 or 1. IF IT ISN'T, the AVL tree isn't balanced.
	if(abs(lheight - rheight) <= 1 && balanced(head -> left) && balanced(head -> right) )
		return 1;		// AVL Tree is balanced!
		
	// If we get here, the tree is not balanced
	return 0;
}		


int getBF(Node* temp)
{
	int bf;	
	
	// If this Node is NULL, the BF is 0.
	if(temp == NULL)
		return 0;
	
	// Get the balance factor (BF)
	bf = height(temp->left) - height(temp->right);
	
	// Return it
	return bf;
}


int balanced(Node* temp)
{
	int lheight = 0;
	int rheight = 0;
	
	// If the set pointer is NULL, well the list is empty!
	if(temp == NULL)
	{				
		return 1;
	}
	
	// Otherwise, search through the list level by level.
	// Once we hit the max level, we can return the # of levels.
	if(temp->left == NULL && temp->right == NULL)
	{
		return 1;	// Only one node, so height 1.
	}
	
	// If it isn't height 0 or 1, then we'll have to search the tree.
	// First get the heights of the left side and the right side
	lheight =  height(temp -> left);
	rheight =  height(temp -> right);
	
	// See if the difference in height is 1 or less. For a balanced AVL tree 
	// it should be 0 or 1. IF IT ISN'T, the AVL tree isn't balanced.
	if(abs(lheight - rheight) <= 1 && balanced(temp -> left) && balanced(temp -> right) )
		return 1;		// AVL Tree is balanced!
		
	// If we get here, the tree is not balanced
	return 0;
}


int height(Node* node)
{
   // See if the tree is empty
   if(node == NULL)
       return 0;
 
   // If tree is not empty then height = 1 + max of left height and right heights
   return 1 + max(height(node->left), height(node->right));
} 


// returns maximum of two numbers
int max(int a, int b)
{
	// Simply see which is larger
	if(a >= b)
		return a;		// A was larger
	else
		return b;		// B was larger
}    
