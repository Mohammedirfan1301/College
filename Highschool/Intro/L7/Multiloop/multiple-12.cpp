#include <iostream.h>
#include <math.h>
#include <iomanip.h>

main()
{
    int num = 1;    
	long a;     
    long b;     
    long c;     

	cout<<"Welcome to the Multi-Loop Program.                    \n";
	cout<<"This program will prompt you to enter two numbers      \n";  
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

        while(c <= 1000)
        {
             c = a * b;
             a = c;
             cout<<setw(10)<<a<<"*"<<b<<"="<<setw(7)<<c<<endl;
        }                                                      
		                                                         
        cout<<endl;
		cout<<"Enter 1 to continue or 0 exit. -> ";         
		cin>>num;
		cout<<endl;
	}

	cout<<endl;
	cout<<"Thank you for using the Multi-Loop Program.";	

	return 0;
}
