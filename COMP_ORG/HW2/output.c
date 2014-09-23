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
	char input[80];
	char output[80];

	do{
		printf("Please enter a line of input: ");
		fgets(input, 256, stdin);
		
		printf("You entered: %s\n", input);



	}while(1);

	return 0;
}