#include <iostream.h> //header for in/output
#include <iomanip.h>  //setw()
#include <math.h>     //pow

main () 
{
    int a, b;    //variables for the for loops
    int x;       //variable for the 10^x.
    int z = 1;   //variable for the do/while loop
    
    cout<<"Welcome to the 10^x Prime Program. \n";                       //introduction to the program
    cout<<"This program will calculate all the primes up to 10^x. \n";   
    
    do{
                
    cout<<"\nEnter a value for x. -> ";     //asks for the x in 10^x.
    cin>>x;                                 //stores the response in variable x.
    cout<<endl;                             
     
    for (a = 2; a < pow(10,x); a++)  //first for loop controls the maxium. in the case of x = 3, that would be 1,000.
    {                                //which means the program would check the numbers 2 up to 1,000. The reason for not checking 0/1 is because they are not prime.
        for (b = 2; b * b <= a; b++) //second for loop controls the calculating part. b is again 2 because 0/1 are not prime. b*b gives the maxium number to try.
        {                            //so if b=2, b*b is 4 and a is 2, so 4 <= 2.
            if (a % b == 0)          //this tests if they are not prime
               break;                //stops it once its found to be not prime and starts trying the next number.
            else if ( b + 1 > sqrt(a) ) //if this is true, then the number is prime and is printed out below.
               cout << a <<setw(5);    //prints the prime number.

        }   
    }
    
    cout<<"\n\nTo continue, enter 1. To exit, press 2. -> ";  //lets the user continue by typing 1, or exit by typing another number (0,2 or any other number but 1).
    cin>>z;
    cout<<endl;
    
    }while(z == 1);  //the do/while lets the user try different values of x.
    return 0;
}
