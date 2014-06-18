#include <stdio.h>
#include "intarray.h"


int main(int argc, char * argv[])
{
    int             i;
    int             value;
    INTARRAY        hIntArray;

    // Create an intarray handle
    hIntArray = intarray_create();

    for (i = 0; i < 3; i++)
    {
        // Set a value at the value's index
        if (intarray_set(hIntArray, i, i) != Intarray_Success)
        {
            printf("Failed to set index %d, value %d\n", i, i);
            intarray_destroy(hIntArray);
            return 1;
        }
    }

    // Set a value at index 10
    if (intarray_set(hIntArray, 10, 23) != Intarray_Success)
    {
        printf("Failed to set index 10, value 23\n");
        intarray_destroy(hIntArray);
        return 1;
    }

    // Retrieve and print all of the values from the array
    printf("Array values:\n");
    for (i = 0; intarray_get(hIntArray, i, &value) == Intarray_Success; i++)
    {
        printf("\t%2d: %d\n", i, value);
    }

    // Retrieve and print the sum of all of these values
    printf("The sum of the array members is %d\n", intarray_sum(hIntArray));

    // Destroy the intarray
    intarray_destroy(hIntArray);

    // Success!
    return 0;
}
