#include <iostream.h>
#include <conio.h>

void meanfunction(int num[]);
void medianfunction(int num[]);
void modefunction(int num []);
void orderfunction(int num[]);

main()
{
	int a = 0, b = 0, x = 0; 	// a/b are for for the loop. x for the do/while.
	int num[10];  					// num[10] is an array with 10 numbers

	do{
	a = 0, b = 1;

	cout<<"Welcome to the MMM & A/D Program. \n";
	cout<<"This program accepts 10 integer numbers in any order. \n";
	cout<<"It can then find the mean, median and mode of the list (MMM) \n";
	cout<<"and it can also sort the numbers in ascending or descending order (A/D). \n\n";
    
	for(a = 0; a < 10; a++)
	{
		cout<<"Please enter a number in the following space. (#"<<b<<") -> ";
		cin>>num[a];
		b++;
	}

	meanfunction(num);
	medianfunction(num);
	modefunction(num);
	orderfunction(num);

	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	}while( (x != 1) && (x != 2) );

	clrscr();

	}while(x == 2);

	return 0;
}


void meanfunction(int num[])
{
	int a = 0, total = 0, mean = 0;

	for(a = 0; a < 10; a++)
	{
		total = total + num[a];
	}
    
    mean = total / 10;

	 cout<<endl<<"The mean of the set of numbers is: "<<mean<<endl;
}

void medianfunction(int num[])
{
	int a = 0, hold = 0, pass = 0, mediantotal = 0, median = 0;

	//sort the numbers in ascending order.
	for(pass = 0; pass < 10; pass++)
	{
		for(a = 0; a < 10; a++)
		{
			if(num[a+1] < num[a])
			{
				hold = num[a];
				num[a] = num[a+1];
				num[a+1] = hold;
			}
		}
	}

	mediantotal = num[4] + num[5];
   median = mediantotal/2;

	cout<<"The median of the set of numbers is: "<<median<<endl;
}

void modefunction(int num[])
{
	int a = 0, hold = 0, pass = 0;      //sorting forloop
	int mode[10];
	int x = 0;

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

	 for(a = 0; a < 9; a++)
    {
		  if(num[a] == num[a+1])
        {
				mode[x] = num[a];
				x++;
		  }

	 }

	 if(x == 0)
    {
        cout<<"There is no mode for this set of integers. \n";
    }
    
	 if(x > 0)
    {
		  cout<<"The mode(s) for this set of numbers is: "<<endl<<endl;

			for(a = 0; a <= x; a++)
			{
				cout<<mode[x]<<endl;
			}
    }

    /*
    3 possible outcomes:
        
        no mode
        1 mode
		  multiple modes
        
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
			for(a = 0; a < 10; a++)
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
			for(a = 0; a < 10; a++)
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
