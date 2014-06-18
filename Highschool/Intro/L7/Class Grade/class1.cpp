#include <iostream.h>

main()
{
	int x;

	cout<<"Welcome to the CLASS GRADE Program. \n";
	cout<<"This program will calculate the class \n";
	cout<<"grade average, invidivual grades and more! \n";
	cout<<endl;

	cout<<"Please input a numerical grade. ";
	cin>>x;
	cout<<endl;


	if((x<=100)&&(x>=97))
		cout<<"Letter Grade: A+";

	if((x<=96)&&(x>=93))
		cout<<"Letter Grade: A";

	if((x<=92)&&(x>=90))
		cout<<"Letter Grade: A-";

	if((x<=89)&&(x>=87))
		cout<<"Letter Grade: B+";

	if((x<=86)&&(x>=83))
		cout<<"Letter Grade: B";

	if((x<=82)&&(x>=80))
		cout<<"Letter Grade: B-";

	if((x<=79)&&(x>=77))
		cout<<"Letter Grade: C+";

	if((x<=76)&&(x>=73))
		cout<<"Letter Grade: C";

	if((x<=72)&&(x>=70))
		cout<<"Letter Grade: C-";

	if((x<=69)&&(x>=65))
		cout<<"Letter Grade: D";

	if((x<=64)&&(x>=0))
		cout<<"Letter Grade: F";

	cout<<endl;
	cout<<endl;
	cout<<"Thank You for using the CLASS GRADE Program. \n";

	return 0;
}
