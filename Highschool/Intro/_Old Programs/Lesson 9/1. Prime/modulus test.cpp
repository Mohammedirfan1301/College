#include <iostream.h>

main()
{
      int a,b,c,x;
      
      do{
      
      a = 0;
      b = 0;
      c = 0;
      x = 1;
          
      cout<<"This is a test. \n";
      
      cout<<"Enter a -> ";
      cin>>a;
      cout<<endl;
      
      cout<<"Enter b -> ";
      cin>>b;
      cout<<endl; 
      
      c = a%b;
      cout<<"The value of the number is: "<<c<<endl;
      
      cout<<"\nTo continue, enter 1. Exit, enter 2. -> ";
      cin>>x;
      
      }while(x == 1);
      
      return 0;
}
