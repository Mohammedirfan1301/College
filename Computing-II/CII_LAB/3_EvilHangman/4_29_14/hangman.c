#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mystring.h"
#include "generic_vector.h"
#include "status.h"

void Intro(void);						//"HANGMAN" ASCII Art
void EvilHangman(int word_size, int guesses, int display_words);

// Used another function to make the EvilHangman function easier to read.
void Print_Information(	int guesses_remaining, int guesses, int words_remaining, int display_words,
						MYSTRING guessed_letters, MYSTRING guess_string, char letter);

// For some reason, there are warnings about "implicit declaration" of these functions?
GENERIC_VECTOR vector_of_vector_dictionary(void);
GENERIC_VECTOR vector_of_mystring_at(GENERIC_VECTOR hVectofVect, int index);

/***********************************************************************
To do:

Associative Array 	- NEED TO DO THIS
Hangman Driver		- This file, which is in progress.
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
		printf("\n\nWould you like to play again?\n");
		printf("Press 1 to continue or 2 to quit: ");
		scanf("%d", &x);
	}
	
	return 0;
}


/*	This will be the man portion of the program. It will run a game of EVILHANGMAN	*/
void EvilHangman(int word_size, int guesses, int display_words)
{
	GENERIC_VECTOR 		hVectofVect = NULL;		// Vector of a vector handle
	GENERIC_VECTOR  hVectofMystring = NULL;		// Vector of Mystring handle
	MYSTRING guess_string;
	MYSTRING guessed_letters;
	MyString_Status test;
	char letter = 'z';
	int i, x, words_remaining = 0, repeat = 0, won = 0;

/*	**************************************************************************************
	Initialize values and objects before playing a round of hangman.
	*************************************************************************************/
	
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
	
	guessed_letters = mystring_init_default();
	
	if(guessed_letters == NULL)
	{
		printf("ERROR: failed to initialize guess_string!\n");
		exit(1);
	}

	hVectofVect = vector_of_vector_dictionary();
	
	// Make sure it initialized
	if(hVectofVect == NULL)
	{
		printf("ERROR: failed to initialize hVectofVect!\n");
		exit(1);
	}
	
	// Get the vector of mystring with the word size we want.
	hVectofMystring = vector_of_mystring_at(hVectofVect, word_size);	
	
	// Make sure it initialized
	if(hVectofMystring == NULL)
	{
		printf("ERROR: failed to initialize hVectofMystring!\n");
		exit(1);
	}
	
	// Get the size of this vector of mystring for debugging purposes.
	words_remaining = generic_vector_size(hVectofMystring);


/*	**************************************************************************************
	The main loop used in playing a game of Evil Hangman
	*************************************************************************************/
	for(i = guesses; i > 0; i--)
	{
		// Print out all the requested information
		Print_Information(	i, guesses, words_remaining, display_words, 
							guessed_letters, guess_string, letter);
	
		// Now we are ready to take character input from the user! :)
		printf("\n\nPlease enter a character to guess. NOTE:\n");
		printf("Characters MUST be letters between A and Z on the alphabet.\n");
		printf("Capital letters are allowed and converted to lower case.\n\n");
		
		repeat = 0;
		// MAKE SURE IT IS A LETTER!
		do{
			printf("Please enter a character: ");
			scanf(" %c", &letter);
			
			// Check to see if the letter entered is a letter of the alphabet
			if(!isalpha(letter))
			{
				printf("\nSORRY - that wasn't a letter!\n\n");
			}
			
			// Check to see if they have guessed the letter before.
			for(x = 0; x < mystring_size(guessed_letters); x++)
			{
				// If they have guessed the word before
				if(letter == mystring_get(guessed_letters, x))
				{
					repeat = 1;		// Promp them again!
					printf("\nSORRY - you already guessed that letter!\n\n");
					break;
				}
				else
				{
					repeat = 0;		// If they haven't - DO NOT prompt them a 2nd time!
				}
			}
		}while(!isalpha(letter) || repeat != 0);
		
		// Push the letter back to the guessed_letters MYSTRING
		test = mystring_push(guessed_letters, letter);
		
		// Make sure it pushed the dash back.
		if(test == MYSTRING_STATUS_ERROR)
		{
			printf("ERROR: failed to push %c back to the MYSTRING object!\n", letter);
			exit(1);
		}
		
		// Here is where the Evil Hangman game comes into play...
		
	}
	
	
/*	**************************************************************************************
	THE GAME IS OVER. DESTROY anything that was allocated! PREVENT MEMORY LEAKS!!
	*************************************************************************************/

	// If they won the game of hangman, great for them! :)
	if(won == 1)
	{
		printf("\n\n===== YOU WON!!! =====\n");
		printf("CONGRATZ! THE CORRECT WORD WAS: ");
		// the word they guessed correctly.
		printf("\nWHATEVER WORD YOU GUESSED");
	}
	// If they lost, then tell them to try again! >:)
	else
	{
		printf("\n\n===== GAME OVER. =====\n");
		printf("YOU LOST. THE CORRECT WORD WAS: ");
		// Any random word from the vector we've been using.
		printf("\nBLAH BLAH BLAH\n");
	}

	generic_vector_destroy(&hVectofVect);
	//generic_vector_destroy(&hVectofMystring);
	mystring_destroy(&guess_string);
	mystring_destroy(&guessed_letters);
	
	// Returns to MAIN at this point.
}


void Print_Information(	int guesses_remaining, int guesses, int words_remaining, int display_words,
						MYSTRING guessed_letters, MYSTRING guess_string, char letter)
{
	int x;	
	MyString_Status test = SUCCESS;
	
	printf("\n\nNumber of guesses remaining: %d\n", guesses_remaining);
	printf("Guessed letters: ");
	
	// Print out dashes if no letters have been guessed yet.
	if(mystring_size(guessed_letters) == 0)
	{
		for(x = 0; x < guesses; x++)
		{
			printf("-");
		}
	}
	// Print out the letters guessed
	else{
		for(x = 0; x < mystring_size(guessed_letters); x++)
		{
			letter = mystring_get(guessed_letters, x);
			printf("%c ", letter);	
		}
	}
	
	printf("\n");	// Make the output look nicer.
	
	// Check mystring_output for failure.
	if(test == MYSTRING_STATUS_ERROR)
	{
		printf("ERROR: failed to output guessed letters!\n");
		exit(1);
	}
	
	printf("Guessed    word: ");
	test = mystring_output(guess_string, stdout);
	printf("\n");
	
	// Check mystring_output for failure.
	if(test == MYSTRING_STATUS_ERROR)
	{
		printf("ERROR: failed to output guessed word!\n");
		exit(1);
	}
	
	// If requested, output how many words are remaining in the vector
	if(display_words == 1)
	{
		printf("Number of words remaining: %d\n", words_remaining);
	}
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

