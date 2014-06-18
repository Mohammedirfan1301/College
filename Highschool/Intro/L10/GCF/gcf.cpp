#include <iostream.h>

int gcf(int);

main()
{
	int x = 2,a,b;

	do{

	cout<<"Welcome to the Greatest Common Factor (GCF) Program. \n";
	cout<<"This program will accept two integers and then find the GCF \n";
	cout<<"of the two numbers. \n";

	cout<<"\nPlease enter two integers. \n";
	cout<<"First Integer. -> ";
	cin>>a;
	cout<<"Second Integer. -> ";
	cin>>b;

	cout<<gcf(a,b);

	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	cout<<endl;
	//clrscr();
	}while((x != 1) && (x != 2));

	}while(x==2);

	return 0;
}

int gcf (int a, int b)
{
	cout<<"THIS IS A TEST OF THE GCF SYSTEM. \n";
	cout<<a<<endl;
	cout<<b<<endl;

	return 0;
}