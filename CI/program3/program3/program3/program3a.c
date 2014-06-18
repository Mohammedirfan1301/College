#include <stdio.h>
#include <math.h>

double get_length(double length);
double get_width(double width);
double get_area(double length, double width);
int display_data(double length, double width, double area);

int main(int argc, int argv[])
{
	char ans = 'y';
	double length = 0, width = 0, area = 0;
	int are_there_errors = 0;

	do{
		length = get_length(length);
		width = get_width(width);
		area = get_area(length, width);
		are_there_errors = display_data(length, width, area);

		do{	//Asks the user if they want to continue. Forces them to enter y/Y for yes and n/N for no
			printf("Do you want to continue running the program or quit? Enter y/n: ");
			scanf(" %c", &ans);
		}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');	//MUST ENTER y/Y/n/N or be asked again.
		printf("\n\n\n");	//Add some space in between program runs
	}while(ans == 'y' || ans == 'Y');
	
	return 0;	//end of the program so return 0 to say 'HEY I DON'T HAVE ANY ERRORS!'.
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
	printf("\nThe area of a rectangle with a width of %.2lf \nand a length of %.2lf is %.2lf! \n\n", length, width, area);
	return 0;	//return 0 to mimic the main program.
}
