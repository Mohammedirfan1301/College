#include <iostream.h>
#include <iomanip.h>

main()
{
	int side;
	int a,b,c,d,e;
	int x = 1;

	cout<<"Welcome to the Square Program. \n";             //introduction
	cout<<"This program will ask you to enter the length of one side      \n";
	cout<<"of a square and it will output a square with sides of that length. \n";

	do{

	cout<<"\n\nPlease enter the length of the side. -> ";
	cin>>side;
	cout<<endl;

   d = side-2;     //d is for
	e = d + 1;      //setw

	for(a = side; a > 0; a--)
	{
		cout<<"*";

      for(b = d; b > 0; b--)
		{
			cout<<"*"<<setw(e)<<"*"<<endl;
		}

		cout<<"*";
	}

	cout<<"\n\nTo continue using the program, enter 1. To stop, enter 2. -> ";
	cin>>x;
	cout<<endl;

	}while(x==1);

	return 0;
}