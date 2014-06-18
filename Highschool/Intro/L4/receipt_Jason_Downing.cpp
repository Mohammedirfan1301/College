#include <iostream.h>       //input, output header file
#include <iomanip.h>        //used for setw() command (input output manipulator header file)
#include <math.h>           //to use the floor(x) command (math header file)

int main()
{
    double b,t,sub,tax1,tax2,tip1,tip2,tip3,total1,total2;
    
	 cout<<"Welcome to the RESTAURANT BILL CALCULATOR Program. \n";                //basic prompt, letting user know how to use the program.
	 cout<<"This program will calculate your restaurant bill. \n";                 //lets them know the program takes into account 8% tax and
	 cout<<"Please note: it takes into account the 8% tax and \n";                 //whatever percent tip they want to leave.
	 cout<<"asks what percent you would like to leave as a tip. \n";
	 cout<<endl;
	 cout<<"Enter the cost of your bill at Bob's Burgers."<<setw(9)<<"$";          //prompt for the cost of their bill.
	 cin>>b;                                                                       //(the setw() is used to line up the total/tip)
	 cout<<endl;
	 cout<<"Enter the percent you would like to leave as a tip." <<setw(3)<<"%";   //prompt for the percent tip.
    cin>>t;                                                     
    cout<<endl;
																						 /*num2=floor(num1*pow(10,x))/pow(10,x) where x is the number of decimal places.*/
	 sub=b;                                                         //This does all the math and stores it in numerous variables.
	 tax1=b*.08;                                                    //calculates the sales tax by * by .08
	 tax2=floor(tax1*pow(10,2))/pow(10,2);                          //uses floor(x) to bring the tax to a nice number (2 decimal places)
	 tip1=t/100;                                                    //because the tip is entered as a whole number, it is made into percent by dividing by 100.
	 tip2=tip1*b;                                                   //this does the actual calc. of the tip, with tip1 = the tip as a percent (ie .12) and b is the
	 tip3=floor(tip2*pow(10,2))/pow(10,2);                          //subtotal. floor(x) is used the same as in tax2, to make the number go to 2 decimal places.
	 total1= tip3+tax1+sub;                                         //calculates the total previous variables, ie the subtotal, tip, and tax.
	 total2= floor(total1*pow(10,2))/pow(10,2);                     //finally, the complete total is calculated by again using floor(x) as in tip2 to bring the
																						 //number of decimal places to 2, ie 24.35 rather then 24.355654 etc.
	 cout<<"----------------------------------------------  \n";    //start of the receipt. -'s used to make receipt look nice.
	 cout<<" BOB'S BURGERS - The best burgers since 2011!  \n";
	 cout<<endl;
	 cout<<" Subtotal"<<setw(31)<<"$"<<sub<<"\n";                   //the next three lines display all the above calculations, ie the subtotal, tax and tip.
	 cout<<" Tax  8%"<<setw(32)<<"$"<<tax2<<"\n";
	 cout<<" Tip "<<t<<"%"<<setw(32)<<"$"<<tip3<<"\n";
	 cout<<endl;
	 cout<<"---------------------------------------------- \n";
	 cout<<" Total Bill"<<setw(29)<<"$"<<total2<<"\n";              //this displays the final calculated bill.
	 cout<<"---------------------------------------------- \n";
	 cout<<endl;
	 cout<<"Thank you for eating at BOB'S BURGERS!";                 //thanks user for using program/eating at the fictional restaurant.
    cout<<endl;
    return 0;
}
