/************************************************************************
Program: Program 4B
Author: Jason Downing
Date: 3/29/2014
Time spent: 1 Hours for Program4B + ? hours for mystring.c (a ton)
Purpose: This program uses my MYSTRING implementation to read a book
		 which is located in book.txt. It prints out all the 4 letter
		 words found in this book.
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mystring.h"

//	I use TRUE / FALSE in a few functions to represent "0" and "1"
#define TRUE 1
#define FALSE 0

int acceptNonWhite(char ch, int *pbDiscardChar);
void is_four_letter_word(MYSTRING hString);

int main(int argc, char* argv[])
{
	MYSTRING hString;
	FILE* Book;
	MyString_Status Code;
	int (* fTerminate)(char, int*);

//	Open the book file, in "read" mode.
	Book = fopen("book.txt", "r");
	
	do{
		hString = mystring_init_default();		// Init. hString
		fTerminate = &acceptNonWhite;			// Init. fTerminate
	
	//	Call the input function, making sure to ignore white space & terminate
	//	input on whitespace or EOF.
		Code = mystring_input(hString, Book, 1, fTerminate);
	
		if(Code == MYSTRING_STATUS_SUCCESS)
		{
		//	We successfully got input from the file.
		//	Determine if hString has a 4 letter word or not.
			is_four_letter_word(hString);
		}
		else if(Code == MYSTRING_STATUS_ERROR)
		{
		//	Something failed. Exit the program after freeing hString.
			fclose(Book);
			mystring_destroy(&hString);
			return 0;
		}
	
	//	Destroy hString when we are done using it.
		mystring_destroy(&hString);
	}while(Code == MYSTRING_STATUS_SUCCESS);

	return 0;
}

int acceptNonWhite(char ch, int *pbDiscardChar)
{
//	Check to see if we have a white space character or not
	if(isspace(ch) || ch == EOF)
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

void is_four_letter_word(MYSTRING hString)
{
	if(hString == NULL)
		return;

//	See what the size of the word we found is.
	if(mystring_size(hString) == 4)
	{
	// Output to stdout
		mystring_output(hString, stdout);
		printf("\n");
	}

//	If it wasn't a four letter word, do nothing - simply return to main
//	for further testing.
	return;
}
