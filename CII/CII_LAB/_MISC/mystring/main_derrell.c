#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mystring.h"	//include the mystring header file

//This file - mystring.c - will implment all the functions in mystring.h
struct _MYSTRING	//_MYSTRING is the name of the struct, *MYSTRING is the type
{
	int  size;
	int  capacity;	//3 Members, 2 ints and an char pointer which will
	char* data;	//point to a dynamically allocated array of chars
};

int main(int argc, char* argv[])
{
	int i;					//used for the for loop below
	MYSTRING pTemp;				//A temp *MYSTRING handle
	MYSTRING pTemp2;			//A second temp *MYSTRING handle
	FILE* output;				//A output file pointer	
	MyString_Status code;			//An enum of type mystring_status, to hold the error cdde
						//returned from the output function	

	pTemp = mystring_init_default();	//Create a 'default' MYSTRING object
	
	//Check and see if we were successful. NULL mean failure, not NULL success
	if(pTemp == NULL)
		printf("Failure for mystring_init_default. \n");
	if(pTemp != NULL)
		printf("Success for mystring_init_default. \n");

	//Test the SIZE and CAPACITY functions for mystring_init_default
        i = mystring_size(pTemp);
        printf("SIZE IS: %d\n", i);
        i = mystring_capacity(pTemp);
        printf("CAPACITY IS: %d\n", i);

	//Destroy the object/set the handle to NULL
	mystring_destroy(&pTemp);
	
	//Test the delete function
	if(pTemp == NULL)
		printf("DESTROY WAS A SUCCESS! Finally! \n");

	//Test the mystring_init_c_string function
	pTemp = mystring_init_c_string("hello\n");
	
	//Test the size/capacity functions for the init_c_string function:
	i = mystring_size(pTemp);
	printf("SIZE IS: %d\n", i);
	i = mystring_capacity(pTemp);
	printf("CAPACITY IS: %d\n", i);
	
	//Now to test the file output function
	output = fopen("test.txt", "w");	//Open a 'test.txt' file in write mode
	code = mystring_output(pTemp, output);	//Send pTemp/output handles to the output function
	if(code == MYSTRING_STATUS_SUCCESS)
		printf("Successful outputing to test.txt!\n");	//Success!
	else
		printf("Failure to output to test.txt!\n");	//Failure!	
	
	//Next test the concatenate_c_string function
	code = mystring_concatenate_c_string(pTemp, "hello\n");
        if(code == MYSTRING_STATUS_SUCCESS)
                printf("Successful concatenating of a string!\n");  //Success!
        else
                printf("Failure to concatenate a string!\n");     //Failure!
	
	//Print out the concatenated MYSTRING/C_STRING:
	for(i = 0; i < pTemp->size; i++)
		printf("%c", pTemp->data[i]);
	
	//Also test the concatenate_mystring function
	code = mystring_concatenate_mystring(pTemp, pTemp2);
	if(code == MYSTRING_STATUS_SUCCESS)
		printf("Successful concatenating of a MYSTRING!\n");  //Success!
    else
		printf("Failure to concatenate a MYSTRING!\n");     //Failure!

	//Print out the concatenated MYSTRING/MYSTRING:
	for(i = 0; i < pTemp->size; i++)
		printf("%c", pTemp->data[i]);

	//Finally, test the truncate function


	//Delete anything structs/arrays that were malloc'd
	mystring_destroy(&pTemp);

	return 0;
}

MYSTRING mystring_init_default(void)
{
	MYSTRING pTemp = NULL;
	
	//Allocate space for the opaque object
	pTemp = (MYSTRING) malloc(sizeof(MYSTRING));	

	if(pTemp == NULL)	//Check to see if the object allocated
		return NULL;	//FAILURE - quit returning NULL
	
	//Create a 'default' MYSTRING object	
	pTemp -> size = 0;								
	pTemp -> capacity = MYSTRING_STARTING_CAPACITY;			
	pTemp -> data = (char*) malloc(sizeof(char) * pTemp->capacity);	//Array should be as large as the capacity

	//Now check to see if the above array was allocated. If so, return the obj, if not return NULL
	if(pTemp -> data == NULL)
	{
		free(pTemp);			//Prevent memory leaks
		pTemp = NULL;
		return NULL;			//FAILURE! WE COULD NOT ALLOCATE MEMORY
	}
	else if(pTemp -> data != NULL)
	{						
		return pTemp;			//SUCCESS! WE WERE ABLE TO ALLOCATE MEMORY
	}
}

MYSTRING mystring_init_c_string(const char * const c_string)
{
	MYSTRING pTemp = NULL;
	size_t len = 0;		//unsigned int to hold the size
	int i;	

	//Figure out the size of the c_string
	len = strlen(c_string);	
	len--;	

	//Allocate space for the opaque object
	pTemp = (MYSTRING) malloc(sizeof(MYSTRING));	

	//Check to see if the object allocated
	if(pTemp == NULL)	
		return NULL;		//FAILURE - quit returning NULL

	//If pTemp wasn't NULL, then fill up the MYSTRING object
	pTemp -> size = len;
	pTemp -> capacity = len;

	//Allocate space for the c_string
	pTemp -> data = (char*) malloc(sizeof(char) * pTemp->capacity);	//Data should be as large as the capacity

	//Copy the c_string into the opaque object's array
	memcpy(pTemp -> data, c_string, len);

	//Now check to see if the above array was allocated. If so, return the obj, if not return NULL
	if(pTemp -> data == NULL)
	{
		free(pTemp);			//Prevent memory leaks
		pTemp = NULL;
		return NULL;			//FAILURE! WE COULD NOT ALLOCATE MEMORY
	}
	else if(pTemp -> data != NULL)
	{						
		return pTemp;			//SUCCESS! WE WERE ABLE TO ALLOCATE MEMORY
	}
}

void mystring_destroy(MYSTRING* p_hString)
{
	if(p_hString == NULL)	//If the handle is NULL don't try to destroy it!
		return;		//Just return
	
	//If we make it here, p_hString isn't NULL - so free it.
	free((*p_hString) -> data);	//Free the dynamically allocated array
	free(*p_hString);		//Then free the structure
	*p_hString = NULL;		//Set p_hString to NULL
	
	return;
}

int mystring_size(MYSTRING hString)
{
	if(hString == NULL)
		return -1;	//hString is NULL
	else{
	//This is rather simple - return the SIZE variable!	
		return hString->size;
	}	
}

int mystring_capacity(MYSTRING hString)
{
	if(hString == NULL)
		return -1;	//hString is NULL
	else{
	//This is also simple - return the CAPACITY variable:
		return hString->capacity;	
	}	
}

MyString_Status mystring_output(MYSTRING hString, FILE* out)
{
	int i;

	//If either are NULL we can't continue.
	if(hString == NULL || out == NULL)
	{
		return MYSTRING_STATUS_ERROR;	//return FAILURE
	}
	
	//Now we output the string to the file
	for(i = 0; i < hString->capacity; i++)	//Run til the end of the string
		fputc(hString->data[i], out);	//Put one char at a time from the array
						//into the output file.

	//if success return:
	return MYSTRING_STATUS_SUCCESS;
}

MyString_Status mystring_concatenate_c_string(MYSTRING hString, char * c_string)
{
	MYSTRING hLarger = NULL;
	int a = 0, b = 0;
	int hString_size, hString_capacity, c_string_size, size_needed;

	//If either hString or the c_string are NULL, we cannot continue.
	if(hString == NULL || c_string == NULL)
	{
                return MYSTRING_STATUS_ERROR;	//Return FAILURE
	}

	//Find the size/capacity of hString/c_string
	hString_size = mystring_size(hString);		
	hString_capacity = mystring_capacity(hString);
	c_string_size = (sizeof(c_string));
	size_needed = hString_size + c_string_size;
	
	//Now determine whether we should increase hString->data's size.
	if(size_needed <= hString_capacity)	//if both strings will fit into hString.
	{					//Then there is no need to resize hString!
		for(a = hString_size; a < size_needed; a++)
		{
			hString->data[a] = c_string[b];	//Add c_string to the end of hString
			b++;	//increase for accessing c_string
		}
		hString->size = size_needed;		//update hString's string size counter
		return MYSTRING_STATUS_SUCCESS;		//Return SUCCESS
	}
	else if(size_needed > hString_capacity)	//We need to increase hString's capacity!
	{
		hLarger = (MYSTRING) realloc(hString, size_needed * sizeof(char));
		
		if(hLarger == NULL)	//The realloc failed!
		{
			return MYSTRING_STATUS_ERROR;	//Return FAILURE
		}
		else if(hLarger != NULL)	//The realloc was a success!
		{
			hString = hLarger;	//Make hString point to the realloced structure
			
			//Concatenate the c_string to hString's data
	                for(a = hString_size; a < size_needed; a++)
                        {	
				hString->data[a] = c_string[b]; //Add c_string to the end of hString
                        	b++;    //increase for accessing c_string
			}
			
			hString->capacity = size_needed;	//capacity has gone up, reassign it.
			hString->size = size_needed;		//String size also increased, reassign it too.
			
			return MYSTRING_STATUS_SUCCESS;		//Return SUCCESS.
		}
	}
}

MyString_Status mystring_concatenate_mystring(MYSTRING hStringDest, MYSTRING hStringSource)
{
	MYSTRING hStringDestLarger;
	int a = 0, b = 0;
	int hStringDest_size, hStringDest_capacity, hStringSource_size, size_needed;
	
	//If either hStringDest or the hStringSource are NULL, we cannot continue.
	if(hStringDest == NULL || hStringSource == NULL)
	{
                return MYSTRING_STATUS_ERROR;	//Return FAILURE
	}

	//Find the size/capacity of hString/c_string
	hStringDest_size = mystring_size(hStringDest);		
	hStringDest_capacity = mystring_capacity(hStringDest);
	hStringSource_size = mystring_size(hStringSource);
	size_needed = hStringDest_size + hStringSource_size;

	//Now determine whether we should increase hString->data's size.
	if(size_needed <= hStringDest_capacity)	//if both hStrings will fit into the destion.
	{										//Then there is no need to resize hStringDest!
		for(a = hStringDest_size; a < size_needed; a++)
		{
			hStringDest->data[a] = hStringSource->data[b];	//Add c_string to the end of hString
			b++;	//increase for accessing c_string
		}
		hStringDest->size = size_needed;		//update hString's string size counter
		return MYSTRING_STATUS_SUCCESS;			//Return SUCCESS
	}
	else if(size_needed > hStringDest_capacity)	//We need to increase hStringDest's capacity!
	{
		hStringDestLarger = (MYSTRING) realloc(hStringDest, size_needed * sizeof(char));
		
		if(hStringDestLarger == NULL)	//The realloc failed!
		{
			return MYSTRING_STATUS_ERROR;	//Return FAILURE
		}
		else if(hStringDestLarger != NULL)	//The realloc was a success!
		{
			hStringDest = hStringDestLarger;	//Make hString point to the realloced structure
			
			//Concatenate the c_string to hString's data
	        for(a = hStringDest_size; a < size_needed; a++)
            {	
				hStringDest->data[a] = hStringSource->data[b]; //Add hStringSource to the end of hStringDest
               	b++;							//increase for accessing hStringSource
			}
			
			hStringDest->capacity = size_needed;	//capacity has gone up, reassign it.
			hStringDest->size = size_needed;		//String size also increased, reassign it too.
			
			return MYSTRING_STATUS_SUCCESS;		//Return SUCCESS.
		}
	}
}

//Truncate a string object to a given length. No change if new length is greater than the object's current length.
//MyString_Status mystring_truncate(MYSTRING hString, int newMaxLen);
