#include <iostream.h>
#include <conio.h>

void stringcopy(void);
//void stringcharcopy(void);
//void stringcompare(void);
//void stringcharcompare(void);
//void stringmerge(void);
//void stringcharmerge(void);
//void stringlength(void);

main()
{
	int x = 1, stringmenu = 0;

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

	switch(stringmenu)
	{
		case 1:
			stringcopy(void);
			break;

		case 2:
			cout<<"This will run the strncpy function \n";
			break;

		case 3:
			cout<<"This will run the strcmp function \n";
			break;

		case 4:
			cout<<"This will run the strncmp function \n";
			break;

		case 5:
			cout<<"This will run the strcat function \n";
			break;

		case 6:
			cout<<"This will run the the strncat function \n";
			break;

		case 7:
			cout<<"This will run the strlen function \n";
			break;

		default:
			cout<<"This is not a valid option! \n";
			cout<<"Choose again! \n";
         break;
	}

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

void stringcopy(void);
{
   cout<<"Stringcopy will

	return 0;
}
