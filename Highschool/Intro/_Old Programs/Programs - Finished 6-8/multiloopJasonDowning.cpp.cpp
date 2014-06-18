#include <iostream.h>
#include <math.h>
#include <iomanip.h>

main()
{
    int num = 1;    //variable for the first while loop   
	float a;        //variable for the 1st number
    float b;        //variable for the multiple

	cout<<"Welcome to the Multi-Loop Program.                    \n";          //intro prompt
	cout<<"This program will prompt you to enter two numbers     \n";  
	cout<<"between 1 and 1000. It will then multiply the first   \n";
	cout<<"number by the second number up to or equal to 1000.   \n\n";

	cout<<"To use the program, press 1. To exit, press 0. \n";             //enter the program by entering 1
	cout<<"Enter the number choice here. -> ";                             //later allows exiting by entering 0.
	cin>>num;

	while(num==1)
	{   
        a = 1;   //if a user uses the program multiple times, this resets the values.
        b = 1;
                         
		cout<<"\nEnter the first number. (Between 1 and 1000) -> ";       
		cin>>a;                                                               //asks for the 1st number/the multiple
		cout<<"\nEnter a number for the multiple. (Between 1 and 1000) -> ";
		cin>>b;
		cout<<endl;
        
        if( (a>=1) && (a<=1000) && (b>=1) && (b<=1000) )
        {
        
            cout<<setw(10)<<a<<setw(13)<<a<<endl;           //displays a
        
            while(a <= 1000)
            {
                 cout<<setw(10)<<a<<"*"<<b<<"=";            //displays the first part, a*b=
                 a *= b;                                    //this means a = a * b
                 cout<<setw(10)<<a<<endl;                   //displays what a ends up equaling
            }                                                      
		
        }
        
        else
            cout<<"You entered a number too large or too small. Please try again. \n";
                                                                 
		cout<<"\nEnter 1 to continue or 0 exit. -> ";         //lets the user continue or exit the program.
		cin>>num;
		cout<<endl;
	}

	cout<<"\nThank you for using the Multi-Loop Program.";	//lets user know the program ended.

	return 0;
}
