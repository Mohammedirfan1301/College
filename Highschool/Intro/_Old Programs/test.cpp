#include <iostream.h>
#include <iomanip.h>

main()
{
	float x;
	cout<<"Enter a number. -> ";
	cin>>x;
	cout<<endl;
	cout.setf(ios::showpoint);
	cout<<x<<endl;

	cout<<setiosflags(ios::fixed);
	cout.precision(2);
	cout<<x;

	return 0;
}