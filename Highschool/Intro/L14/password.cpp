#include <iostream.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a = 0, b = 0, d = 0;
char c = 0;
int lenpass = 0, leninput = 0, lenofinput = 0;
int entry = 0;
char password[30] = {"jasondowning"};  //orignal password
char input[30] = {'\0'};               //array for the user entered password

main()
{
	a = 0, b = 0;
	memset(input, '\0', 30);

	cout<<"\t\tPassword Protector V1.2 \n";
	cout<<"Welcome. Enter your password in the space below. \n";
	cout<<"NOTE: The USER only has THREE attempts at the password. \n";
	cout<<"ALSO: Capital letters and spaces will not effect the password. \n\n";

	for(a = 0; a < 3; a++)
	{
		cout<<"Enter the password here: ";

		for(b = 0; input[b] != 13; b++)
		{
			input[b] = getch();
			cout<<"*";

			//If the user enters 'backspace', ASCII value of 8: the program will back up 2 spaces.
			if(input[b] == 8)
				b = b - 2;

			//If the user enters 'enter', ASCII value of 13: the loop will stop.
			if(input[b] == 13)
			{
				lenofinput = b;  //the length of the password - needed for the compare part.
				input[b] = '\0'; //the last spot is '13' or return - setting it equal to 'NULL' fixes any compare problems with the program.
				cout<<endl;      //new line
				break;           //breaks the loop.
			}

			//if the user enters a space, ASCII value of 32: the value backs up by 1, to overwrite the space with a character.
			if(input[b] == 32)
				b = b - 1;
		}

		cout<<"\nChecking password... \n";
		cout<<endl;

		lenpass = strlen(password); //lenpass equals the length of the orignal password
		leninput = strlen(input);   //leninput is equal to the length of the user entered password

		if(lenpass == leninput)     //if the lengths match up, the program continues
		{
			cout<<"Password length is correct. Proceding... \n\n";

			for(a = 0; input[a] != '\0'; a++)
				input[a] = tolower(input[a]);		//converts all letters entered to lowercase

			if(strncmp(password, input, lenpass) == 0)
			{
				entry = 1;
				break;
			}
			else
				cout<<"Error! Password length correct - but password is incorrect! \n\n";
		}
		else if(lenpass > leninput) 								//if the length is too short
			cout<<"Error! Password length too short! \n\n";
		else if(lenpass < leninput) 								//if the length is too long
			cout<<"Error! Password length too long! \n\n";
	}

	if(entry == 0) //if the user is unable to enter the correct password, the following is printed to the screen
	{
		//clrscr();
		cout<<"ERROR! ERROR! \n";
		cout<<"ACCESS DENIED! ACCESS DENIED! \n";
		cout<<"ERROR CODE: TOO MANY ATTEMPTS AT PASSWORD! \n\n";
		cout<<"Enter any key to ABORT: ";
		c = getch();
		abort();
	}

	if(entry == 1) //if the user manages to enter the correct password, the following is printed to the screen
	{
		clrscr();
		cout<<"ACCESS GRANTED. \n";
		cout<<"You now have the highest access level and may read all the \n";
		cout<<"secrets held within this file. \n";
	}

   return 0;
}
