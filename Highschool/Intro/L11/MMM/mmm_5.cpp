#include <iostream.h>
#include <conio.h>

int meanfunction(int num[]);
int medianfunction(int num[]);
void modefunction(int num []);
int orderfunction(int num[]);

main()
{
	int a = 0, b = 0, s = 0, x = 0; // a/b are for for the loop. s for the switch(). x for the do/while.
	int num[10];  						  // num[10] is an array with 10 numbers
	int mean = 0, median = 0;       //variables for the mean/median/etc

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
    
    do{
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
				modefunction(num);
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
    cout<<"\nTo clear the numbers, enter 1. To continue calculations enter 2. \n";
    cout<<"Enter your selection. -> ";
    cin>>x;
    system("cls");
    }while( (x != 1) && (x != 2) );
    
    }while(x ==2);
    
	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	}while( (x != 1) && (x != 2) );

//	clrscr();
    system("cls");

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

void modefunction(int num[])
{
    int a = 0, hold = 0, pass = 0;      //sorting forloop
    int count = 0, mode = 0;            //checking for mode forloop
    
	for(a = 0; a < 10; a++)
	{
		if(num[a+1] < num[a])
		{
			hold = num[a];
			num[a] = num[a+1];
			num[a+1] = hold;
		}
	}
	
	for(a=0; a<10; a++)
	{
		cout<<num[a]<<endl;
	}

    
/*    
    for(a = 0; a < 9; a++)
    {
        if(num[a] == num[a+1])
        {
            mode = num[a];
            count++;
        }
        
        if(counter >
        
    }

    if(mode == 0)
    {
        cout<<"There is no mode for this set of integers. \n";
    }
    
    if(mode > 0)
    {
        cout<<"The mode for this set of numbers is: "<<mode<<endl;
    }

    /*
    3 possible outcomes:
        
        no mode
        1 mode
        multiple modes
        
    */

}

int orderfunction(int num[])
{
	int a = 0, b = 1, hold = 0, pass = 0, s = 0;
    
    do{
	cout<<"Do you want to put the numbers in ASCENDING or DESCENDING order? \n";
	cout<<"Enter 1 for ascending. Enter 2 for descending. -> ";
	cin>>s;
	cout<<endl;
    }while(s != 1 && s != 2);
    
	if(s == 1)
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

	if(s == 2)
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
    
	return 0;
}


/*
======TEST======

	for(a=0; a<10; a++)
	{
		cout<<num[a]<<endl;
	}

*/
