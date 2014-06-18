#include <iostream.h>   //in/output
#include <iomanip.h>    //for set precision
#include <math.h>       //for pow/fabs/sqrt commands

main()
{
	double a,b,c,e;  //for the sides and calculations.
	int n;           //for the precision
	int d;           //for the switch command
	int x = 1;         //for the do/while loop

	cout<<"Welcome to the Pythagorean Theorem Program.           \n";    //the intro prompt
	cout<<"\nThis program allows you to use Pythagorean Theorem  \n";
	cout<<"to find the third side of a triangle when given the   \n";
	cout<<"other two sides (leg/leg or leg/hypotenuse).          \n";

	do{
	a = 0;         //resets the variables for rerunning the program.
	b = 0;         //this just insures that when the program is used for a second/third time
	e = 0;         //that the variables are equal to 0 and not equal to another number.
	n = 0;

	cout<<"\n\nTo use this program, type in the measure of the two sides. \n"; 
	cout<<"Please input the first side.       -> ";    //the first side
	cin>>a;
	cout<<"Please input the second side.      -> ";    //the second side
	cin>>b; 
	cout<<"Enter the precision of the answer. -> ";    //the precision.
	cin>>n;
	cout<<"\nIf you entered two legs, Press 1.           \n";   //explains what to do if the user enters two legs
	cout<<"If you entered a leg and a hypotenuse, Press 2. \n";   //explains what to do if a leg and hypotenuse is entered.
	cout<<"Enter your selection here. -> ";                       //tells the user to enter a number.
	cin>>d;
                       //this calculates if they enter 2 legs.
	a = pow(a,2);      //does a to the 2nd power
	b = pow(b,2);      //b to the second power
	c = a + b;         //adds a and b and puts the value of that in the c variable
	c = sqrt(c);       //squares the value of c for the final answer.
	
                       //this calculates if they enter a leg/hypotenuse
	e = a - b;         //since a/b have already been squared, this simply subtracts a and b.
	e = fabs(e);       //e could be neg (because 4-6 could be done as 6-4) so this finds the absolute value.
	e = sqrt(e);       //squares e for the final answer

	switch(d)
	{
		case 1:
				 cout<<"\nThe third side (hypotenuse) is: " << setprecision (n) << c << endl;     //the first possible outcome
				 break;
		case 2:
				 cout<<"\nThe third side (leg) is: " << setprecision (n) << e << endl;           //the second possible outcome
				 break;
		default:                                                         //if the user enters any other number for d, this is displayed.
				 cout<<"\nYou didn't follow directions!                \n";
				 cout<<"Please try again - make sure to enter 1 or 2.  \n";
				 break;
	}

	cout<<"\n\nYou can continue to use the program if you'd like. \n";  //allows user to rerun the program via a do/while loop.
	cout<<"Enter 1 to continue or 2 to quit. -> ";
	cin>>x;

	}while(x==1);

	cout<<"\nThank You for using the Pythagorean Theorem Program. \n";   //ending prompt
	return 0;
}
