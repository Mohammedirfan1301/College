#include <stdio.h>
#include <stdlib.h>
#include "my_set.h"

typedef struct node Node;

// LH = left higher		EQ = equal heights		RH = right higher
typedef enum Balanced{LH, EH, RH} Balanced;	// Enum for determing if a tree is balanced

// TREE STRUCTURE.
struct node
{
	int data;		// Each node contains an int, and left / right pointers.
	Node * left;	// which point to another node and so on.
	Node * right;		
	Balanced bf;	// Know whether the function is balanced or not.
};

struct my_set
{
	Node * root;	
};

typedef struct my_set My_set;

//	 Function declarations
void in_order_traverse(Node* root, void (*visit)(int));
void           destroy(Node* root);
Boolean     SearchTree(Node *head, int item);
Node* my_set_at(Node *head, int item);
int           FindSize(Node *temp, Node *numb);
Node*              Add(Node *head, Node *temp, Boolean *taller, Boolean *InSet, int item);
Node*           Remove(Node *head, Node *next, int item, Boolean *shorter, Boolean *InList);

//	Functions for TESTING
void pre_order_traverse(Node* root, void(*visit)(int));
void post_order_traverse(Node* root, void(*visit)(int));

// Helpers for the size function
int isbalanced(MY_SET hMY_SET);
int balanced(Node* temp);
int height(Node* node);
int max(int a, int b);

// Balancing functions
Node*  Balance_Left(Node *head, Boolean *taller);
Node* Balance_Right(Node *head, Boolean *taller);

// Rotating Functions
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
	Node *temp = pSet->root;
	Boolean Code;
	
	// First see if the list is empty.
	if(temp == NULL)
	{
		printf("Error: can't find an item in an empty list!\n");
		return FALSE;
	}
			
	// Other wise run through the list until we find the item!
	if(temp != NULL)
	{
		// Call Search tree to do this for us.
		Code = SearchTree(temp, item);
	}

	if(Code == TRUE)
		return TRUE;

//	Failed to find the item!
	return FALSE;
}

// Returns TRUE if an item is in the set. False if it is not.
Boolean SearchTree(Node *head, int item)
{
	Boolean test;
	
	// Run through the list until we find the item!
	if(head != NULL)
	{
		if(head->data == item) 	// If we find the item, return TRUE!
			return TRUE;
		test = SearchTree(head->left, item);	// Search  left side
		test = SearchTree(head->right, item);	// Search right side
	}
	
	// If one of the recursive functions found the item, return SUCCESS!
	if(test == TRUE)
		return TRUE;
	
	// If we get here, return FALSE - we didn't find the item.
	return FALSE;
}


// Returns TRUE if an item is in the set. False if it is not.
Node* my_set_at(Node *head, int item)
{	
	// Run through the list until we find the item!
	if(head != NULL)
	{
		if(head -> data == item) 	// If we find the item, return TRUE!
			return head;
		head = my_set_at(head->left, item);	// Search  left side
		head = my_set_at(head->right, item);	// Search right side
	}
	
	// If one of the recursive functions found the item, return SUCCESS!
	if(head -> data == item)
		return head;
	
	// If we get here, return FALSE - we didn't find the item.
	return NULL;
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
	
	destroy(numb);		// Prevent memory leaks.
	
	return number_of_nodes;
}

int FindSize(Node *temp, Node *numb)
{
	if(temp != NULL)
	{
		numb->data++;	// Increase n for each node we find.
		FindSize(temp->right, numb);	// Search right
		FindSize(temp->left, numb);	// Search left
	}
	
	// Return the number of nodes.
	return numb->data;
}

// Call visit on each node in the set. (Inorder traversal)
Status my_set_traverse(MY_SET hMY_SET, void (*visit)(int))
{
	My_set * temp = (My_set*) hMY_SET;

	if (temp != NULL) 	// Make sure the set isn't empty!
	{
		printf("IN_ORDER\n");
		in_order_traverse(temp->root, visit);	// First in_order (REQUIRED)
		printf("\n\n");
		printf("PRE_ORDER\n");
		pre_order_traverse(temp->root, visit);	// Then pre_order (NOT REQUIRED)
		printf("\n\n");
		printf("POST_ORDER\n");
		post_order_traverse(temp->root, visit);	// Finally post_order (NOT REQUIRED)
		return SUCCESS;
	}

	return FAILURE;		// If temp was NULL, must return a FAILURE. 
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
	Node *temp = NULL;
	Boolean taller = TRUE;
	Boolean InSet   = TRUE;		// Used to indicate if a node is in the set or not.
	
	// If the handle isn't valid, we can't continue!
	if(hMY_SET == NULL)
	{
		printf("Error: hMY_SET is not valid!\n");
		return FAILURE;
	}
	
	temp = (Node*) malloc(sizeof(Node));
	
	if(temp == NULL)
	{
		printf("Error: failed to malloc node!\n");
		return FAILURE;
	}
	
	temp -> data = item;				// Store the item in the node
	
	// Other wise we can just see if there's room somewhere,
	// by looking left / right etc.
	head = Add(head, temp, &taller, &InSet, item);
	
	// If InList did not change to FALSE, then we found remove the Node!
	if(InSet == TRUE)
	{
		pSet->root = head;	// Updated pSet (hMY_SET) to include the new head.
		return SUCCESS;
	}
	
	return FAILURE;		// Something failed...
}


Node* Add(Node *head, Node *temp, Boolean *taller, Boolean *InSet, int item)
{
	// If this is the first item in the tree, we must start at root!
	if(head == NULL)
	{
		head = temp;							// Set root equal to the new node.
		head ->  left = head -> right = NULL;	// Make left/right side NULL
		temp -> bf = EH;						// Root is equal
		*taller = TRUE;							// Height increased
	}
	
	else if(head->data == item)
	{
		printf("Error: cannot insert same element twice into the AVL tree!\n");
		destroy(temp);		// Prevent memory leaks, as we malloc'd temp in my_set_add!
		*taller = FALSE;
		*InSet = FALSE;
		return head;
	}
	
	else if(temp->data < head->data)	// Look to the left side
	{
		head -> left = Add(head -> left, temp, taller, InSet, item);
		if(*taller)
			switch(head -> bf)
			{
				case LH:
					head = Balance_Left(head, taller);	// Node was high on the left side.	
					break;
				case EH:
					head -> bf = LH;	// Node is now higher on the left side.
					break;
				case RH:
					head -> bf = EH;	// Node is now balanced height
					*taller = FALSE;
					break;
			}
	}
	
	else 					// Look to the right side
	{
		head -> right = Add(head -> right, temp, taller, InSet, item);
		if(*taller)
			switch(head -> bf)
			{
				case LH:				
					head -> bf = EH;	// Node is now balanced height
					*taller = FALSE;
					break;
				
				case EH:
					head -> bf = RH;	// Node is now higher on the right side.
					break;
				case RH:				// Node was higher on the right side.	
					head = Balance_Right(head, taller);	
					break;
			}
	}
	
	return head;
}


// Find and remove item from the set if it is present. Otherwise ignore.
Status my_set_remove(MY_SET hMY_SET, int item)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;
	Node *next = head;
	Boolean shorter = TRUE;
	Boolean InSet   = TRUE;		// Used to indicate if a node is in the set or not.
	
	// If the set isn't initialized, don't bother searching!
	if(hMY_SET == NULL)
	{
		printf("Error: set is not initialized!\n");
		return FAILURE;
	}
	
	// If the set contains no nodes, don't bother searching!
	if(head == NULL)
	{
		printf("Error: cannot remove from an empty list!\n");
		return FAILURE;
	}
	
	// Other wise go through the list and try to find the item.
	next = Remove(head, next, item, &shorter, &InSet);
	
	// If InList did not change to FALSE, then we found remove the Node!
	if(InSet == TRUE)
	{
		pSet->root = next;	// Updated pSet (hMY_SET) to include the new head.
		return SUCCESS;
	}
	
	return FAILURE;		// Something failed...
}

Node* Remove(Node *head, Node *next, int item, Boolean *shorter, Boolean *InSet)
{
	Node *temp;

	// FIRST STEP: Perform the usual BST Delete

	// If head is NULL, the set is empty. So we can't remove anything, so return NULL.
	if(head == NULL)
	{
		printf("Error - can't remove from an empty set!\n");
		*InSet = FALSE;		// Signal to my_set_remove that we failed. :(
		return NULL;
	}
	
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
		next -> left = Remove(head, next->left, item, shorter, InSet);/*
		if(*shorter)
			switch(next -> bf)
			{
				case RH:
					// Changes should be made HERE
					temp = next->right;
					
					// next is P
					// temp is Q
					
					switch(temp->bf)
					{
						case LH:	// NOT EQUAL
							// Double rotation, leave as TRUE	
							// FIRST around Q then around P
							temp = RotateRight(temp);
							next = RotateLeft(next);
							next->bf = EH;
							next->right->bf = EH;
							next->left->bf = EH;

							break;
							
						case EH:	// Q IS EQUAL
							// Single rotation, FALSE
								temp = RotateLeft(temp);
							temp->bf = LH;
							next->bf = RH;
							*shorter = FALSE;
							break;
						
						case RH:	// EQUAL
							// Single rotation, leave TRUE
								temp = RotateLeft(temp);
							temp->bf = EH;
							next->bf = EH;
						
							break;
					}
					
					break;
					
				case EH:
					next -> bf = RH;	// Node is now higher on the left side.
					*shorter = FALSE;
					break;
					
				case LH:
					next -> bf = EH;	// Node is now balanced height
					break;
			}*/
	}
	
	// If item is greater than the current Node we are testing, go to the right subtree
	else if(item > next->data)			
	{
		next -> right = Remove(head, next->right, item, shorter, InSet);
		/*if(*shorter)
			switch(head -> bf)
			{
				case LH:				
					next -> bf = EH;	// Node is now balanced height
					break;
				case EH:
					next -> bf = LH;	// Node is now higher on the right side.
					*shorter = FALSE;
					break;
				case RH:				// Node was higher on the right side.	
					// Changes should be made HERE
					
					
					break;
			}*/
	}
	
	// WE FOUND THE ITEM! Now we have a few cases to run through
	else if(item == next->data)			
	{		
		// NO sub children
		if(next->left == NULL && next->right == NULL)
		{
			free(next);
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
			temp = next -> right;
			
			while(temp -> left != NULL)	// When head->right == NULL, this stops.
			{
			 	temp = temp -> left;
			}
			
			// Now copy temp into next
			next -> data = temp -> data;
			
			// Now delete the inorder successor
			next -> right = Remove(head, next -> right, next -> data, shorter, InSet);
			
			// List did NOT get get shorter!
			*shorter = FALSE;
			
			// Return next
			return next;
		}
	}	

	// Just return head.
	return head;
}


// Balancing functions.
Node* Balance_Left(Node *head, Boolean *taller)
{
	Node* ls = head -> left;				// Left subtree of root
	Node* rs;								// Right subtree of root
	
	switch (ls -> bf)
	{
		case RH:							// Double roation right
			rs = ls -> right;				// (Left Right Case)
			
			switch(rs -> bf)
			{
				case RH:
					head -> bf = EH;
					  ls -> bf = LH;
					break;
					
				case EH:
					head -> bf = ls -> bf = EH;
					break;

				case LH:
					head -> bf = RH;
					  ls -> bf = EH;
					break;
			}
			
			// Double rotation. First rotate left, then right.
			  rs -> bf   = EH;				
			head -> left = RotateLeft(ls);
			        head = RotateRight(head);
			*taller = FALSE;
			break;
		
		case EH:							// No need to rotate!
			printf("Error: the tree is already balanced! (BL)\n");
			break;
		
		case LH:							// Single rotation right
			head -> bf = ls -> bf = EH;
			head = RotateRight(head);
			*taller = FALSE;							
			break;
	}
	return head;
}

Node* Balance_Right(Node *head, Boolean *taller)
{
	Node* rs = head -> right;		// Right subtree of root
	Node* ls;						// Left subtree of right subtree
	
	switch (rs -> bf)
	{
		case RH:								// Single rotation left
			head -> bf = rs -> bf = EH;			// (Right Right Case)
			head = RotateLeft(head);
			*taller = FALSE;
			break;
		
		case EH:								// No need to rotate!
			printf("Error: the tree is already balanced! (BR)\n");
			break;
		
		case LH:								// Double roation left
			ls = rs -> left;					// (Right Left Case)
			
			switch(ls -> bf)
			{
				case RH:						
					head -> bf = LH;
					  rs -> bf = EH;
					break;
					
				case EH:
					head -> bf = rs -> bf = EH;
					break;

				case LH:
					head -> bf = EH;
					  rs -> bf = RH;
					break;
			}
			// Double rotation. First rotate right, then left.
			     ls -> bf = EH;	
			head -> right = RotateRight(rs);
			         head = RotateLeft(head);
				  *taller = FALSE;
			
			break;
	}
	return head;
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
		return 1;
	}
	
	// Otherwise, search through the list level by level.
	// Once we hit the max level, we can return the # of levels.
	if(head->left == NULL && head->right == NULL)
	{
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