#include <conio.h>	 //clear screen
#include <iostream.h> //in/output
#include <string.h>   //string commands (strcpy/strncpy/etc)

//function for the menu
void menufunction(int);

//all seven command functions
void stringcopy(void);         //strcpy
void stringcharcopy(void);     //strncpy
void stringcompare(void);      //strcmp
void stringcharcompare(void);  //strncmp
void stringmerge(void);        //strcat
void stringcharmerge(void);    //strncat
void stringlength(void);       //strlen

//global variables
int stringmenu = 0;

main()
{
	int x = 1;

	do{
	cout<<"String Example Program \n\n";
	cout<<"This program has seven functions that will explain and \n";
	cout<<"demonstrate these seven commands: \n\n";
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
	cout<<"Strcmp is a command that will compare two arrays to see if they \n";
	cout<<"are equal to each other. If they are equal, it will return a zero value; \n";
	cout<<"if they are not equal it will return a positive or negative number. \n";
	cout<<"It will return a positive number if the first array is larger then the second, \n";
	cout<<"and it will return a negative number if it is smaller then the second array. \n";
   cout<<"This makes it a useful command when comparing arrays. \n\n";

	cout<<"To use this command: \n";
	cout<<"1. Declare two arrays. \n";
	cout<<"2. Make the two arrays equal to something - for instance: \n";
	cout<<"   char array1[20] = ''this is a test''; \n";
	cout<<"   char array2[20] = ''this is not a test''; \n";
	cout<<"(You could also make them equal to each other as well) \n";
	cout<<"3. Write the following command (using an if statement or a loop): \n";
	cout<<"   if(strcmp(array1, array2) > 0) \n";
	cout<<"       cout<<''NOT EQUAL''; \n";
	cout<<"4. Using the above arrays, the cout will output as array1 is larger \n";
	cout<<"then array2. \n\n";

	cout<<"Here is a working example: \n";
	char array1[20] = "this is a test";
	char array2[20] = "this is not a test";
	cout<<array1<<endl;
	cout<<array2<<endl;
	if(strcmp(array1, array2) > 0);
		cout<<"These strings are not equal! \n";
}

void stringcharcompare(void)
{
	cout<<"Strncmp is a command that will compare two arrays to see if they are \n";
	cout<<"equal to each other. This is similar to the strcmp command - but the \n";
	cout<<"major difference is that strncmp will only compare up to a certain number \n";
	cout<<"of characters. \n\n";

	cout<<"Basically, to use strncmp just follow the same steps as strcmp, but add \n";
	cout<<"a number to the end of the strncmp command. This is number is how many  \n";
	cout<<"characters in the array the command will compare. \n\n";

	cout<<"For instance: \n";
	cout<<"if(strncmp(array1, array2, 5) == 0) \n";
	cout<<"   cout<<''EQUAL!'';  \n";
	cout<<"The above example will only compare to the 5th character - it will ignore \n";
	cout<<"the rest of the array. \n\n";

	cout<<"Here is a working example: \n";
	char array1[30] = "this is a test of strncmp";
	char array2[30] = "this isn't a test of strncmp";
	cout<<array1<<endl;
	cout<<array2<<endl;
	if(strncmp(array1, array2, 5) == 0)
	{
		cout<<"These arrays are not really equal... but this works anyway because \n";
		cout<<"the command only checks up to the 5th character! \n";
	}
}

void stringmerge(void)
{
	cout<<"Strcat is a command that will connect different arrays together. \n";
	cout<<"This works by taking different arrays and at the end of the first array \n";
	cout<<"the strcat command will add the second array to it. \n";
	cout<<"You can also use two arrays and merge them into one, new, array. \n\n";

	cout<<"Here is an example of the command: \n\n";
	char array1[50] = "This is a test ";
	char array2[50] = "of the strncmp command";
	cout<<array1<<endl;
	cout<<array2<<endl<<endl;
	cout<<"Now to combine the two arrays: \n\n";
	cout<<strcat(array1, array2)<<endl;
}

void stringcharmerge(void)
{
	cout<<"Strncat is a command that is similar to strcat, but different. \n";
	cout<<"Strncat will combine two arrays, but it allows you to set a maxium \n";
	cout<<"number of characters to combine. This is like the difference between \n";
	cout<<"strcpy and strncpy. \n\n";

	cout<<"Here is an example of the command: \n\n";
	char array1[40] = "I think this is a test ";
	char array2[40] = "of the strncmp command...";
	cout<<array1<<endl;
	cout<<array2<<endl<<endl;
	cout<<"Now to combine the arrays (up to the 6th character of the 2nd array): \n\n";
	strncat(array1, array2, 6);
	cout<<array1<<endl;

}

void stringlength(void)
{
	cout<<"Strlen is a command that will return the length of a string in a character \n";
	cout<<"array. The length in question is not the size of the entire array - it is  \n";
	cout<<"the length of the array from beginning to the end. For example: \n";
	cout<<"THIS IS A TEST \n";
	cout<<"The above, if declared in an array, would have a length of 14. It could be \n";
	cout<<"declared in an array with a length of 20. Strlen would return 14 - not 20. \n\n";

	cout<<"To use strlen: \n";
	cout<<"1. Declare a character array \n";
	cout<<"2. Set the array equal to a string, ie 'Jason'. \n";
   cout<<"3. Write 'cout<<strlen(array)' and that will output the length. \n\n";

	cout<<"Here is an example of strlen: \n\n";
   cout<<"char name[20] = {''Jason''};"<<endl;
	char name[20] = {"Jason"};
	cout<<name<<endl;
   cout<<"This name has "<<strlen(name)<<" letters. \n";

}
