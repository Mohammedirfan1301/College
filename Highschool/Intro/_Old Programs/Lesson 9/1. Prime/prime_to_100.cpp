#include <iostream.h>
#include <math.h>
#include <iomanip.h>

main()
{
      int a,b;
      int primesfound = 0;
      int x = 1;

      cout<<"Welcome to the Prime Program. \n";
      cout<<"This program will analyze the first 100 numbers \n"; 
      cout<<"to determine if they are prime. \n";
      
      do{
      
      bool prime = false;
         
      for(a = 2; primesfound <= 100; a++)
      {
      prime = true;
          for (b = 2; b < a; b++)
          {
              if(a % b == 0)
              {
                   prime = false;     
              }
              
              if(prime)
              {
                   primesfound++;
                   cout<<a<<" ";        
              }
          }
      }
      
      cout<<"\nTo continue using the program, enter 1. To exit, enter 2. -> ";
      cin>>x;
      
      }while(x==1);
      
      return 0;     
}
/*

int numPrimesFound = 0; //we want 100 of these
	bool prime = false; //conditional for each number
	for(int i = 2;numPrimesFound <= 100; i++){//our exit condition
		prime = true; //default to true, we have to disprove it's prime-ness
		for(int j = 2; j < i/2 + 1; j++){ //we only need to check to "half" 2,3,5, etc...
			if (i % j == 0){prime = false;} //set its prime-ness
		}
		if(prime) { //print if it's prime and increment our counter
			numPrimesFound++;
			cout << i <<  " ";
		}
	}
	cout << endl << endl;

*/
