#include <iostream.h>
#include <iomanip.h>

main()
{
		int num = 1;
		int decimal = 1;
		int bit = 1;
      
      cout<<"This program will prompt for a decimal value  \n";
      cout<<"and then convert it to Binary. It will also   \n";
      cout<<"let you enter the number of bits you want the \n";
      cout<<"program to calculate to. \n"<<endl;
      
      cout<<"Enter 1 to use the program or 0 to exit. \n";
      cin>>num;
      
      while(num==1)
      {
           cout<<"Enter the number you want to convert to binary. -> ";
           cin>>decimal;
           cout<<"Enter the number of bits you want to calculate out to. -> ";
           cin>>bit;

			  cout<<"The binary value for"<<decimal<<"is: ";

			  if( (decimal >= 1) && (bits >= 1) )
			  {
					while(decimal > 0)
					{
						cout<<"Test";
					}
			  }
			  else
			  {
					cout<<"You entered a number of bits that is too small. \n";
			  }
			  cout<<"Enter 1 to continue or 0 to exit. \n";
			  cin>>num;
		}

		cout<<endl<<"Thank you for using the Decimal to Binary Convertor. ";

		return 0;
}
