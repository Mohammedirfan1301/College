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
 *     MYSTRING_STATUS_ERROR (e.g., the hString handle is invalid)
 ****************************************************************************/
MyString_Status mystring_truncate(MYSTRING hString, int newMaxLen);


/**
 * Append one character to the end of the string, simulating a stack push
 * operation.
 *
 * @param hString
 *   MYSTRING handle of the object whose string data is being manipulated
 *
 * @param ch
 *   The character to be appended to the string object
 * 
 * @return
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (e.g., the hString handle is invalid)
 */
MyString_Status mystring_push(MYSTRING hString, char ch);


/**
 * Remove one character from the end of the string, simulating a stack pop
 * operation.
 *
 * @param hString
 *   MYSTRING handle of the object whose string data is being manipulated
 * 
 * @return
 *   If the string object has size at least one, the last character is removed
 *   from the end of the string (i.e, the string is truncated to one less than
 *   its previous size), and the removed character is returned.
 *
 *   If the string object has size 0, a null character ('\0') is returned.
 */
char mystring_pop(MYSTRING hString);


/**
 * Obtain the character that is at the end of the string.
 *
 * @param hString
 *   MYSTRING handle of the object whose string data is being manipulated
 * 
 * @return
 *   If the string object has size at least one, the last character of the
 *   string is returned.
 *
 *   If the string object has size 0, a null character ('\0') is returned.
 *
 *   In either case, the string object is not modified in any way.
 */
char mystring_peek(MYSTRING hString);



/**
 * Get a character from a given position in the string
 *
 * @param hString
 *   MYSTRING handle of the object whose string data is being manipulated
 *
 * @param index
 *   Index of the character to be retrieved
 *
 * @return
 *   If the string object has size at least one greater than the requested
 *   index (i.e., the requested index exists in the string), the character at
 *   that position is returned.
 *
 *   If the requested index does not exist in the string, a null character
 *   ('\0') is returned.
 */
char mystring_get(MYSTRING hString, int index);


/**
 * Put a character at a given index in the string. A character may only be
 * placed at an index where a character currently exists. This function may
 * not be used to increase the size of the string.
 *
 * @param hString
 *   MYSTRING handle of the object whose string data is being manipulated
 *
 * @param index
 *   Index where the character should be placed
 *
 * @param ch
 *   The character to be put at the specified index
 *
 * @return
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (index out of bounds)
 *
 *
 */
MyString_Status mystring_put(MYSTRING hString, int index, char ch);


/**
 * Create a new MYSTRING opaque object from a substring of an existing, source
 * MYSTRING opaque object. The source object's string data, beginning at the
 * specified index and extending for the specified length, is used as the new
 * object's string data. The new object's size and capacity are set to exactly
 * the number of characters copied from the source object to the new
 * object. It is an error if the specified index is out of bounds, or if the
 * number of characters specified by length, beyond the index, is out of
 * bounds.
 *
 * @param hStringSource
 *   The MYSTRING handle which contains the substring to be copied to this new
 *   object.
 *
 * @param index
 *   The index, within the source object, of the beginning of the string data
 *   with which to initialize this new object.
 *
 * @param length
 *   The number of characters, beginning at index, to be copied from the
 *   source object, with which to initialize this new object.
 *
 * @return
 *   upon failure: NULL
 *     The function fails if memory to complete the operation is not
 *     available, or if the index is out of bounds within the source object,
 *     or if the length is less than one or greater than the number of
 *     characters available in the source object beyond the specified index.
 *
 *   upon success:
 *     A MYSTRING handle that has size and capacity set to the specified
 *     length, and string data copied from the source object.
 */
MYSTRING mystring_init_substring(MYSTRING hStringSource, int index, int length);


/**
 * Convert a string in a MYSTRING object to a c_string
 *
 * @param hString
 *   The MYSTRING handle of the string containing the data to be converted to
 *   a c_string
 *
 * @param c_string_arr
 *   The address of a statically- or dynamically-allocated character array
 *   into which the c_string will be placed.
 *
 * @param arrSize
 *   The maximum number of characters that can be copied to c_string_arr. The
 *   array will ALWAYS be null-terminated, even if that means that less than
 *   the entire string data from the MYSTRING object can be copied given this
 *   size.
 *
 * @return
 *   upon failure:
 *     NULL, e.g., hString or c_string_arr is null; arrSize is less than one
 *
 *   upon success:
 *     The address of the beginning of the c_string_arr is returned, allowing
 *     this function to be used as an expression value, e.g., to pass to
 *     printf.
 */
char * mystring_to_c_string(MYSTRING hString, char c_string_arr[], int arrSize);


/**
 * Read input from a given file, until being told to stop reading characters,
 * or until EOF. The input replaces, entirely, any data that was already in
 * the MYSTRING object.
 *
 * @param hString
 *   The MYSTRING handle of the string into which the input data should be
 *   placed, replacing any prior data in this string
 *
 * @param hFile
 *   A FILE* handle from which input should be read
 *
 * @param fTerminate
 *   A pointer to a function to be called upon reading each character, to
 *   determine whether the character just read is a "terminator", i.e.,
 *   whether mystring_input should return after storing (or not storing, as
 *   indicated by *pbDiscardChar) this character. This function will be called
 *   as each character is read. It must return TRUE (non-zero) if the
 *   just-read character should terminate input. It should set
 *   *pbDiscardChar, as described below, before returning.
 *
 *   The fTerminate function's signature is:
 *     int (* fTerminate)(char ch, int * pbDiscardChar);
 *
 *   with the following documentation:
 *     @param ch
 *       The character that was just read. fTerminate should determine whether
 *       this character is a terminator.
 *
 *     @param pbDiscardChar
 *       Whether this character should be added to the MYSTRING object. Prior
 *       to returning TRUE (non-zero) or FALSE (zero), fTerminate should set
 *       *pbDiscardChar to one of the following values:
 *
 *         0: Do not discard the character. Add it to the MYSTRING object
 *         1: Discard the character. Do not add it to the MYSTRING object
 *
 *     @return
 *       TRUE if this character should cause termination of input; FALSE
 *       otherwise.
 *
 *   The fTerminate function is not called upon EOF.
 *
 * @return
 *   upon failure:
 *     MYSTRING_STATUS_ERROR (any of the arguments are null)
 *
 *   upon success:
 *     MYSTRING_STATUS_SUCCESS
 *
 * @example
 *   Assume that you want to accept all sequences of digits, ignoring any even
 *   digit. Any other character is to terminate input and that chraracter is
 *   to be ignored. In this scenario, if the input were "12345 23476abc" then
 *   you want the MYSTRING object to contain "135", and the next time this
 *   function was called with the same arguments, it would retrieve "37". On
 *   the first call, the space is discarded. ON the second call, the 'a' is
 *   discarded. You might define a function such as acceptDigits, that meets
 *   the signature requirements of fTerminate:
 *
 *   int acceptDigits(char ch, int * pbDiscardChar)
 *   {
 *     // If the character is a digit, ...
 *     if (isdigit(ch))
 *     {
 *       // First, convert the character containing the digit to its numeric
 *       // value.
 *       ch -= '0';
 *
 *       // Discard the character if it is even; do not discard it otherwise.
 *       *pbDiscardChar = (ch % 2 == 0);
 *
 *       // Do not terminate. We want to keep retrieving input.
 *       return FALSE;
 *     }
 *
 *     // It's not a digit. Throw away the character, ...
 *     *pDiscardChar = TRUE;
 *
 *     // and terminate input into this MYSTRING object
 *     return TRUE;
 *   }
 *
 *   // Now we can call mystring_input using that function:
 *   ...
 *   status = mystring_input(hString, stdin, acceptDigits);
 *   ...
 */
MyString_Status mystring_input(MYSTRING hString,
                               FILE * hFile,
                               int (* fTerminate)(char ch,
                                                  int * pbDiscardChar));

#endif /* MYSTRING */

