#include "status.h"

#ifndef CHAR_VECTOR_H
#define CHAR_VECTOR_H

typedef struct _CHAR_VECTOR *CHAR_VECTOR;  //very similar to void*


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

#endif
