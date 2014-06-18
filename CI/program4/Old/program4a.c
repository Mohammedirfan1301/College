/*	   Program: Program4a.c
	    Author: Jason Downing
	      Date: October 31, 2013
	Time Spent: 1/2 Hour
	   Purpose: The purpose of this program is to ask the user if they want to convert a length
				or a weight. It should run until the user enters '0' to quit the program.
 */
#include <stdio.h>

//Functions used in the program
void convert_lengths(void);
void convert_weights(void);

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
    printf("\n\nYou choose to convert lengths! \n\n\n");  //For Part A, just print out a 'hey' to the user
}

void convert_weights(void)
{
    printf("\n\nYou choose to convert weights! \n\n\n");  //For Part A, just print out a 'hey' to the user
}
