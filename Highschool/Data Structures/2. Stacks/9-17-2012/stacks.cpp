#include <iostream>
#include <windows.h>
using namespace std;

int push(int arg[], int);

int main()
{
    int stack[10] = {0};                ///stack array of 10 ints
    int temp = 0;                       //temp int variable
    int opt = 0, comd = 0, end = 0;     //end variables
    
    cout<<"Welcome. Choose an option: \n";  //tells user the following options
    cout<<"1. Manual Entry \n";
    cout<<"2. File Entry \n";
    cout<<"3. Quit \n";
    
    do{
    cout<<"Enter an option. -> ";           //asks user to enter one of the above numbers.
    cin>>opt;
    }while(opt != 1 && opt != 2 && opt != 3);
    
    cout<<"\n";
    
    switch(opt)
    {
        case 1:
            cout<<"\nManual Entry. \n";
            break;
        case 2:
            cout<<"\nFile Entry. \n";
            break;
        case 3:
            cout<<"\nGood bye, Commander. \n";
            cout<<"It was nice knowing you. \n";
            Sleep(5000);    //pause for 5 seconds as 1 sec = 1000 ms
            break;
        default:
            cout<<"\nYou didn't enter a valid command, Sir. \n";
            cout<<"Please enter a number between 1 and 3. \n";
            break;
    }
    
    cout<<"\nWelcome, Commander. \n";
    cout<<"COMMANDS: \n";
    cout<<"1 -> PUSH \n";
    cout<<"2 -> POP  \n";
    cout<<"3 -> PEEK \n";
    cout<<"4 -> PRINT \n";
    cout<<"5 -> QUIT   \n";
    
    do{
    cout<<"Enter one of the above numbers. -> ";
    cin>>comd;
    }while(comd != 1 && comd != 2 && comd != 3 && comd != 4 && comd != 5);
    
    switch(comd)
    {
        case 1:
            cout<<"Push Function. \n";
            cout<<"Enter a number to push to the stack: ";
            cin>>temp;
            push(stack, temp);
            break;
            
        case 2:
            cout<<"Pop Function. \n";
            break;
            
        case 3:
            cout<<"Peek Function. \n";
            break;
            
        case 4:
            cout<<"Print Function. \n";
            break;
            
        case 5:
            cout<<"Good bye, Commander. \n";
            cout<<"Printing stack to file... \n";
            break;
            
        default:
            cout<<"How did you get here? \n";
            break;
    }
    
    cout<<"So, you have decided to leave teh program?? \n";
    cout<<"R u sure??? Press 1 or 2 -> ";
    cin>>end;
    
    return 0;
}

//Functions
//The following section is where all of the functions for this program are located.
//I tried to keep them in order or at least some sort of logical arrangement. :\

//Push Function
int push(int arg[],int)
{
    //zero is the top, 9 is the bottom.
    int a = 0;
    if(stack[a] == 0)
        stack[a] = temp;
}

//Useful Websites
//Sites that have helpful hints or tricks
/*
http://login2win.blogspot.com/2008/07/c-stacks.html

*/
