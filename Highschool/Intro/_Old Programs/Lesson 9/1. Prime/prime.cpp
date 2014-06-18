#include <iostream.h>
#include <math.h>
#include <iomanip.h>

main()
{
      int startnum, divisor;
      int x;
      int z = 1;
      
      cout<<"Welcome to the Prime 10x Program. \n";
      cout<<"This program will analyze numbers to determine if they are prime. \n";
      cout<<"You will be able to select up to how many powers of ten you want the \n";
      cout<<"program to calculate to. \n";
      
      do{
      
      cout<<"\nThis program finds all the prime up to 10^x.";
      cout<<"\nEnter a value for x. -> ";
      cin>>x;
      cout<<endl;
         
      for(startnum = 1; startnum <= pow(10,x); startnum++)
      {
          for(divisor = 2; divisor <= startnum / 2; divisor++)
          {
               if(startnum % divisor = 0)
               {
                                
               }        
      }
      
      cout<<"\nTo continue using the program, enter 1. To exit, enter 2. -> ";
      cin>>z;
      
      }while(z==1);
      
      return 0;     
}

/* NOTES ABOUT THE PROGRAM:
         
Remainder in a prime should be n/1 = 0 and n/n = 0; no other number should equal 0.

instance:
         5/5 = 0
         5/4 = 1
         5/3 = 2
         5/2 = 1
         5/1 = 0

*/
