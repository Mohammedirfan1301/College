#include <stdlib.h>
#include <stdio.h>
#include "generic_vector.h"

struct generic_vector
{
	int size;
	int capacity;
	Generic_vector_functions functions;
	void** data; //dynamic array of void*
};
typedef struct generic_vector Generic_vector;

GENERIC_VECTOR generic_vector_init_default(Generic_vector_functions functions)
{
	Generic_vector *temp = NULL;
	int i;

	//allocate space for the vector object
	temp = (Generic_vector*)malloc(sizeof(Generic_vector));
	if(temp != NULL)
	{
		temp->size = 0;
		temp->capacity = 1;
		temp->functions = functions;
		temp->data = (void**) malloc(sizeof(void*)*temp->capacity);
		for(i=0; i<temp->capacity; i++)
		{
			temp->data[i] = NULL; 
			//this is new in order to allow our assignment operator to "notice" when an object is invalid
		}
		if(temp->data == NULL)
		{
			free(temp);
			temp = NULL;
		}
	}

	return (GENERIC_VECTOR) temp;
}

//fix memory leak for opaque objects by calling a generic destroy on each valid element before freeing the array
void generic_vector_destroy(GENERIC_VECTOR* pGENERIC_VECTOR)
{
	Generic_vector *temp = (Generic_vector*)(*pGENERIC_VECTOR);
	int i;
	if(temp != NULL)
	{
		for(i=0; i<temp->size; i++)
		{
			temp->functions.destructor(&(temp->data[i]));
		}
		free(temp->data);
		free(temp);
		*pGENERIC_VECTOR = NULL;
	}
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, void* item)
{
	Generic_vector *vector = (Generic_vector*)(hVector);
	void** temp;
	int i;

	if(vector != NULL)
	{
		//is there enough room?
		if(vector->size >= vector->capacity)
		{
			vector->capacity *= 2;
			temp = (void**)malloc(sizeof(void*)*vector->capacity);
			if(temp != NULL)
			{			
				for(i = 0; i < vector->size; i++)
				{
					temp[i] = vector->data[i]; //safe to do a shallow copy
				}
				for(;i<vector->capacity; i++) //fill the rest of the added capacity with NULL
				{
					temp[i] = NULL;
				}
				free(vector->data);
				vector->data = temp;
			}
			else
			{
				vector->capacity /= 2;
				return FAILURE;
			}

		}
		vector->functions.assignment(&(vector->data[vector->size]), item);  //insert the element at position size...
		vector->size++;  //increase the size
		return SUCCESS;
	}

	return FAILURE;	
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
	Generic_vector *vector = (Generic_vector*)(hVector);
	if(vector != NULL)
	{
		if(vector->size > 0)
		{
			vector->size--;
			return SUCCESS;
		}
	}
	return FAILURE;
}



int generic_vector_size(GENERIC_VECTOR hVector)
{
	Generic_vector* vector = (Generic_vector*) hVector;

	if(vector != NULL)
	{
		return vector->size;
	}
	else
	{
		return -1; // some invalid size
	}

}

int generic_vector_capacity(GENERIC_VECTOR hVector)
{
	Generic_vector* vector = (Generic_vector*) hVector;

	if(vector != NULL)
	{
		return vector->capacity;
	}
	else
	{
		return -1; // some invalid capacity
	}
}

void* generic_vector_at(GENERIC_VECTOR hVector, int index)
{
	Generic_vector* vector = (Generic_vector*) hVector;

	if(vector != NULL)
	{
		//check the bounds
		if(index < vector->size && index >= 0 )
		{
			return &(vector->data[index]);
		}
	}

	return NULL;
}

// Makes a vector of vector
GENERIC_VECTOR make_vector_of_vector(void)
{
	GENERIC_VECTOR temp;				// temp ptr to GEN VECTOR
	Generic_vector_functions functions;	// ptr to functions struct
		
	// Set the function pointers equal to their respected functions.
	functions.assignment = myvector_assignment;
	functions.destructor = myvector_destroyer;
	
	// Initialize the Vector, send it the functions ptr as well!
	temp = generic_vector_init_default(functions);
	
	// Check to see it initialized!
	if(temp == NULL)
		return NULL;
	
	// Return the pointer to the vector if it exists.
	return temp;
}


// ASSIGNMENT USED IN DICTIONARY.C
void myvector_assignment(void** hVectVect, void* hVectofStr)
{
	Generic_vector* real_left  = (Generic_vector*) *hVectVect;
	Generic_vector* real_right = (Generic_vector*)  hVectofStr;
	void** temp;
	int x;
	
	if(real_left == NULL)
	{
		// Left side doesn't exist, so create it!
		*hVectVect = real_left = (Generic_vector*)make_vector_of_vector();
	}
	if(real_left != NULL && real_right != NULL)
	{
		// Both objects should exist, so we should be able to store the
		// Vector of MYSTRINGs in the Vector of GENERIC_VECTORs

		//	If left side is smaller than the right side, we must do a resize.
		if(real_left -> capacity < real_right -> size)
		{
			real_left -> capacity = real_right -> size;
			temp = (void**)malloc(sizeof(void)*real_left->capacity);
			
		//	If the resize failed,
			if(temp == NULL)
			{
			//	Print an error and quit.
				fprintf(stderr, "Malloc failed!\n");
				exit(1);
			}
			
			free(real_left -> data);		// Free up the old array
			real_left -> data = temp;		// Update left's data array pointer.
		}
		
	//	Update left side's size, so it matches the right side.
		real_left -> size = real_right -> size;
		
	//	Copy all the data from right side to left side.
		for(x = 0; x < real_right -> size; x++)
		{
			real_left -> data[x] = real_right -> data[x];
		}	
	}
	else
	{
	//	If both real's are NULL, it is not safe to do a myvector assignment.
		fprintf(stderr, "Tried to do myvector_assignment but the right hand side was NULL\n");
		exit(1);
	} 

	return;
}


void myvector_destroyer(void** hVector)
{
	generic_vector_destroy((GENERIC_VECTOR*)&hVector);
	
	return;
}
