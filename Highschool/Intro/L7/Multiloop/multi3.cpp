#include <iostream.h>
#include <math.h>

main()
{
	int x,y;
	int z;
	int num = 1;
	int counter=1000;

	cout<<"Welcome to the Multiple Program. \n";
	cout<<"This program can calculate all the multiples \n";  //intro prompt for the user.
	cout<<"for a number up to 1000. \n";
	cout<<endl;
	cout<<"Enter a number between 0 and 1000. ";
	cin>>x;
	cout<<"Enter a number for the multiple. (Between 1 and 1000) ";
	cin>>y;
	cout<<endl;
	cout<<"To use the program, press 1. ";
	cin>>num;
   cout<<endl;

	z = x * y;

	while(num==1)
	{
		cout<<x<<"\n ";
		cout<<z<<"\n ";
		counter=counter+z;
		cout<<z<<"\n ";
		cout<<"Enter 1 to continue or 0 exit. \n";   //user can cont. by entering 1 or exit by entering 0 or any other number except 1.
		cin>>num;
	}

	cout<<endl;
	cout<<"Thank you for using the Multiple Program.";	//lets the user know the program has ended.

	return 0;
}
