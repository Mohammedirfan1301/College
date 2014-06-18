#include <iostream.h>
#include <math.h>
#include <iomanip.h>

main()
{
	int a,b;        //variables for 1st num + multiple
	int num = 1;    //for the while loop.

	cout<<"Welcome to the Multi-Loop Program.                    \n";
	cout<<"This program will allow you to enter two numbers      \n";  //intro prompt for the user.
	cout<<"between 1 and 1000. It will then multiply the first   \n";
	cout<<"number by the second number up to or equal to 1000.   \n"<<endl;

	cout<<"To use the program, press 1. To exit, press 0. \n";
	cout<<"Enter the number choice here. -> ";
	cin>>num;
   cout<<endl;

	while(num==1)
	{

		cout<<"Enter the first number (between 0 and 1000). -> ";
		cin>>a;
		cout<<endl;
		cout<<"Enter a number for the multiple. (Between 1 and 1000) -> ";
		cin>>b;
		cout<<endl;

		while((a>1)&&(a<1000)&&(b>1)&&(b<1000))
		{
			cout<<a<<"="<<b;
		}

		cout<<"Enter 1 to continue or 0 exit. -> ";         //user can cont. by entering 1 or exit by entering 0 or any other number except 1.
		cin>>num;
		cout<<endl;

	}

	cout<<endl;
	cout<<"Thank you for using the Multi-Loop Program.";	//lets the user know the program has ended.

	return 0;
}
