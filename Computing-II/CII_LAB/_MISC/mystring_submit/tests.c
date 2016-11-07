#include <stdio.h>
#include <string.h>
#include "unittest.h"
#include "mystring.h"

// Forward declarations
static int test_init_default_size_capacity(void);
static int test_init_c_string_size_capacity(void);
static int test_init_c_string_value(void);
static int test_mystring_concatenate_c_string(void);
static int test_mystring_concatenate_mystring(void);
static int test_mystring_truncate(void);

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
    },
    {
		test_mystring_concatenate_c_string,
		"Initialize from c-string, test concatenate c_string to my_string object"
	},
	{
		test_mystring_concatenate_mystring,
		"Initialize from c_string, test concatenate my_string obj to my_string obj"
	},
	{
		test_mystring_truncate,
		"Initialize from c_string, test truncate function"
	}

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

static int test_mystring_concatenate_c_string(void)
{
	int size;
	int capacity;
	MYSTRING hString;
	MyString_Status code;
	
	// First initialize a my_string object
	hString = mystring_init_c_string("hello\n");
	
	// Make sure it initialized
	if(hString == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
	// Otherwise continue testing
	// Next concatenate a c_string to the my_string object. In this case,
	// we will add "hello" to the end of "hello"
	code = mystring_concatenate_c_string(hString, "hello\n");
	
	// See if it failed to concatenate
	if(code == MYSTRING_STATUS_ERROR)
	{
		 printf("\tFailure to concatenate a string!\n");
		 return 1;
	}
	
	// Test the size and capacity of the concatenated my_string object
	size = mystring_size(hString);
	capacity = mystring_capacity(hString);
	
	// Test size
	if(size != 12)
	{
		printf("\tSize should be 12; we got %d\n", size);
		return 1;
	}
	
	if(capacity < 12)
	{
		printf("\tCapacity should be at least 12; we got %d\n", capacity);
		return 1;
	
	}

	// Destroy the my_string object
    mystring_destroy(&hString);
    
    // Success!
    return 0;
}

static int test_mystring_concatenate_mystring(void)
{
	int size;
	int capacity;
	MYSTRING hDest;
	MYSTRING hSource;
	MyString_Status code;
	
	// First initialize the my_string object
	hDest = mystring_init_c_string("hello\n");
	hSource = mystring_init_c_string("hello\n");
	
	// Make sure they initialized
	if(hDest == NULL || hSource == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
	// Otherwise continue testing
	// Next concatenate a c_string to the my_string object. In this case,
	// we will add "hello" to the end of "hello"
	code = mystring_concatenate_mystring(hDest, hSource);
	
	// See if it failed to concatenate
	if(code == MYSTRING_STATUS_ERROR)
	{
		 printf("\tFailure to concatenate a mystring!\n");
		 return 1;
	}
	
	// Test the size and capacity of the concatenated my_string object
	size = mystring_size(hDest);
	capacity = mystring_capacity(hDest);
	
	// Test size
	if(size != 12)
	{
		printf("\tSize should be 12; we got %d\n", size);
		return 1;
	}
	
	if(capacity < 12)
	{
		printf("\tCapacity should be at least 12; we got %d\n", capacity);
		return 1;
	
	}

	// Destroy the mystring objects
    mystring_destroy(&hDest);
    mystring_destroy(&hSource);
    
    // Success!
    return 0;

}

static int test_mystring_truncate(void)
{
	int size;
	MYSTRING hString;
	MyString_Status code;
	
	// Create an inital mystring object to truncate
	hString = mystring_init_c_string("hello\n");
	
	// Make sure it initialized
	if(hString == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
	// Otherwise continue testing
	
	// First, truncate it to size 5.
	code = mystring_truncate(hString, 5);

	// See if it failed
	if(code == MYSTRING_STATUS_ERROR)
	{
		 printf("\tFailure to truncate a mystring!\n");
		 return 1;
	}
	
	// Test the size of the new mystring object
	size = mystring_size(hString);
	
	// Test size
	if(size != 5)
	{
		printf("\tSize should be 5; we got %d\n", size);
		return 1;
	}

	// Destroy the my_string object
    mystring_destroy(&hString);
    
    // Success!
    return 0;
}
