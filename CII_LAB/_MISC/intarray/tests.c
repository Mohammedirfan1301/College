#include <stdio.h>
#include "intarray.h"

// Forward declarations
static Intarray_Status test_create_destroy(void);
static Intarray_Status test_set_0_get_0(void);
static Intarray_Status test_set_1_get_0_get_1(void);
static Intarray_Status test_set_4_get_4_get_3_get_2_get_1(void);
static Intarray_Status test_sum(void);
static Intarray_Status test_sum_multiple_intarrays(void);

typedef struct Test
{
    // Test function to be run
    Intarray_Status (* pfThisTest)(void);

    // Name of the test, to be displayed
    char *             pTestName;
} Test;


/*
 * Array of test functions to be called
 *
 * Each function returns 1 upon success; 0 upon failure
 *
 */
Test            tests[] =
{
    {
        test_create_destroy,
        "Create and destroy an IntArray object"
    },
    {
        test_set_0_get_0,
        "Set a value at index 0, then retrieve it"
    },
    {
        test_set_1_get_0_get_1,
        "Set a value at index 1; ensure index 0 was set to 0"
    },
    {
        test_set_4_get_4_get_3_get_2_get_1,
        "Set a value at index 4; ensure all intervening values are set to 0"
    },
    {
        test_sum,
        "Check the sum function on an 11-element array"
    },
    {
        test_sum_multiple_intarrays,
        "Ensure that use of multiple IntArray objects do not conflict"
    }
};

int main(int argc, char * argv[])
{
    int             i;
    Intarray_Status result;
    Test *          pTest;

    // For each defined test...
    for (i = 0, pTest = &tests[0];
         i < sizeof(tests) / sizeof(tests[0]);
         ++i, ++pTest)
    {
        // ... run that test and display the result.
        // Each test displays its particular error message.
        printf("Test %2d (%s):\n", i, pTest->pTestName);
        result = (* pTest->pfThisTest)();
        printf("    %s\n",
               result == Intarray_Success ? "SUCCESS" : "FAIL");
    }
}


static Intarray_Status test_create_destroy(void)
{
    INTARRAY        hIntArray;

    // Create an intarray handle
    hIntArray = intarray_create();

    // Destroy the intarray
    intarray_destroy(hIntArray);

    // There were no failure cases in this test
    return Intarray_Success;
}

static Intarray_Status test_set_0_get_0(void)
{
    int             value;
    INTARRAY        hIntArray;

    // Create an intarray handle
    hIntArray = intarray_create();

    // Set a value at index 0
    if (intarray_set(hIntArray, 0, 23) != Intarray_Success)
    {
        printf("\tset failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Get the value from index 0
    if (intarray_get(hIntArray, 0, &value) != Intarray_Success)
    {
        printf("\tget failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Ensure that the value we retrieved matches what we'd set
    if (value != 23)
    {
        printf("\tcomparison failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Destroy the intarray
    intarray_destroy(hIntArray);

    // If we get here, everything succeeded
    return Intarray_Success;
}

static Intarray_Status test_set_1_get_0_get_1(void)
{
    int             value;
    INTARRAY        hIntArray;

    // Create an intarray handle
    hIntArray = intarray_create();

    // Set a value at index 1
    if (intarray_set(hIntArray, 1, 23) != Intarray_Success)
    {
        printf("\tset failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Get the value from index 0
    if (intarray_get(hIntArray, 0, &value) != Intarray_Success)
    {
        printf("\tget failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Ensure that the value we retrieved was automatically set to 0
    if (value != 0)
    {
        printf("\tcomparison at index 0 failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Get the value from index 1
    if (intarray_get(hIntArray, 1, &value) != Intarray_Success)
    {
        printf("\tget failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Ensure that the value we retrieved matches what we set
    if (value != 23)
    {
        printf("\tcomparison at index 1 failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Destroy the intarray
    intarray_destroy(hIntArray);

    // If we get here, everything succeeded
    return Intarray_Success;
}

static Intarray_Status test_set_4_get_4_get_3_get_2_get_1(void)
{
    int             i;
    int             value;
    INTARRAY        hIntArray;

    // Create an intarray handle
    hIntArray = intarray_create();

    // Set a value at index 4
    if (intarray_set(hIntArray, 4, 23) != Intarray_Success)
    {
        printf("\tset failed\n");
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Ensure that all values at indexes up to 4 contain 0, and index 4
    // contains the value we set (23)
    for (i = 0; i <= 4; i++)
    {
        // Get the value from this index
        if (intarray_get(hIntArray, i, &value) != Intarray_Success)
        {
            printf("\tget at index %d failed\n", i);
            intarray_destroy(hIntArray);
            return Intarray_Fail;
        }

        // Ensure that the value we retrieved was automatically set to 0
        if (value != (i == 4 ? 23 : 0))
        {
            printf("\tcomparison at index %d failed\n", i);
            intarray_destroy(hIntArray);
            return Intarray_Fail;
        }
    }

    // Destroy the intarray
    intarray_destroy(hIntArray);

    // If we get here, everything succeeded
    return Intarray_Success;
}

static Intarray_Status test_sum(void)
{
    int             i;
    int             sum;
    int             expectedSum;
    INTARRAY        hIntArray;
    struct
    {
        int             index;
        int             value;
    }               valuesToSet[] =
        {
            {  1,  1 },
            {  2,  2 },
            { 10, 23 },
            { -1 }
        };

    // Create an intarray handle
    hIntArray = intarray_create();

    // Set the value at certain indexes, with all intervening ones
    // automatically set to 0. As we're setting values, calculate the sum that
    // we expect to receive.
    for (i = 0, expectedSum = 0; valuesToSet[i].index >= 0; i++)
    {
        if (intarray_set(hIntArray,
                         valuesToSet[i].index,
                         valuesToSet[i].value) != Intarray_Success)
        {
            printf("\tset index %d failed\n", valuesToSet[i].index);
            intarray_destroy(hIntArray);
            return Intarray_Fail;
        }

        // Update the sum
        expectedSum += valuesToSet[i].value;
    }

    // Validate the sum of the values in the array
    if ((sum = intarray_sum(hIntArray)) != expectedSum)
    {
        printf("\tsum failed: expected %d, got %d\n", expectedSum, sum);
        intarray_destroy(hIntArray);
        return Intarray_Fail;
    }

    // Destroy the intarray
    intarray_destroy(hIntArray);

    // If we get here, everything succeeded
    return Intarray_Success;
}

static Intarray_Status test_sum_multiple_intarrays(void)
{
    int             i;
    int             sum;
    int             expectedSum1;
    int             expectedSum2;
    INTARRAY        hIntArray1;
    INTARRAY        hIntArray2;
    struct ValuesToSet
    {
        int             index;
        int             value;
    };
    struct ValuesToSet valuesToSet1[] =
        {
            {  1,  1 },
            {  2,  2 },
            { 10, 23 },
            { -1 }
        };
    struct ValuesToSet valuesToSet2[] =
        {
            {  1,  2 },
            {  2,  3 },
            { 10, 24 },
            { -1 }
        };

    // Create two intarray handles
    hIntArray1 = intarray_create();
    hIntArray2 = intarray_create();

    // Set the value at certain indexes in the first intarray.
    for (i = 0, expectedSum1 = 0; valuesToSet1[i].index >= 0; i++)
    {
        if (intarray_set(hIntArray1,
                         valuesToSet1[i].index,
                         valuesToSet1[i].value) != Intarray_Success)
        {
            printf("\tset index %d failed\n", valuesToSet1[i].index);
            intarray_destroy(hIntArray1);
            return Intarray_Fail;
        }

        // Update the sum
        expectedSum1 += valuesToSet1[i].value;
    }

    // Set the value at certain indexes in the second intarray.
    for (i = 0, expectedSum2 = 0; valuesToSet2[i].index >= 0; i++)
    {
        if (intarray_set(hIntArray2,
                         valuesToSet2[i].index,
                         valuesToSet2[i].value) != Intarray_Success)
        {
            printf("\tset index %d failed\n", valuesToSet2[i].index);
            intarray_destroy(hIntArray2);
            return Intarray_Fail;
        }

        // Update the sum
        expectedSum2 += valuesToSet2[i].value;
    }

    // Validate the sum of the values in the first array
    if ((sum = intarray_sum(hIntArray1)) != expectedSum1)
    {
        printf("\tsum on IntArray 1 failed: expected %d, got %d\n",
               expectedSum1, sum);
        intarray_destroy(hIntArray1);
        return Intarray_Fail;
    }

    // Validate the sum of the values in the second array
    if ((sum = intarray_sum(hIntArray2)) != expectedSum2)
    {
        printf("\tsum on IntArray 2 failed: expected %d, got %d\n",
               expectedSum2, sum);
        intarray_destroy(hIntArray1);
        return Intarray_Fail;
    }

    // Destroy the intarrays
    intarray_destroy(hIntArray1);
    intarray_destroy(hIntArray2);

    // If we get here, everything succeeded
    return Intarray_Success;
}
