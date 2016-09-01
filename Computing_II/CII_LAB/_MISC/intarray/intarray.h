/*
 * A resizable array of integers, and operations thereon
 *
 * Copyright (c) 2014 Derrell Lipman
 *
 * License:
 *   LGPL: http://www.gnu.org/licenses/lgpl.html 
 */

#ifndef __INTARRAY__
#define __INTARRAY__


/** An opaque intarray handle */
typedef struct _IntArray *                              INTARRAY;

/** Failure/Success values */
typedef enum { Intarray_Fail, Intarray_Success }        Intarray_Status;


/**
 * Create a new integer intarray object.
 *
 * @return
 *   The handle to be used for referencing this new integer array
 */
INTARRAY intarray_create(void);


/**
 * Destroy an intarray object when it is no longer needed.
 *
 * @param hIntArray
 *   The handle to the intarray object to be destroyed
 */
void intarray_destroy(INTARRAY hIntArray);


/**
 * Set a value in the array. If the specified index is beyond the current
 * maximum bound of the array, the values at all intervening indexes (between
 * the current maximum bound and the specified index) are set to zero.
 *
 * @param hIntArray
 *   The handle to the intarray object to be operated on
 *
 * @param index
 *   The index in the array whose value is to be set
 *
 * @param value
 *   The value to place at the specified index
 *
 * @return
 *   Intarray_Success upon success; Intarray_Fail if a negative index value is
 *   provided.
 */
Intarray_Status intarray_set(INTARRAY hIntArray, int index, int value);

/**
 * Get a value from the array
 *
 * @param hIntArray
 *   The handle to the intarray object to be operated on
 *
 * @param index
 *   The index in the array whose value is to be obtained
 *
 * @param pValue
 *   The location to put the returned value (upon success)
 *
 * @return
 *   Intarray_Success upon success;
 *   Intarray_Fail if the index is outside of the current bounds of the array
 */
Intarray_Status intarray_get(INTARRAY hIntArray, int index, int * pValue);


/**
 * Get the sum of the values in the intarray
 *
 * @param hIntArray
 *   The handle to the intarray object to be operated on
 *
 * @return
 *   The sum of each of the values within the intarray
 */
int intarray_sum(INTARRAY hIntArray);



#endif   // __INTARRAY__
