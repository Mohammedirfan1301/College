#include <iostream.h>
#include <conio.h>

float management(float);            			//management function
float hourly(float, float, float, float);       //hourly employee function
float commission(float, float);     			//commission worker function
float piece(float, float);          			//piece worker function

int main()
{
	int numemployee = 0, a = 0, b = 0, x = 2, y = 1;        //variables the # of employees, for loop (a), switch (b) and 
                                                            //do whiles (x = main do/while y = final print out)
	float hours = 0, holidayhours = 0, otholidayhours = 0, hourlyrate = 0;  //variables for the functions (hour related)
	float sales = 0, pieces = 0, pay = 0;                   //variables for the functions (comm/pieceworker/pay)
	float totalhours = 0, totalpay = 0;                     //variables for hours/pay - ALL employees that is.
    int numbertwo = 0;                                         //used to pause the screen temporary.
    
	do{
	cout<<"Welcome to the PAYROLL TRACKER 3000 (V2.0) \n";

	cout<<"This program will help your company calculate the earnings of your \n";
	cout<<"employees by having them enter the hours they have worked, the overtime \n";          //intro
	cout<<"and holiday hours they worked, and the amount of items or sales they made. \n";

	cout<<"\n*** A manager is required to enter the number of employees before \n";   //warning manager req.
	cout<<"the employees may enter their work information. *** \n";

	cout<<"\n!!MANAGEMENT ONLY!!\n";
	cout<<"How many employee's work at your company? \n";      //enter the # of employees for the for loop.
	cout<<"Enter the number. -> ";
	cin>>numemployee;
//	clrscr();
    system("cls");  //REMOVE WHEN DONE WITH DEV.

	for(a = numemployee; a > 0; a--)        //runs for # of employees needed.
	{
        cout<<"Welcome to the PAYROLL TRACKER 3000. \n";
		cout<<"This program is used for tracking the hours worked by employees. \n";

		cout<<"\nEmployees: Please enter your hours that you worked this week into \n";
		cout<<"this program. The program will then calculate out your pay, taking  \n";
		cout<<"into account holiday/overtime/etc. \n";
        cout<<"\nAlso, please be honest - failure to do so can result in punishment up to: \n";
        cout<<"***** TERMINATION OF EMPLOYMENT ***** \n";
        
		cout<<"\nBefore we get started, what is your pay code? You can get this \n";
		cout<<"information from your supervisor. Also refer to the following list: \n\n";

		cout<<"Pay Code 1 -> Management \n";
		cout<<"Pay Code 2 -> Hourly Employees \n";
		cout<<"Pay Code 3 -> Commission Employees \n";
		cout<<"Pay Code 4 -> Pieceworker \n";
        
		cout<<"\nPlease enter your pay code below. (Only enter the number) \n";
		cout<<"Enter your pay code. -> ";
		cin>>b;
        
        if( (b == 1) || (b == 2) || (b == 3) || (b == 4) )      //stops program from asking pointless questions 
                                                                //if an incorrect pay code is entered. (ie not 1-4)
        {
		  cout<<"\nAlso, how many hours did you work this week? \n";
		  cout<<"Enter the hours worked. -> ";
		  cin>>hours;
        }
        
		if(b == 2)
		{
			cout<<"\nDid you work any holidays? If so: \n";
			cout<<"Enter the number of holiday hours worked. -> ";
			cin>>holidayhours;
			
			if(holidayhours > 0)
				{
					cout<<"\nOf those holiday hours, how many were overtime? \n";
					cout<<"Enter the overtime holiday Hours worked. -> ";
					cin>>otholidayhours;
				}

			cout<<"\nWhat is your hourly rate of pay? \n";
			cout<<"Enter hourly rate of pay. -> $";
			cin>>hourlyrate;
		}
		
		if(b == 3)
		{
			cout<<"\nHow much did you do in sales this week? -> $";
			cin>>sales;
		}
        
		if(b == 4)
		{
			cout<<"\nHow many pieces did you make this week? -> ";
			cin>>pieces;
		}

			switch(b)
			{
				case 1:
					pay = management(hours);
					break;
				case 2:
					pay = hourly(hours, holidayhours, otholidayhours, hourlyrate);
					break;
				case 3:
					pay = commission(hours, sales);
					break;
				case 4:
					pay = piece(hours, pieces);
					break;
				default:
					cout<<"\nYou didn't enter a correct pay code. Either speak with your supervisor\n";
					cout<<"for the correct pay code or try again by continuing the program. \n";
					break;
			}

			totalhours += hours; //running total of all the hours for employees
			totalpay += pay;     //running total of all the pay for employees
			
			do{
			cout<<"\nWhen you are done viewing this screen, enter 1 to continue. -> ";   //simple question to keep the screen
			cin>>numbertwo;                                                              //on the pay information for employees.
            }while(numbertwo != 1);
            
		//	clrscr();
            system("cls");  //REMOVE WHEN DONE WITH DEV.
	}
    //this part just sums everything up and asks for a manager to check the hours or stop/rerun the program.
    cout<<"PAYROLL TRACKER 3000 (V2.0) \n";
    
    cout<<"\nYou are the last employee to enter their information. Please let your \n";
    cout<<"supervisor know so he or she may verify that this information is correct. \n";

	do{
	cout<<"\n!!MANAGEMENT ONLY!!\n";
	cout<<"To check the hours and pay of all employees, enter 1. \n";
	cout<<"If you do not want to check the hours and pay, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>y;

	if(y == 1)
	{
	   cout<<"\nThe total hours for all employees is: "<<totalhours<<". \n";
	   cout<<"The total pay for all employees is: $"<<totalpay<<". \n";
	}
	
	}while( (y != 1) && (y != 2) );
    
    totalhours = 0;
    totalpay = 0;
    
	do{
	cout<<"\n!!MANAGEMENT ONLY!! \n";
	cout<<"To stop the program, enter 1. \n";
	cout<<"To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	}while( (x != 1) && (x != 2) );

//	clrscr();
    system("cls");  //REMOVE WHEN DONE WITH DEV.

	}while(x == 2);

	return 0;
}

float management(float hours)
{
    float pay = 0, rate = 0, otrate = 0, othours = 0;
    
    if(hours <= 45)
    {
        pay = 900;
    }

    if(hours > 45)
    {
        rate = 900/45;
        otrate = rate * 1.5;
        othours = hours - 45;
        pay = 900 + (othours * otrate);
    }

        cout<<"\nYour pay is $"<<pay<<" dollars. \n";
        cout<<"You worked "<<hours<<" hours. \n";
        cout<<"You worked "<<othours<<" overtime hours. \n";

return pay;
}


float hourly(float hours, float holidayhours, float otholidayhours, float hourlyrate)
{
	float pay = 0, otrate = 0, holidayrate = 0, otholidayrate = 0, othours = 0, nonothours = 0;
    
    if(hours <= 40)
	{
		pay = hours * hourlyrate;     //pay for hours when 40 hours or less is worked.
	}

	if( (hours >= 40) && (holidayhours == 0) && (otholidayhours == 0) )
	{
        otrate = hourlyrate * 1.5;      //overtime rate of pay (1.5x normal rate)
		othours = hours - 40;           //overtime hours worked (hours worked - 40 = othours)
		nonothours = hours - othours;   //non overtime hours. used for calc. pay up to the 40 hours. then othours/otrate is used.
		
//              hours up to 40              overtime hours
		pay = (nonothours * hourlyrate) + (othours * otrate);
	}

	if( (hours >= 40) && (holidayhours > 0) && (otholidayhours == 0) )
	{
		otrate = hourlyrate * 1.5;       //overtime rate of pay (1.5x normal rate)
		holidayrate = hourlyrate * 2;    //holiday rate of pay (double normal rate)
		othours = hours - 40;            //overtime hours worked (hours worked - 40 = othours)
		nonothours = hours - othours - holidayhours;  //non overtime hours, only change is that holiday hours is also removed
		                                              //since they pay more then normal hours and overtime hours.
		                                              
//		          hours up to 40            overtime hours           holiday hours
		pay = (nonothours * hourlyrate) + (othours * otrate) + (holidayhours * holidayrate);
	}

	if( (hours >= 40) && (holidayhours > 0) && (otholidayhours > 0) )
	{
		otrate = hourlyrate * 1.5;         //overtime rate of pay (1.5x normal rate)
		holidayrate = hourlyrate * 2;      //holiday rate of pay (2x normal rate)
		otholidayrate = hourlyrate * 2.5;  //overtime holiday rate of pay (2.5x normal rate)
		othours = hours - 40;              //overtime hours worked (hours worked - 40 = othours)
		holidayhours = holidayhours - otholidayhours;                  //holidayhours without any overtime holiday hours included.
		nonothours = hours - othours - holidayhours - otholidayhours;  //hours paid at the normal rate. does not include:
                                                                       //overtime hours, holiday hours, overtime holiday hours
		
//		          hours up to 40            overtime hours          holiday hours                  overtime holiday hours
        pay = (nonothours * hourlyrate) + (othours * otrate) + (holidayhours * holidayrate); + (otholidayhours * otholidayrate);
	}

	cout<<"\nYour pay is $"<<pay<<" dollars. \n";
	cout<<"You worked "<<hours<<" hours. \n";
	cout<<"You worked "<<othours<<" overtime hours. \n";
	cout<<"You worked "<<holidayhours<<" holiday hours. \n";
	cout<<"You worked "<<otholidayhours<<" overtime holiday hours. \n";
    
    return pay;
}


float commission(float hours, float sales)
{
    float pay, commission;
    
    if(hours >= 40)
	{
        commission = sales * .09;
        pay = 250 + commission;
	}

	if(hours < 40)
	{
        commission = sales * .09;
        pay = commission;
    }

	cout<<"\nYour pay is $"<<pay<<" dollars. \n";
	cout<<"Your pay for commission is $"<<commission<<" dollars this week. \n";
	cout<<"You worked "<<hours<<" hours. \n";

    return pay;    
}

float piece(float hours, float pieces)
{
    float commission, pay;
    
    commission = pieces * 5;
	pay = 300 + commission;

	cout<<"\nYour pay is $"<<pay<<" dollars. \n";
	cout<<"You made "<<pieces<<" pieces this week. Great Job! \n";
    cout<<"You worked "<<hours<<" hours. \n";
    
    return pay;
}
