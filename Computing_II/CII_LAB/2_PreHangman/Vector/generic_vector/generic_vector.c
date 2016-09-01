#include <stdlib.h>
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
			temp->data[i] = NULL; //this is new in order to allow our assignment operator to "notice" when an object is invalid
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
		vector->functions.assignment(vector->data[vector->size], item);  //insert the element at position size...
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
