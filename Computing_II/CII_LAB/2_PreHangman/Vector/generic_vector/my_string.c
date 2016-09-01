#include <stdlib.h>
#include "my_string.h"


struct my_string
{
	int size;
	int capacity;
	char* data;
};
typedef struct my_string My_string;

void string_assignment(void* left, void* right)
{
	char* temp;
	int i; 
	My_string* real_left = (My_string*) left;
	My_string* real_right = (My_string*) right;

	if(real_left == NULL)
	{
		real_left = (My_string*) mystring_init_default();
	}
	if(real_left != NULL && real_right != NULL)
	{
		//both objects "supposedly" exist so try to do a deep copy
		//if the left side is not big enough to store the right's data then 
		//make it bigger.
		if(real_left->capacity < real_right->size)
		{
			real_left->capacity = real_right->size;
			temp = (char*)malloc(sizeof(char)*real_left->capacity);
			if(temp == NULL)
			{
				fprintf(stderr, "I ran out of memory and I give up...\n");
				exit(1);
			}
			free(real_left->data);
			real_left->data = temp;
		}
		//fix left's size to match right's
		real_left->size = real_right->size;
		//copy over all the data
		for(i=0; i<real_right->size; i++)
		{
			real_left->data[i] = real_right->data[i];
		}
	}
	else
	{
		//if right is NULL we can't really do the right thing so let's just crash for now
		fprintf(stderr, "Tried to do string_assignment but the right hand side was NULL\n");
		exit(1);
	}

}

MYSTRING mystring_init_default(void)
{
	My_string* temp;

	temp = (My_string*) malloc(sizeof(My_string));
	if(temp != NULL)
	{
		temp->capacity = MYSTRING_STARTING_CAPACITY;
		temp->size = 0;
		temp->data = (char*) malloc(sizeof(char)*temp->capacity);
		if(temp->data == NULL)
		{
			free(temp);
			temp = NULL;
		}
	}

	return (MYSTRING) temp;
}

void mystring_destroy(MYSTRING* p_hString)
{
	My_string* temp = (My_string*) *p_hString;

	if(temp != NULL)
	{
		free(temp->data);
		free(temp);
		*p_hString = NULL;
	}
}

void string_destructor(void** object)
{
	mystring_destroy((MYSTRING*)object);
}