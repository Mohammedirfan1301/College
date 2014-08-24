#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"
#include "my_string.h"

void int_assignment(void* left, void* right)
{
	int i; 
	int* real_left = (int*) left;
	int* real_right = (int*) right;

	if(real_left == NULL)
	{
		real_left = malloc.....;
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

int main(int argc, char* argv[])
{
	GENERIC_VECTOR hVector_of_strings;
	GENERIC_VECTOR hVector_of_integers;
	Generic_vector_functions functions;
	Generic_vector_functions int_functions;
	MYSTRING hString;
	int i;

	
	functions.assignment = string_assignment;
	functions.destructor = string_destructor;

	int_functions.assignment = int_assignment;
	int_functions.destructor = int_destructor;

	hVector_of_strings = generic_vector_init_default(functions);
	hVector_of_integers = generic_vector_init_default(int_functions);

	for(i=0; i<1000; i++)
	{
		printf("%d\n", i);
		hString = mystring_init_default();
		printf("%d\n", i);
		generic_vector_push_back(hVector_of_strings, hString);
		mystring_destroy(&hString);
	}

	generic_vector_destroy(&hVector_of_strings);

	return 0;
}
