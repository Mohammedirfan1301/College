/*	   Program: Program4b.c
	    Author: Jason Downing
	      Date: November 2, 2013
	Time Spent: 1/2 Hour
	   Purpose: The purpose of this program is to ask the user if they want to convert a length
				or a weight. Once the user enters a selection the program will then ask the user
				if they want to convert between various units of measure (feet/meters or kilograms/pounds).
				The program then prints out what they selected. It runs until the user enters '0' to quit the program.
 */
#include <stdio.h>

//Functions called by main
void convert_lengths(void);
void convert_weights(void);

//Functions called by other functions (ie convert_lengths or convert_weights)
void convert_to_metric(void);
void convert_to_us(void);
void weight_to_metric(void);
void weight_to_us(void);

int main(int argc, char* argv[])
{
   int ans;    //Used in the switch/question below
   
   do{
        printf("This program lets you convert lengths and weights. \n");
		printf("Enter one of the following numbers to use the program. \n\n");
        printf("1. Convert Length \n");                 
        printf("2. Convert Weight \n");                 //Prompt telling the user what options they may enter.
        printf("TO QUIT: Enter 0  \n\n");
   
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

   }while(ans == 1 || ans == 2);       //run while "ans" equals 1 or 2. quits if 0 is entered.
   
   printf("\nThanks for using this program! \n");        //Good bye to the user
   
   return 0;   //end of the program.
}

void convert_lengths(void)
{
   int ans;	//used in the switch below.
   printf("\nWhat would you like to convert? \n");
   printf("1. Feet/inches to Meters/centimeters \n");	//Prompt asking the user what unit of length they want to convert to/from
   printf("2. Meters/centimeters to Feet/inches \n");
   printf("TO QUIT: ENTER 0 \n\n");
   
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
}

void convert_weights(void)
{
   int ans;	//used in the switch below
   printf("\nWhat would you like to convert? \n");
   printf("1. Pounds/ounces to Kilograms/grams \n");	//Prompt asking the user what unit of length they want to convert to/from
   printf("2. Kilograms/grams to Pounds/ounces \n");
   printf("TO QUIT: ENTER 0 \n\n");
   
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
}

void convert_to_metric(void)
{
   printf("\n\nYou wanted to convert feet/inches to meters/centimeters! \n\n\n");	//print out of the user's selection
}

void convert_to_us(void)
{
   printf("\n\nYou wanted to convert meters/centimeters to feet/inches! \n\n\n");	//print out of the user's selection
}
void weight_to_metric(void)
{
   printf("\n\nYou wanted to convert pounds/ounces to kilograms/grams! \n\n\n");	//print out of the user's selection
}

void weight_to_us(void)
{
   printf("\n\nYou wanted to convert kilograms/grams to pounds/ounces! \n\n\n");	//print out of the user's selection
}