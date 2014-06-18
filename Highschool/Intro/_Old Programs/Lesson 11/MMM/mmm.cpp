#include <iostream.h>
#include <conio.h>

int mean(int num[10]);
/*
int mode(int num[10]);
int median(int num[10]);
int ascend(int num[10]);
int dscend(int num[10]);
*/

main()
{
	int a = 0, b = 0, c = 1, num[10], x = 0;  //a/b/c are used in for loops. num[10] is an array. x is for the do/while.
	int s = 0;  //for the switch
	int mean;

	do{
	a = 0, b = 0, c = 1;

	cout<<"Welcome to the MMM & A/D Program. \n";
	cout<<"This program accepts 10 integer numbers in any order. \n";
	cout<<"It can then find the mean, median and mode of the list (MMM) \n";
	cout<<"and it can also sort the numbers in ascending or descending order (A/D). \n\n";

	for(a = 0; a < 10; a++)
	{
		cout<<"Please enter ten numbers in the following space. (#"<<c<<") -> ";
		cin>>num[b];
		b += 1;
		c++;
	}

	b = 0;
	cout<<endl;

	cout<<"Now that you have entered the ten numbers, what would you like to do? \n";
	cout<<"1. Find the mean of the list.         \n";
	cout<<"2. Find the mode of the list.         \n";
	cout<<"3. Find the median of the list.       \n";
	cout<<"4. Sort the list in ascending order.  \n";
	cout<<"5. Sort the list in descending order. \n";

	cout<<"\nEnter your selection here. (ONLY the #) -> ";
	cin>>s;

	switch(s)
	{
		case 1:
				mean = mean(int num[10]);
				cout<<endl<<mean<<endl;
				break;

		case 2:
				cout<<"\nFind the Mode. \n";
				cout<<"UNDER CONSTRUCTION. \n";
				break;

		case 3:
				cout<<"\nFind the Median. \n";
				cout<<"UNDER CONSTRUCTION. \n";
				break;

		case 4:
				cout<<"\nFind the ascending order. \n";
				cout<<"UNDER CONSTRUCTION. \n";
				break;

		case 5:
				cout<<"\nFind the descending order. \n";
				cout<<"UNDER CONSTRUCTION. \n";
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


int mean(int num[10])
{
	int a = 0, total = 0, mean = 0;

	for(a = 0; a < 10; a++)
	{
		total =+ num[a];

		if(a == 10)
		{
			mean = total / a;
		}

	return mean;
}
