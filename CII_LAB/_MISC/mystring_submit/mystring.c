#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mystring.h"	

struct _MYSTRING	// _MYSTRING = name of the struct
{				// *MYSTRING = the type
	int  size;	//Size of the string in data
	int  capacity;	//Capacity of the string in data
	char* data;	//dynamically allocated array of chars
};

MYSTRING mystring_init_default(void)
{
	MYSTRING pTemp = NULL;
	
	//Allocate space for the opaque object
	pTemp = (MYSTRING) malloc(sizeof(MYSTRING));	

	if(pTemp == NULL)	//Check to see if the object allocated
		return NULL;	//FAILURE = return NULL
	
	//Create a 'default' MYSTRING object	
	pTemp -> size = 0;								
	pTemp -> capacity = MYSTRING_STARTING_CAPACITY;			
	pTemp -> data = (char*) malloc(sizeof(char) * pTemp->capacity);	
	//Array should be as large as the capacity

	//Now check to see if the above array was allocated.
	if(pTemp -> data == NULL)
	{
		free(pTemp);		//Prevent memory leaks
		pTemp = NULL;
		return NULL;		//FAILURE! WE COULD NOT ALLOCATE MEMORY
	}
	
	return pTemp;		//SUCCESS! WE WERE ABLE TO ALLOCATE MEMORY
}

MYSTRING mystring_init_c_string(const char * const c_string)
{
	MYSTRING pTemp = NULL;
	size_t len = 0;		//unsigned int to hold the size	

	//Figure out the size of the c_string
	len = strlen(c_string);	

	//Allocate space for the opaque object
	pTemp = (MYSTRING) malloc(sizeof(MYSTRING));	

	//Check to see if the object allocated
	if(pTemp == NULL)	
		return NULL;		//FAILURE - quit returning NULL

	//If pTemp wasn't NULL, then fill up the MYSTRING object
	pTemp -> size = len;
	pTemp -> capacity = len;

	//Allocate space for the c_string
	pTemp -> data = (char*) malloc(sizeof(char) * pTemp->capacity);	
	// (Data should be as large as the capacity)

	//Copy the c_string into the opaque object's array
	memcpy(pTemp -> data, c_string, len);

	//Now check to see if the above array was allocated. 
	if(pTemp -> data == NULL)
	{
		free(pTemp);		//Prevent memory leaks
		pTemp = NULL;
		return NULL;		//FAILURE! WE COULD NOT ALLOCATE MEMORY
	}
							
	return pTemp;		//SUCCESS! WE WERE ABLE TO ALLOCATE MEMORY
}

void mystring_destroy(MYSTRING* p_hString)
{
	if(p_hString == NULL) 	//If the handle is NULL don't try to destroy it!
		return;			//Just return
	
	//If we make it here, p_hString isn't NULL - so free it.
	free((*p_hString) -> data);	//Free the dynamically allocated array
	free(*p_hString);			//Then free the structure
	*p_hString = NULL;			//Set p_hString to NULL
	
	return;
}

int mystring_size(MYSTRING hString)
{
	if(hString == NULL)
	{
		return -1;	
	}
		
	return hString->size;	
}

int mystring_capacity(MYSTRING hString)
{
	if(hString == NULL)
		return -1;
		
	return hString->capacity;	
}

MyString_Status mystring_output(MYSTRING hString, FILE* out)
{
	int i;

	//If either are NULL we can't continue.
	if(hString == NULL || out == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	
	//Now we output the string to the file
	for(i = 0; i < hString->size; i++)	//Run til the end of the string
		fputc(hString->data[i], out);	
	//Put one char at a time from the array into the output file.

	return MYSTRING_STATUS_SUCCESS;	//If neither were NULL, 
}									//Then return success

MyString_Status mystring_concatenate_c_string(MYSTRING hString, char * c_string)
{
	MYSTRING hTemp;
	int a = 0, b = 0;
	int hString_size, hString_capacity, c_string_size, size_needed;

	//If either hString or the c_string are NULL, we cannot continue.
	if(hString == NULL || c_string == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}

	//Find the size/capacity of hString/c_string
	hString_size = mystring_size(hString);		
	hString_capacity = mystring_capacity(hString);
	c_string_size = strlen(c_string);
	size_needed = hString_size + c_string_size;
	
	//Now determine whether we should increase hString->data's size.
	if(size_needed <= hString_capacity) 	//if both strings fit.
	{	
		//Then there is no need to resize hString!
		for(a = hString_size; a < size_needed; a++)
		{	
			//c_string added to hString
			hString->data[a] = c_string[b];	
			b++;	//increase for accessing c_string
		}
		hString->size = size_needed;		//update hString's string size
		return MYSTRING_STATUS_SUCCESS;	
	}
	
	//Otherwise we need to resize hString's data string!
	hTemp = realloc(hString->data, size_needed * sizeof(char));
	
	if(hTemp == NULL)	//The realloc failed!
	{
		return MYSTRING_STATUS_ERROR;	
	}
	
	//The realloc was a success!		
	//Concatenate the c_string to hString's data
   	for(a = hString_size; a < size_needed; a++)
  	{	
  	//c_string added to hString
		hString->data[a] = c_string[b]; 
      	b++;    //increase for accessing c_string
	}
	
	hString->capacity = size_needed;	//capacity updated
	hString->size = size_needed;		//size updated
	
	hTemp = NULL;
	
	return MYSTRING_STATUS_SUCCESS;	
}

MyString_Status mystring_concatenate_mystring
(MYSTRING hStringDest, MYSTRING hStringSource)
{
	MYSTRING hTemp;
	int a = 0, b = 0;
	int hStringDest_size, hStringDest_capacity;
	int hStringSource_size, size_needed;
	
	//If either hStringDest or the hStringSource are NULL, we cannot continue.
	if(hStringDest == NULL || hStringSource == NULL)
	{
                return MYSTRING_STATUS_ERROR;	
	}

	//Find the size/capacity of hString/c_string
	hStringDest_size = mystring_size(hStringDest);		
	hStringDest_capacity = mystring_capacity(hStringDest);
	hStringSource_size = mystring_size(hStringSource);
	size_needed = hStringDest_size + hStringSource_size;

	//Now determine whether we should increase hString->data's size.
	if(size_needed <= hStringDest_capacity)	//if both hStrings will fit.
	{	
		//Then there is no need to resize hStringDest!
		for(a = hStringDest_size; a < size_needed; a++)
		{	
			//Add mystring to a mystring
			hStringDest->data[a] = hStringSource->data[b];
			b++;	//increase for accessing the mystring_source
		}
		hStringDest->size = size_needed;  	//update hString's string size
		return MYSTRING_STATUS_SUCCESS;		
	}
	
	//We need to increase hStringDest's capacity!
	hTemp = realloc(hStringDest->data, size_needed * sizeof(char));
	
	if(hTemp == NULL)		//The realloc failed!
	{
		return MYSTRING_STATUS_ERROR;	
	}
	
	//The realloc was a success!
	//Add hStringSource to hStringDest's data
   	for(a = hStringDest_size; a < size_needed; a++)
  	{	
  	//Add hStringSource to the end of hStringDest
		hStringDest->data[a] = hStringSource->data[b]; 
     	b++;	//increase for accessing hStringSource
	}

	hStringDest->capacity = size_needed;	//update capicity.
	hStringDest->size = size_needed;		//update size.
	
	hTemp = NULL;

	return MYSTRING_STATUS_SUCCESS;		
}

//Truncate a string object to a given length. 
//No change if new length is greater than the object's current length.
MyString_Status mystring_truncate(MYSTRING hString, int newMaxLen)
{
	int i;
	
	//Make sure we have a MYSTRING object to work with
	if(hString == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}

	//Check and see if we need to change the string
	if(newMaxLen > hString->size)
	{
		//No need to change it, so just return SUCCESS!
		return MYSTRING_STATUS_SUCCESS;
	}
	
	//Otherwise We need to chop the array at this point
	//Basically everything past newMaxLen will be empty and
	//size will be set to newMaxLen
	for(i = newMaxLen; i < hString->size; i++)
	{
		//Empty these parts of the array.
		hString->data[i] = '\0';
	}
	
	//Make size equal to the newMaxLen
	hString->size = newMaxLen;
	
	return MYSTRING_STATUS_SUCCESS;
}


