/*
Program: program5a.c
Author: Zachary Wong
Date: 11/26/2013
Time Spent:99 minutes
Purpose:  This program takes from two sorted number text files and merges them together into one sorted file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void file_in(FILE** file1, FILE** file2, FILE** file_out);	//Opens the files properly	
void sortFiles(FILE* file1, FILE* file2, FILE* file_out);	//Merges the two files

int main(int argc, char * argv[])
{
	FILE* fnum1;
	FILE* fnum2;
	FILE* fout;
    
	file_in(&fnum1, &fnum2, &fout);
	sortFiles(fnum1, fnum2, fout);

	fclose(fnum1);
	fclose(fnum2);
	fclose(fout);

	return 0;

}

//pre:  file1, file2 and file_out are defined.
//post: file1, file2 and file_out are opened properly

void file_in(FILE** file1, FILE** file2, FILE** file_out)
{
	*file1 = fopen("numbers1.txt", "r");
	if (*file1 == NULL)
	{
		fprintf(stderr, "File: numbers1.txt failed to open.\n");
		exit(1);
	}

	*file2 = fopen("numbers2.txt", "r");
	if (*file2 == NULL)
	{
		fprintf(stderr, "File: numbers2.txt failed to open.\n");
		exit(1);
	}

	*file_out = fopen("output.txt", "wb");
	if (*file_out == NULL)
	{
		fprintf(stderr, "File: output.txt failed to open.\n");
		exit(1);
	}
}

//pre: file1, file2, and file_out are defined.
//post: the function merged the two files sucessfully in numerical order.

void sortFiles(FILE* file1, FILE* file2, FILE* file_out)
{
	int filenum1;
	int filenum2;
	int f1;
	int f2;


	filenum1 = fscanf(file1, "%d", &f1);
	filenum2 = fscanf(file2, "%d", &f2);

	while (filenum1 == 1  && filenum2 == 1)
	{
		if (f1 > f2)
		{
			fprintf(file_out, "%d ", f2);
			filenum2 = fscanf(file2, "%d", &f2);
		}

		else
		{
			fprintf(file_out, "%d ", f1);
			filenum1 = fscanf(file1, "%d", &f1);
		}
	}

	while (filenum1 == 1)
	{
		fprintf(file_out, "%d ", f1);
		filenum1 = fscanf(file1, "%d", &f1);
	}

	while (filenum2 == 1)
	{
		fprintf(file_out, "%d ", f2);
		filenum2 = fscanf(file2, "%d", &f2);
	}
}
