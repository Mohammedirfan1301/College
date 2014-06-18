/*
	Author: Jason Downing
	Course: Computing I 91 101-203
	  Date: 11/26/2013
	  Description: 

*/
#include <stdio.h>
#include <stdlib.h>

void open_files(FILE** pquiz, FILE** paverage);	//Function to open the files
void work_files(FILE* quiz, FILE* average);		//Function to work with the files

int main(int argc, int argv[])
{
	FILE *quiz, *average;	//File pointers

	open_files(&quiz, &average);	//Open the files
	work_files(quiz, average);		//Work on the files

	//Close the files
	fclose(quiz);
	fclose(average);

	return 0;
}

// Pre-Condition: The files are not opened
//Post-Condition: The files are opened and in the correct mode for reading/writing
void open_files(FILE** pquiz, FILE** paverage)
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

// Pre-Condition: The average file is empty
//Post-Condition: The average file is the same as the quiz file, with averages for each of the set of quizzes.
void work_files(FILE* quiz, FILE* average)
{
	char name;
	int num = 0;
	int sum = 0;
	int avg = 0;
	int not_empty = 0;
	int count = 0;
	int buffer = 0;
	long pos;
	
	fprintf(average, "Student Name:       | Quiz Scores                            | Average Quiz Score \n");

	do{
		sum = 0;	//Reset variables
		num = 0;
		count = 0;
		
		//Get the first name (only have many characters long it is)
		do{
			fscanf(quiz, "%c", &name);
			count++;	//Increase character count by one each time.
		}while(name != 32);

		//Get the second name (only have many characters long it is)
		do{
			fscanf(quiz, "%c", &name);
			count++;	//Increase character count by one each time.
		}while(name != 32);

		pos = ftell(quiz);	//Get the current file position, store it for future use.

		/*
			Now we know: 
			The pos of the beginning of this line.
			How many characters long the name is.
			So we can use this to left allign the output file
		*/

		//First, some math: 20 - # of characters. This is the minimum buffer to add
		buffer = 20 - count;

		//If the buffer is positive, good. This means add that many characters (white space) to the output file
		//This is so that the output file looks neat.
		if(buffer > 0)
		{
			while(buffer => 0)
			{
				fprintf(average, " ");
				buffer--;
			}
		}
		//Else, if buffer is negative, simply add the mimimum buffer (20 spaces) to the output file.
		else 
		{
			buffer = 20;
			while(buffer => 0)
			{
				fprintf(average, " ");
				buffer--;
			}
		}

		//Now that the buffer has been added to the file, we may add the name to the file!
		//First reset the file position:
		fseek(quiz, -pos, SEEK_CUR);	//Go back "X" amount

		//Get the first name, store in average
		do{
			fscanf(quiz, "%c", &name);
			fprintf(average, "%c", name);
		}while(name != 32);

		//Get the second name, store it in average
		do{
			fscanf(quiz, "%c", &name);
			fprintf(average, "%c", name);
		}while(name != 32);

		//Try to get the next 10 (if they are there) numbers
		while(fscanf(quiz, "%d", &num) == 1)	//Run while fscanf is able to get a number
		{
			sum += num;
			fprintf(average, "%4d ", num);
		}

		//Now we have sum, we can calculate the average.
		avg = sum / 10;

		//Print average to the output doc
		fprintf(average, " %10d\n", avg);

		not_empty = fgetc(quiz);	//Test the next line
		ungetc(not_empty, quiz);

	}while(not_empty != EOF);	//Run while the file has names & numbers in it
	
	return;
}