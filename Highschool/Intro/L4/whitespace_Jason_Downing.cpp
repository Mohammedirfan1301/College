#include <iostream.h>      //header file for input-output
#include <iomanip.h>       //header file for input-output manipulator (used fro setw())

int main()
{
	char x;                                               //declares variable 'char'. should only use 1 character due to the nature of char.
	cout<<"Welcome to the CHARACTER PROGRAM.";
	cout<<"Please enter any character on the keyboard.\n";         //the prompt for the prompt. explains everything for new people.
	cout<<"(This program will construct a picture out of \n";
	cout<<"the symbol/character you enter into the program.) \n";
	cout<<endl;
	cin>>x;
	cout<<endl;
	cout<<x<<x<<x<<x<<x<<x<<x<<x<<x<<setw(7)<<x<<x<<x<<setw(10)<<x<<setw(10)<<x;                       //the annoying part. just a bunch of setw() and
	cout<<endl;                                                                                        // a bunch of endl, along with displaying the
	cout<<x<<setw(8)<<x<<setw(5)<<x<<setw(4)<<setw(6)<<x<<setw(7)<<x<<x<<x<<setw(8)<<x<<setw(2)<<x;    //character entered.
	cout<<endl;
	cout<<x<<setw(8)<<x<<setw(4)<<x<<setw(3)<<setw(8)<<x<<setw(5)<<x<<x<<x<<x<<x<<setw(6)<<x<<setw(4)<<x;
	cout<<endl;
	cout<<x<<setw(8)<<x<<setw(4)<<x<<setw(3)<<setw(8)<<x<<setw(7)<<x<<setw(7)<<x<<setw(6)<<x;
	cout<<endl;
	cout<<x<<setw(8)<<x<<setw(4)<<x<<setw(3)<<setw(8)<<x<<setw(7)<<x<<setw(6)<<x<<setw(8)<<x;
	cout<<endl;
	cout<<x<<setw(8)<<x<<setw(4)<<x<<setw(3)<<setw(8)<<x<<setw(7)<<x<<setw(7)<<x<<setw(6)<<x;
	cout<<endl;
	cout<<x<<setw(8)<<x<<setw(4)<<x<<setw(3)<<setw(8)<<x<<setw(7)<<x<<setw(8)<<x<<setw(4)<<x;
	cout<<endl;
	cout<<x<<setw(8)<<x<<setw(5)<<x<<setw(4)<<setw(6)<<x<<setw(8)<<x<<setw(9)<<x<<setw(2)<<x;
	cout<<endl;
	cout<<x<<x<<x<<x<<x<<x<<x<<x<<x<<setw(7)<<x<<x<<x<<setw(10)<<x<<setw(10)<<x;
	cout<<endl;
	cout<<endl;
	cout<<"Thank You for using the CHARACTER PROGRAM.\n";        //Lets the user know the program is DONE.


	return 0;
}