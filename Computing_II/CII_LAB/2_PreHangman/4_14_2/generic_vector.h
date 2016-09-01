#include "status.h"

#ifndef VECTOR_H
#define VECTOR_H

typedef struct _GENERIC_VECTOR *GENERIC_VECTOR;  //very similar to void*

/*****************************************************************************
 * The Generic vector type requires you to populate and pass in a set of
 * function pointers that allow for all of the basic operations on the 
 * vector.
 ****************************************************************************/
struct generic_vector_functions
{
	void (*assignment)(void**, void*);
	//destroy
	void (*destructor)(void**);
};
typedef struct generic_vector_functions Generic_vector_functions;


// Makes vector of vector
GENERIC_VECTOR make_vector_of_vector(void);

// Assignment / Destroy functions
void myvector_assignment(void** hVectVect, void* hVectofStr);
void myvector_destroyer(void** hVector);


/*****************************************************************************
 * Create a new GENERIC_VECTOR opaque object.
 *
 * @return
 *   Not enough memory = NULL
 *
 *   SUCCESS
 *   A GENERIC_VECTOR handle to an empty vector object that has:
 *   size = 0, capacity = 1
 ****************************************************************************/
GENERIC_VECTOR generic_vector_init_default(Generic_vector_functions functions);

/*****************************************************************************
 * Retrieves the number of integers that the current vector holds.
 *
 * @param hVector
 *   GENERIC_VECTOR handle to the vector object that you want to query the size of.
 *
 * @return
 *   The size of the vector or -1 on Error
 ****************************************************************************/
int generic_vector_size(GENERIC_VECTOR hVector);

/*****************************************************************************
 * Retrieves the total number of integers that the vector can contain before
 * it has to do an internal resize operation of the dynamic array.
 *
 * @param hVector
 *   GENERIC_VECTOR handle to the vector object that you want to query the capacity of.
 * 
 * @return
 *   The capacity of the vector or -1 on Error
 ****************************************************************************/
int generic_vector_capacity(GENERIC_VECTOR hVector);

/*****************************************************************************
 * Attempts to add an element to the back of the vector, resizing if necessary
 * in order to hold the new element.
 *
 * @param hVector
 *   GENERIC_VECTOR handle to the vector object that you want to insert a new element
 *   into.
 * @param item
 *   integer element to be copied and placed in the vector at the high end of
 *   the array indexes.
 * 
 * @return
 *   SUCCESS or
 *   FAILURE The internal resize operation failed with out of memory.
 ****************************************************************************/
Status generic_vector_push_back(GENERIC_VECTOR hVector, void* item);

/*****************************************************************************
 * Attempts to remove an element from the back of the vector.  Will fail
 * if the vector is empty.
 *
 * @param hVector
 *   GENERIC_VECTOR handle to the vector object that you want to remove an element
 *   from.
 * 
 * @return
 *   SUCCESS or
 *   FAILURE if the vector is empty.
 ****************************************************************************/
Status generic_vector_pop_back(GENERIC_VECTOR hVector);

/*****************************************************************************
 * Gives the user a pointer to the element at index param index so that they
 * can freely change it or view it.  This pointer will be invalidated if
 * any internal resize operation happens between when the user grabbed the
 * value and when they use it.
 *
 * @param hVector
 *   GENERIC_VECTOR handle to the vector object that you want to look at the nth
 *   item.
 * @param index
 *   integer representing the index of the item that you want to have access to.
 * 
 * @return
 *   pointer to index of the index'th item
 *   NULL if the vector is empty or if the index is out of bounds
 ****************************************************************************/
void* generic_vector_at(GENERIC_VECTOR hVector, int index); //will do bounds checking


/*****************************************************************************
 * Destroy a GENERIC_VECTOR opaque object and set the handle to NULL.
 * Will not attempt to destroy an object if the handle is NULL.
 *
 * @param pGENERIC_VECTOR
 *   Address of a GENERIC_VECTOR handle so that the function can free it and 
 *   change it to NULL.
 ****************************************************************************/
void generic_vector_destroy(GENERIC_VECTOR* pGENERIC_VECTOR);

#endif
