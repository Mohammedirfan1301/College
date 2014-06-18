#include <iostream.h>
#include <math.h>
#include <conio.h>

void gcf(int a, int b);

main()
{
	int x = 2, int1, int2;

	do{

	cout<<"Welcome to the Greatest Common Factor (GCF) Program. \n";
	cout<<"This program will accept two integers and then find the GCF \n";    //intro
	cout<<"of the two numbers. \n";

	cout<<"\nPlease enter two integers. \n";
	cout<<"First Integer.  -> ";        //first number
	cin>>int1;
	cout<<"Second Integer. -> ";        //second number
	cin>>int2;

	gcf(int1,int2);        //sends the two values, doesn't return them.

    do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. -> ";
	cin>>x;
	cout<<endl;
//	clrscr();
    system("cls");  //remove this when done with dev.
	}while((x != 1) && (x != 2)); //makes it so only 1 or 2 can be entered - cannot enter 3 to quit for instance.

	}while(x==2);

	return 0;
}

void gcf (int a, int b)
{
    int remainder;
    
    do{
    remainder = a % b;       
    a = b;                   
    b = remainder;
    }while(remainder != 0);  //runs until the remainder is equal to 0.
    
    cout<<"\nThe GCF is "<<a<<endl;
}

/*
int1 = 18
int2 = 24
GCF = 6

prime factors of 18 = 2 x 3 x 3
prime factors of 24 = 2 x 2 x 2 x 3
2 x 3 = 6

example of do/while

24 % 18 = 6
so 6 is the remainder
24 = 18, now a is 18.
18 = 6, now b is 6

18 % 6 = 0
so the GCF is 6.

*/
