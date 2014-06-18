#include <iostream.h>

main()
{
    int numemployee, paycode;
    int a;
    int x = 1;
    float hrswork, pay, rate, otrate, othours;
    
    do{
	cout<<"Welcome to the PAYROLL TRACKER 5000. \n";
	
	cout<<"This program will help your company calculate the earnings of your \n";
	cout<<"employees by having them enter the hours they have worked, the overtime \n";
	cout<<"and holiday hours they worked, and the amount of items or sales they made. \n";
	
	cout<<"\n*** A manager is required to enter the number of employees before \n";
	cout<<"the employees may enter their work information. *** \n";
	
	cout<<"\nHow many employee's work at your company? \n";
	cout<<"Enter the number. -> ";
	cin>>numemployee;
	cout<<endl;
	cout<<"*********************************************************************\n";
	
	for(a = 1; a <= numemployee; a++)
	{
    
    paycode = 0;
    
         cout<<"\nWelcome to the Payroll Tracker 5000. \n";
         
         cout<<"Before we get started, what is your pay code? You can get this \n";
         cout<<"information from your supervisor. Also refer to the following list: \n\n";
         cout<<"Pay Code 1 -> Management \n";
         cout<<"Pay Code 2 -> Hourly Employees \n";
         cout<<"Pay Code 3 -> Commission Employees \n";
         cout<<"Pay Code 4 -> Pieceworker \n";
         
         cout<<"\nPlease enter your pay code below. (*Only* the number) \n";
         cout<<"Enter your pay code. -> ";
         cin>>paycode;
         cout<<endl;
         
         if(paycode == 1)
         {
             cout<<"Alright, now we can get started! \n";
             cout<<"How many hours did you work this week? -> ";
             cin>>hrswork;
             
             if(hrswork <= 45)
             {
                  pay = 900;
             }
             
             if(hrswork > 45)
             {
                 rate = 900/45;
                 otrate = rate * 1.5;
                 othours = hrswork - 45;
                 pay = 900 + (othours * otrate);
             }
             
             cout<<"\nYour pay is $"<<pay<<"dollars. \n";
             cout<<"Note that you worked "<<hrswork<<"hours and of that \n";
             cout<<othours<<" hours was overtime. \n";        
         }
         
         if(paycode == 2)
         {
             cout<<"Test 2";        
         }  
         
         if(paycode == 3)
         {
             cout<<"Test 3";       
         }  
         
         if(paycode == 4)
         {
             cout<<"Test 4";       
         }
             
         if(paycode >= 0 || <=5)
         {
             cout<<"You did not enter a valid number; please try again. \n";
         }  
    }
	
	cout<<"To rerun this program, simply enter 1 below. To exit, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	cout<<endl;
	
	}while(x == 1);
	
	return 0;
}

/*
Notes

Management overtime is equal to
900/45 = 20 an hour
say they work 5 hours over 45 (so 50)
20 x 1.5 = 30
30 x 5 = 150
thus total amount would be
1050 dollars

http://www.blr.com/compensationtips/overtime-calculation

*/
