/***********************************************************************************************
	Program:	Example of MIPs program in C
	 Author:	Jason Downing
	   Date:	9/22/2014
 Time Spent:	--
	Purpose:	This program is just a "pseudocode" implementation of the MIPS
				assignment for Comp Org.
************************************************************************************************/
#include <stdio.h>

int main(int argc, char* argv[])
{
	char input[80] = {0};
	char output[80] = {0};
	char Tabchar[20] = {" 5#6(4)4*3+3,4-3.4#6"};
	char temp;
	int index_input;
	int index_loop;

	do{
		printf("Please enter a line of input: ");
		fgets(input, 256, stdin);
		
		printf("You entered: %s\n", input);
		index_input = 0;
		temp = input[index_input];
		goto main_loop;

		// This part checks the entire input line.
		main_loop:
			index_loop = 0;
			
			// This part checks an individual character to find its number.
			char_loop:
				if(temp == Tabchar[index_loop])
				{
					// Found a match!
					printf("Found %c\n", Tabchar[index_loop]);
					printf("The number is: %c\n", Tabchar[index_loop+1]);
					output[index_input] = Tabchar[index_loop+1];
					index_input++;	// Increase by one for each character.

					// See if we hit the end of the input.
					if(temp == '#')
					{
						// If we did, quit.
						output[index_input] = '\n';
						goto end_of_loop;
					}

					// Otherwise, continue the main loop.
					goto main_loop;	// goto because I'm mimicking MIPS
				}

				// Check to see if we hit the end of the array
				else if(Tabchar[index_loop] == '#')
				{
					index_input++;
					goto main_loop;
				}

				else{
					index_loop += 2;	// Move forward by two 
										// (numbers don't need to be checked).
				}

		end_of_loop:
		printf("The final string is: %s\n", output);

	}while(1);

	return 0;
}