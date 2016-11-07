/*
 * A resizable array of integers, and operations thereon
 *
 * Copyright (c) 2014 Derrell Lipman
 *
 * License:
 *   LGPL: http://www.gnu.org/licenses/lgpl.html 
 */

#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"


/** Our internal structure which implements intarray object */
struct _IntArray
{
    int             maxIndex;   // the maximum index value currently in use
    int *           pInts;      // malloc'ed array of integers
};



/**
 * Create a new integer array (intarray) object.
 *
 * @return
 *   The handle to be used for referencing this new integer array
 */
INTARRAY intarray_create(void)
{
    INTARRAY        pIntArray;

    // Allocate a new intarray object
    if ((pIntArray = malloc(sizeof(struct _IntArray))) == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    // The array is currently empty
    pIntArray->maxIndex = -1;

    // We have not yet allocate the internal array of integers. Indicate that
    // by setting it to NULL.
    pIntArray->pInts = NULL;

    // Give 'em the handle to this intarray object
    return pIntArray;
}


/**
 * Destroy an intarray object when it is no longer needed.
 *
 * @param pIntArray
 *   The handle to the intarray object to be destroyed
 */
void intarray_destroy(INTARRAY pIntArray)
{
    // If the internal array of integers has been allocated...
    if (pIntArray->pInts != NULL)
    {
        // ... then free it.
        free(pIntArray->pInts);
    }

    // Free the object itself
    free(pIntArray);
}


/**
 * Set a value in the array. If the specified index is beyond the current
 * maximum bound of the array, the values at all intervening indexes (between
 * the current maximum bound and the specified index) are set to zero.
 *
 * @param pIntArray
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
Intarray_Status intarray_set(INTARRAY pIntArray, int index, int value)
{
    int             i;
    int *           pTemp;

    // Validate that the index is feasible
    if (index < 0)
    {
        return Intarray_Fail;
    }

    // Is the internal array already large enough to set a value at the
    // specified index?
    if (pIntArray->maxIndex < index)
    {
        // Nope. We need to allocate it larger. (Note that calling realloc
        // with NULL as the first argument is the same as calling malloc: it
        // just allocates new memory without doing any copying.)
        if ((pTemp =
             realloc(pIntArray->pInts, (index + 1) * sizeof(int))) == NULL)
        {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }

        // We had a successful reallocation. Use the newly-allocated memory now.
        pIntArray->pInts = pTemp;

        // Fill in all values between the old max index and the new max index
        // with zeros.
        for (i = pIntArray->maxIndex + 1; i < index; i++)
        {
            pIntArray->pInts[i] = 0;
        }
    }

    // We now have valid values up through the new index
    pIntArray->maxIndex = index;

    // Set the specified index to the specified value
    pIntArray->pInts[index] = value;

    return Intarray_Success;
}

/**
 * Get a value from the array
 *
 * @param pIntArray
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
Intarray_Status intarray_get(INTARRAY pIntArray, int index, int * pValue)
{
    // Validate that the index is in bounds
    if (index < 0 || index > pIntArray->maxIndex)
    {
        return Intarray_Fail;
    }

    // Give 'em the value at the specified index
    *pValue = pIntArray->pInts[index];

    // Success
    return Intarray_Success;
}


/**
 * Get the sum of the values in the intarray
 *
 * @param pIntArray
 *   The handle to the intarray object to be operated on
 *
 * @return
 *   The sum of each of the values within the intarray
 */
int intarray_sum(INTARRAY pIntArray)
{
    int             i;
    int             sum;

    // Iterate through the elements of the array and calculate the sum
    for (i = 0; i <= pIntArray->maxIndex; i++)
    {
        sum += pIntArray->pInts[i];
    }

    return sum;
}
