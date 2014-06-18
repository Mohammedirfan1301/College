#include <iostream.h>

int main()
{

	double x;                                                 //Declares variable "x", for the National Debt to be entered in.
	cout<<"Please enter the National Debt. \n";               //Asks the user for the National Debt
	cout<<"(The NATIONAL DEBT is: $14,713,343,820,018)\n";    //lets the user know the National Debt (week old but still accuarate to the trillions/billions? (hopefully D:)
	cout.precision(16);                                       //sets precision (number of decimal places) to 16. Allows the full National Debt to be entered.
	 cin>>x;                                                  //accepts the National Debt and stores it in variable 'x'
	cout<<endl;                                               //ends line to make program look nice
	cout<<"The National Debt is: \t";                         //Prompts user
	cout<<x;                                                  //Displays National Debt that had been entered by the user

	return 0;                                                 //ends program
}
