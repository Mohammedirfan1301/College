/*
MYSTRING opaque object interface
*/

//CAN FIND THIS AT THE FOLLOWING ADDRESS:
//cs.uml.edu/~dlipman/mystring.h
//CAN NOT MODIFY THIS DOCUMENT!!! YOU ARE USING MYSTRING.C!!!
//Implement all these functions

#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>


/*****************************************************************************
 * The opaque object type provided by mystring_init_default and
 * mystring_init_c_string, and provided to the other functions in this
 * module.
 *****************************************************************************/
typedef struct _MYSTRING *MYSTRING;


/****************************************************************************
 * Status values returned by some functions in this module
 ****************************************************************************/
enum mystring_status {MYSTRING_STATUS_ERROR, MYSTRING_STATUS_SUCCESS};
typedef enum mystring_status MyString_Status;


/****************************************************************************
 * The starting capacity for a default MYSTRING instance
 ****************************************************************************/
#define MYSTRING_STARTING_CAPACITY     7


/*****************************************************************************
 * Create a new MYSTRING opaque object from a given c-string (null terminated
 * array).
 *
 * @param c_string
 *   The null-terminated C string used to initialize the new MYSTRING
 *   object.
 *
 * @return
 *   upon failure: NULL
 *     The function fails if memory to complete the operation is not available
 *
 *   upon success:
 *     A MYSTRING handle to a string object representing the given c-string 
 *     that has:
 *       size     = number of characters in the initializer, c_string, 
 *                  not including its null terminator
 *       capacity = number of characters in the initializer, c_string,
 *                  not including its null terminator
 *
 * @note
 *   Internally, the string is NOT stored with a null terminator. Only enough
 *   memory for the string's length (not including its null terminator) is
 *   allocated, and the c_string's characters are copied into that memory.
 ****************************************************************************/
MYSTRING mystring_init_c_string(const char * const c_string)
{
	//Create a structure
	//Allocate it (default size = 7)
	//Return?
	
	struct _MYSTRING 
	
	
	if(//SUCCESS!)
	{
		return;
	}
	else if(//FAILURE)
	{
		return NULL;
	}
}

/*****************************************************************************
 * Destroy a MYSTRING opaque object and set the handle to NULL.
 * Will not attempt to destroy an object if the handle is NULL.
 *
 * @param p_str
 *   Address of a MYSTRING handle so that the function can free the MYSTRING
 *   object, and then change the passed variable to NULL.
 ****************************************************************************/
void mystring_destroy(MYSTRING* p_hString)
{
	
	//Test to see if MYSTRING object is NULL or not
	if(*p_hString == NULL)
	{
		//DO NOT REMOVE! JUST RETURN!
		return;
	}
	else if(*p_hString != NULL)
	{
		//Destroy the object, calling free
		free(*p_hString)
		//Set the handle equal to NULL
		*p_hString = NULL;
	}

}


/*****************************************************************************
 * Retrieves the number of characters that the current string holds.
 *
 * @param hString
 *   MYSTRING handle to the object that you want to query the size of.
 *
 * @return
 *   upon success:
 *     The size of the string is returned
 *
 *   upon failure:
 *    -1 is returned (e.g., hString is NULL)
 ****************************************************************************/
int mystring_size(MYSTRING hString)
{

	//????

}


/*****************************************************************************
 * Retrieves the total number of characters that the string can contain before
 * it has to do an internal resize operation of its dynamic array.
 *
 * @param hString
 *   MYSTRING handle to the object that you want to query the capacity of.
 * 
 * @return
 *   upon success:
 *     The capacity of the string is returend
 *
 *   upon failure:
 *     -1 is returned (e.g., hString is NULL)
 ****************************************************************************/
int mystring_capacity(MYSTRING hString)
{

	//????

}


/*****************************************************************************
 * Outputs the string to the given output file handle.
 *
 * @param hString
 *   MYSTRING handle to the object whose string data is to be output.
 * 
 * @param out
 *   output file handle as the target for writing the string.
 * 
 * @return
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (e.g., either of the hString or out handles are
 *     invalid)
 ****************************************************************************/
MyString_Status mystring_output(MYSTRING hString, FILE* out)
{

	//????

}


#endif /* MYSTRING */
