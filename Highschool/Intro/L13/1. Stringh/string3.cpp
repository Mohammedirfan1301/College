#include <conio.h>	 //clear screen
#include <iostream.h> //in/output
#include <string.h>   //string commands (strcpy/strncpy/etc)

//function for the menu
void menufunction(int);

//all seven command functions
void stringcopy(void);
void stringcharcopy(void);
void stringcompare(void);
void stringcharcompare(void);
void stringmerge(void);
void stringcharmerge(void);
void stringlength(void);

//global variables
int stringmenu = 0;

main()
{
	int x = 1;

	do{
	cout<<"Welcome to the String Example Program \n";
	cout<<"This program has seven functions that will explain and \n";
	cout<<"demonstrate these seven commands: \n";
	cout<<"1. Strcpy \n";
	cout<<"2. Strncpy \n";
	cout<<"3. Strcmp \n";
	cout<<"4. Strncmp \n";
	cout<<"5. Strcat \n";
	cout<<"6. Strncat \n";
	cout<<"7. Strlen \n\n";

	do{
	cout<<"Please enter one of the above numbers for an example of the command: ";
	cin>>stringmenu;
	}while(stringmenu != 1 && stringmenu != 2 && stringmenu != 3 && stringmenu != 4 && stringmenu != 5 && stringmenu != 6 && stringmenu != 7);

	cout<<endl;

	clrscr();
	menufunction(stringmenu);  //menu function

   cout<<endl;

	do{
	cout<<"To continue using the program, enter 1. To quit, enter 2. -> ";
	cin>>x;
   }while(x != 1 && x != 2);

	clrscr();

	}while(x == 1);

   cout<<"Thanks for using the String Example Program! \n";

	return 0;
}

void menufunction(int)
{
	switch(stringmenu)
	{
		case 1:
			stringcopy();
			break;

		case 2:
			stringcharcopy();
			break;

		case 3:
         stringcompare();
			break;

		case 4:
         stringcharcompare();
			break;

		case 5:
			stringmerge();
			break;

		case 6:
			stringcharmerge();
			break;

		case 7:
         stringlength();
			break;

		default:
			cout<<"This is not a valid option! \n";
			cout<<"Choose again! \n";
         break;
	}
}

void stringcopy(void)
{
	cout<<"Strcpy is a command that will copy a string to an array. \n";
	cout<<"It can also copy a string from one array to another array. \n";
	cout<<"\nTo use strcpy: \n";
	cout<<"1. Declare two arrays (or one if you wish to copy something to an array) \n";
	cout<<"2. Write: strcpy(1,2); \n";
	cout<<"2A. In the parentheses, the 1 represents the array you wish to copy to. \n";
	cout<<"2B. The 2 represents the array/text you wish to have copied to the other array \n";
	cout<<"\nHere is an example: \n\n";

	char test1[] = "This is a test of the strcpy";
	char test2[40];

	cout<<test1<<endl;
	cout<<"Now copying to another array... \n";
	strcpy(test2, test1);
	cout<<"Below is the second array and: \n";
	cout<<test2<<endl;
	cout<<"It works! \n";

}

void stringcharcopy(void)
{
	cout<<"Strncpy is a command that is similar to strcpy, with one difference: \n";
	cout<<"it limits how many characters will be copied. \n\n";

	cout<<"First, like strcpy, strncpy will copy text or an array to another array. \n";
	cout<<"With strcpy, you would write 'strcpy(array2, array1);' \n";
	cout<<"Where array2 is the array to be copied to, and array1 is the text/array \n";
	cout<<"that you want copied to array2. \n\n";

	cout<<"Strncpy works like this: 'strncpy(array2, array1, 5);' \n";
	cout<<"The five in this case will limit how many characters of array1 will be copied \n";
	cout<<"to array2. \n";

	cout<<"\nHere is an example: \n\n";

	char test1[] = "This text is a test of the strncpy command";
	char test2[40] = " "; //make sure to set equal to something (blank, \0, etc) or random stuff will appear after 10

	cout<<test1<<endl;
	cout<<"Now to copy the above text to another array... \n";
	strncpy(test2, test1, 5);
	cout<<"Below is the second array: \n";
	cout<<test2<<endl;
   cout<<"...IT WORKS! \n";
}

void stringcompare(void)
{
	cout<<"Strncmp is a command that will compare two arrays to see if they \n";
	cout<<"are equal to each other. If they are equal, it will return a zero value; \n";
	cout<<"if they are not equal it will return a positive or negative number. \n";
	cout<<"It will return a positive number if the first array is larger then the second, \n";
	cout<<"and it will return a negative number if it is smaller then the second array. \n";
   cout<<"This makes it a useful command when comparing arrays. \n";

	cout<<"To use this command: \n";
	cout<<"1. Declare two arrays. \n";
	cout<<"2. Make the two arrays equal to something - for instance: \n";
	cout<<"   char array1[20] = 'this is a test'";
	cout<<"   char array2[20] = 'this is not a test'";
	cout<<"(You could also make them equal to each other as well) \n";
	cout<<"3. Write the following command: \n";
	cout<<"   int strncmp(array1, array2) \n";
	cout<<"4. Now output strncmp and see what it returns. \n\n";

	cout<<"Here is a working example: \n";
	char array1[20] = "this is a test";
	char array2[20] = "this is not a test";
	cout<<array1<<endl;
	cout<<array2<<endl;
	int strncmp(array1, array2);
	if(strncmp > 0)
   	cout<<"These strings are not equal! \n";
}

void stringcharcompare(void)
{
	cout<<"This will run the strncmp function \n";
}

void stringmerge(void)
{
	cout<<"This will run the strcat function \n";
}

void stringcharmerge(void)
{
	cout<<"This will run the the strncat function \n";
}

void stringlength(void)
{
	cout<<"This will run the strlen function \n";
}
