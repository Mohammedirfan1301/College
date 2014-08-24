#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mystring.h"	

struct _MYSTRING		// _MYSTRING = name of the struct
{						// *MYSTRING = the type
	int  size;			//Size of the string in data
	int  capacity;		//Capacity of the string in data
	char* data;			//dynamically allocated array of chars
};

//	I use TRUE / FALSE in a few functions to represent "0" and "1"
#define TRUE 1
#define FALSE 0

MYSTRING mystring_init_default(void)
{
	MYSTRING pTemp = NULL;
	MYSTRING hTemp = NULL;
	char* temp;
	
//	Allocate space for the opaque object
	pTemp = (MYSTRING) malloc(sizeof(MYSTRING));	

	if(pTemp == NULL)	//Check to see if the object allocated
		return NULL;	//FAILURE = return NULL
	
	hTemp = pTemp;
	
//	Create a 'default' MYSTRING object	
	hTemp -> size = 0;								
	hTemp -> capacity = MYSTRING_STARTING_CAPACITY;			
	temp = (char*) malloc(sizeof(char) * MYSTRING_STARTING_CAPACITY);	
//	Array should be as large as the capacity

//	Now check to see if the above array was allocated.
	if(temp == NULL)
	{
	//	Prevent Memory leaks - destroy/free what we have used.
		mystring_destroy(&pTemp);
		mystring_destroy(&hTemp);
		temp = NULL;
		pTemp = NULL;
		return NULL;		//FAILURE! WE COULD NOT ALLOCATE MEMORY
	}
	
//	If we get here, the array allocated. So make pTemp->data point to the array.
	hTemp->data = temp;
	
	return hTemp;			//SUCCESS! WE WERE ABLE TO ALLOCATE MEMORY
}


MYSTRING mystring_init_c_string(const char * const c_string)
{
	MYSTRING pTemp = NULL;
	char* temp;
	size_t len = 0;		//	unsigned int to hold the size	

//	Figure out the size of the c_string
	len = strlen(c_string);	

//	Allocate space for the opaque object
	pTemp = (MYSTRING) malloc(sizeof(MYSTRING));	

//	Check to see if the object allocated
	if(pTemp == NULL)	
		return NULL;

//	If pTemp wasn't NULL, then fill up the MYSTRING object
	pTemp -> size = len;
	pTemp -> capacity = len;

//	Allocate space for the c_string
	temp = (char*) malloc(sizeof(char) * len);	

//	Now check to see if the above array was allocated. 
	if(temp == NULL)
	{
	//	Prevent memory leaks
		mystring_destroy(&pTemp);
		temp = NULL;	
		pTemp = NULL;
		return NULL;		//FAILURE! WE COULD NOT ALLOCATE MEMORY
	}
	
//	If the array allocated, then great! Make pTemp->data point to temp!
	pTemp->data = temp;
	
//	Copy the c_string into the opaque object's array
	memcpy(pTemp -> data, c_string, len);			
		
	return pTemp;		//SUCCESS! WE WERE ABLE TO ALLOCATE MEMORY
}


int mystring_compare(MYSTRING source, MYSTRING test)
{
	int i;
	
	//printf("Size of source: %d\n", mystring_size(source));
	
	for(i = 0; i < mystring_size(source); i++)
	{
		// If the first MYSTRING is larger than the second one
		if((mystring_get(test, i)) == '\0')
		{
		//	Then we return 1 to indicate that source > test
			return 1;
		}
		
		/* 	If the first MYSTRING has a character that is larger than
			the second MYSTRING object	*/
		if((mystring_get(test, i)) > (mystring_get(source, i)))
		{
		//	Then we return -1 to indicate that source < test
			return -1;
		}
		
		/*	If the first MYSTRING object has a character that is smaller than
			the second MYSTRING object	*/
		if((mystring_get(source, i)) > (mystring_get(test, i)))
		{
		//	Then return 1 to indicate that source > test
			return 1;
		}
		
		// i increases, thus moving both strings forward 1 index.
	}
	
	// One last check - see if first MYSTRING object ended up at the end.
	if((mystring_get(test, i)) != '\0')
	{
	//	Then we return 1 to indicate that source < test
		return -1;
	}
	
	return 0;
}


void mystring_destroy(MYSTRING* p_hString)
{
//	Check to see if there is a my_string object to destroy.
	if(p_hString == NULL) 	//If p_hString is NULL, there isn't one.
		return;			
	
	if((*p_hString) -> data == NULL)	//If, however the data IS NULL
	{
	//	Then only free p_hString!
		free(p_hString);
		return;
	}
	
//	If we make it here, p_hString isn't NULL - so free it.
	free((*p_hString) -> data);	//Free the dynamically allocated array
	free(*p_hString);			//Then free the structure
	*p_hString = NULL;			//Set p_hString to NULL
	
	return;
}


/*		THIS IS USED IN DICTIONARY.C!		*/
void mystring_destroyer(void** hString)
{
// 	For MYSTRING objects, simply need to cast the void** to a MYSTRING*
	mystring_destroy((MYSTRING*)hString);
	return;
}


/*		ALSO USED IN DICTIONARY.C!		*/
void mystring_assignment(void** left, void* right)
{
//	Add a mystring object to the vector of mystrings...
	MYSTRING real_left  = (MYSTRING) *left;
	MYSTRING real_right = (MYSTRING)  right;
	char* temp;
	int x;
	
//	If left doesn't exist, create it.
	if(real_left == NULL)
	{
		*left = real_left = (MYSTRING)mystring_init_default();
	}
	
//	If both exist, we should be fine to do a deep copy.
	if(real_left != NULL && real_right != NULL)
	{
	//	If left side is smaller than the right side, we must do a resize.
		if(real_left -> capacity < real_right -> size)
		{
			real_left -> capacity = real_right -> size;
			temp = (char*)malloc(sizeof(char)*real_left->capacity);
			
		//	If the resize failed,
			if(temp == NULL)
			{
			//	Print an error and quit.
				fprintf(stderr, "Malloc failed!\n");
				exit(1);
			}
			
			free(real_left -> data);		// Free up the old array
			real_left -> data = temp;		// Update left's data array pointer.
		}
		
	//	Update left side's size, so it matches the right side.
		real_left -> size = real_right -> size;
		
	//	Copy all the data from right side to left side.
		for(x = 0; x < real_right -> size; x++)
		{
			real_left -> data[x] = real_right -> data[x];
		}
	}
	
//	Otherwise, throw an error - we are out of luck...
	else
	{
	//	We're out of luck if right is NULL. So just print an error & crash. :(
		fprintf(stderr, "Tried to do MYSTRING assignment but the right hand side was NULL\n");
		exit(1);
	}
	
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

//	If either are NULL we can't continue.
	if(hString == NULL || out == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	
//	Now we output the string to the file
	for(i = 0; i < hString->size; i++)	//Run til the end of the string
		fprintf(out, "%c", hString->data[i]);		
//	Put one char at a time from the array into the output file.

	return MYSTRING_STATUS_SUCCESS;	//If neither were NULL, 
}								//Then return success


MyString_Status mystring_concatenate_c_string(MYSTRING hString, char * c_string)
{
	char* temp;
	int a = 0, b = 0;
	int hString_size, hString_capacity, c_string_size, size_needed;

//	If either hString or the c_string are NULL, we cannot continue.
	if(hString == NULL || c_string == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}

//	Find the size/capacity of hString/c_string
	hString_size = mystring_size(hString);		
	hString_capacity = mystring_capacity(hString);
	c_string_size = strlen(c_string);
	size_needed = hString_size + c_string_size;
	
//	Now determine whether we should increase hString->data's size.
	if(size_needed <= hString_capacity) 	//if both strings fit.
	{	
	//	Then there is no need to resize hString!
		for(a = hString_size; a < size_needed; a++)
		{	
		//	c_string added to hString
			hString->data[a] = c_string[b];	
			b++;	// increase for accessing c_string
		}
		hString->size = size_needed;	//	update hString's string size
		return MYSTRING_STATUS_SUCCESS;	
	}
	
//	Otherwise we need to resize hString's data string!
	temp = (char*) realloc(hString->data, size_needed * sizeof(char));
	
	if(temp == NULL)	//	The realloc failed!
	{
	// 	Make sure to free any memory we tried to realloc!
		mystring_destroy(&hString);
		free(temp);
		return MYSTRING_STATUS_ERROR;	
	}
	
//	Make hString->data point to the newly realloc'd data
	hString->data = temp;
	
/*	The realloc was a success!		
	Concatenate the c_string to hString's data	*/
   	for(a = hString_size; a < size_needed; a++)
  	{	
//	c_string added to hString
		hString->data[a] = c_string[b]; 
      	b++; // increase for accessing c_string
	}
	
	hString->capacity = size_needed;	// capacity updated
	hString->size = size_needed;		// size updated
	
	return MYSTRING_STATUS_SUCCESS;	
}


MyString_Status mystring_concatenate_mystring (MYSTRING hStringDest, MYSTRING hStringSource)
{
	char* temp;
	int a = 0, b = 0;
	int hStringDest_size, hStringDest_capacity;
	int hStringSource_size, size_needed;
	
//	If either hStringDest or the hStringSource are NULL, we cannot continue.
	if(hStringDest == NULL || hStringSource == NULL)
	{
                return MYSTRING_STATUS_ERROR;	
	}

//	Find the size/capacity of hString/c_string
	hStringDest_size = mystring_size(hStringDest);		
	hStringDest_capacity = mystring_capacity(hStringDest);
	hStringSource_size = mystring_size(hStringSource);
	size_needed = hStringDest_size + hStringSource_size;

//	Now determine whether we should increase hString->data's size.
	if(size_needed <= hStringDest_capacity)	// if both hStrings will fit.
	{	
	//	Then there is no need to resize hStringDest!
		for(a = hStringDest_size; a < size_needed; a++)
		{	
		//	Add mystring to a mystring
			hStringDest->data[a] = hStringSource->data[b];
			b++;	// increase for accessing the mystring_source
		}
		hStringDest->size = size_needed;  	// update hString's string size
		return MYSTRING_STATUS_SUCCESS;		
	}
	
//	We need to increase hStringDest's capacity!
	temp = (char*) realloc(hStringDest->data, size_needed * sizeof(char));
	
// 	See if the realloc failed.
	if(temp == NULL)		
	{	// It did. Do two things:
		free(hStringDest->data);			// Prevent memory leaks.
		return MYSTRING_STATUS_ERROR;		// Throw an error.
	}

/* 	The realloc was a success.
	Add hStringSource to hStringDest's data 	*/
	hStringDest->data = temp;

   	for(a = hStringDest_size; a < size_needed; a++)
  	{	
  	// 	Add hStringSource to the end of hStringDest
		hStringDest->data[a] = hStringSource->data[b]; 
     	b++;	// increase for accessing hStringSource
	}

	hStringDest->capacity = size_needed;	// update capicity.
	hStringDest->size = size_needed;	// update size.
	
	temp = NULL;

	return MYSTRING_STATUS_SUCCESS;		
}


/* 	Truncate a string object to a given length. 
  	No change if new length is greater than the object's current length. */
MyString_Status mystring_truncate(MYSTRING hString, int newMaxLen)
{
	int i;
	
//	Make sure we have a MYSTRING object to work with
	if(hString == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}

//	Check and see if we need to change the string
	if(newMaxLen > hString->size)
	{
	//	No need to change it, so just return SUCCESS!
		return MYSTRING_STATUS_SUCCESS;
	}
	
/*	Otherwise We need to chop the array at this point
	Basically everything past newMaxLen will be empty and
	size will be set to newMaxLen						*/
	for(i = newMaxLen; i < hString->size; i++)
	{
	//	Empty these parts of the array.
		hString->data[i] = '\0';
	}
	
//	Make size equal to the newMaxLen
	hString->size = newMaxLen;
	
	return MYSTRING_STATUS_SUCCESS;
}


MyString_Status mystring_push(MYSTRING hString, char ch)
{
	char* temp;
	int index, size_needed = 0;

//	Check & see if hString exists.
	if(hString == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
		
	index = mystring_size(hString);
//	index = mystring_size(hString) - 1;
		
/*	Add one char to the end of the my_string object
	To do so, first see if we need to increase hString's capacity	*/
	if(hString->capacity < hString->size + 1)
	{
	//	Yes, we must, since it is smaller than size + 1
		size_needed = hString->size + 1;
		temp = (char*) realloc(hString->data, size_needed * sizeof(char));
		
	//	Check & see if the realloc failed
		if(temp == NULL)
		{
		//	Make sure to destroy all the memory we have alloc'd! Prevent memory leaks!
			mystring_destroy(&hString);
			free(temp);
			return MYSTRING_STATUS_ERROR;
		}
		
	//	Make hString->data point to the newly reallocated memory
		hString->data = temp;
		
	//	Add the char to the back of the string
		hString->data[index] = ch;
		
	//	Update the string's size/capacity
		hString->size++;
		hString->capacity++;
		
		return  MYSTRING_STATUS_SUCCESS;
	}
	
//	If we get to this point, we can just add the character to the object.
	hString->data[index] = ch;
	hString->size++;
	
	return  MYSTRING_STATUS_SUCCESS;
}


char mystring_pop(MYSTRING hString)
{
	int index;
	char pop;

//	Check & see if hString exists.
	if(hString == NULL)
	{
		return '\0';
	}

//	See if we can remove an item
	if(hString->size == 0)
	{
		return '\0';
	}
	
	index = mystring_size(hString) - 1;
	
//	Pop the item by finding it, setting that spot to NULL and decreasing size by 1.
	pop = hString->data[index];
	hString->data[index] = '\0';
	hString->size--;
	
//	Return the popped item
	return pop;
}


char mystring_peek(MYSTRING hString)
{
	int index;

//	Check & see if hString exists.
	if(hString == NULL)
	{
		return '\0';
	}

//	See if we can peek at an item
	if(hString->size == 0)
	{
		return '\0';
	}
	
	index = mystring_size(hString) - 1;
	
//	Otherwise, return the last item in the string
	return hString->data[index];
}


char mystring_get(MYSTRING hString, int index)
{
//	Check and see if the MYSTRING object exists
	if(hString == NULL)
	{
		return '\0';
	}

//	Make sure the given index is valid for this MYSTRING array.
	if(index < 0 || index > mystring_size(hString))
	{
	/*	Because this given index is LESS THAN 0 or greater than the given size
		It IS NOT VALID. So we must exit before trying to access memory
		that is out of bounds (not our memory to touch basically)	*/
		return '\0';
	}
	
//	Return the character at the given index
	return hString->data[index];
}


MyString_Status mystring_put(MYSTRING hString, int index, char ch)
{
//	Check and see if the MYSTRING object exists
	if(hString == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	
//	Make sure the given index is valid for this MYSTRING object
	if( ( index < 0 ) || ( index > (mystring_size(hString) - 1) ) )
	{
	/*	Because this given index is LESS THAN 0 or greater than the given size
		It IS NOT VALID. So we must exit before trying to access memory
		that is out of bounds (not our memory to touch basically)	*/
		return MYSTRING_STATUS_ERROR;
	}
	
//	Put the given character in the MYSTRING array
	hString->data[index] = ch;
	
//	Return success if we got to this point
	return MYSTRING_STATUS_SUCCESS;
}


MYSTRING mystring_init_substring(MYSTRING hStringSource, int index, int length)
{
	MYSTRING hStringDest;
	char* temp;
	int i;

//	Check and see if hStringSource exists
	if(hStringSource == NULL)
	{
	// 	Nope, doesn't exist. Return NULL for error.
		return NULL;
	}

//	Now see if the index is valid
	if(index < 0 || index > (mystring_size(hStringSource) - 1) )
	{
	/*	Because this given index is LESS THAN 0 or greater than the given size
		It IS NOT VALID. So we must exit before trying to access memory
		that is out of bounds (not our memory to touch basically)	*/
		return NULL;
	}

//	See if length is within the given bounds
	if(length < 0 || length > mystring_size(hStringSource))
	{
		// Not in the bounds! Error.
		return NULL;
	}

/*	If we get to this point, we should be set to:
	1. Create a NEW MYSTRING object with the given size/capacity
	2. Put characters from the old mystring object into the new one,
	   but only from the given index to the end of the object.
	
	NOTE: size/capacity of new hStringDest should be LENGTH, since we only
		  want those characters to be copied!		*/

//	Create a new hString object.
	hStringDest = mystring_init_default();
	
//	MAKE SURE IT INITIALIZED!
	if(hStringDest == NULL)
	{
		hStringDest = NULL;
		return NULL;
	}
	
//	Realloc the array of this mystring object.
	temp = (char*) realloc(hStringDest->data, length * sizeof(char));
	
//	Check & see if the realloc failed
	if(temp == NULL)
	{
	// 	Prevent memory leaks - make sure to free everything!
		free(hStringDest);
		free(temp);	
		return NULL;
	}
	
//	Make hStringDest->data point to the newly reallocated memory!
	hStringDest->data = temp;	
	
//	Update the size/capacity
	hStringDest->size = length;
	hStringDest->capacity = length;

//	Now copy every character from the source MYSTRING to the new MYSTRING (dest)
	for(i = 0; i < length; i++)
	{
		hStringDest->data[i] = hStringSource->data[index];
		index++;
	}

//	Destroy the source MYSTRING
//	mystring_destroy(&hStringSource);
	hStringSource = NULL;

//	Return the new MYSTRING Dest
	return hStringDest;
	
	return NULL;
}


char * mystring_to_c_string(MYSTRING hString, char c_string_arr[], int arrSize)
{
	int i, hsize, end, index;

//	Get the size of the MYSTRING object
	hsize = mystring_size(hString);
	
//	Determine which is larger - the mystring object, or the array
	if(hsize+1 <= arrSize)	//	The MYSTRING is smaller.
	{			//	So, we can't fit it in the array.
		end = hsize;	//	So end the input at the end of the array.
		index = hsize;	
	}	
	else if(hsize+1 > arrSize)//	The MYSTRING is larger.
	{			  //	So, we can fit it in the array.
		end = arrSize - 1;//	So end the input at the end of the mystring.
		index = arrSize; 
	}

/* 	Check to see if:
	1. hString is NULL
	2. c_string_arr is NULL
	3. arrSize is less than 1	*/
	
	if(hString == NULL || c_string_arr == NULL || arrSize < 1)
		return NULL;

//	Copy hString's data to the c_string_arr;
	for(i = 0; i < index; i++)
	{
	
	//	Copy hString's data to the c_string
		 c_string_arr[i] = hString->data[i];
	}

//	The last value in the array must be NULL terminated.
	c_string_arr[end] = '\0';

//	Return a pointer to the beginning of the c_string
	return &c_string_arr[0];
}


MyString_Status mystring_input(MYSTRING hString, FILE * hFile, int bIgnoreLeadingWhiteSpace,
int (* fTerminate)(char ch, int * pbDiscardChar) )
{
	int i = 0, discard = 0, TERMINATE = 0, test = 1, SeenChar = 0;
	char c;
	char *temp;

//	Check to see if hString/hFile/fTerminate is NULL
	if(hString == NULL || hFile == NULL || fTerminate == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	
//	Make sure to clear the array
	hString->size = 0;

//	If safe to continue, then start testing!
	do{
	//	Get a character from the file
		test = fscanf(hFile, "%c", &c);
		
	//	If we find that the scanf failed or that we hit EOF, end input.
		if(test != 1 || c == EOF)
		{
			return MYSTRING_STATUS_SUCCESS;
		}

	//	If we should ignore leading white space, and we haven't seen a 
	//	character yet - then check for white space and discard any that we find.
		if(bIgnoreLeadingWhiteSpace == TRUE && SeenChar == 0)
		{	
		//	See if it is a space or not	
			if(isspace(c))		 // Yep.
			{
				// IGNORE IT.
			}
			else if(!isspace(c)) // Nope.
			{
				// We've spotted a character!
				SeenChar = 1;
			}	
		}
	
	//	If we don't care about leading white space, then just start testing.
		if(bIgnoreLeadingWhiteSpace == FALSE)
		{
			SeenChar = 1;
		}
	
	//	Once we find a character,
		if(SeenChar == 1)
		{
		//	Call fTerminate and seen if we should discard it or not.
			TERMINATE = fTerminate(c, &discard);
			
		// 	Don't discard or terminate!
			if(TERMINATE == FALSE && discard == FALSE)	
			{
			//	Put it into the data array
				if(hString->capacity <= i)	// Check to see if there is room.
				{							// Yes, there is in this case.
					hString->data[i] = c;
					i++;
					hString->size = i;
				}
				else if(hString->capacity > i)	// No, there isn't. Need to
				{								// reallocate more space!
					temp = (char*) realloc(hString->data, (hString->capacity + 2) * sizeof(char));
					
					if(temp != NULL)			// If the realloc didn't fail
					{
						hString->data = temp;	// Update the array.
						hString->data[i] = c;	// Safe to update hString!
						i++;
						hString->size = i;
						hString->capacity += 2;
					}
					else if(temp == NULL)		// If  the realloc did fail
					{
					//	Not safe to do anything but quit with an error. :(
						temp = NULL;
						free(&hString->data);	// Also PREVENT MEMORY LEAKS!
						//free(&hString);
						return MYSTRING_STATUS_ERROR;	// ERROR
					}
				}
			}
			
		//	Discard and terminate input!
			else if(TERMINATE == TRUE)	
			{
				return MYSTRING_STATUS_SUCCESS;
			}
		}
			
	}while(test == 1);
	
	return MYSTRING_STATUS_SUCCESS;
}

