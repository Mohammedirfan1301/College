#include <iostream.h>
#include <math.h>

main()
{
	int x,y;
	int z;
	int num=1;
	int counter=0;

	cout<<"Welcome to the Multiple Program. \n";
	cout<<"This program can calculate all the multiples \n";
	cout<<"for a number up to 1000. \n";
	cout<<endl;
	cout<<"Enter a number between 0 and 1000. ";
	cin>>x;
	cout<<"Enter a number for the multiple. (Between 1 and 1000) ";
	cin>>y;
	cout<<endl;

	while(num==1)
	{
		z=x*y;
		cout<<x;
		cout<<endl;
		cout<<x<<"*"<<y<<"="<<z;
		cout<<endl;

		cout<<"Enter 1 to continue or any other number to exit. \n";
		cin>>num;
      counter=counter+1;

	}

	cout<<endl;
	cout<<"Thank you for using the Multiple Program.";

	return 0;
}
