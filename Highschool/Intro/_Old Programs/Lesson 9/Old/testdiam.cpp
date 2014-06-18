#include <iostream.h>
#include <math.h>

main()
{
	int a,b;
	char z;

	cout<<"TEST PROGRAM V1.00 \n";
	cout<<"Enter a char -> ";
	cin>>z;
	cout<<endl;

	for(a=0; a<9; a++)
	{
		for(b=0; (4-a); b++)
		{
			cout<<" ";
		}

		cout<<z;
	}

	cout<<endl;
	cout<<"\nThanks for using TEST PROGRAM V1.00";

	return 0;
}
