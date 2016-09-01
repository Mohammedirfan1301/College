#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unittest.h"
#include "mystring.h"

// UNIT TESTS - 18 in total, one for each function
static int test_mystring_init_default(void);
static int test_mystring_init_c_string(void);
static int test_mystring_destroy(void);
static int test_mystring_size(void);
static int test_mystring_capacity(void);
static int test_mystring_output(void);

static int test_mystring_concatenate_c_string(void);	
static int test_mystring_concatenate_mystring(void);	
static int test_mystring_truncate(void);				
static int test_mystring_push(void);					

static int test_mystring_pop(void);
static int test_mystring_peek(void);
static int test_mystring_get(void);
static int test_mystring_put(void);

static int test_mystring_init_substring(void);
static int test_mystring_to_c_string(void);
static int test_mystring_input(void);
static int test_mystring_input_lineinput(void);

// 	Functions for test_mystring_input
int acceptNonWhite(char ch, int *pbDiscardChar);
int acceptOddDigits(char ch, int * pbDiscardChar);
int acceptLineInput(char ch, int * pbDiscardChar);

//	I use TRUE / FALSE in a few functions to represent "0" and "1"
#define TRUE 1
#define FALSE 0
/*
 * Array of test functions to be called
 *
 * Each function returns 0 upon success; 1 upon failure
 *
 */
UnitTest            tests[] =
{
	{
		test_mystring_init_default,
		"Initialize a default mystring and test the init_default function"
	},
	{
		test_mystring_init_c_string,
		"Initialize from a c_string to test the init_c_string function"
	},
	{
		test_mystring_destroy,
		"Initialize a default mystring and test the destroy function"
	},
	{
		test_mystring_size,
		"Initialize several mystrings and test the mystring_size function"
	},
	{
		test_mystring_capacity,
		"Initialize several mystrings and test the mystring_capacity function"		
	},
    {
    	test_mystring_output,
    	"Initialize several mystrings to test the output function"
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
	},
	{
		test_mystring_push,
		"Initialize from c_string, test the push function"
	},
	{
		test_mystring_pop,
		"Initialize from c_string, to test the pop function"
	},
	{
		test_mystring_peek,
		"Initialize from c_string, to test the peek function"
	},
	{
		test_mystring_get,
		"Initialize a mystring and test the get function"
	},
	{
		test_mystring_put,
		"Initialize a mystring and test the put function"
	},
	{
		test_mystring_init_substring,
		"Initialize a mystring and test the init_substring function"
	},
	{
		test_mystring_to_c_string,
		"Initialize several mystrings and test the mystring_to_c_string function"
	},
	{
		test_mystring_input,
		"Initialize several mystrings and test the mystring_input function"
	},
	{
		test_mystring_input_lineinput,
		"Test mystring_input: Get an entire line, terminating on newline."
	}
};

/** The number of tests */
int numberOfTests = sizeof(tests) / sizeof(tests[0]);

// DONE:
static int test_mystring_init_default(void)
{
	int size;
	int capacity;
	MYSTRING hTemp;
	
//	See if we can even initialize a default MYSTRING
	hTemp = mystring_init_default();
	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}
	
//	Now check and see if it was initialized properly. Size of 0 & Capacity of 7
	size = mystring_size(hTemp);
	capacity = mystring_capacity(hTemp);
	
	if(size != 0)
	{
		printf("\tERROR: Expected size of 0; got size of %d", size);
		return 1;
	}
	
	if(capacity != MYSTRING_STARTING_CAPACITY)
	{
		printf("\tERROR: Expected capacity of %d; got capacity of %d", MYSTRING_STARTING_CAPACITY, capacity);
		return 1;
	}
	
//	Now destroy hTemp
	mystring_destroy(&hTemp);
	
//	IF we get this far, then SUCCESS
	return 0;
}


static int test_mystring_init_c_string(void)
{
	int size;
	int capacity;
	MYSTRING hTemp;
	
//	Try & initialize a MYSTRING object from a c_string
	hTemp = mystring_init_c_string("Hello\n");
	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}
	
//	Now check the size & capacity of this new MYSTRING object
	size = mystring_size(hTemp);
	capacity = mystring_capacity(hTemp);
	
	if(size < 6)
	{
		printf("\tERROR: Expected size of at least 6; got size of %d", size);
		return 1;
	}
	
	if(capacity < 6)
	{
		printf("\tERROR: Expected capacity of at least 6; got capacity of %d", capacity);
		return 1;
	}
	
//	Now destroy hTemp
	mystring_destroy(&hTemp);
	
//	IF we get this far, then SUCCESS
	return 0;
}


static int test_mystring_destroy(void)
{
	MYSTRING hTemp;
	
//	Intitialize a MYSTRING object using init_default
	hTemp = mystring_init_default();
	
// 	See if it initialized	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}

//	Now DESTROY it and see if it is NULL.
	mystring_destroy(&hTemp);
	
	if(hTemp != NULL)
	{
		printf("\tERROR: Failed to destroy a mystring object!\n");
		return 1;
	}
	
//	Initialize a MYSTRING object using init_c_string
	hTemp = mystring_init_c_string("Hello\n");

// 	See if it initialized	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}

//	Now DESTROY it and see if it is NULL.
	mystring_destroy(&hTemp);
	
	if(hTemp != NULL)
	{
		printf("\tERROR: Failed to destroy a mystring object!\n");
		return 1;
	}
	
//	IF we get this far, then SUCCESS
	return 0;
}


static int test_mystring_size(void)
{
	int size;
	MYSTRING hTemp;
	
//	Try & initialize a MYSTRING object from a c_string
	hTemp = mystring_init_c_string("The\n");
	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}
	
//	Now check the size of the MYSTRING object
	size = mystring_size(hTemp);
	
	if(size < 3)
	{
		printf("\tERROR: Expected size of at least 3; got size of %d", size);
		return 1;
	}
	
//	Destroy hTemp
	mystring_destroy(&hTemp);
	
//	Initialize an empty MYSTRING object & check its size
	hTemp = mystring_init_c_string("\n");
	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}
	
	size = mystring_size(hTemp);
	
	if(size < 1)
	{
		printf("\tERROR: Expected size of at least 1; got size of %d", size);
		return 1;
	}
	
//	Destroy hTemp
	mystring_destroy(&hTemp);	
	
//	IF we get this far, then SUCCESS
	return 0;
}


static int test_mystring_capacity(void)
{
	int capacity;
	MYSTRING hTemp;
	
//	Try & initialize a MYSTRING object from a c_string
	hTemp = mystring_init_c_string("The\n");
	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}
	
//	Now check the size of the MYSTRING object
	capacity = mystring_capacity(hTemp);
	
	if(capacity < 4)
	{
		printf("\tERROR: Expected size of at least 4; got size of %d", capacity);
		return 1;
	}
	
//	Now destroy hTemp
	mystring_destroy(&hTemp);
	
//	Initialize an empty MYSTRING object & check its capacity
	hTemp = mystring_init_c_string("\n");
	
	if(hTemp == NULL)
	{
		printf("\tERROR: Failed to initialize a default MYSTRING object! \n");
		return 1;
	}
	
	capacity = mystring_capacity(hTemp);
	
	if(capacity < 1)
	{
		printf("\tERROR: Expected size of at least 1; got size of %d", capacity);
		return 1;
	}
	
//	Destroy hTemp
	mystring_destroy(&hTemp);
	
//	IF we get this far, then SUCCESS
	return 0;
}


static int test_mystring_output(void)
{
	MYSTRING hTemp;
	FILE* output;
	MyString_Status Code;
	char arr_test[6];
	int i;
	
//	Try & initialize a MYSTRING object from a c_string
	hTemp = mystring_init_c_string("hello, World!\n");
	
//	Open a text file for outputting.
	output = fopen("test.txt", "w");
	
//	See if the output file opened correctly
	if(output == NULL)
	{
		printf("\tERROR: Failed to open output file!\n");
		return 1;
	}
	
//	Now output to the text file
	Code = mystring_output(hTemp, output);
	
//	See if we got an error code from the output function
	if(Code == MYSTRING_STATUS_ERROR)
	{
		printf("\tERROR: mystring_output failed to output hString to the file!\n");
		return 1;
	}
	
//	Close the file & reopen it in read mode
	fclose(output);
	output = fopen("test.txt", "r");
	
	if(output == NULL)
	{
		printf("\tERROR: Failed to open output file!\n");
		return 1;
	}
	
//	Check the output file for the correct characters
	for(i = 0; i < 6; i++)
	{
		fscanf(output, "%c", &arr_test[i]);
	}
	arr_test[5] = '\n';		// NULL Terminate the string
	
//	Close the file (for good now)
	fclose(output);
	
//	Compare what we put into the MYSTRING to what we got from the file.
//	This will tell us if mystring_output correctly outputed or not.
	if(strncmp(arr_test, "hello", 5) != 0)
	{
		printf("\tERROR: Expected \"hello\" in the output file - got %s\n", arr_test);
		return 1;
	}
	
//	Destroy hTemp
	mystring_destroy(&hTemp);

//	IF we get this far, then SUCCESS
	return 0;
}


static int test_mystring_concatenate_c_string(void)
{
	int size;
	int capacity;
	MYSTRING hString;
	MyString_Status code;
	
// 	First initialize a my_string object
	hString = mystring_init_c_string("hello\n");
	
// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
/* 	Otherwise continue testing
	Next concatenate a c_string to the my_string object. In this case,
	we will add "hello" to the end of "hello"						*/
	code = mystring_concatenate_c_string(hString, "hello\n");
	
// 	See if it failed to concatenate
	if(code == MYSTRING_STATUS_ERROR)
	{
		 printf("\tFailure to concatenate a string!\n");
		 return 1;
	}
	
// 	Test the size and capacity of the concatenated my_string object
	size = mystring_size(hString);
	capacity = mystring_capacity(hString);
	
//  Test size
	if(size < 12)
	{
		printf("\tSize should be at least 12; we got %d\n", size);
		return 1;
	}
	
//	Test capacity
	if(capacity < 12)
	{
		printf("\tCapacity should be at least 12; we got %d\n", capacity);
		return 1;
	
	}

// 	Destroy the my_string object
    mystring_destroy(&hString);
    
// 	Success!
    return 0;
}


static int test_mystring_concatenate_mystring(void)
{
	int size;
	int capacity;
	MYSTRING hDest;
	MYSTRING hSource;
	MyString_Status code;
	
// 	First initialize the my_string object
	hDest = mystring_init_c_string("hello\n");
	hSource = mystring_init_c_string("hello\n");
	
// 	Make sure they initialized
	if(hDest == NULL || hSource == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
/*  Otherwise continue testing
 	Next concatenate a c_string to the my_string object. In this case,
  	we will add "hello" to the end of "hello"							*/
	code = mystring_concatenate_mystring(hDest, hSource);
	
// 	See if it failed to concatenate
	if(code == MYSTRING_STATUS_ERROR)
	{
		 printf("\tFailure to concatenate a mystring!\n");
		 return 1;
	}
	
// 	Test the size and capacity of the concatenated my_string object
	size = mystring_size(hDest);
	capacity = mystring_capacity(hDest);
	
// 	Test size
	if(size < 12)
	{
		printf("\tSize should be at least 12; we got %d\n", size);
		return 1;
	}
	
//	Test capacity
	if(capacity < 12)
	{
		printf("\tCapacity should be at least 12; we got %d\n", capacity);
		return 1;
	}

//	Destroy the mystring objects
    mystring_destroy(&hDest);
    mystring_destroy(&hSource);
    
// 	Success!
    return 0;

}


static int test_mystring_truncate(void)
{
	int size;
	MYSTRING hString;
	MyString_Status code;
	
// 	Create an inital mystring object to truncate
	hString = mystring_init_c_string("hello\n");
	
// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
// 	Otherwise continue testing
	
// 	First, truncate it to size 5.
	code = mystring_truncate(hString, 5);

// 	See if it failed
	if(code == MYSTRING_STATUS_ERROR)
	{
		 printf("\tFailure to truncate a mystring!\n");
		 return 1;
	}
	
// 	Test the size of the new mystring object
	size = mystring_size(hString);
	
//	 Test size
	if(size < 5)
	{
		printf("\tSize should be at least 5; we got %d\n", size);
		return 1;
	}

// 	Destroy the my_string object
    mystring_destroy(&hString);
    
// 	Success!
    return 0;
}


static int test_mystring_push(void)
{
	MYSTRING hString;
	MyString_Status code;
	int i, check = 0;
	char ch;
	char test[7];
	
	strcpy(test, "helloh");
	
//	First initialize a mystring object
	hString = mystring_init_c_string("hello");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Try to push several characters and see if anything happens
	code = mystring_push(hString, 'h');

//	The above SHOULD work. See if it did:
	if(code == MYSTRING_STATUS_ERROR)
	{
		printf("\tFailed to push 'h' onto the mystring object! \n");
		return 1;
	}
//	If it did work, did the person implement the function correctly?
//	We should be able to see "helloh" in the mystring object. Let's see
//	if we do or not:

//	CHECK CHAR BY CHAR
	for(i = 0; i <= 6; i++)
	{
		ch = mystring_get(hString, i);
		if(ch != test[i])
			check = 1;
	}

	if(check == 1)
	{
	//	FAIL
		printf("\tExpect string of 'helloh'; got ");
		for(i = 0; i <= 6; i++)
		{
			ch = mystring_get(hString, i);
			printf("%c", ch);
		}
		printf("\n");
		return 1;
	}
	
//	Try to push another character - this one should work as well
	code = mystring_push(hString, 'h');
	if(code == MYSTRING_STATUS_ERROR)
	{
		printf("\tFailed to push 'h' onto the mystring object! \n");
		return 1;
	}

//	Do another comparision
	check = 0;
	strcpy(test, "hellohh");
	
//	CHECK CHAR BY CHAR
	for(i = 0; i <= 6; i++)
	{
		ch = mystring_get(hString, i);
		if(ch != test[i])
			check = 1;
	}

	if(check == 1)
	{
	//	FAIL
		printf("\tExpect string of 'hellohh'; got ");
		for(i = 0; i <= 6; i++)
		{
			ch = mystring_get(hString, i);
			printf("%c", ch);
		}
		printf("\n");
		return 1;
	}
	
// 	Destroy the my_string object
    mystring_destroy(&hString);
	
//	SUCCESS
	return 0;
}


static int test_mystring_pop(void)
{
	MYSTRING hString;
	int i;
	char ch;
	
//	First initialize a mystring object
	hString = mystring_init_c_string("hello");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tMYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Test the pop function - multiple times
	ch = mystring_pop(hString);
	
	// Check for failure
	if(ch != 'o')
	{
		printf("\tFailed to pop 'o'!\n");
		return 1;
	}
	
//	From "hello" we now should have "hell" - try pop 4 characters.
	for(i = 0; i < 4; i++)
		ch = mystring_pop(hString);

//	Check for the last character, "h"
	if(ch != 'h')
	{
		printf("\tFailed to pop 'h'!\n");
		return 1;
	}
	
//	One last test - try to pop from an empty string
	ch = mystring_pop(hString);
	
//	Check and see if we got NULL or not
	if(ch != '\0')
	{
		printf("\tPopped %c from an empty mystring! \n", ch);
		return 1;
	}
	
// 	Destroy the my_string object
    	mystring_destroy(&hString);
	
//	SUCCESS!
	return 0;
}


static int test_mystring_peek(void)
{
	MYSTRING hString;
	char ch;
	
//	First initialize a mystring object
	hString = mystring_init_c_string("hello");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tERROR: MYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Test the peek function
	ch = mystring_peek(hString);
	
	if(ch != 'o')
	{
		printf("\tERROR: Peeked %c and not 'o' from the mystring object! \n", ch);
		return 1;
	}
	
// 	Destroy the my_string object
    mystring_destroy(&hString);
    	
//	Now make a new one, but make it default and try to peek at an empty mystring object
	hString = mystring_init_default();
	
//	Try to peek at an empty MYSTRING
	ch = mystring_peek(hString);
	
	if(ch != '\0')
	{
		printf("\tERROR: Peeked %c from an empty mystring object!\n", ch);
		return 1;
	}

// 	Destroy the my_string object
    mystring_destroy(&hString);
    
//	SUCCESS!
	return 0;
}


static int test_mystring_get(void)
{
	MYSTRING hString;
	char ch;
	
//	First initialize a mystring object
	hString = mystring_init_c_string("hello\n");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tERROR: MYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Check the mystring_get function
	ch = mystring_get(hString, -1);		//INVALID INDEX CHECK
	
	if(ch != '\0')
	{
		printf("\tERROR: got a char from invalid index of -1!\n");
		return 1; 
	}
	
	ch = mystring_get(hString, 0);	//VALID CHECK - should be "h"
	
	if(ch != 'h')
	{
		printf("\tERROR: got %c and not 'h'!\n", ch);
		return 1; 
	}
	
	ch = mystring_get(hString, 5);	//VALID - should be '\n'
	if(ch != '\n')
	{
		printf("\tERROR: got %c and not '\\n'!\n", ch);
		return 1; 
	}
	
	ch = mystring_get(hString, 6);	//INVALID - shouldn't exist/shouldn't let us access it
	if(ch != '\0')
	{
		printf("\tERROR: got a char from invalid index of 6!\n");
		return 1; 
	}

// 	Destroy the my_string object
    mystring_destroy(&hString);
    
//	SUCCESS!
	return 0;
}


static int test_mystring_put(void)
{
	MYSTRING hString;
	MyString_Status Code;
	
//	First initialize a mystring object
	hString = mystring_init_c_string("hello\n");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tERROR: MYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Check the put function 4 times, for both valid & invalid indexes

	Code = mystring_put(hString, -1, 'h');	//INVALID
	if(Code == MYSTRING_STATUS_SUCCESS)
	{
		printf("\ERROR: put something in an invalid index of -1!\n");
		return 1;
	}

	Code = mystring_put(hString, 1, 'h');	//VALID
	if(Code == MYSTRING_STATUS_ERROR)
	{
		printf("\tERROR: failed to put something in a valid index of 1!\n");
		return 1;
	}
	
	Code = mystring_put(hString, 5, 'h');	//VALID
	if(Code == MYSTRING_STATUS_ERROR)
	{
		printf("\tERROR: failed to put something in a valid index of 5!\n");
		return 1;
	}
	
	Code = mystring_put(hString, 6, 'h');	//INVALID
	if(Code == MYSTRING_STATUS_SUCCESS)
	{
		printf("\ERROR: put something in an invalid index of 6!\n");
		return 1;
	}
	
// 	Destroy the my_string object
    mystring_destroy(&hString);
    
//	SUCCESS!
	return 0;
}


static int test_mystring_init_substring(void)
{
	MYSTRING hStart;
	MYSTRING hEnd;
	
//	First initialize a mystring object
	hStart = mystring_init_c_string("hello\n");

// 	Make sure it initialized
	if(hStart == NULL)
	{
		printf("\tERROR: MYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Now, send hStart to init_substring to make a new MYSTRING. store it in hEnd
	hEnd = mystring_init_substring(hStart, 0, 5); 	// Testing whole MYSTRING
	
//	See if hEnd exists or not.
	if(hEnd == NULL)
	{
		printf("\tERROR: failed to initialize a MYSTRING object from another MYSTRING!\n");
		return 1;
	}
	
//	Destroy the two MYSTRING objects!
	mystring_destroy(&hStart);
	mystring_destroy(&hEnd);
	
//	Otherwise, SUCCESS!
	return 0;
}


static int test_mystring_to_c_string(void)
{
	MYSTRING hString;
	char test_arr[6];
	char *temp;
	
//	First initialize a mystring object
	hString = mystring_init_c_string("hello\n");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tERROR: MYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Now test the mystring_to_c_string function
	temp = (char*) mystring_to_c_string(hString, test_arr, 6);
	
//	See if we got anything from mystring_to_c_string
	if(temp == NULL)
	{
		printf("\tERROR: failed to convert mystring to c_string!\n");
		return 1;
	}
	
//	Now move temp to test_arr	
	memcpy(test_arr, temp, 6);
	
//	Compare what we sent to the function to what we got from the function
	if(strncmp("hello\n", test_arr, 5) != 0)
	{
		printf("\tERROR: Expected \"hello\", got %s\n", test_arr);
		return 1;
	}
	
//	Destroy the MYSTRING object
	mystring_destroy(&hString);
	
//	If we get here - SUCCESS!	
	return 0;
}


static int test_mystring_input(void)
{
	MYSTRING 			hString;
	FILE* 				hFile;
	char 				test_arr[10];
	int 				i;
	MyString_Status 	Code;
	int (* fTerminate)(char, int*);
	
//	First initialize a mystring object
	hString = mystring_init_c_string("     ");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tERROR: MYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Open the file
	hFile = fopen("test2.txt", "w");
	
//	Put some random stuff in the file. (0-4 in this case)
	fprintf(hFile, "   11111");
	
//	Close the file
	fclose(hFile);
	
//	Reopen the file in "read" mode!!!
	hFile = fopen("test2.txt", "r");
	
//	Send the MYSTRING to mystring_input several times

	fTerminate = acceptNonWhite;	//	Function Pointer

	Code = mystring_input(hString, hFile, 1, fTerminate);
	
	if(Code == MYSTRING_STATUS_ERROR)
	{
		printf("\tERROR: Expected SUCCESS - got ERROR!\n");
		return 1;
	}
	
//	See if we got back just "01234"
	for(i = 0; i < 5; i++)	
		test_arr[i] = mystring_get(hString, i);
	
	if(strncmp(test_arr, "11111", 5) != 0)
	{
	//	FAIL!	
		printf("\tERROR: Expected \"11111\" - got %s\n", test_arr);
		return 1;
	}
	
//	Close the file (for the final time)
	fclose(hFile);
	
//	Destroy the MYSTRING object
	mystring_destroy(&hString);
	
//	OTHER WISE - SUCCESS!
	return 0;
}

static int test_mystring_input_lineinput(void)
{
	MYSTRING 			hString;
	FILE* 				hFile;
	char 				test_arr[35];
	int 				i;
	MyString_Status 	Code;
	int (* fTerminate)(char, int*);
	
	//	First initialize a mystring object
	hString = mystring_init_c_string("     ");

// 	Make sure it initialized
	if(hString == NULL)
	{
		printf("\tERROR: MYSTRING object failed to initialize! \n");
		return 1;
	}
	
//	Open the file
	hFile = fopen("test2.txt", "w");
	
//	Put a line of text into the file, terminated by a newline
	fprintf(hFile, "   Hello, world. How are you today?\n");
	
//	Close the file
	fclose(hFile);
	
//	Reopen the file in "read" mode!!!
	hFile = fopen("test2.txt", "r");
	
//	Send the MYSTRING to mystring_input several times

	fTerminate = acceptLineInput;	//	Function Pointer

	Code = mystring_input(hString, hFile, 1, fTerminate);
	
	if(Code == MYSTRING_STATUS_ERROR)
	{
		printf("\tERROR: Expected SUCCESS - got ERROR!\n");
		return 1;
	}
	
//	See what we got back from the function
	for(i = 0; i < 32; i++)	
		test_arr[i] = mystring_get(hString, i);
	
	// DEBUGGING PURPOSES:
	/*
	printf("\tInput to the file was: \n");
	printf("\t   Hello, world. How are you today?\n");
	printf("\tGot back: \n");
	printf("\t%s\n", test_arr);	*/
	
	if(strncmp(test_arr, "Hello, world. How are you today?", 32) != 0)
	{
	//	FAIL!	
		printf("\tERROR: Line was:\n");
		printf("Hello, world. How are you today? - got:\n");
		printf("%s\n", test_arr);
		return 1;
	}
	
//	Close the file (for the final time)
	fclose(hFile);
	
//	Destroy the MYSTRING object
	mystring_destroy(&hString);
	
//	OTHER WISE - SUCCESS!
	return 0;
}

int acceptNonWhite(char ch, int *pbDiscardChar)
{
//	Check to see if we have a white space character or not
	if(isspace(ch))
	{
	//	We do, so discard it
		*pbDiscardChar = TRUE;

	//	And signal to terminate input.
		return TRUE;
	}
	
//	If it isn't whitespace, don't discard the character.
	*pbDiscardChar = FALSE;

//	Also, do not terminate input!
	return FALSE;
}                        

int acceptOddDigits(char ch, int * pbDiscardChar)
{
// 	If we have a digit:
	if (isdigit(ch))
	{
	//	Convert the character to decimal
		ch -= '0';
	
	//	Discard the character if its even.
		*pbDiscardChar = (ch % 2 == 0);
		
	//	Don't terminate yet.
		return FALSE;
	}

//	If it isn't a digit, discard the character!
	*pbDiscardChar = TRUE;

//	And terminate input!
	return TRUE;
} 

int acceptLineInput(char ch, int * pbDiscardChar)
{
//	See if we have a newline
	if(ch == '\n')
	{
	//	Yes, we do. Discard the character
		*pbDiscardChar = TRUE;

	//	Also, terminate input.
		return TRUE;	
	}

//	If we don't have a newline:
//	 don't discard & don't terminate input.
	*pbDiscardChar = FALSE;
	return FALSE;
}
