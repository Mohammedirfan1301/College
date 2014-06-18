#include <stdio.h>
#include <string.h>
#include "unittest.h"
#include "mystring.h"

// Forward declarations
static int test_init_default_size_capacity(void);
static int test_init_c_string_size_capacity(void);
static int test_init_c_string_value(void);
// TODO: add forward declarations of each new test here


/*
 * Array of test functions to be called
 *
 * Each function returns 1 upon success; 0 upon failure
 *
 */
UnitTest            tests[] =
{
    {
        test_init_default_size_capacity,
        "Initialize from a c-string; validate size and capacity"
    },
    {
        test_init_c_string_size_capacity,
        "Initialize from a c-string; validate size and capacity"
    },
    {
        test_init_c_string_value,
        "Initialize from a c-string; validate character data"
    }
    // TODO: add more UnitTest initializers here. Don't forget to add a comma,
    // above, when you add more here.
};

/** The number of tests */
int numberOfTests = sizeof(tests) / sizeof(tests[0]);


static int test_init_default_size_capacity(void)
{
    int             size;
    int             capacity;
    MYSTRING        hMyString;
    
    // Create an intarray handle
    hMyString = mystring_init_default();

    // Ensure that it has a size of 0
    size = mystring_size(hMyString);
    if (size != 0)
    {
        printf("\tExpected size to be 0; got %d\n", size);
        mystring_destroy(&hMyString);
        return 1;
    }
    
    // Ensure that it has a capacity of MYSTRING_STARTING_CAPACITY
    capacity = mystring_capacity(hMyString);
    if (capacity != MYSTRING_STARTING_CAPACITY)
    {
        printf("\tExpected capacity to be %d; got %d\n",
               MYSTRING_STARTING_CAPACITY, capacity);
        mystring_destroy(&hMyString);
        return 1;
    }

    // Destroy the intarray
    mystring_destroy(&hMyString);
    
    // Success!
    return 0;
}


static int test_init_c_string_size_capacity(void)
{
    int             size;
    int             capacity;
    MYSTRING        hMyString;
    
    // Create an intarray handle
    hMyString = mystring_init_c_string("hello");

    // Ensure that it has a size of 5
    size = mystring_size(hMyString);
    if (size != 5)
    {
        printf("\tExpected size to be 5; got %d\n", size);
        mystring_destroy(&hMyString);
        return 1;
    }
    
    // Ensure that it has a capacity of 5
    capacity = mystring_capacity(hMyString);
    if (capacity != 5)
    {
        printf("\tExpected capacity to be 5; got %d\n", capacity);
        mystring_destroy(&hMyString);
        return 1;
    }

    // Destroy the intarray
    mystring_destroy(&hMyString);
    
    // Success!
    return 0;
}

static int test_init_c_string_value(void)
{
    char            outputBuffer[BUFSIZ] = { '\0' };
    MYSTRING        hMyString;
    FILE *          hNullFile;
    
    // Create an intarray handle
    hMyString = mystring_init_c_string("hello");

    // Open the null file, so the actual output will be ignored
    if ((hNullFile = fopen("/dev/null", "w")) == NULL)
    {
        printf("Could not open /dev/null\n");
        mystring_destroy(&hMyString);
        return 1;
    }

    // Use our local buffer for output, so we can examine what got written
    setbuf(hNullFile, outputBuffer);

    // Output the current string into our buffer
    mystring_output(hMyString, hNullFile);

    // Close the null file
    fclose(hNullFile);

    // We expect to see "hello" in the first five bytes of the local buffer
    if (strncmp(outputBuffer, "hello", 5) != 0)
    {
        printf("\tMyString object contains wrong data: "
               "expected \"hello\"; found \"%.5s\"\n", outputBuffer);
        mystring_destroy(&hMyString);
        return 1;
    }

    // Destroy the intarray
    mystring_destroy(&hMyString);
    
    // Success!
    return 0;
}

// TODO: add more test implementations here
