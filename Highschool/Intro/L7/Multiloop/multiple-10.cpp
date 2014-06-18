#include <iostream.h>
#include <math.h>
#include <iomanip.h>

main()
{
    int num = 1;    //for the main while loop.  
	long a;     //variables for 1st num
    long b;     //variable for the multiple
    long c;     //variable for the calculation while loop.

	cout<<"Welcome to the Multi-Loop Program.                    \n";
	cout<<"This program will prompt you to enter two numbers      \n";  //intro prompt for the user.
	cout<<"between 1 and 1000. It will then multiply the first   \n";
	cout<<"number by the second number up to or equal to 1000.   \n"<<endl;

	cout<<"To use the program, press 1. To exit, press 0. \n";
	cout<<"Enter the number choice here. -> ";
	cin>>num;
    cout<<endl;

	while(num==1)
	{   
        a = 1;
        b = 1;
        c = 1;                  
		cout<<"Enter the first number. (Between 1 and 1000) -> ";
		cin>>a;
		cout<<endl;
		cout<<"Enter a number for the multiple. (Between 1 and 1000) -> ";
		cin>>b;
		cout<<endl;
        cout<<setw(10)<<a<<setw(10)<<a<<endl;
		
        while(a >= 0 && a <= 1000 && b >= 1 && b <= 1000 && c >=0 && c <= 1000)
		{
            c = a * b;
            cout<<setw(10)<<a<<"*"<<b<<"="<<setw(7)<<c<<endl;
            a = c * b;
            cout<<setw(10)<<c<<"*"<<b<<"="<<setw(7)<<a<<endl;
		}   
		
        cout<<endl;
		cout<<"Enter 1 to continue or 0 exit. -> ";         //user can cont. by entering 1 or exit by entering 0 or any other number except 1.
		cin>>num;
		cout<<endl;
	}

	cout<<endl;
	cout<<"Thank you for using the Multi-Loop Program.";	//lets the user know the program has ended.

	return 0;
}
