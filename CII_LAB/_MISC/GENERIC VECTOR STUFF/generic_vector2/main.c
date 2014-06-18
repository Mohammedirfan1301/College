#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"
#include "my_string.h"

void int_assignment(void** left, void* right)
{
	int i; 
	int* real_left = (int*) *left;
	int* real_right = (int*) right;

	if(real_left == NULL)
	{
		*left = real_left = (int*)malloc(sizeof(int));
	}
	if(real_left != NULL && real_right != NULL)
	{
		//both objects "supposedly" exist so try to do a deep copy
		*real_left = *real_right;
	}
	else
	{
		//if right is NULL we can't really do the right thing so let's just crash for now
		fprintf(stderr, "Tried to do int_assignment but the right hand side was NULL\n");
		exit(1);
	}
	
}

void int_destructor(void** object)
{
	int* temp = (int*)*object;
	if(temp != NULL)
	{
		free(temp);
	}
	*object = NULL;
}

int main(int argc, char* argv[])
{
	GENERIC_VECTOR hVector_of_strings;
	GENERIC_VECTOR hVector_of_integers;
	Generic_vector_functions functions;
	Generic_vector_functions int_functions;
	MYSTRING hString;
	int i;
	int** ptr;
	int item;

	
	functions.assignment = string_assignment;
	functions.destructor = string_destructor;

	int_functions.assignment = int_assignment;
	int_functions.destructor = int_destructor;

	hVector_of_strings = generic_vector_init_default(functions);
	hVector_of_integers = generic_vector_init_default(int_functions);

	for(i=0; i<1000; i++)
	{
		item = rand();
		generic_vector_push_back(hVector_of_integers, &item);
	}

	for(i=0; i<generic_vector_size(hVector_of_integers); i++)
	{
		ptr = (int**)generic_vector_at(hVector_of_integers, i);
		printf("%d\n", **ptr);
	}

	generic_vector_destroy(&hVector_of_integers);
	generic_vector_destroy(&hVector_of_strings);

	return 0;
}
