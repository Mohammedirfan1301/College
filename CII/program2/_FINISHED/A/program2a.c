/**********************************************************************
Program: Program2A
Author: Jason Downing
Date: 2/13/2014
Time spent: 3 Hours
Purpose: This program uses the my_vector object type to store integers.
	 First the program opens a text document containing several numbers.
	 Next the program reads these numbers into a my_vector object
	 Finally, the program writes the numbers in reverse order to
	 another text document. It then closes all files and deletes
	 the my_vector object.
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "my_vector.h"

void open_files(FILE** numbers, FILE** reverse);
void work_files(MY_VECTOR hNumbers, FILE* numbers, FILE* reverse);
void close_files(FILE* numbers, FILE* reverse);

int main(int argc, char* argv[])
{
	MY_VECTOR hNumbers;	//MY_VECTOR header - points to my_vector object
	FILE* numbers;	//File pointer to numbers.txt
	FILE* reverse;	//File pointer to reverse.txt

	//Create an inital my_vector object
	hNumbers = my_vector_init_default();	
	
	//Open the files
	open_files(&numbers, &reverse);

	//Work on the files
	work_files(hNumbers, numbers, reverse);	

	//Close the files.
	close_files(numbers, reverse);	
	
	//Destroy the vector
	my_vector_destroy(&hNumbers);

	return 0;
}

/* Pre-Condition: The files are not opened
  Post-Condition: The files are opened and in the correct mode for reading/writing */
void open_files(FILE** numbers, FILE** reverse)
{
	//Open the numbers.txt file in READ mode
	*numbers = fopen("numbers.txt", "r");
	
	//Check the and see if the file opened correctly. NULL means it didn't.
	if(*numbers == NULL) 
	{	
		//If NULL return an error for the user to see.
		fprintf(stderr, "The File: numbers.txt failed to open correctly. \n");
		exit(1);	
	}

	//Open the reverse.txt file in WRITE mode
	*reverse = fopen("reverse.txt", "w");
	
	//Check the and see if the file opened correctly. NULL means it didn't.
	if(*numbers == NULL)
	{	
		//If NULL return an error for the user to see.
		fprintf(stderr, "The File: reverse.txt failed to open correctly. \n");
		exit(1);	
	}
}

/* Pre-Condition: The files are open, but have not been used yet for reading/writing of numbers
  Post-Condition: The files have been worked on - numbers reader from numbers.txt are now
                  in reversed order in reverse.txt */
void work_files(MY_VECTOR hNumbers, FILE* numbers, FILE* reverse)
{
	int i, num, err, size;

	//Test the list first
	err = fscanf(numbers, "%d", &num);	//Err = return value of fscanf

	//If err is 1, we have numbers in the list. If it isn't 1, something failed.
	if(err == 1)
	{
		//Get one number at a time from numbers.txt
		do{	
			if(my_vector_push_back(hNumbers, num) == FAILURE)
			{
				//Failed to add to the vector!
				printf("Error! Couldn't add numbers to the vector!\n");
				exit(1);
			}

			//Get a number from numbers.txt
			err = fscanf(numbers, "%d", &num);
		}while(err == 1);	//Run while there's numbers to get!
	}
	else{	//The list is empty if the first value of err isn't 1.
		printf("List empty!\n");
	}	
	
	//Now we can reverse the numbers and output them to the reverse.txt file
	size = my_vector_size(hNumbers);	//Vector's size, for the loop
	
	//Using the "safe" way of getting numbers from the vector.
	for(i = size - 1; i >= 0; i--) //Reverse order works like this:
	{	//start at the back (1 less than size) and work forward to 0.
		num = *(my_vector_at(hNumbers, i));	//Get a num (using * to make it an int)
		fprintf(reverse, "%d\n", num);		//Store it in reverse.txt
	}
}

/* Pre-Condition: The files are open
  Post-Condition: The files are closed */
void close_files(FILE* numbers, FILE* reverse)
{
	//Close the files
	fclose(numbers);
	fclose(reverse);
}
