#include <stdlib.h>
#include "my_vector.h"

struct my_vector
{
	int size;
	int capacity;
	int* data;
};
typedef struct my_vector My_vector;

MY_VECTOR my_vector_init_default(void)
{
	My_vector *temp = NULL;

	//allocate space for the vector object
	temp = (My_vector*)malloc(sizeof(My_vector));
	if(temp != NULL)
	{
		temp->size = 0;
		temp->capacity = 1;
		temp->data = (int*) malloc(sizeof(int)*temp->capacity);
		if(temp->data == NULL)
		{
			free(temp);
			temp = NULL;
		}
	}

	return (MY_VECTOR) temp;
}

void my_vector_destroy(MY_VECTOR* pMY_VECTOR)
{
	My_vector *temp = (My_vector*)(*pMY_VECTOR);
	if(temp != NULL)
	{
		free(temp->data);
		free(temp);
		*pMY_VECTOR = NULL;
	}
}

Status my_vector_push_back(MY_VECTOR hVector, int item)
{
	My_vector *vector = (My_vector*)(hVector);
	int *temp;
	int i;

	if(vector != NULL)
	{
		//is there enough room?
		if(vector->size >= vector->capacity)
		{
			vector->capacity *= 2;
			temp = (int*)malloc(sizeof(int)*vector->capacity);
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



int my_vector_size(MY_VECTOR hVector)
{
	My_vector* vector = (My_vector*) hVector;

	if(vector != NULL)
	{
		return vector->size;
	}
	else
	{
		return -1; // some invalid size
	}

}

int my_vector_capacity(MY_VECTOR hVector)
{
	My_vector* vector = (My_vector*) hVector;

	if(vector != NULL)
	{
		return vector->capacity;
	}
	else
	{
		return -1; // some invalid capacity
	}
}

int* my_vector_at(MY_VECTOR hVector, int index)
{
	My_vector* vector = (My_vector*) hVector;

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
