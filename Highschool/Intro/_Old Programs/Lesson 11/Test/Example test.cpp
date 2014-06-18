#include <iostream.h>

main()
{
    int x, y, pass, hold;
    int string[5]={2,3,1,7,5};
    
    do{
    

        for(x=0;x<4;x++)
        {
            if(string[x]>string[x+1])
            {
                hold=string[x];
                string[x] = string[x+1];
                string[x+1] = hold;
            }
        }
    
    
    for(x=0;x<5;x++)
    {
        cout<<string[x]<<" ";
    }
    
    system("PAUSE");
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>y;

    }while(y == 2);
    
    return 0;
}

/* #include <iostream.h>

main()
{
    do{
    int x;
    int y = 2;
    char string[]={'h','i',' ','t','h','e','r','e','\0'};
    
    cout<<string<<endl;
    
    for(x=0;string[x]!='\0';x++)
    cout<<string[x];
    
    cout<<"\nTo continue Press 2: ";
    cin>>y;
    cout<<endl;
    }while('y' == 2);
    
    return 0;
}

*/
/*
#include <iostream.h>

main()
{
    do{
    int y = 2;
    
    
    
    int x;
    char string[]="Hi there";
    
    cout<<string<<endl;
    
    for(x=0;string[x]!='\0';x++)
    cout<<string[x];
    
    
    
    cout<<"\nTo continue Press 2: ";
    cin>>y;
    cout<<endl;
    }while('y' == 2);
    
    return 0;
}

*/
