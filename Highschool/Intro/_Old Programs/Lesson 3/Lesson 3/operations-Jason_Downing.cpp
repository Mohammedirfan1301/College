#include <iostream.h>       //makes use of the input/output header file to use the keyboard.

int main()
{
    float num1, num2, num3, sum, diff, prod, quot, average;             //declares the variables needed for the program.
    cout<<"Hello. Welcome to the OPERATIONS program. \n";               //First prompt/text for the user to read.
    cout<<"Please enter three numbers to use this program.\n";          //Asks for the user to enter three numbers.
    cout<<"(This program will calculate the sum, difference, \n";       //Explains program to the user.
	 cout<<"product and quotient of the first two numbers. \n";          //continues explaining program (separate line to make program look nice).
	 cout<<"The program will then calculate the average of all three numbers.) \n";            //final explanation.
    
    cout<<endl;                                                                //ends the line (make program look nice)
    
	 cout<<"Please enter the first number.\t";              //first prompt, asks for user to enter first number.
	 cin>>num1;                                             //stores number in the variable num1.
	 cout<<"Please enter the second number.\t";             //second propmt, asks for another number.
	 cin>>num2;                                             //stores 2nd number in variable num2
	 cout<<"Please enter the final number. \t";             //final prompt, asks for the final number.
	 cin>>num3;                                             //stores final number in variable num3
    
	 cout<<endl;                                            //ends the line
    
	 sum=num1+num2;        //these next 5 lines calculate sum, product, difference and quotient, along with the average.
    diff=num1-num2;
    prod=num1*num2;
    quot=num1/num2;
	 average=(num1+num2+num3)/3;

	 //The next 5 lines prompt the user and display the calculations.

	 cout<<"The sum of the first two numbers is " <<sum <<"\n";
	 cout<<"The difference between the first two numbers is " <<diff <<"\n";
    cout<<"The product of the first two numbers is " <<prod <<"\n";
    cout<<"The quotient of the first two numbers is " <<quot <<"\n";
    cout<<"The average of all three numbers is " <<average <<"\n";
    
	 cout<<endl;                                                  //ends the line
    
	 cout<<"THANK YOU FOR USING THE OPERATIONS PROGRAM.";         //final prompt to thank user for using thr program.
	 return 0;                                                    //ends the program.
}
    
    
