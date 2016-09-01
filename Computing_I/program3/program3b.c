/*******************************
Author: Jason Downing
Course: 91.101-203 Computing I
Date: 10/21/2013
Time spent: Aprox. 2 hours
Description: 	This program finds the force between two objects and a distance. 
				The user enters the two masses and the distance and the program 
				uses this information to calculate the force between the two objects.

Attractive force between the moon and the earth = 1.98e25 dynes
*******************************/
#include <math.h>
#include <stdio.h>

const double GRAVITATIONAL_CONSTANT = 6.673e-8;		/*constant double for the gravitational constant used in
													  the gravitional force calculation. */
double gravity_force(double mass1, double mass2, double distance);
double ask_user(void);

int main(int argc, char* argv[])
{
	char ans = 'y';		//for the continue prompt
	double force;		//holds the force that has been returned from the ask_user function

	do{
		//Tell the user what to enter
		printf("This program is capitable of calculating the force between two objects \n");
		printf("given two masses (in grams) and a distance (in cm). \n\n");
		
		//Get the value of the force, by asking the user for m1/m2/distance and computing the value of the force.		
		force = ask_user();	

		//Print of the gravitional force for the user to see.
		printf("The gravitional attractive force is: %g dynes\n\n", force);

		do{		
			//Ask the user if they want to continue or quit			
			printf("Do you wish to continue?\nEnter y for yes or n for no: ");
			scanf(" %c", &ans);
		}while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');	//continue asking the user if they enter ANYTHING but y/Y/n/N.
		
		//Some new lines will make the 2nd/3rd/etc runs nicer looking
		printf("\n\n\n");

	//run while the user wants to continue
	}while(ans == 'y' || ans == 'Y');
	
	//end the program at this point
	return 0;
}

double gravity_force(double mass1, double mass2, double distance)
{
	double force;	
	
	//the force formula is: f = Gm1m2/d^2
	force = (GRAVITATIONAL_CONSTANT * mass1 * mass2) / (pow(distance, 2.0));
	
	//Return the force back to the ask_user function
	return force;	
}

double ask_user(void)
{
	double distance, mass1, mass2, force;
	int units = 0;

	//Ask which units they prefere to use
	printf("What units would you prefer to use for these calculations? \n");
	printf("1. Grams & Centimeters \n");
	printf("2. Kilograms & kilometers \n\n");

	//Force the user to enter 1 or 2 with this do/while loop
	do{
		printf("Enter 1 or 2 for the desired units: ");
		scanf(" %d", &units);
	}while(units != 1 && units != 2);
		
	
	//Ask the user for the 2 masses & the distance 
	printf("\nPlease enter the first mass: ");
	scanf("%lf", &mass1); 

	printf("Please enter the second mass: ");
	scanf("%lf", &mass2);
	
	printf("Please enter a distance: ");
	scanf("%lf", &distance);

	//If the user wanted G/C, no need to convert anything!
	//Otherwise if the user wants to use different units (ie KG/KM rather than G/CM)
	//then we must convert them to G/CM.
	if(units == 2)
	{
		//Convert mass1 / mass 2 by multiplying the respected mass by 1000
		mass1 = mass1 * 1000;
		mass2 = mass2 * 1000;

		//Convert distance to kilometers by multiplying by 100,000
		distance = distance * 100000;
	}

	//Send these masses & distance to the gravity_force function
	force = gravity_force(mass1, mass2, distance);

	//Return the force found above back to main	
	return force;
}
