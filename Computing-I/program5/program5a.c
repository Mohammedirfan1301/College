/*
	Author: Jason Downing
	Course: Computing I 91 101-203
	  Date: 11/27/2013
Time Spent: 4 Hours
	Description: This program takes two files which each list of numbers in ascending order.
				 It reads input from the two files and writes the output to another file called
				 output.txt. The output.txt file will contain all the numbers in a longer list
				 in ascending order. 
*/
#include <stdio.h>
#include <stdlib.h>

void open_files(FILE** pnumbers1, FILE** pnumbers2, FILE** poutput);	//Function to open the files
void work_files(FILE* numbers1, FILE* numbers2, FILE* output);			//Function to work on the files
void close_files(FILE* numbers1, FILE* numbers2, FILE* output);			//Function to close the files

int main(int argc, char* arv[])
{
	FILE *numbers1, *numbers2, *output;		//File pointers to the 3 files used in this program.
	
	printf("List Merging Program\n");			//Prompt to know the program is opened.
	open_files(&numbers1, &numbers2, &output);	//Open the files
	work_files(numbers1, numbers2, output);		//Merge the two files into the output file
	close_files(numbers1, numbers2, output);	//Close the files

	return 0;
}

// Pre-Condition: The files are not opened
//Post-Condition: The files are opened and in the correct mode for reading/writing
void open_files(FILE** pnumbers1, FILE** pnumbers2, FILE** poutput)
{	
	*pnumbers1 = fopen("numbers1.txt", "r");	//Open the first file in read mode.

	if(*pnumbers1 == NULL)		//If the file didn't open right, exit with an error.
	{
		fprintf(stderr, "The File: numbers1.txt failed to open correctly. \n");
		exit(1);	
	}

	*pnumbers2 = fopen("numbers2.txt", "r");	//Open the second file in read mode.

	if(*pnumbers2 == NULL)		//If the file didn't open right, exit with an error.
	{
		fprintf(stderr, "The File: numbers2.txt failed to open correctly. \n");
		exit(1);	
	}

	*poutput = fopen("output.txt", "w");	//Open the output file in write mode.
											//If this file doesn't exist the program will simply write a file called
	if(*poutput == NULL)					//output.txt
	{						//If the file didn't open right, exit with an error.
		fprintf(stderr, "The File: output.txt failed to open correctly. \n");
		exit(1);	
	}
}

// Pre-Condition: The files are open
//Post-Condition: The files are closed
void close_files(FILE* numbers1, FILE* numbers2, FILE* output)
{
	fclose(numbers1);	//CLOSE THE FILES once we are done working with them
	fclose(numbers2);
	fclose(output);
}


// Pre-Condition: The output file is empty
//Post-Condition: The output file contains both list1/list2 and in ascending order
void work_files(FILE *numbers1, FILE*numbers2, FILE*output)
{
	int num1 = 0;	//Holds each files number;
	int num2 = 0;	//Holds a second number to compare to
	int not_empty1 = 0;
	int not_empty2 = 0;
	
	//Get the first numbers
	not_empty1 = fscanf(numbers1, "%d", &num1);
	not_empty2 = fscanf(numbers2, "%d", &num2);
	
	//IF both lists contain numbers, put them in ascending order into the output.txt file
	if(not_empty1 == 1 && not_empty2 == 1)
	{
		do{
			//CHECK
			if(num1 > num2)	//If the first number is larger than the second number
			{
				//Put the first number in the output file
				fprintf(output, "%d\n", num2);

				//Get another number to use for future comparision.
				not_empty2 = fscanf(numbers2, "%d", &num2);
			}

			//CHECK
			if(num1 < num2)	//If the second number is larger than the first number
			{
				//Put the first number in the output file
				fprintf(output, "%d\n", num1);

				//Get another number to use for future comparision
				not_empty1 = fscanf(numbers1, "%d", &num1);
			}

		}while(not_empty1 == 1 && not_empty2 == 1);	//Run til both lists are empty
	}

	//IF only num1 contains numbers, put all of its numbers into the output file
	if(not_empty1 == 1)
	{
		do{
			//USE
			fprintf(output, "%d\n", num1);				//Put it in the output list
			
			//TRY
			not_empty1 = fscanf(numbers1, "%d", &num1);	//Get the next number
		}while(not_empty1 == 1);						//CHECK
	}

	//IF only num2 contains numbers, put all of its numbers into the output file
	if(not_empty2 == 1)	
	{		
		do{
			//USE
			fprintf(output, "%d\n", num2);				//Put it in the output list
			
			//TRY
			not_empty2 = fscanf(numbers2, "%d", &num2);	//Get the first number
		}while(not_empty2 == 1);						//CHECK
	}

	printf("Successfully merged the files!\n");
}