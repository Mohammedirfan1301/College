#include <stdio.h>
#include <stdlib.h>
#include "my_vector.h"

int main(int argc, char* argv[])
{
	MY_VECTOR hNumbers;
	int i;
	int size;
	int *unsafe_iter;

	hNumbers = my_vector_init_default();

	for(i = 0; i<100; i++)
	{
		if(my_vector_push_back(hNumbers, rand()) == FAILURE)
		{
			printf("bad stuff\n");
			exit(1);
		}
		printf("%d / %d\n", my_vector_size(hNumbers),my_vector_capacity(hNumbers));
	}

	//safe way
	size = my_vector_size(hNumbers);
	for(i=0; i<size; i++)
	{
		printf("%d\t", *(my_vector_at(hNumbers, i)));
	}

	//unsafe (fast) way
	size = my_vector_size(hNumbers);

	for(i=0, unsafe_iter = my_vector_at(hNumbers, 0); i<size; i++, unsafe_iter++)
	{
		printf("%d\t", *unsafe_iter);
	}
	my_vector_destroy(&hNumbers);



	return 0;
}
