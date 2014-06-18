/*
	Author: Jason Downing
	Course: Computing I 91 101-203
	  Date: 11/26/2013
	  Description: 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char fullname[40];
	int num = 0;
	int sum = 0;
	int avg = 0;
	int not_empty = 0;
	int a = 0;
	
	fprintf(average, "Student Name:       | Quiz Scores                            | Average Quiz Score \n");
	
	do{
		sum = 0;	//Reset variables
		num = 0;
		
		//Get the first name/last name and store it in a string
		//First name
		for(a = 0; fullname[a] != 32; a++;)
		{
			fullname[a] = fgetc(quiz);
		}
		//Add the space
		fullname[a] = fgetc(quiz);
		a++;	//Increase a by one for the next loop

		//Last name
		for(; fullname[a] != 32); a++)
		{
			fullname[a] = fgetc(quiz);
		}

		//Add a newline to the end of this string
		fullname[a] = '\n';

		//Output the full name to the output file, left justified and with a 20 character width minimum.
		fprintf(average, "%-20s", fullname);
		
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