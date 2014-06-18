#include <iostream.h>

main()
{
	int x;
	int y = 1;
	int counter=0;

	cout<<"Welcome to the CLASS GRADE Program. \n";
	cout<<"This program will calculate the class \n";
	cout<<"grade average, invidivual grades and more! \n";
	cout<<endl;

	cout<<"Which calculation do you need to do? \n";
	cout<<endl;
	cout<<"Numerical Grade to Letter Grade \n";
	cout<<"If so, press 0. \n";
	cout<<"Letter Grade to Numerical Range \n";
	cout<<"If so, press 1. \n";
	cin>>y;
	cout<<endl;

	while(y==0)
	{
		cout<<"Please input a numerical grade. ";
		cin>>x;
		cout<<endl;


		if((x<=100)&&(x>=97))
		cout<<"Letter Grade: A+ \n";

		if((x<=96)&&(x>=93))
		cout<<"Letter Grade: A \n";

		if((x<=92)&&(x>=90))
		cout<<"Letter Grade: A- \n";

		if((x<=89)&&(x>=87))
		cout<<"Letter Grade: B+ \n";

		if((x<=86)&&(x>=83))
		cout<<"Letter Grade: B \n";

		if((x<=82)&&(x>=80))
		cout<<"Letter Grade: B- \n";

		if((x<=79)&&(x>=77))
		cout<<"Letter Grade: C+ \n";

		if((x<=76)&&(x>=73))
		cout<<"Letter Grade: C \n";

		if((x<=72)&&(x>=70))
		cout<<"Letter Grade: C- \n";

		if((x<=69)&&(x>=65))
		cout<<"Letter Grade: D \n";

		if((x<=64)&&(x>=0))
		cout<<"Letter Grade: F \n";

		if(x>=65)
			cout<<"You Passed!";
		else
			cout<<"You Failed!";

		cout<<endl;
		cout<<"Press 0 to continue, 2 to exit.";
		cin>>y;
      cout<<endl;
		counter=counter+1;
	}

	while(y==1)
	{
		cout<<"Sorry. This section not yet completed. ";
		cin>>y;
	}
  	cout<<endl;
	cout<<"Thank You for using the CLASS GRADE Program. \n";

	return 0;
}
