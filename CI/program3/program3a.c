/*******************************
Author: Jason Downing
Course: 91.101-203 Computing I
Date: 10/21/2013
Time spent: Aprox. 1 hour
Description: 	This program will calculate the area of a rectangle given an input
				that is positive, ie a length and a width. The program calculates the area
				and then displays it along with the width and length for the user to see.

*******************************/
#include <stdio.h>
#include <math.h>

//Function definitions. the get_s take user input and return it to main.
double get_length(double length);
double get_width(double width);
double get_area(double length, double width);

//display_data displays the length/width and the area calculated in get_area
int display_data(double length, double width, double area);

int main(int argc, int argv[])
{
	char ans = 'y';							//for the 'continue' response
	double length = 0, width = 0, area = 0;	//doubles for the gets_
	int are_there_errors = 0;				//for the return part of 'display_data'

	do{
		printf("AREA CALCULATOR PROGRAM \n");
		printf("This program will allow you to calculate the area of a rectangle \n");
		printf("given that you enter a positive length and a positive width. \n\n");
		
		//function calls - each name explains itself. All gets_ take user input and return it here, to main.
		length = get_length(length);
		width = get_width(width);
		area = get_area(length, width);
		
		//"are_there_errors" simply mimics the 'main' return - ie it just equals 0 if the function ran.
		are_there_errors = display_data(length, width, area);

		do{	//Asks the user if they want to continue. Forces them to enter y/Y for yes and n/N for no
			printf("Do you want to continue running the program or quit? Enter y/n: ");
			scanf(" %c", &ans);
		}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');	//MUST ENTER y/Y/n/N or be asked again.
		
		printf("\n\n\n");	//Add some space in between program runs
	
	}while(ans == 'y' || ans == 'Y');	//run while ans equals y OR Y. IF they entered n OR N this do/while breaks
	
	//When that do/while breaks the user ends up here and then main returns 0 below.

	return 0;	//end of the program so return 0 to say "HEY I DON'T HAVE ANY ERRORS!".
}

double get_length(double length)
{
	//IF the USER fails to follow directions, then we force them to enter a valid number!
	do{
		printf("Please enter a POSITIVE length: ");
		scanf("%lf", &length);
	}while(length <= 0);

	//As soon as they enter a positive length, return length back to MAIN.
	return length;
}

double get_width(double width)
{
	//Again, if the user doesn't listen to directions, then force them to.
	do{
		printf("Please enter a POSITIVE width: ");
		scanf("%lf", &width);
	}while(width <= 0);
	
	//Once the USER behaviors we may return the width!
	return width;
}

double get_area(double length, double width)
{
	//Since A = L * W, just return L * W!
	return length * width;
}
int display_data(double length, double width, double area)
{
	printf("\nA rectangle with a length of %.2lf and a width of %.2lf\nhas an area of %.2lf! \n\n", length, width, area);
	return 0;	//return 0 to mimic the main program.
}
