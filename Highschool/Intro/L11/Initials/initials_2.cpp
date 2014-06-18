#include <iostream.h>
#include <conio.h>

main()
{
    int x = 2;
    char fullname[100];
    int a = 1, b = 0, c = 0, d = 0, e = 0;
    
    do{
    cout<<"Welcome to the INITIALS Program. \n";
    cout<<"This program will turn a full name into initials. \n";
    cout<<"Enter your full name: ";
    gets(fullname);
    
    cout<<"Your initials are: ";
    d = 100;
    
    for(a = 1; a < d; a++)
    {
        if(fullname[a] == 32)
        {
            b = a + 1;
            
            do{
                if(fullname[b] == 32)
                {
                    cout<<fullname[a+1];
                    break;
                }
                else if(fullname[b]=='\0')
                    break;
                else
                    b++;
            }while(b < d);
        }
    }
    
    c = d;
    
    do{
        c--;
    }while(fullname[c] != 32);
    
    for(e = c; e < d; e++)
    {
        cout<<fullname[e];
    }
    getch();
    
    do{
    cout<<"To stop the program, enter 1. To rerun the program, enter 2. \n";
    cout<<"Enter your selection. -> ";
    cin>>x;
    }while(x != 1 && x != 2);
    
    }while(x == 2);
    
    return 0;    
}
