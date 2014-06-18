#include <iostream.h>
#include <conio.h>

void convert (char letter);

main()
{
	int x = 2;   //for the do/while
	char b;      //to accept letter input

	do{
	cout<<"Welcome to the Letter Converter Program. \n";
	cout<<"This program will accept a letter and convert it between \n";  //introduction
	cout<<"uppercase and lower case. \n";

	cout<<"\nEnter a letter to convert. -> ";
	cin>>b;

	convert(b);    //sends b to the function convert, doesn't return.

	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. -> ";
	cin>>x;
	cout<<endl;
	}while((x != 1) && (x != 2)); //makes it so only 1 or 2 can be entered - cannot enter 3 to quit for instance.

	clrscr();

	}while(x==2);

	return 0;
}

void convert (char letter)
{
	//The letter must be between 65-90 and 97-122 to be 'a to z'.
	//Which is why 91-96 is not allowed.

	if(letter >= 65 && letter <= 122)
	{

		//uppercase to lower case.
		if(letter >= 65 && letter <= 90)
		{
			letter = letter + 32;
			cout<<endl<<letter<<endl;
			letter = letter - 32; //without this it seems to convert it back to uppercase, but this fixes that issue.
		}

        //for 91 to 96, which are not letters.
		if(letter >=91 && letter <= 96)
		{
			cout<<"\nYou didn't enter a letter; try again. \n";
		}

		//lower case to upper case.
		if(letter >= 97 && letter <= 122)
		{
			letter = letter - 32;
			cout<<endl<<letter<<endl;
		}

	}
	else    //if the user enters something else that isn't letter (65-90 or 97-122), the program prints this.
	{
		cout<<"\nYou didn't enter a letter; try again. \n";
	}
}
