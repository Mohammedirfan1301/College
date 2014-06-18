#include <iostream.h>
#include <conio.h>

int meanfunction(int num[]);
int medianfunction(int num[]);
int modefunction(int);
int orderfunction(int num[]);

main()
{
	int a = 0, b = 0, s = 0, x = 0; // a/b are for for the loop. s for the switch(). x for the do/while.
	int num[10];  						  // num[10] is an array with 10 numbers
	int mean = 0, median = 0, mode = 0;       //variables for the mean/median/etc

	do{
	a = 0, b = 1;

	cout<<"Welcome to the MMM & A/D Program. \n";
	cout<<"This program accepts 10 integer numbers in any order. \n";
	cout<<"It can then find the mean, median and mode of the list (MMM) \n";
	cout<<"and it can also sort the numbers in ascending or descending order (A/D). \n\n";

	for(a = 0; a < 10; a++)
	{
		cout<<"Please a number in the following space. (#"<<b<<") -> ";
		cin>>num[a];
		b++;
	}

	cout<<"\nNow that you have entered the ten numbers, what would you like to do? \n";
	cout<<"1. Find the mean of the list.         \n";
	cout<<"2. Find the median of the list.       \n";
	cout<<"3. Find the mode of the list.         \n";
	cout<<"4. Sort the list in ascending or descending order.  \n";

	do{
	cout<<"\nEnter your selection here. (ONLY the #) -> ";
	cin>>s;
	cout<<endl;
	}while(s != 1 && s != 2 && s != 3 && s !=4);

	switch(s)
	{
		case 1:
				mean = meanfunction(num);
				cout<<"The mean is "<<mean<<endl;
				break;

		case 2:
				median = medianfunction(num);
				cout<<"The median is "<<median<<endl;
				break;

		case 3:
				mode = modefunction(num);
				cout<<"The mode is "<<mode<<endl;
				break;

		case 4:
				orderfunction(num);
				break;

		default:
				cout<<"\nYou entered an incorrect number. \n";
				cout<<"Please try again. \n";
				break;
	}

	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	}while( (x != 1) && (x != 2) );

	clrscr();

	}while(x == 2);

	return 0;
}


int meanfunction(int num[])
{
	int a = 0, total = 0, mean = 0;

	for(a = 0; a < 10; a++)
	{
		total = total + num[a];
	}
    
    mean = total / 10;
    
	return mean;
}

int medianfunction(int num[])
{
	int a = 0, hold = 0, pass = 0, median = 0;

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

	return median;
}

int modefunction(int num[]);
{
   int a = 0, hold = 0, pass = 0;

	for(a = 0; a < 10; a++)
	{
		if(num[a+1] < num[a])
		{
			hold = num[a];
			num[a] = num[a+1];
			num[a+1] = hold;
		}
	}

	//now go through the list and if a number appears multiple times, add a '1' to a counter. if no numbers appear more then once (ie counter = 1)
   //the mode is none. otherwise its whatever number appears the most. and there COULD be multiply modes... D:

}

int orderfunction(int num[])
{
	int a = 0, b = 1, hold = 0, pass = 0, s = 0;

	cout<<"Do you want to put the numbers in ASCENDING or DESCENDING order? \n";
	cout<<"Enter 1 for ascending. Enter 2 for descending. -> ";
	cin>>s;
	cout<<endl;

	if(s == 1)
	{

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

		for(a = 0; a < 10; a++)
		{
			cout<<"#"<<b<<"\t"<<num[a]<<endl;
			b++;
		}
	}

	if(s == 2)
	{
		//sort the numbers in ascending order.
		for(pass = 0; pass < 10; pass++)
		{
			for(a = 0; a < 10; a++)
			{
				if(num[a+1] > num[a])
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

	return 0;
}


/*
======TEST======

	for(a=0; a<10; a++)
	{
		cout<<num[a]<<endl;
	}

*/
