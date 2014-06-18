#include <iostream.h> //header for in/output
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
     
	 for (a = 2; a < pow(10,x); a++)    //this makes it run 10^x times. so if x = 3, it will check all numbers up to 1,000.
	 {
		  unsigned int prime = 1;        //bool didn't seem to work so I used 1 for true, 0 for false and an unsigned int.

        for (b = 2; b * b <= a; b++)   //this does the numbers to test it with.
        {
            if (a % b == 0)            //if a % b = 0, the number cannot be prime.
            {
					 prime = 0;         //since it cannot be prime, it's false.
                break;                 //and this breaks it, as once its found to not be prime, there's no need to test further.
            }
        }   
		  if(prime == 1)                     //if it hasn't been proven to not be prime, then the number will be printed out below.
        cout<<a<<"\t";                //i also found \t to make nice columns compared to setw.
    }
    
    cout<<"\n\nTo continue, enter 1. To exit, press 2. -> ";  //lets the user continue by typing 1, or exit by typing another number (0,2 or any other number but 1).
    cin>>z;
    cout<<endl;
    
    }while(z == 1);  //the do/while lets the user try different values of x.
    return 0;
}
