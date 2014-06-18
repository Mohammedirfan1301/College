#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct char_vector
{
	int size;
	int capacity;
	char* data;
};
typedef struct char_vector Char_vector;
typedef struct _CHAR_VECTOR *CHAR_VECTOR;

struct my_vector
{
	int size;
	int capacity;
	int* data;
};
typedef struct my_vector My_vector; 
typedef struct _MY_VECTOR *MY_VECTOR;  

enum status {FAILURE, SUCCESS};
typedef enum status Status;

/*****************************************************************************
 * Create a new MY_VECTOR opaque object.
 *
 * @return
 *   Not enough memory = NULL
 *
 *   SUCCESS
 *   A MY_VECTOR handle to an empty vector object that has:
 *   size = 0, capacity = 1
 ****************************************************************************/
MY_VECTOR my_vector_init_default(void);

/*****************************************************************************
 * Retrieves the number of integers that the current vector holds.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to query the size of.
 *
 * @return
 *   The size of the vector or -1 on Error
 ****************************************************************************/
int my_vector_size(MY_VECTOR hVector);

/*****************************************************************************
 * Retrieves the total number of integers that the vector can contain before
 * it has to do an internal resize operation of the dynamic array.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to query the capacity of.
 * 
 * @return
 *   The capacity of the vector or -1 on Error
 ****************************************************************************/
int my_vector_capacity(MY_VECTOR hVector);

/*****************************************************************************
 * Attempts to add an element to the back of the vector, resizing if necessary
 * in order to hold the new element.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to insert a new element
 *   into.
 * @param item
 *   integer element to be copied and placed in the vector at the high end of
 *   the array indexes.
 * 
 * @return
 *   SUCCESS or
 *   FAILURE The internal resize operation failed with out of memory.
 ****************************************************************************/
Status my_vector_push_back(MY_VECTOR hVector, int item);

/*****************************************************************************
 * Attempts to remove an element from the back of the vector.  Will fail
 * if the vector is empty.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to remove an element
 *   from.
 * 
 * @return
 *   SUCCESS or
 *   FAILURE if the vector is empty.
 ****************************************************************************/
Status my_vector_pop_back(MY_VECTOR hVector);

/*****************************************************************************
 * Gives the user a pointer to the element at index param index so that they
 * can freely change it or view it.  This pointer will be invalidated if
 * any internal resize operation happens between when the user grabbed the
 * value and when they use it.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to look at the nth
 *   item.
 * @param index
 *   integer representing the index of the item that you want to have access to.
 * 
 * @return
 *   pointer to index of the index'th item
 *   NULL if the vector is empty or if the index is out of bounds
 ****************************************************************************/
int* my_vector_at(MY_VECTOR hVector, int index); //will do bounds checking


/*****************************************************************************
 * Destroy a MY_VECTOR opaque object and set the handle to NULL.
 * Will not attempt to destroy an object if the handle is NULL.
 *
 * @param pMy_VECTOR
 *   Address of a MY_VECTOR handle so that the function can free it and 
 *   change it to NULL.
 ****************************************************************************/
void my_vector_destroy(MY_VECTOR* pMY_VECTOR);


/*****************************************************************************
 * Create a new MY_VECTOR opaque object.
 *
 * @return
 *   Not enough memory = NULL
 *
 *   SUCCESS
 *   A MY_VECTOR handle to an empty vector object that has:
 *   size = 0, capacity = 1
 ****************************************************************************/
CHAR_VECTOR char_vector_init_default(void);

/*****************************************************************************
 * Retrieves the number of CHARACTERS that the current vector holds.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to query the size of.
 *
 * @return
 *   The size of the vector or -1 on Error
 ****************************************************************************/
int char_vector_size(CHAR_VECTOR hVector);

/*****************************************************************************
 * Retrieves the total number of CHARACTERS that the vector can contain before
 * it has to do an internal resize operation of the dynamic array.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to query the capacity of.
 * 
 * @return
 *   The capacity of the vector or -1 on Error
 ****************************************************************************/
int char_vector_capacity(CHAR_VECTOR hVector);

/*****************************************************************************
 * Attempts to add an element to the back of the vector, resizing if necessary
 * in order to hold the new element.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to insert a new element
 *   into.
 * @param item
 *   CHARACTER element to be copied and placed in the vector at the high end of
 *   the array indexes.
 * 
 * @return
 *   SUCCESS or
 *   FAILURE The internal resize operation failed with out of memory.
 ****************************************************************************/
Status char_vector_push_back(CHAR_VECTOR hVector, char item);

/*****************************************************************************
 * Attempts to remove an element from the back of the vector.  Will fail
 * if the vector is empty.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to remove an element
 *   from.
 * 
 * @return
 *   SUCCESS or
 *   FAILURE if the vector is empty.
 ****************************************************************************/
Status char_vector_pop_back(CHAR_VECTOR hVector);

/*****************************************************************************
 * Gives the user a pointer to the element at index param index so that they
 * can freely change it or view it.  This pointer will be invalidated if
 * any internal resize operation happens between when the user grabbed the
 * value and when they use it.
 *
 * @param hVector
 *   MY_VECTOR handle to the vector object that you want to look at the nth
 *   item.
 * @param index
 *   integer representing the index of the item that you want to have access to.
 * 
 * @return
 *   pointer to index of the index'th item
 *   NULL if the vector is empty or if the index is out of bounds
 ****************************************************************************/
char* char_vector_at(CHAR_VECTOR hVector, int index); //will do bounds checking


/*****************************************************************************
 * Destroy a MY_VECTOR opaque object and set the handle to NULL.
 * Will not attempt to destroy an object if the handle is NULL.
 *
 * @param pMy_VECTOR
 *   Address of a MY_VECTOR handle so that the function can free it and 
 *   change it to NULL.
 ****************************************************************************/
void char_vector_destroy(CHAR_VECTOR* pCHAR_VECTOR);

void run_tests(MY_VECTOR hVector, int n);
char get_user(void);
void print_vector(MY_VECTOR hVector, int n);

int main(int argc, char* argv[])
{
	MY_VECTOR hVector;
	int n;
	
	hVector = my_vector_init_default();
	
	if(hVector == NULL)
	{
		printf("Failed allocate space for the vector object!\n");
		exit(1);
	}

	printf("Enter a number, followed by that number of strings. -> ");
	scanf("%d ", &n);
	
	run_tests(hVector, n);
	
	print_vector(hVector, n);

	my_vector_destroy(&hVector);
	
	return 0;
}

char get_user(void)
{
	char input;
	struct termios change, current;				
	
	tcgetattr(STDIN_FILENO, &current );		
	change = current;
	change.c_lflag &= ~ICANON;				
	tcsetattr(STDIN_FILENO, TCSANOW, &change);

	input = getchar();						
	
	tcsetattr(STDIN_FILENO, TCSANOW, &current);
	
	return input;							
}

void print_vector(MY_VECTOR hVector, int n)
{
	int i;
	
	for(i = 0; i < n; i++)
	{
		if( *(my_vector_at(hVector, i) ) == 1)
			printf("Yes \n");
		else								
			printf("No \n");
	}
}

void run_tests(MY_VECTOR hVector, int n)
{
	CHAR_VECTOR hChar;	
	char *temp = NULL;
	char input = '\0', test = '\0';
	int i, problem;

	for(i = 0; i < n; i++)	
	{
		problem = 0;
		test = '\0';
		
		hChar = char_vector_init_default();
		
		if(hChar == NULL)
		{
			printf("Failed allocate space for the vector object!\n");
			exit(1);
		}
		
		do{
			input = get_user();
			
			test = '\0';

			if(input == '[' || input == '{' || input == '(') 
			{
				if(char_vector_push_back(hChar, input) == FAILURE) 
				{
					printf("Failed to push to the vector!\n");
					exit(1);
				}
			}
			
			if(input == ']' || input == '}' || input == ')') 
			{
				temp = char_vector_at(hChar, char_vector_size(hChar) - 1 );
					if(temp != NULL) 
						test = *temp;	
			
				if(test == '[' && input == ']') 
				{	 
					char_vector_pop_back(hChar);
				}
			
				if(test == '{' && input == '}') 
				{ 
					char_vector_pop_back(hChar);
				}
			
				if(test == '(' && input == ')') 
				{ 
					char_vector_pop_back(hChar);
				}

				if(test == '\0')
				{
					problem = 2;
				}
			}
			
		}while(input != '\n');
		
		if(char_vector_size(hChar) == 0 && problem != 2) 
		{
			problem = 1;	
		}
		
		if(problem == 2)
			problem = 0;
		
		if( (my_vector_push_back(hVector, problem)) == FAILURE)
		{
			printf("Failed to push to the vector!\n");
			exit(1);
		}
		
		char_vector_destroy(&hChar);
	}
}


CHAR_VECTOR char_vector_init_default(void)
{
	Char_vector *temp = NULL;

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
		vector->data[vector->size] = item;  
		vector->size++;  
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
		return FAILURE;
	}
	
	size = vector->size;

	if(size > 0)
	{
		vector->data[size] = 0;	
		vector->size--;			
	}
	else
		return FAILURE;
	
	return SUCCESS;		

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
		return -1;
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
		return -1;
	}
}

char* char_vector_at(CHAR_VECTOR hVector, int index)
{
	Char_vector* vector = (Char_vector*) hVector;

	if(vector != NULL)
	{
		if(index < vector->size && index >= 0 )
		{
			return &(vector->data[index]);
		}
	}

	return NULL;
}


MY_VECTOR my_vector_init_default(void)
{
	My_vector *temp = NULL;

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
		vector->data[vector->size] = item;  
		vector->size++;  
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
		return -1; 
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
		return -1; 
	}
}

int* my_vector_at(MY_VECTOR hVector, int index)
{
	My_vector* vector = (My_vector*) hVector;

	if(vector != NULL)
	{
		if(index < vector->size && index >= 0 )
		{
			return &(vector->data[index]);
		}
	}

	return NULL;
}


