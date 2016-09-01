#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mystring.h"
#include "generic_vector.h"
#include "assocarray.h"
#include "status.h"

void Intro(void);						//"HANGMAN" ASCII Art

// Primary driver for each round of hangman
void EvilHangman(int word_size, int guesses, int display_words);

// Tests each guess and returns either 1, 0 or -1, depending on whether the guess
// was right or wrong or whether the word has been completely guessed.
int CheckGuess(	int word_size, char letter, MY_SET* oldSet, MY_SET* newSet,
				GENERIC_VECTOR* word_list, MYSTRING* guessed_string);

// Used another function to make the EvilHangman function easier to read.
void Print_Information(	int guesses_remaining, int guesses, int words_remaining, int display_words,
						MYSTRING guessed_letters, MYSTRING guessed_string, char letter);

// For some reason, there are warnings about "implicit declaration" of these functions?
GENERIC_VECTOR vector_of_vector_dictionary(void);
GENERIC_VECTOR vector_of_mystring_at(GENERIC_VECTOR hVectofVect, int index);
GENERIC_VECTOR 	max_vector_node(MY_SET hMY_SET, MYSTRING* key);


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
	MY_SET  oldSet = NULL;						// MY_SET handle
	MY_SET  newSet = NULL;
	MYSTRING guessed_string = NULL;
	MYSTRING guessed_letters = NULL;
	MYSTRING* ptr = NULL;
	MyString_Status test = MYSTRING_STATUS_ERROR;
	char letter = 'z';
	int i, x, words_remaining = 0, repeat = 0, won = 0;

/*	**************************************************************************************
	Initialize values and objects before playing a round of hangman.
	*************************************************************************************/
	
	guessed_string = mystring_init_default();		
	
	if(guessed_string == NULL)
	{
		printf("ERROR: failed to initialize guessed_string!\n");
		exit(1);
	}
	
	// guessed_string will contain the "word". At the start, it is only dashes.
	for(i = 0; i < word_size; i++)
	{
		// Push a dash to the back of the MYSTRING
		test = mystring_push(guessed_string, '-');
		
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
		printf("ERROR: failed to initialize guessed_string!\n");
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
							guessed_letters, guessed_string, letter);
	
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
					printf("\nSORRY - you already guessed the letter %c!\n\n", letter);
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
		
		/* 	Here is where the Evil Hangman game comes into play...
			We shall summon another function to determine what to do next.	*/
		won = CheckGuess(word_size, letter, &oldSet, &newSet, &hVectofMystring, &guessed_string);
		
		// If this was the first guess, we have some cleaning to do
		if(i == guesses)
		{
			//my_set_destroy(&oldSet);
			
		}
		
		// Update the word size count!
		words_remaining = generic_vector_size(hVectofMystring);
		
		// Guess was wrong
		if(won == -1)
		{
			printf("SORRY, there wasn't any %c's in the word! :[\n", letter);
		}
		
		// Guess was right
		if(won == 0)
		{
			printf("Yes, there was some %c's in the word! :]\n", letter);
			
			// Make sure to increase the guess count by 1! Do this by increasing i.
			i++;
		}
		
		// If the user won the game, break out of this loop.
		if(won == 1)
		{
			break;
		}
	}
	
	
/*	**************************************************************************************
	THE GAME IS OVER. DESTROY anything that was allocated! PREVENT MEMORY LEAKS!!
	*************************************************************************************/

	// If they won the game of hangman, great for them! :)
	if(won == 1)
	{
		printf("\n\n===== YOU WON!!! =====\n");
		printf("CONGRATZ! THE CORRECT WORD WAS: ");
		mystring_output(guessed_string, stdout);		
	}
	// If they lost, then tell them to try again! >:)
	else
	{
		printf("\n\n===== GAME OVER. =====\n");
		printf("YOU LOST. THE CORRECT WORD WAS: ");
		
		// Pick a random word off the generic_vector
		// (I didn't bother seeding it since there is such a large word list.)
		i = 0;
		i = rand() % (generic_vector_size(hVectofMystring) - 1);
		ptr = (MYSTRING*)generic_vector_at(hVectofMystring, i);
		
		if(ptr == NULL)
		{
			printf("Error: failed to grab the word to print out!\n");
			return;
		}
		
		// Print out the given mystring
		mystring_output(*ptr, stdout);
	}
	
	
	my_set_destroy(&oldSet);
	//my_set_destroy(&newSet);
	mystring_destroy(&guessed_letters);
	generic_vector_destroy(&hVectofVect);
	// Returns to MAIN at this point.
}

/*	
	This function is used for checking each letter that is guessed by the user.
	Everytime it determines what the largest word list is, by using the associative array.
	If the blank string is still the largest word list, it returns 0 to indicate the game
	should continue. It also takes the address of the word list and the guess string and
	changes those as needed. It returns 1 to indicate that the game has been won - that is,
	there is 1 possible word remaining and the guessed_string is currently equal to that word.		
*/
int CheckGuess(int word_size, char letter, MY_SET* oldSet, MY_SET* newSet, 
               GENERIC_VECTOR* word_list, MYSTRING* guessed_string)
{
	MYSTRING* temp = NULL;
	MYSTRING  hold = NULL;
	MYSTRING  word = NULL;
	MYSTRING   key = NULL;
	MyString_Status code;
	int i, x, dash = 0;
	
	// First make a "new" associative array!
	*newSet = my_set_init_default();
	
	// See if hSet initialized.
	if(newSet == FALSE)
	{
		printf("Something failed! OH N0!\n");
		return 0;
	}
	
	// Go through the word list, picking out words and sorting them based on their key.
	for(i = 0; i < generic_vector_size(*word_list); i++)
	{
		key = mystring_init_default();
		
		// Make key start with just dashes.
		for(x = 0; x < word_size; x++)
		{
			// If the guessed_string has a dash, push that to the key
			if('-' == mystring_get(*guessed_string, x))
			{
				// Push a dash to the back of the MYSTRING
				code = mystring_push(key, '-');
		
				// Make sure it pushed the dash back.
				if(code == MYSTRING_STATUS_ERROR)
				{
					printf("ERROR: failed to push '-' back to the MYSTRING object!\n");
					exit(1);
				}
			}
			// Otherwise push whatever is in the guessed string to the key
			else
			{
				// Push a w/e is in guessed_string to the back of the MYSTRING
				code = mystring_push(key, (mystring_get(*guessed_string, x)));
		
				// Make sure it pushed the dash back.
				if(code == MYSTRING_STATUS_ERROR)
				{
					printf("ERROR: failed to push %c back to the MYSTRING object!\n",
					 			mystring_get(*guessed_string, x));
					exit(1);
				}
			}
		}
		
		// Now get a MYSTRING from the generic_vector
		temp = (MYSTRING*)generic_vector_at(*word_list, i);
		
		if(temp == NULL)
		{
			printf("SOMETHING BAD HAPPENED!\n");
			exit(1);
		}
		
		hold = (MYSTRING) *temp;
		
		// Make a copy of this MYSTRING object for later use!
		word = mystring_init_substring(hold, 0, mystring_size(hold));
		
		/* 	Look at the word, looking for the given letter. If we find a match, change
			the key. If we find no matches, then it is just a blank key. Which is fine. */
		
		for(x = 0; x < word_size; x++)
		{
			// If this spot in the word contains the given letter
			if(mystring_get(word, x) == letter)
			{
				// Then change the key at this spot
				code = mystring_put(key, x, letter);
				
				if(code == MYSTRING_STATUS_ERROR)
				{
					printf("ERROR: failed to put %c into key!\n", letter);
					exit(1);
				}
				
				/*	If it wasn't equal to the letter, we don't do anything. 
					Just keep searching...		*/
			}
		}
		
		/*	Once we've gotten a word from the generic_vector and generated a key for it,
			we are now able to add it to the associative array!		*/
		my_set_add(*newSet, key, word);
		
		/* 	Once we have pushed the key & the word to the associative array, we
			can destroy this round's current key!	*/
		mystring_destroy(&key);
	}
	
	//  Key is being reused here, so let's initialize it.
	key = NULL;
	
	/*	All this work was so that we could generated an associative array, and thus use
		the array to do our dirty work. Now we can simply call a function from 
		assocarray.c that will return the generic_vector that is the largest, thus
		giving us the most options for stumping the user!		*/
	
	// We always grab the largest generic_vector from the tree however.
	*word_list = max_vector_node(*newSet, &key);
	
	// NOTE: 	word_list is now a location in the tree! When we want to destroy 
	//			it, we simply destroy the tree!
	
	// If this is the first guess, destroy guessed_string! and update it to the key!
	if(oldSet == NULL)
	{
		mystring_destroy(guessed_string);
		*guessed_string = key;
	}
	// If it isn't the first guess, then the key is a location in the oldSet. Which
	// we will destroy at the end of the game. So no need to worry about this MYSTRING.
	else{
		*guessed_string = key;
	}
	
	// Now the memory management part. Let's see if we have an oldSet to destroy or not.
	if(oldSet == NULL)	// First time the user has guessed, so no.
	{
		*oldSet = *newSet;	// Let's save the location of the current associative array.
							// Which ATM is the ONLY associative array.
	}
	else 					// There's an old associative array to destroy.
	{
		// Since we made copies of the MYSTRING objects and thus created brand new
		// generic_vectors in the process, we can savely destroy the old array
		// and just save the location of the current array.
		my_set_destroy(oldSet);		// Delete the old array
		*oldSet = *newSet;			// Save the current array for the next round.
	}
	
	// 	We would now want to check and see if guessed_string contains all dashes or not.
	// 	If it has NO dashes - return 1, the user won! 
	//	Other wise return either 1 or 0.
	
	dash = 0;
	
	// First see if the letter they guessed was in the word.
	// If it was, return 0. Increase guesses count by 1.
	for(x = 0; x < word_size; x++)
	{
		if(mystring_get(*guessed_string, x) == letter)
		{
			// Hey, the letter they guessed was in the word!
			
			// Wait just a second. Has the entire word been guessed? 
			// Let's double check that, shall we?

			for(x = 0; x < word_size; x++)
			{
				if(mystring_get(*guessed_string, x) == '-')
				{
					// Looks like we found a dash. Make the dash detector equal to 1.
					dash = 1;
				}
			}
	
			// Check and see if dash equals 0 (no dashes in the guessed_string) or
			// 1 (there are dashes in the guessed_string)
			if(dash == 0)
			{
				// THE USER WON IF THEY GOT HERE!
				return 1;
			}
			
			// If we get here, it was just another letter shown.
			return 0;
		}
	}
	
	// Also, check and see if the ENTIRE guessed_string contains no dashes
	// If it has NONE, then they win!
	for(x = 0; x < word_size; x++)
	{
		if(mystring_get(*guessed_string, x) == '-')
		{
			// Looks like we found a dash. Make the dash detector equal to 1.
			dash = 1;
		}
	}
	
	// Check and see if dash equals 0 (no dashes in the guessed_string) or
	// 1 (there are dashes in the guessed_string)
	if(dash == 0)
	{
		// THE USER WON IF THEY GOT HERE!
		return 1;
	}
	
	// If we get here, their letter was not in the word & 
	// they did not guess the word completely.
	return -1;
}


void Print_Information(	int guesses_remaining, int guesses, int words_remaining, int display_words,
						MYSTRING guessed_letters, MYSTRING guessed_string, char letter)
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
			printf("- ");
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
	test = mystring_output(guessed_string, stdout);
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
	printf(" |                               V1.3                                       \n");
    printf(" ======================================================================     \n");
    
    printf("Welcome to the HANGMAN game!\n\n");
}

