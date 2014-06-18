#include <iostream.h>
#include <conio.h>

main()
{
	char string[50];

	cout<<"Welcome to the Initials Program. \n";
	cout<<"This program allows you to enter your full name and \n";
	cout<<"the program will print out your initials. \n";

	cout<<"Enter your full name in the spaces provided below: \n";
	cin>>string;
	cout<<" ";
	cin>>string;
	cout<<" ";
	cin>>string;
   cout<<" \0";

   cout<<"Your name is: "<<string;

	return 0;
}