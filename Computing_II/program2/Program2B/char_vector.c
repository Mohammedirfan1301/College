#include <stdlib.h>
#include "char_vector.h"

struct char_vector
{
	int size;
	int capacity;
	char* data;
};
typedef struct char_vector Char_vector;

CHAR_VECTOR char_vector_init_default(void)
{
	Char_vector *temp = NULL;

	//allocate space for the vector object
	temp = (Char_vector*)malloc(sizeof(Char_vector));
	if(temp != NULL)
	{
		temp->size = 0;
		temp->capacity = 1;
		temp->data = (char*) malloc(sizeof(char)*temp->capacity);
		if(temp->data == NULL)
		{
			free(temp);
			temp = NULL;
		}
	}

	return (CHAR_VECTOR) temp;
}

void char_vector_destroy(CHAR_VECTOR* pCHAR_VECTOR)
{
	Char_vector *temp = (Char_vector*)(*pCHAR_VECTOR);
	if(temp != NULL)
	{
		free(temp->data);
		free(temp);
		*pCHAR_VECTOR = NULL;
	}
}

Status char_vector_push_back(CHAR_VECTOR hVector, char item)
{
	Char_vector *vector = (Char_vector*)(hVector);
	char *temp;
	int i;

	if(vector != NULL)
	{
		//is there enough room?
		if(vector->size >= vector->capacity)
		{
			vector->capacity *= 2;
			temp = (char*)malloc(sizeof(char)*vector->capacity);
			if(temp != NULL)
			{			
				for(i = 0; i < vector->size; i++)
				{
					temp[i] = vector->data[i];
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
		vector->data[vector->size] = item;  //insert the element at position size...
		vector->size++;  //increase the size
		return SUCCESS;
	}

	return FAILURE;	
}

Status char_vector_pop_back(CHAR_VECTOR hVector)
{
	Char_vector *vector = (Char_vector*)(hVector);
	int size;
	
	if(vector == NULL)
	{
		//Vector is empty - return FAILURE.
		return FAILURE;
	}
	
	//If it isn't failure, attempt to remove from the back of the vector.
	size = vector->size;	//Get the size, store it in i.
	
	//Try to remove the item
	if(size > 0)
	{
		vector->data[size] = 0;	//The empty is removed.
		vector->size--;			//Decrease size by 1. Leave capacity as is.
	}
	else
		return FAILURE;
	
	return SUCCESS;		//We're done! Return success.	

}

int char_vector_size(CHAR_VECTOR hVector)
{
	Char_vector* vector = (Char_vector*) hVector;

	if(vector != NULL)
	{
		return vector->size;
	}
	else
	{
		return -1; // some invalid size
	}

}

int char_vector_capacity(CHAR_VECTOR hVector)
{
	Char_vector* vector = (Char_vector*) hVector;

	if(vector != NULL)
	{
		return vector->capacity;
	}
	else
	{
		return -1; // some invalid capacity
	}
}

char* char_vector_at(CHAR_VECTOR hVector, int index)
{
	Char_vector* vector = (Char_vector*) hVector;

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
