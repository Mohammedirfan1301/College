#include <stdio.h>
#include <stdlib.h>
#include "assocarray.h"

typedef struct node Node;

// TREE STRUCTURE.
struct node
{
	int data;		// Each node contains an int, and left / right pointers.
	Node *left;		// which point to another node and so on.
	Node *right;		
	int height;		// Keep track of the height of each node.
};

struct my_set		// MY_SET holds the root pointer.
{
	Node *root;	
};

typedef struct my_set My_set;

//	 Function declarations
void in_order_traverse(Node* root, void (*visit)(int));
void           destroy(Node* root);
void     SearchTree(Node *head, int item, Boolean *test);
int           FindSize(Node *temp, Node *numb);
Node*              Add(Node *head, Node *temp, Boolean *InSet, int item);
Node*           Remove(Node *next, int item, Boolean *InList);

//	Functions for TESTING
void other_traverse(MY_SET hMY_SET, void (*visit)(int));
void pre_order_traverse(Node* root, void(*visit)(int));
void post_order_traverse(Node* root, void(*visit)(int));

// Helpers for the size function
int isbalanced(MY_SET hMY_SET);
int balanced(Node* temp);
int height(Node* node);
int max(int a, int b);

// Rotating Functions
int getBF(Node* temp);
Node* RotateLeft(Node* ptr);
Node* RotateRight(Node* ptr);

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
Boolean my_set_is_element(MY_SET hMY_SET, int item)	
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
void SearchTree(Node *head, int item, Boolean *test)
{
	
	// Run through the list until we find the item!
	if(head != NULL)
	{
		if(head->data == item) 	// If we find the item, return TRUE!
		{
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
	numb->data = 0;
	
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
		numb->data++;	// Increase n for each node we find.
		FindSize(temp->right, numb);	// Search right
		FindSize(temp->left, numb);		// Search left
	}
	
	// Return the number of nodes.
	return numb->data;
}

// Call visit on each node in the set. (Inorder traversal)
Status my_set_traverse(MY_SET hMY_SET, void (*visit)(int))
{
	My_set *pSet = (My_set*) hMY_SET;
	Node *temp = pSet->root;

	if(temp != NULL) 				// Make sure the set isn't empty!
	{
		printf("IN_ORDER\n");
		in_order_traverse(temp, visit);	// First in_order (REQUIRED)
		printf("\n\n");
		return SUCCESS;
	}
	else{
		printf("IN_ORDER\n\n");
		printf(" ( EMPTY ) \n\n");
	}

	return FAILURE;		// If temp was NULL, must return a FAILURE. 
}

void other_traverse(MY_SET hMY_SET, void (*visit)(int))
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
void in_order_traverse(Node* root, void (*visit)(int))
{
	if(root == NULL)	// Can't traverse an empty set!
	{
		return;
	}
	else
	{
		in_order_traverse(root->left, visit);	// Traverse left side.
		visit(root->data);						// Then visit root.
		in_order_traverse(root->right, visit);	// Traverse right side.
		return;
	}
}

void pre_order_traverse(Node* root, void(*visit)(int))
{
	if(root == NULL)	// Can't traverse an empty set!
	{
		return;
	}
	else
	{
		visit(root->data);						// Then visit root.
		pre_order_traverse(root->left, visit);	// Traverse left side.
		pre_order_traverse(root->right, visit);	// Traverse right side.
		return;
	}

}

void post_order_traverse(Node* root, void(*visit)(int))
{
	if(root == NULL)	// Can't traverse an empty set!
	{
		return;
	}
	else
	{
		post_order_traverse(root->left, visit);	// Traverse left side.
		post_order_traverse(root->right, visit);	// Traverse right side.
		visit(root->data);						// Then visit root.
		return;
	}

}

// Adds item to the set if it is not already in it.
Status my_set_add(MY_SET hMY_SET, int item)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;
	Node *node = NULL;
	Boolean InSet   = TRUE;		// Used to indicate if a node is in the set or not.
	
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
	
	node->data   = item;				// Store the item in the node
	node->left   = NULL;				// Make left/right NULL
	node->right  = NULL;
	node->height = 1;					// Starts as a leaf at first.
	
	// Other wise we can just see if there's room somewhere,
	// by looking left / right etc.
	head = Add(head, node, &InSet, item);
	
	// If InList did not change to FALSE, then we found remove the Node!
	if(InSet == TRUE)
	{
		pSet->root = head;	// Updated pSet (hMY_SET) to include the new head.
		return SUCCESS;
	}
	
	return FAILURE;		// Something failed...
}


Node* Add(Node *next, Node *temp, Boolean *InSet, int item)
{
	int bf;
	/* First do the standard BST insertion */

	// If this is the first item in the tree, we must start at root!
	if(next == NULL){
		return temp;
	}
	
	// Cannot have the same item in the set twice!
	else if(next->data == item)
	{
		printf("Error: cannot insert same element twice into the AVL tree!\n");
		destroy(temp);		// Prevent memory leaks, as we malloc'd temp in my_set_add!
		*InSet = FALSE;
		return next;
	}
	
	// Look to the left side
	if(temp->data < next->data){
		next->left = Add(next->left, temp, InSet, item);
	}
	
	// Look to the right side
	else{
		next->right = Add(next->right, temp, InSet, item);
	}
	
	/* Next update the height of the node that was just inserted	*/
	next->height = max(height(next->left), height(next->right)) + 1;
	
	/* Finally, get the balance factor of the node to see if it made the
	   set unbalanced.	*/
	bf = getBF(next);
	
	// If the tree is unbalanced, then we have a few cases to test
	// Left Left
	if (bf > 1 && item < next->left->data)
	{
        next = RotateRight(next);
        return next;
	}
	
	// Right Right
	if (bf < -1 && item > next->right->data)
	{
		next = RotateLeft(next);
        return next;
	}
	
	// Left Right
	if (bf > 1 && item > next->left->data)
    {
        next->left =  RotateLeft(next->left);
        next = RotateRight(next);
        return next;
    }
	
	// Right Left
	if (bf < -1 && item < next->right->data)
    {
        next->right = RotateRight(next->right);
        next = RotateLeft(next);
        return next;
    }
	
	// Return the given node.
	return next;
}


// Find and remove item from the set if it is present. Otherwise ignore.
Status my_set_remove(MY_SET hMY_SET, int item)		
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
		return SUCCESS;
	}
	
	return FAILURE;		// Something failed...
}

Node* Remove(Node *next, int item, Boolean *InSet)
{
	Node *temp;
	int bf;

	// FIRST STEP: Perform the usual BST Delete
	
	// We found the end of a subtree, which means we didn't find the item!
	if(next == NULL)
	{
		printf("Error  %d is not in the list! Failed to remove it!\n", item);
		*InSet = FALSE;		// Signal to my_set_remove that we failed. :(
		return NULL;
	}	
	
	// If item is less than the current Node we are testing, go to the left subtree
	if(item < next->data)				
	{
		next->left = Remove(next->left, item, InSet);
	}
	// Otherwise, go to the right subtree 
	else if(item > next->data)			
	{
		next->right = Remove(next->right, item, InSet);
	}
	
	// WE FOUND THE ITEM! Now we have a few cases to run through
	else if(item == next->data)			
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
			next->data = temp->data;
			
			// Now delete the successor
			next->right = Remove(next->right, temp->data, InSet);
			
			return next;
		}
	}	

	// If this was a tree with one node, simply return.
	if(next == NULL)
		return next;
		
	/* Next update the height of the current node	*/
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
