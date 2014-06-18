#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mystring.h"
#include "generic_vector.h"
#include "status.h"

void Intro(void);						//"HANGMAN" ASCII Art
void EvilHangman(int word_size, int guesses, int display_words);

/***********************************************************************
To do:

CHECK TAB WIDTH??

MYSTRING	 		- implemented
Generic_vector 	- have
Dictionary.c 		- implemented
Associative Array 	- NEED TO DO THIS
Hangman Drier		- This file, which is in progress.
************************************************************************/

int main(int argc, char* argv[])
{
	int x = 1, word_size = 0, guesses = 0, display_words = 0;
	
	while(x == 1)
	{
		Intro();

		printf("What size word would you like to play with? (Numbers 2 - 29)\n");
		
		/* 	Only let the user enter numbers between 2 and 29, 
			as those are the lengths of words stored in the dictionary file.	*/
		do{
			printf("Enter a word size here: ");
			scanf("%d", &word_size);
			
			// If they fail to follow directions, warn them of their mistake.
			if(word_size > 30 || word_size < 2)	
				printf("\nSorry! That's not a valid word size to use! :(\n\n");
		}while(word_size > 30 || word_size < 2);
		
		printf("\nHow many guesses would you like? (Numbers greater than 0)\n");
		
		/*	Only let the user enter a valid number of guesses.
			In our case, this is any integer greater than zero.	*/
		do{
			printf("Enter a number of guesses here: ");
			scanf("%d", &guesses);
		
			// If the user fails to follow directions, warn them that they made a mistake.
			if(guesses <= 0)
				printf("\nSorry! That's not a valid number of guesses! :(\n\n");
		}while(guesses <= 0);
		
		/*	Ask the user if they want a running number of the remaining words in 
			the associative array. Make sure they only enter 1 or 2.		*/
		printf("\nWould you like the number of remaining words to be displayed?\n");
		
		do{
			printf("Enter 1 for YES or 2 for NO: ");
			scanf("%d%*c", &display_words);  			// %*c eats newlines!
		
			if(display_words > 2 || display_words < 1)
				printf("\nSorry! Please enter a number ONE for YES or TWO for NO.\n");
		}while(display_words > 2 || display_words < 1);
	
		/*	Start playing a game of hangman at this point!	*/
		EvilHangman(word_size, guesses, display_words);
	
		// Ask the user if they want to keep playing the game after they've finished.
		printf("\nWould you like to play again?\n");
		printf("Press 1 to continue or 2 to quit: ");
		scanf("%d", &x);
	}
	
	return 0;
}

/*	This will be the man portion of the program. It will run a game of EVILHANGMAN	*/
void EvilHangman(int word_size, int guesses, int display_words)
{
	MYSTRING guess_string;
	MYSTRING guessed_letters;
	MyString_Status test;
	char letter;
	int i;
	
	
	// Initialize the guess_string object
	guess_string = mystring_init_default();
	
	if(guess_string == NULL)
	{
		printf("ERROR: failed to initialize guess_string!\n");
		exit(1);
	}
	
	// guess_string will contain the "word". At the start, it is only dashes.
	for(i = 0; i < word_size; i++)
	{
		// Push a dash to the back of the MYSTRING
		test = mystring_push(guess_string, '-');
		
		// Make sure it pushed the dash back.
		if(test == MYSTRING_STATUS_ERROR)
		{
			printf("ERROR: failed to push '-' back to the MYSTRING object!\n");
			exit(1);
		}
	}
	
	// Initialize guessed_letters object
	guessed_letters = mystring_init_default();
	
	if(guessed_letters == NULL)
	{
		printf("ERROR: failed to initialize guess_string!\n");
		exit(1);
	}


/************************************************************************
	How to implement EVIL HANGMAN
	
	1. Select VECTOR OF MYSTRINGS of size word_size
	2. printout:
		- remaining guesses
		- letters play has guessed
		- current blanked version of the word
		- (If choosen to) print out number of words remaining
	3. Prompt for a guess. Make sure:
		- it hasn't been guessed before.
		- It is a letter A to Z
		- ONE char long
	4. Use associative array to find the most possible words to choose from.
	5. When the player:
		A.  Runs out of guesses, pick any word in the array and say that was the word
			they were trying to guess.
		B.	Correctly guesses the word, then congratulate them!
	6. Return to main, and ask to play again or quit.
************************************************************************/
	for(i = guesses; i > 0; i--)
	{
		printf("\n\nNumber of guesses remaining: %d\n", i);
		
		printf("Guessed letters: ");
		test = mystring_output(guessed_letters, stdout);
		printf("\n");
		
		// check mystring_output for failure.
		if(test == MYSTRING_STATUS_ERROR)
		{
			printf("ERROR: failed to push '-' back to the MYSTRING object!\n");
			exit(1);
		}
		
		printf("Guessed word: ");
		test = mystring_output(guess_string, stdout);
		printf("\n");
		
		// check mystring_output for failure.
		if(test == MYSTRING_STATUS_ERROR)
		{
			printf("ERROR: failed to push '-' back to the MYSTRING object!\n");
			exit(1);
		}
		
		if(display_words == 1)
		{
			printf("Number of words remaining: ?");
			// Do something to get remaining words?
			printf("\n\n\n");
		}
		
		// Now we are ready to take character input from the user! :)
		printf("Please enter a character to guess. NOTES:\n");
		printf("Characters MUST be letters between A and Z on the\n");
		printf("alphabet. Capital letters are allowed and converted to\n");
		printf("lower case.\n");
		
		// MAKE SURE IT IS A LETTER!
		do{
			printf("Please enter a character: ");
			scanf("%c", &letter);
			
			// If the user fails to follow directions, warn them.
			if(!isalpha(letter))
			{
				printf("\nSORRY - that wasn't a letter!\n\n");
			}
		}while(isalpha(letter));
	}
	
	// Now return to MAIN
	return;
}



void Intro(void)						
{			/******************************(EVIL)****************************************/
	printf(" ------------------------------------------------------------------------   \n");
    	printf(" |  *    *     ***     *   *   *******   *       *     ***     *   *    |   \n");
    	printf(" |  *    *    *   *    **  *   #         **     **    *   *    **  *    O   \n");
  	printf(" |  ******   *******   * * *   #  ****   * *   * *   *******   * * *   \\|/ \n");
	printf(" |  *    *   *     *   *  **   #     *   *  * *  *   *     *   *  **   / \\ \n");
	printf(" |  *    *   *     *   *   *   *******   *   *   *   *     *   *   *        \n");
	printf(" |                               V1.0                                       \n");
    	printf(" ======================================================================     \n");
    
    printf("Welcome to the HANGMAN game!\n");
}

