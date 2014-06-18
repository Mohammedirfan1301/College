#include <iostream.h>
#include <conio.h>

main()
{
    int x = 2;
    char fullname[100];
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    
    do{
    cout<<"Welcome to the INITIALS Program. \n";
    cout<<"This program will turn a full name into initials. \n";
    cout<<"Enter your full name: ";
    gets(fullname);
    
    cout<<"\nYour initials are: ";
    
    cout<<fullname[0];
    
    for(a = 0; a < 100; a++)
    {
        if(fullname[a] == 32)
        {
            cout<<fullname[a+1];
            b = a;
            break;
        }
    }
    
    for(b; b < 100; b++)
    {
        if(fullname[b] == 32)
        {
            cout<<fullname[b+1];
            break;
        }
    }
    
    cout<<endl;
    
    do{
    cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
    cout<<"Enter your selection. -> ";
    cin>>x;
    }while(x != 1 && x != 2);
    
    system("cls");
    
    }while(x == 2);
    
    return 0;    
}

/*

Jason Patrick Downing

cout<<fullname[0];
if(fullname[a] == 32)
cout<<fullname[a+1];

JPD

http://www.mybestnotes.co.in/source-code/?source=INITIALS.C

*/
