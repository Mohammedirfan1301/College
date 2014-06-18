/*	   Program: Program4b.c
	    Author: Jason Downing
	      Date: November 4, 2013
	Time Spent: 4 Hours
	   Purpose: The purpose of this program is to ask the user if they want to convert a length
		or a weight. Once the user enters a selection the program will then ask the user
		if they want to convert between various units of measure (feet/meters or kilograms/pounds).
		The program then prints out what they selected. It runs until the user enters '0' to quit the program.
 */
#include <stdio.h>

//Functions called by main
void convert_lengths(void);	//When called, asks user what unit of length to convert
void convert_weights(void);	//When called, asks user what unit of weight to convert

//Functions called by convert_lengths or convert_weights
void convert_to_metric(void);	//Takes input, converts and outputs from US to Metric length
void convert_to_us(void);		//Takes input, converts and outputs from Metric to US length
void weight_to_metric(void);	//Takes input, converts and outputs from US to Metric weight
void weight_to_us(void);		//Takes input, converts and outputs from Metric to US weight

//Functions called by convert_to_metric
void us_to_metric_input(int *ft, double *in);	//Takes input of feet & inches and stores it in the convert_to_metric function (by using pointers)
void us_to_metric_convert(int feet, double inches, int *meters, double *centimeters); 	//converts us lengths to metric lengths.
void us_to_metric_output(int feet, int meters, double inches, double centimeters);		//outputs the inputed and converted lengths for
																						//the user to see
//Functions called by convert_to_us
void metric_to_us_input(int *m, double *cm);	//Takes input of meters and centimeters and stores it in the convert_to_us function using pointers
void metric_to_us_convert(int meters, double centimeters, int *feet, double *inches);	//converts metric lengths to us lengths
void metric_to_us_output(int feet, int meters, double inches, double centimeters);		//outputs the inputed and converted lengths for
																						//the user to see
//Functions called by weight_to_metric
void weight_to_metric_input(int *lb, double *on);									//takes input of lbs/ounces and stores the input in the weight_to_metric
void weight_to_metric_convert(int pounds, double onces, int *kg, double *g);		//converts us weights to metric weights 
void weight_to_metric_output(int pounds, int kilograms, double onces, double grams);//outputs the inputed and converted lengths for
																					//the user to see
//Functions called by weight_to_us
void weight_to_us_input(int *kg, double *g);										//takes input of kg/grams and stores them in weight_to_us
void weight_to_us_convert(int kilograms, double grams, int *lb, double *on);		//converts metric weights to us weights
void weight_to_us_output(int pounds, int kilograms, double ounces, double grams);	//outputs the inputed and converted lengths for
																					//the user to see

//Constants used by the program
const double meters_to_feet = .3048;
const int inches_in_foot = 12;
const int centi_in_meters = 100;
const double pounds_to_kilograms = 2.2046;
const int grams_in_kilogram = 1000;
const int ounces_in_pound = 16;

int main(int argc, char* argv[])
{
	int ans;    //Used in the switch/question below

	do{
		printf("This program lets you convert lengths and weights. \n");
		printf("Enter one of the following numbers to use the program. \n\n");
		printf("1. Convert Length \n");                 
		printf("2. Convert Weight \n");                 //Prompt telling the user what options they may enter.
        printf("TO QUIT THE PROGRAM: ENTER 0  \n\n");
   
		do{
			printf("Please make your selection: ");     //Ask the user to enter a number 0, 1 or 2.
			scanf(" %d", &ans);                         //If they don't follow directions:

			if(ans < 0 || ans > 2)
				printf("\nPlease read the instructions and enter a 0, 1 or 2 for an option. \n\n");

		}while(ans != 0 && ans != 1 && ans != 2);       //Continue looping until they do.

		switch(ans)     //Take ans and figure out which option the user entered
		{
			case 0:
				break;  //get out of the switch statement as they want to quit!
			case 1:
				convert_lengths();      //Call the length function
				break;

			case 2:
				convert_weights();      //Call the weight function
				break;

			default:
				printf("How did you get here? \n");     //They shouldn't get here b/c of the do/while
				break;                                  //This is just in case for debugging
		}
	
		printf("\n************************************************************* \n\n"); //This is just for separating multiple runs.

	}while(ans == 1 || ans == 2);       //run while "ans" equals 1 or 2. quits if 0 is entered.
   
	printf("Thanks for using this program! \n");        //Good bye to the user
   
	return 0;   //end of the program.
}

void convert_lengths(void)
{
	int ans;	//used in the switch below.
	
	do{
		printf("\nWhat would you like to convert? \n");
		printf("1. Feet/inches to meters/centimeters \n");	//Prompt asking the user what unit of length they want to convert to/from
		printf("2. Meters/centimeters to feet/inches \n");
	    printf("TO QUIT OUT OF THIS PART: ENTER 0 \n\n");
   
		do{
			printf("Please make your selection: ");     //Ask the user to enter a number 0, 1 or 2.
			scanf(" %d", &ans);                         //If they don't follow directions:
		}while(ans != 0 && ans != 1 && ans != 2);       //Continue looping until they do.
   
		switch(ans)
		{
			case 0:
				printf("\n");		//This is just to separate out the inputs - just make the output nicer looking
				return;				//return to main since the user wanted to quit if they entered 0.
			case 1:
				convert_to_metric();	//call the metric function since the user entered 1
				break;
			case 2:
				convert_to_us();		//call the us function since the user entered 2
				break;
		}

	}while(ans == 1 || ans == 2);
}

void convert_weights(void)
{
	int ans;	//used in the switch below
	do{
		printf("\nWhat would you like to convert? \n");
		printf("1. Pounds/ounces to kilograms/grams \n");	//Prompt asking the user what unit of length they want to convert to/from
		printf("2. Kilograms/grams to pounds/ounces \n");
	    printf("TO QUIT OUT OF THIS PART: ENTER 0 \n\n");
   
		do{
			printf("Please make your selection: ");     //Ask the user to enter a number 0, 1 or 2.
			scanf(" %d", &ans);                         //If they don't follow directions:
		}while(ans != 0 && ans != 1 && ans != 2);       //Continue looping until they do.
   
		switch(ans)
		{
			case 0:
				printf("\n");       //This is just to separate out the inputs - just make the output nicer looking
				return;
			case 1:
				weight_to_metric();	//call the metric function since the user entered 1
				break;
			case 2:
				weight_to_us();		//call the us function since the user entered 2
				break;
		}

	}while(ans == 1 || ans == 2);
}
	
//************************************************************************************
// CONVERTING FROM US LENGTHS TO METRIC 
//************************************************************************************

void convert_to_metric(void)
{	
	int feet = 0, meters = 0;		//Various variables used in the next three functions.
	double inches = 0, centimeters = 0;
	int *ft, *m;				//Pointers are used to modify the above variables.
	double *in, *cm;

	ft = &feet;
	in = &inches;			//getting the address of the variables for use in the functions
	m = &meters;
	cm = &centimeters;

	us_to_metric_input(ft, in);	//send feet/inches location to the input function so that it can store the values in the feet/inches variables.
	us_to_metric_convert(feet, inches, m, cm);	//send feet/inches along with the address of meters/centimeters. Convert feet/inches to meters/centimeters
	us_to_metric_output(feet, meters, inches, centimeters);	//send all the variables to the output function to print them to the screen

	return;		//return back to main
}

void us_to_metric_input(int *ft, double *in)
{
	printf("\nPlease enter the number in feet/inches that you would like \n");	//Ask the user to enter a length in feet/inches
	printf("to convert to meters/centimeters. \n");					
	printf("Enter the numbers here (separated by spaces/enter): ");			//Note: it can be separated by spaces or enters
	scanf("%d %lf", ft, in);							//ie "8 feet 2 inches" could be entered as "8 2"
	
	return;	//return to the convert_to_metric function
}

void us_to_metric_convert(int feet, double inches, int *meters, double *centimeters)
{
	/*	Convert feet/inches to meters/centimeters. Do this by:
		1. Finding the total number of inches
		2. Convert this to cm
		3. Find out how many whole meters are in this value
		4. Put the remaining cm into the cm variable

		NOTE THESE CONSTANTS	(declared on the top of the source code - THIS IS REFERENCE ONLY)
		const double meters_to_feet = .3048;
		const int inches_in_foot = 12;
		const int centi_in_meters = 100;

	I use pointers to change the value of the meters/centimeters variables (which are located in the convert_to_metric function)
	*/
	
	double total_inches = 0, total_cm = 0;
	
	total_inches = ((double)feet * (double)inches_in_foot) + inches;	//find the total number of inches entered
	total_cm = (total_inches / (double)inches_in_foot) * meters_to_feet * (double)centi_in_meters;	//convert inches to cm

	//Now figure out how many whole meters are in total_cm
	while(total_cm > 100)
	{
		*meters = *meters + 1;		//Add 1 to meters
		total_cm = total_cm - 100;	//subtract 100 cm (1m) from total_cm
	}
	
	//At the end of this while loop, total_cm should be a value between 0 and 99.99...
	//So simply make *centimeters equal to total_cm!
	*centimeters = total_cm;

	return;	//Now return to convert_to_metric
}

void us_to_metric_output(int feet, int meters, double inches, double centimeters)
{
	//Output the results here
	printf("\n%d Feet %.2lf inches equals %d meters %.2lf centimeters. \n", feet, inches, meters, centimeters);
	
	return;	//Now return to convert_to_metric
}

//************************************************************************************
// CONVERTING FROM METRIC LENGTHS TO US LENGTHS. IE METERS/CENTIMETERS TO FEET/INCHES
//************************************************************************************

void convert_to_us(void)
{
	int feet = 0, meters = 0;		//Various variables used in the next three functions.
	double inches = 0, centimeters = 0;	
	int *ft, *m;				//Pointers are used to modify the above variables.
	double *in, *cm;

	ft = &feet;
	in = &inches;			//getting the address of the variables for use in the functions
	m = &meters;
	cm = &centimeters;

	metric_to_us_input(m, cm);	//send feet/inches location to the input function so that it can store the values in the feet/inches variables.
	metric_to_us_convert(meters, centimeters, ft, in);	//Convert feet/inches to meters/centimeters
	metric_to_us_output(feet, meters, inches, centimeters);	//send all the variables to the output function to print them to the screen

	return;		//return back to main
}

void metric_to_us_input(int *m, double *cm)
{
	printf("\nPlease enter the number in feet/inches that you would like \n");	//Ask the user to enter a length in feet/inches
	printf("to convert to meters/centimeters. \n");					
	printf("Enter the numbers here (separated by spaces/enter): ");			//Note: it can be separated by spaces or enters
	scanf("%d %lf", m, cm);								//ie "8 feet 2 inches" could be entered as "8 2"
	
	return;	//return to the convert_to_us function
}

void metric_to_us_convert(int meters, double centimeters, int *feet, double *inches)
{
	/*	Convert meters/centimeters to feet/inches. Do this by:
		1. Finding the total number of cm
		2. Convert this to inches
		3. Find out how many whole feet are in this value
		4. Put the remaining inches into the inches variable

		NOTE THESE CONSTANTS	(declared on the top of the source code - THIS IS REFERENCE ONLY)
		const double meters_to_feet = .3048;
		const int inches_in_foot = 12;
		const int centi_in_meters = 100;

	I use pointers to change the value of the feet/inches variables (which are located in the convert_to_us function)	*/
	
	double total_inches = 0, total_cm = 0;
	
	total_cm = ((double)meters * (double)centi_in_meters) + centimeters;	//find the total number of centimeters entered
	total_inches = ((total_cm / (double)centi_in_meters) / meters_to_feet) * (double)inches_in_foot;//convert cm to inches

	//Now figure out how many whole feet are in total_inches
	while(total_inches > 12)
	{
		*feet = *feet + 1;			//Add 1 to feet
		total_inches = total_inches - 12;	//Subtract 12 inches.
	}
	
	//At the end of this while loop, total_inches should be a value between 0 and 11.99....
	//So simply make *inches equal to total_inches!
	*inches = total_inches;

	return;	//Now return to convert_to_us
}

void metric_to_us_output(int feet, int meters, double inches, double centimeters)
{
	//Output the results here
	printf("\n%d Meters %.2lf centimeters equals %d feet %.2lf inches. \n", meters, centimeters, feet, inches);
	
	return;	//return to metric_to_us
}

//************************************************************************************
// CONVERTING FROM US WEIGHTS TO METRIC WEIGHTS. IE POUNDS/OUNCES TO KILOGRAMS/GRAMS
//************************************************************************************

void weight_to_metric(void)
{
   	int kilograms = 0, pounds = 0;	//Variables used throughout this function
	double grams = 0, ounces = 0;
	int *kg, *lb;			//Pointers which point to the above variables
	double *g, *on; 

	kg = &kilograms;
	lb = &pounds;		//Make the pointers hold the address of the above variables
	g = &grams;
	on = &ounces;

	//Now call the three functions to do the blunt work of input/converting/outputting
	weight_to_metric_input(lb, on);				//Take the input
	weight_to_metric_convert(pounds, ounces, kg, g);	//Convert us to metric
	weight_to_metric_output(pounds, kilograms, ounces, grams); //Output all the variables to the screen
	
	return;		//return back to main
}

void weight_to_metric_input(int *lb, double *on)
{
	printf("\nPlease enter the number in pounds/onces that you would like \n");	//Ask the user to enter a weight in pounds/onces
	printf("to convert to kilograms/grams. \n");					
	printf("Enter the numbers here (separated by spaces/enter): ");			//Note: it can be separated by spaces or enters
	scanf("%d %lf", lb, on);							//ie "5 pounds 4 onces" can be entered "5 4"
	
	return;	//return to the weight_to_metric function
}

void weight_to_metric_convert(int pounds, double ounces, int *kg, double *g)
{
	/*	Convert pounds/onces to kilograms/grams. Do this by:
		1. Finding the total number of ounces
		2. Convert this to grams
		3. Find out how many whole kilograms are in this value
		4. Put the remaining grams into the g variable

		NOTE THESE CONSTANTS	(declared on the top of the source code - THIS IS REFERENCE ONLY)
		pounds_to_kilograms = 2.2046;
		grams_in_kilogram = 1000;
		ounces_in_pound = 16;

	I use pointers to change the value of the kg/g variables (which are located in the weight_to_metric function)	*/
	
	double total_ounces = 0, total_grams = 0;
	
	total_ounces = ((double)pounds * (double)ounces_in_pound) + ounces;	//find the total number of ounces entered
	total_grams = ((total_ounces / (double)ounces_in_pound) / pounds_to_kilograms) * (double)grams_in_kilogram;	//convert ounces to grams

	//Now figure out how many whole kilograms are in total_grams
	while(total_grams > 1000)
	{
		*kg = *kg + 1;				//Add 1 to kilograms
		total_grams = total_grams - 1000;	//Subtract 1000 grams (1 kg).
	}
	
	//At the end of this while loop, total_grams should be a value between 0 and 999.99...
	//So simply make *g equal to total_grams!
	*g = total_grams;

	return;	//Now return to weight_to_metric
}

void weight_to_metric_output(int pounds, int kilograms, double ounces, double grams)
{
	//Output the results here
	printf("\n%d Pounds %.2lf ounces equals %d kilograms %.2lf grams. \n", pounds, ounces, kilograms, grams);

	return;	//return to weight_to_metric function
}

//************************************************************************************
// CONVERTING FROM METRIC WEIGHTS TO US WEIGHTS. IE KILOGRAMS/GRAMS TO POUNDS/OUNCES
//************************************************************************************

void weight_to_us(void)
{
   	int kilograms = 0, pounds = 0;	//Variables used throughout this function
	double grams = 0, ounces = 0;
	int *kg, *lb;			//Pointers which point to the above variables
	double *g, *on; 

	kg = &kilograms;
	lb = &pounds;		//Make the pointers hold the address of the above variables
	g = &grams;
	on = &ounces;

	//Now call the three functions to do the blunt work of input/converting/outputting
	weight_to_us_input(kg, g);			//Take the input
	weight_to_us_convert(kilograms, grams, lb, on);	//Convert metric to us
	weight_to_us_output(pounds, kilograms, ounces, grams); //Output all the variables to the screen

	return;		//return back to main
}

void weight_to_us_input(int *kg, double *g)
{
	printf("\nPlease enter the number in kilograms/grams that you would like \n");	//Ask the user to enter a weight in kg/g
	printf("to convert to pounds/onces . \n");					
	printf("Enter the numbers here (separated by spaces/enter): ");			//Note: it can be separated by spaces or enters
	scanf("%d %lf", kg, g);								//ie "5 kg 4 grams" can be entered "5 4"
	
	return;	//return to the weight_to_us function
}

void weight_to_us_convert(int kilograms, double grams, int *lb, double *on)
{
	/*	Convert kilograms/grams to pounds/onces. Do this by:
		1. Finding the total number of grams
		2. Convert this to ounces
		3. Find out how many whole pounds are in this value
		4. Put the remaining ounces into the on variable

		NOTE THESE CONSTANTS (declared on the top of the source code - THIS IS REFERENCE ONLY)
		pounds_to_kilograms = 2.2046;
		grams_in_kilogram = 1000;
		ounces_in_pound = 16;

	I use pointers to change the value of the pound/ounces variables (which are located in the weight_to_us function)	*/
	
	double total_ounces = 0, total_grams = 0;
	
	total_grams = ((double)kilograms * (double)grams_in_kilogram) + grams;		//find the total number of grams entered
	total_ounces = ((total_grams / (double)grams_in_kilogram) * pounds_to_kilograms) * (double)ounces_in_pound;	//convert grams to ounces

	//Now figure out how many whole pounds are in total_ounces
	while(total_ounces > 16)
	{
		*lb = *lb + 1;				//Add 1 to pounds
		total_ounces = total_ounces - 16;	//Subtract 16 ounces (1 lb).
	}
	
	//At the end of this while loop, total_ounces should be a value between 0 and 15.99...
	//So simply make *on equal to total_ounces!
	*on = total_ounces;

	return;	//return to the weight_to_us function
}

void weight_to_us_output(int pounds, int kilograms, double ounces, double grams)
{
	//Output the results here
	printf("\n%d Kilograms %.2lf grams equals %d pounds %.2lf ounces. \n", kilograms, grams, pounds, ounces);

	return;	//return to the weight_to_us function
}
