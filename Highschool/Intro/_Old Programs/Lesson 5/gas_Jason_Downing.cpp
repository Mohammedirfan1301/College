#include <iostream.h>

main()
{
	double c,m;

	cout<<"Welcome to the CHEAP GAS PROGRAM. \n";
	cout<<"Please enter the price of gas at Mobil \n";
	cout<<"and Citgo. This program can tell you \n";
	cout<<"which gas station to go to so you save money! \n";
	cout<<endl;
	cout<<"Enter the price of gas at Citgo. \t";
	cin>>c;
	cout<<endl;
	cout<<"Enter the price of gas at Mobil. \t";
	cin>>m;
	cout<<endl;

	if (c<m)
		cout<<"Citgo is cheaper than Mobil. \n";
	if (m<c)
		cout<<"Mobil is cheaper than Citgo. \n";
	if (c==m)
    {
		cout<<"There is no difference. Go to either Gas Station \n";
		cout<<"(Why did you even use this program?) \n";
    }

	cout<<endl;
	cout<<"Thank you for using the CHEAP GAS PROGRAM. \n";

	return 0;
}
