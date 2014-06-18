#include <iostream.h>   //for input output
#include <iomanip.h>    //for setw
#include <math.h>       //for pow

main()
{
      int num = 1;             //variable for the main loop.
      double dec = 0;          //variable for the decimal.
      double bit = 0;          //variable for the number of bits.
      double n   = 0;          //variable for the calculations (2^n, where n = bit - 1)
      double sum = 0;          //variable for the calculations (sum of 2^n, ie 2^9 = 512)
      
      cout<<"This program will prompt for a decimal value and then  \n";
      cout<<"convert it to Binary. It will also let you enter the   \n";   //introduction prompt to the program.
      cout<<"number of bits you want the program to calculate to.   \n";
      cout<<endl;
      cout<<"Enter 1 to use the program or 0 to exit. -> ";               //starts the main while loop by entering 1.
      cin>>num;                                                           //ends the main while loop by entering 0.
      cout<<endl;
      
      while(num==1)
      {
           cout<<"Enter the number you want to convert to binary. -> ";          //user enters the decimal value.
           cin>>dec;
           cout<<"Enter the number of bits you want to calculate out to. -> ";   //user enters the bit number to convert to.
           cin>>bit;
           cout<<endl;

			  cout<<"The binary value for "<<dec<<" is: \n \n";       //Lets user know value, which will be listed below this statement.

			  if( (dec >= 1) && (bit >= 1) )          //this if lets only positive decimal/bit values calculate.
			  {
					while(bit > 0)                      //the while loop which loops the calculates
					{                                 
						n = bit - 1;                  // n is bit - 1, so if bit=10, n=10-1 or n=9
						sum = pow (2, n);             //sum is the total of 2 raised to the n power. so if n=9, 2^9=sum (or sum=512)
						
						if(dec >= sum)                //this makes it so that if dec is greater than sum, it displays a 1.
						{                             //also, if it is greater, it subtracts dec by the sum, and restates dec.
                             cout<<"1"<<setw(5)<<2<<"^"<<n<<"="<<sum<<setw(10);     //ie "331 is greater than 256", displays 1, 75=331-256. dec is now 75 in the future
                             cout<<dec<<"-"<<sum<<"=";
                             dec = dec - sum;
                             cout<<dec<<endl;
                        }
                        
						else                          //else is used because another if complicates things as in the above if dec is reset to 75... 
						{                             //so putting "dec < sum" would add an extra 0 because 75 becomes less then 256.
                             cout<<"0"<<setw(5)<<2<<"^"<<n<<"="<<sum<<setw(10);       //if, however, the first if is not true (ie 75 < 128) then the else works
                             cout<<dec<<"<"<<sum<<setw(5)<<"N/A"<<endl;              //by adding a 0. it also does not change the value of dec.
                        }
                        
                        bit--;      //useful thing subtracts bit by 1 each time. this makes the while loop work correctly as the bit number is slowly reduced.
					}
			  }
			  else                                 //if the user entes a value too small, the above if doesn't let the value through
			  {                                    //and this else displays the statement below, letting the user know they made a mistake.
					cout<<"You entered a number of bits that is too small. \n";
			  }

			  cout<<"\nEnter 1 to continue or 0 to exit. -> ";         //lets user continue using the program by pressing 1 (ie enter another decimal to convert)
			  cin>>num;                                             //or lets the user end by pressing 0.
              cout<<endl;                                             
		}

		cout<<endl<<"Thank You for using the Decimal to Binary Convertor. ";      //ending prompt which lets the user know the program has ended.

		return 0;
}
