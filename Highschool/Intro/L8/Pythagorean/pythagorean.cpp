#include <iostream.h>
#include <math.h>

main()
{
	int a,b,c,d,e;
	int x=1;

	cout<<"Welcome to the Pythagorean Theorem Program.         \n";
	cout<<"\nThis program allows you to use Pythagorean Theorem  \n";
	cout<<"to find the third side of a triangle when given the \n";
	cout<<"other two sides (leg/leg or leg/hypotenuse).        \n";

	do{
	a=0;
	b=0;
	e=0;

	cout<<"\nTo use this program, type in the measure of the two sides. \n";
	cout<<"Please input the first side. -> ";
	cin>>a;
	cout<<"Please input the second side -> ";
	cin>>b;
	cout<<"\nIf you entered two legs, Press 1. \n";
	cout<<"If you entered a leg and a hypotenuse, Press 2. \n";
	cout<<"Enter your selection here. -> ";
	cin>>d;

	a = pow(a,2);
	b = pow(b,2);
	c = a + b;     //this calculates if they enter 2 legs.
	c = sqrt(c);

	e = a - b;
	e = fabs(e);    //this calculates if they enter a leg/hypotenuse
	e = sqrt(e);

	switch(d)
	{
		case 1:
				 cout<<"\nThe third side (hypotenuse) is: "<<c<<"\n";
				 break;
		case 2:
				 cout<<"\nThe third side (leg) is: "<<e<<"\n";
				 break;
		default:
				 cout<<"\nYou didn't follow directions!                \n";
				 cout<<"Please try again - make sure to enter 1 or 2.  \n";
				 break;
	}

	cout<<"\nYou can continue to use the program if you'd like. Simply \n";
	cout<<"Enter 1 to continue or 2 to quit. -> ";
	cin>>x;

	}while(x==1);

	cout<<"\nThank You for using the Pythagorean Theorem Program. \n";
	return 0;
}
