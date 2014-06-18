#include <iostream.h>   //input and output
#include <iomanip.h>    //setw
#include <conio.h>      //clrscr();

void meanfunction(int num[]);       //mean
void medianfunction(int num[]);     //median
void modefunction(int num []);      //mode
void orderfunction(int num[]);      //two part: ascending order or descending order

main()
{
	int a = 0, b = 0, x = 0; 	// a/b are for for the loop. x for the do/while.
	int num[10];  				// num[10] is an array with 10 numbers (0-9)

	do{
	a = 0, b = 1;

    //introduction prompt
	cout<<"Welcome to the MMM & A/D Program. \n";
	cout<<"This program accepts 10 integer numbers in any order. \n";
	cout<<"It can then find the mean, median and mode of the list (MMM) \n";
	cout<<"and it can also sort the numbers in ascending or descending order (A/D). \n\n";
    
	for(a = 0; a < 10; a++)
	{
		cout<<"Please enter a number in the following space. (#"<<setw(2)<<b<<") -> ";
		cin>>num[a];
		b++;
	}

	meanfunction(num);     //function for the mean
	medianfunction(num);   //function for the median
	modefunction(num);     //function for the mode
	orderfunction(num);    //function for ascending/descending order

	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	}while( (x != 1) && (x != 2) );

//	clrscr();
    system("cls");  //remove when done with dev.

	}while(x == 2);

	return 0;
}


void meanfunction(int num[])
{
	int a = 0;
    float total = 0, mean = 0;

    //adds each number in num array to 'total'
	for(a = 0; a < 10; a++)
	{
		total = total + num[a];
	}
    
    //which is then divided by the total number of numbers (ie 10)
    mean = total / 10;

    cout<<endl<<"The mean of the set of numbers is: "<<mean<<endl;
}

void medianfunction(int num[])
{
	int a = 0, hold = 0, pass = 0;
    float mediantotal = 0, median = 0;

	//the numbers are first sorted into ascending order
	for(pass = 0; pass < 10; pass++)
	{
		for(a = 0; a < 9; a++)
		{
			if(num[a+1] < num[a])
			{
				hold = num[a];
				num[a] = num[a+1];
				num[a+1] = hold;
			}
		}
	}

    //which makes numbers 5/6 out of 10 the median.
    //but because arrays start at 0, 4/5 are them middle
	mediantotal = num[4] + num[5];
    median = mediantotal/2;

	cout<<"The median of the set of numbers is: "<<median<<endl;
}

void modefunction(int num[])
{
	int a = 0, hold = 0, pass = 0;      //sorting for loop
	int mode, x = 0;   //checks if there's a mode
    
    //sorts the numbers in ascending order
	for(pass = 1; pass < 10; pass++)
	{
		for(a = 0; a < 9; a++)
		{
			if(num[a] > num[a+1])
			{
				hold = num[a];
				num[a] = num[a+1];
				num[a+1] = hold;
			}
		}
	}

    //checks to see if any numbers are equal to each other
	for(a = 0; a < 9; a++)
    {
	    if(num[a] == num[a+1])
        {
            mode = num[a];
			x++;
	    }

	}
	 
	//if x is greater than 1, there's either multiple modes or one number appears several times
	if(x > 1)
	{
            
    }
            

    //if x equals 0, no numbers are equal so there is no mode
    if(x == 0)
    {
        cout<<"There is no mode for this set of numbers. \n";
    }
    
    //if x is greater then 0, then there is at least one mode.
	if(x > 0)
    {
        //simple: one number is equal and must be the mode.
        if(x == 1)
        {
            cout<<"The mode of this set of numbers is: "<<mode<<endl;
        }
        
        //more complex: there are multiple numbers equal
        if(x > 1)
        {
                
        }

    }
	
    /*
    3 possible outcomes:
        
        If nothing appears more than once = NO MODE
        If one number appears the most = ONE MODE
		If several numbers appear the most and appear the same amount = MULTIPLE MODES
        
	 */
    
    cout<<endl;
}

void orderfunction(int num[])
{
	int a = 0, b = 1, hold = 0, pass = 0, x = 0;
    
	do{
	cout<<"Do you want to put the numbers in ASCENDING or DESCENDING order? \n";
	cout<<"Enter 1 for ascending. Enter 2 for descending. -> ";
	cin>>x;
	cout<<endl;
	}while(x != 1 && x != 2);

	if(x == 1)
	{

		//sort the numbers in ascending order.
        for(pass = 1; pass < 10; pass++)
        {
            for(a = 0; a < 9; a++)
			{
                if(num[a] > num[a+1])
				{
				    hold = num[a];
					num[a] = num[a+1];
					num[a+1] = hold;
				}
			}
		}

		for(a = 0; a < 10; a++)
		{
            cout<<"#"<<b<<"\t"<<num[a]<<endl;
			b++;
		}
	}

	if(x == 2)
	{
		//sort the numbers in descending order.
        for(pass = 1; pass < 10; pass++)
		{
            for(a = 0; a < 9; a++)
			{
				if(num[a] < num[a+1])
				{
				    hold = num[a];
					num[a] = num[a+1];
					num[a+1] = hold;
				}
			}
		}

        for(a = 0; a < 10; a++)
		{
            cout<<"#"<<b<<"\t"<<num[a]<<endl;
			b++;
		}
	}
	
	 cout<<endl;

}


/*
======TEST======

	for(a=0; a<10; a++)
	{
		cout<<num[a]<<endl;
	}

*/
