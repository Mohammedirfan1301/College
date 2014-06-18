#include <iostream.h>
#include <iomanip.h>
#include <math.h>

main () 
{
    int a, b, x;
    int z = 1;
    
    cout<<"Welcome to the 10^x Prime Program. \n";
    cout<<"This program will calculate all the primes up to 10^x. \n";
    
    do{
                
    cout<<"\nEnter a value for x. -> ";
    cin>>x;
    cout<<endl;
     
    for (a = 2; a < pow(10,x); a++) 
    {
        for (b = 2; b * b <= a; b++)
        {
            if (a % b == 0)  
               break;
            else if ( b + 1 > sqrt(a) )
               cout << a <<setw(10);       

        }   
    }
    
    cout<<"\n\nTo continue, enter 1. To exit, press 2. -> ";
    cin>>z;
    cout<<endl;
    
    }while(z == 1);
    return 0;
}
