#include <iostream.h>
#include <math.h>
#include <iomanip.h>

main () 
{
    int a,b; 
    int z = 1;
    
    cout
    
    do{
     
    for (a = 2; a < pow(10,x); a++) 
    {
        bool prime = true;
        
        for (b = 2; b*b<=a; b++)
        {
            if (a % b == 0) 
            {
                prime = false;
                break;    
            }
        }   
        if(prime)
        cout<<a<<"\t";
    }
    
    cout<<"\n\nEnter 1. ->";
    cin>>z;
    
    }while(z == 1);
    return 0;
}
