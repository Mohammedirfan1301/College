/*
MYSTRING opaque object interface
*/

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
 * Create a "default" new MYSTRING opaque object (with no initial data)
 *
 *
 * @return
 *   upon failure: NULL
 *     The function fails if memory to complete the operation is not available
 *
 *   upon success:
 *     A MYSTRING handle to a default string object that has:
 *       size     = 0
 *       capacity = MYSTRING_STARTING_CAPACITY
****************************************************************************/
MYSTRING mystring_init_default(void);


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
MYSTRING mystring_init_c_string(const char * const c_string);


/*****************************************************************************
 * Destroy a MYSTRING opaque object and set the handle to NULL.
 * Will not attempt to destroy an object if the handle is NULL.
 *
 * @param p_str
 *   Address of a MYSTRING handle so that the function can free the MYSTRING
 *   object, and then change the passed variable to NULL.
 ****************************************************************************/
void mystring_destroy(MYSTRING* p_hString);


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
int mystring_size(MYSTRING hString);


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
int mystring_capacity(MYSTRING hString);


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
MyString_Status mystring_output(MYSTRING hString, FILE* out);


/*****************************************************************************
 * Concatenate a c-string to an existing MYSTRING object. The c-string is
 * concatenated to the end of MYSTRING object's existing string data, which
 * may require enlarging the MYSTRING object's capacity.
 *
 * Upon failure, the MYSTRING object must be left unaltered.
 *
 * @param hString
 *   The MYSTRING handle which is the destination of the concatenation
 *
 * @param c_string_Source
 *   The c-string which is the source of the concatenation
 * 
 * @return
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (e.g., either of the hString or out handles are
 *     invalid)
 ****************************************************************************/
MyString_Status mystring_concatenate_c_string(MYSTRING hString,
                                              char * c_string);



/*****************************************************************************
 * Concatenate a source MYSTRING object to an existing, destination MYSTRING
 * object. The source object's string data is concatenated to the end of the
 * destination object's string data, which may require enlarging the
 * destination object's capacity. The source object is not altered.
 *
 * Upon failure, the destination object must be left unaltered.
 *
 * @param hStringDest
 *   The MYSTRING handle which is the destination of the concatenation
 *
 * @param hStringSource
 *   The MYSTRING handle which is the source of the concatenation
 * 
 * @return
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (e.g., either of the hString handle or c_string
 *     pointer is null)
 ****************************************************************************/
MyString_Status mystring_concatenate_mystring(MYSTRING hStringDest,
                                              MYSTRING hStringSource);

/*****************************************************************************
 * Truncate a string object to a given length. No change is made if the
 * specified new length is greater than the object's current length.
 *
 * @param hString
 *   MYSTRING handle of the object whose string data is to be truncated
 * 
 * @param newMaxLen
 *   new length of the string (if greater than the current length)
 * 
 * @return
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (e.g., either of the hString or out handles are
 *     invalid)
 ****************************************************************************/
MyString_Status mystring_truncate(MYSTRING hString, int newMaxLen);



#endif /* MYSTRING */

