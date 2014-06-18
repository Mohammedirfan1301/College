#include <iostream.h>   //in/output
#include <conio.h>      //clrscr();

void meanfunction(int num[]);      //the function for mean
void medianfunction(int num[]);    //the function for median
void modefunction(int num []);     //the function for mode
void orderfunction(int num[]);     //the function for ascending or descending order

main()
{
	int a = 0, b = 0, x = 0; 	// a/b are for for the loop. x for the do/while.
	int num[10];  					// num[10] is an array with 10 numbers

	do{
	a = 0, b = 1;

	//introduction prompt
	cout<<"Welcome to the MMM & A/D Program. \n";
	cout<<"This program accepts 10 integer numbers in any order. \n";
	cout<<"It can then find the mean, median and mode of the list (MMM) \n";
	cout<<"and it can also sort the numbers in ascending or descending order (A/D). \n\n";

	//loops through asking the user for 10 numbers and displays which number they are on (b does this)
	for(a = 0; a < 10; a++)
	{
		cout<<"Please enter a number in the following space. (#"<<b<<") -> ";
		cin>>num[a];
		b++;
	}

	meanfunction(num);        //each of these calls up its function (ie mean calls up the mean function)
	medianfunction(num);
	modefunction(num);
	orderfunction(num);

	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	}while( (x != 1) && (x != 2) );    //only 1 and 2 can be entered.

	clrscr();   //clears the screen

	}while(x == 2);

	return 0;
}


void meanfunction(int num[])
{
	int a = 0;
	float total = 0, mean = 0;

	//for the mean, just add all the numbers
	for(a = 0; a < 10; a++)
	{
		total = total + num[a];
	}

	//and divide by the total number of numbers (which is 10)
	mean = total / 10;

	cout<<endl<<"The mean of the set of numbers is: "<<mean<<endl;
}

void medianfunction(int num[])
{
	int a = 0, hold = 0, pass = 0;
	float mediantotal = 0, median = 0;

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

	//now that the numbers are in order, 4/5 is the median. Simply add and divide by 2.
	mediantotal = num[4] + num[5];
   median = mediantotal/2;

	cout<<"The median of the set of numbers is: "<<median<<endl;
}

void modefunction(int num[])
{
	int a = 0, b = 0, freq = 0, test = 0;
	int mode = 0, x = 0;

	for(a = 1; a < 10; a++)
	{
		test = num[a];
		freq = 0;

			for(b = 0; b < 9; b++)
			{
				if(num[a] == num[a+1])
				{
					mode = num[a];
					freq++;
				}
			}

		if(

	cout<<"The mode of the set of numbers is: "<<mode<<endl;
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

http://www.daniweb.com/software-development/cpp/threads/352878

/*
======TEST======

	for(a=0; a<10; a++)
	{
		cout<<num[a]<<endl;
	}

*/
