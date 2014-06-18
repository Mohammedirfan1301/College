#include <iostream.h>
#include <conio.h>

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

//global variable
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
	cout<<"This will run the the strcpy function. \n";
}

void stringcharcopy(void)
{
	cout<<"This will run the strncpy function. \n";
}

void stringcompare(void)
{
	cout<<"This will run the strcmp function. \n";
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
