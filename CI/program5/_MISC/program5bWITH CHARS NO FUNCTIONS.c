/*
	Author: Jason Downing
	Course: Computing I 91 101-203
	  Date: 11/26/2013
	  Description:  This program takes input from a text doc containing the names of various students along
					with their quiz scores. It then finds each students average quiz score and the program
					then writes all data to an output file, including names, quiz scores and a quiz average.
					After this is completed it copies all data back from the output file to the input file.

	MAJOR THING TO DO:
	- Need to throw everything in the output file into the input file.

*/
#include <stdio.h>
#include <stdlib.h>

void open_files(FILE** pquiz, FILE** paverage, int mode);	//Function to open the files
void close_files(FILE* quiz, FILE* average);	//Function to close the files
int work_files(FILE* quiz, FILE* average);		//Function to work with the files
void reverse_files(FILE* quiz, FILE* average);	//Function to put data in quiz from average

int main(int argc, int argv[])
{
	FILE *quiz, *average;	//File pointers
	int outcome = 0;

	printf("QUIZ AVERAGE PROGRAM. V1.0 \n");
	open_files(&quiz, &average, 1);			//Open the files in mode "1", or "R" for quiz and "W" for average
	outcome = work_files(quiz, average);	//Work on the files - find the averages, put all the data into the output file
	
	if(outcome == -1)
		printf("ERROR - INPUT FILE EMPTY! \n");

	close_files(quiz, average);					//Close the files "for now"
	//open_files(&quiz, &average, 2);			//Open the files in mode "2", or "W" for quiz and "R" for average
	//reverse_files(quiz, average);				//Reverse the files - ie make the quiz file contain all the data in the average file

	//Random note that everything was successful if the program managed to get to this point.
	if(outcome == 1)
		printf("Successfully completed the averaging of those quiz scores, sir! \n");

	return 0;
}



// Pre-Condition: The files are not opened
//Post-Condition: The files are opened and in the correct mode for reading/writing
void open_files(FILE** pquiz, FILE** paverage, int mode)
{	
	if(mode == 1)	//"R" / "W" mode
	{
		*pquiz = fopen("quiz.txt", "r");	//Open the first file in read mode.

		if(*pquiz == NULL)		//If the file didn't open right, exit with an error.
		{
			fprintf(stderr, "The File: quiz.txt failed to open correctly. \n");
			exit(1);	
		}


		*paverage = fopen("average.txt", "w");	//Open the output file in write mode.
												//If this file doesn't exist the program will simply write a file called
		if(*paverage == NULL)					//average.txt
		{						//If the file didn't open right, exit with an error.
			fprintf(stderr, "The File: average.txt failed to open correctly. \n");
			exit(1);	
		}
	}

	if(mode == 2)	//"W" / "R" mode
	{
		*pquiz = fopen("quiz.txt", "w");	//Open the quiz file in write mode.
		
		if(*pquiz == NULL)			//If the file didn't open right, exit with an error.
		{
			fprintf(stderr, "The File: quiz.txt failed to open correctly. \n");
			exit(1);	
		}

		*paverage = fopen("average.txt", "r");	//Open the average file in read mode.

		if(*paverage == NULL)		//If the file didn't open right, exit with an error.		
		{									
			fprintf(stderr, "The File: average.txt failed to open correctly. \n");
			exit(1);	
		}
	}

}


// Pre-Condition: The files are open
//Post-Condition: The files are closed
void close_files(FILE* quiz, FILE* average)	//Function to close the files
{
	//Close the files
	fclose(quiz);
	fclose(average);
}


// Pre-Condition: The average file is empty
//Post-Condition: The average file is the same as the quiz file, with averages for each of the set of quizzes.
int work_files(FILE* quiz, FILE* average)
{
	int name;							//Various variables needed
	int num = 0, sum = 0, avg = 0;
	int count = 0, buffer = 0;
	int not_empty = 0;
	int check_EOF = 0;
	
	//Check to see if the input file contains anything
	not_empty = fgetc(quiz);	//Test the first line
	ungetc(not_empty, quiz);	//Undo the file position

	if(not_empty == EOF)		//IF we get an EOF right off the bat, the files empty
	{
		return -1;	//Return -1 for error: INPUT FILE EMPTY
	}

	//Print out column headers
	fprintf(average, "    Student Name     |              Quiz Scores                | Average Quiz Score \n");

	do{
		sum = 0, num = 0, count = 0;	//Reset variables
		
		//Get the first/last names (only have many characters long they are)	
		do{
			name = fgetc(quiz);			
			count++;				//Increase character count by one each time.
		}while(name != 32);

		do{
			name = fgetc(quiz);			
			count++;				//Increase character count by one each time.
		}while(isalpha(name) != 0 && name != '\n' && name != EOF);
		//Run while we are able to get a successful return from fscanf OR we hit an enter (carriage return)

		//Fix issue with no quiz scores being present:
		//simply increase count to prevent letters of names from being cut off.
		if(name == '\n')
			count++;

		//Now that we've counted how many chars the name is, we can figure out how many spaces to add as a buffer.
		//First, some math: 20 - # of characters. This is the minimum buffer to add
		buffer = 20 - count;

		//If the buffer is positive, good. This means add that many characters (white space) to the output file
		if(buffer > 0)
		{
			if(name == '\n')		//Fix for cases where students had no quiz scores
				buffer++;			//The buffer was off by 1, now it isn't!

			while(buffer >= 0)		//Run til all th
			{
				fprintf(average, " ");	//Print spaces to the file.
				buffer--;
			}
		}
		//Else, if buffer is negative, add nothing since the name is at least 20 chars wide.

		//Now that the buffer has been added to the file, we may add the name to the file!
		fseek(quiz, -(long)count, SEEK_CUR);	//First reset the file position
		//(NOTE: count contains how many chars far into the current line we went using fgetc.
		//Casting it as a long and using the negative of this allows us to go back X number of spaces in the file.

		//Get the first name, store in the output file
		do{
			name = fgetc(quiz);
			if(name != '\n')			//DO NOT WRITE NEWLINES AT THIS POINT. 
				fputc(name, average);	//(Fix for an error where no quiz scores were present)
		}while(name != 32);

		//Get the second name, store it in average
		do{
			name = fgetc(quiz);
			if(name != '\n' && name != EOF)		//DO NOT PRINT NEW LINES OR EOF
				fputc(name, average);
			if(name == EOF || name == '\n')		//Add an extra space for students with no quiz scores
				fputc(' ', average);			
		}while(name != 32 && name != '\n' && name != EOF);		//Run til the next space, or newline or EOF

		fprintf(average, "|");	//Add a divider between names and quiz scores
		count = 0;

		if(name != 13)
		{
			//If there are numbers, do the following:
			//Try to get the next 10 (if they are there) numbers
			while(fscanf(quiz, "%d", &num) == 1)	//Run while fscanf is able to get a number
			{
				sum += num;
				fprintf(average, "%4d", num);
				count++;
			}
		}
		else
			sum = 0;

		//IF there is not a min of 10 numbers, add the required spaces (4 x 10-count)
		if(count != 10)
		{
			count = 10 - count;		//How many to add is just 10 - how many we counted, which is less than 10. 
									//Ex: 10 - 8 = 2 decimals aren't there, 2 * 4 = 8 spaces to add
			while(count > 0)
			{
				fprintf(average, "   0");	//Add 4 spaces per decimal that isn't there.
				count--;					//NOTE: I opted to add "0s" as well, since it is assumed they missed
			}								//the quiz and thus got a "0" for it.
		}
		
		fprintf(average, " |");	//Add a divider between quiz scores and the averages
		
		//Now we have sum, we can calculate the average.
		avg = sum / 10;

		//Print average to the output doc
		fprintf(average, " %10d\n", avg);
		
		not_empty = fgetc(quiz);	//Test the next line
		ungetc(not_empty, quiz);

	}while(not_empty != EOF);	//Run while the file has names & numbers in it
	
	return 1;	//Assuming the program worked correctly (it got to this point w/o infinite looping), return 1 for success.
}


// Pre-Condition: Original data in Quiz file, correctly formatted data + averages in the average file
//Post-Condition: Quiz file contains all data/formatting in the average file
void reverse_files(FILE* quiz, FILE* average)	//Function to put data in quiz from average
{


	return;
}