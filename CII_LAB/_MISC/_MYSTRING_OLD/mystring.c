#include <stdio.h>
#include <mystring.h>	//include the mystring header file

//This file - mystring.c - will implment all the functions in mystring.h

int main(int argc, char* argv[])
{
	char* pTemp;
	pTemp = mystring_init_default();
	
	if(pTemp == NULL)
		printf("Failure -> mystring_init_default. \n");
	if(pTemp != NULL)
		printf("Success -> mystring_init_default. \n");
	
}

MYSTRING mystring_init_default(void)
{
	struct *MYSTRING{
		int size = 0;
		int capacity = MYSTRING_STARTING_CAPACITY;
		char* cstring;
	}
	
	if(*MYSTRING == NULL)
	{
		return NULL;				//FAILURE! WE COULD NOT ALLOCATE MEMORY
	}
	else if(*MYSTRING != NULL)
	{						
		return *MYSTRING;			//SUCCESS! WE WERE ABLE TO ALLOCATE MEMORY
	}
}

MYSTRING mystring_init_c_string(const char * const c_string)
{
	int len;
	//Figure out the size of the c_string
	while(len = 0);
	{
		if(c_string[len] = NULL)	//Stop searching if the c_string equals NULL
			break;
		else						//To keep searching add 1 to the length variable
			len++;
	}
	
	/*
	Few things need to happen:
	Malloc a struct - a 'bubble' containing the three members - size, capacity and a pointer to a string
	Malloc up enough space for the pString in the struct - NOT including its NULL terminator
	Copy the data from c_string into the pString's memory
	Test to insure the above steps were successful - make sure *MYSTRING is not NULL and pString is not NULL
	ie check the two malloc's - DON'T assume they were successful
	
	Note: int = 4, char* = 4
	Thus need to allocate: 4 + 4 + 4 = 12 for *MYSTRING
	*/
	
	malloc struct *MYSTRING;
	
	//New MYSTRING opaque object. Has two ints + a char pointer which will point to a c string
	struct *MYSTRING{
		int size;		//Size of the string (not incl. NULL term)
		int capacity; 	//Capacity of the string (not incl. NULL term)
		char* pString;	//Pointer to a string
	}
	
	
	
	if(*MYSTRING == NULL)
	{
		return NULL;
	}
	else if(*MYSTRING != NULL)
	{
		return *MYSTRING;
	}
}

