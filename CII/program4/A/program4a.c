/************************************************************************
Program: Program 4A
Author: Jason Downing
Date: 3/29/2014
Time spent: 2 Hours for Program4A + ? hours for mystring.c (a ton)
Purpose: This program uses my MYSTRING implementation to determine if 
		 strings inputed by the user are palindromes or not.
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mystring.h"

//	I use TRUE / FALSE in a few functions to represent "0" and "1"
#define TRUE 1
#define FALSE 0

int acceptLineInput(char ch, int * pbDiscardChar);
int is_palindrome(MYSTRING hString);

int main(int argc, char* argv[])
{
	MYSTRING hString;
	MyString_Status Code;
	int (* fTerminate)(char, int*);
	int i;
	
	do{
		hString = mystring_init_default();
		fTerminate = acceptLineInput;
		Code = mystring_input(hString, stdin, 0, fTerminate);
	
		if(Code == MYSTRING_STATUS_SUCCESS)
		{
		//	We successfully got input from the user. 
		//	Send input to the palindrome function.
			i = is_palindrome(hString);			
					
		//	Print Yes or No, depending on what is_palindrome returns (1 - yes, 0 - no)	
			if(i == TRUE)
				printf("Yes\n");
			if(i == FALSE)
				printf("No\n");
		}
		else if(Code == MYSTRING_STATUS_ERROR)
		{
		//	Something failed. Exit the program after freeing hString.
			mystring_destroy(&hString);
			return 0;
		}
	
	//	Destroy hString when we are done using it.
		mystring_destroy(&hString);
	}while(i != -1);

	return 0;
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

int is_palindrome(MYSTRING hString)
{
	MYSTRING hTemp;
	char c;
	int i, index;
	
//	Create a temporary MYSTRING object	
	hTemp = mystring_init_default();
	
//	Run through the whole MYSTRING we were given
	for(i = 0; i < mystring_size(hString); i++)
	{
	//	Get one character at a time
		c = mystring_get(hString, i);
		
	//	See if it is a character
		if(isalpha(c))
		{
		//	If it is, make it lowercase & store it in the temp MYSTRING
			c = tolower(c);
			mystring_push(hTemp, c);
		}
		
		if(c == EOF)
			return -1;
	}

//	At this point we have the whole string stored in hTemp with 
//	only characters present. We should be set now to see if it is a palindrome.
	
//	Use index to backtrack through the string, makes comparing easy.
	index = mystring_size(hTemp) - 1;
	
//	Run through the string, comparing front vs back up to the halfway point.
	for(i = 0; i < (mystring_size(hTemp) / 2); i++)
	{
	//	If the two characters are the same, keep searching
		if(mystring_get(hTemp, i) == mystring_get(hTemp, index))
		{
			index--;	// Decreasing the back index - i is the front index.
		}
		else	// If we fail the above test:
		{
		//	Prevent memory leaks by freeing hTemp
			mystring_destroy(&hTemp);
		
		//	And return FALSE as we didn't get a palindrome.
			return FALSE;
		}
	}
	
//	Destroy hTemp to prevent memory leaks.
	mystring_destroy(&hTemp);

//	If we get here, it was a success!
	return TRUE;
}





