#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

/*Error codes throughout the functions:
1 = Array is empty
2 = Stack overflow
3 = ??????
*/

int push(int stack[], int tmp);
int peek(int stack[]);
void manual(int stack[]);

int main()
{
    int stackarg[10] = {0};    //stack array of 10 ints (stack is name the functions pass of this array)
    int opt = 0;               //end variable
    
    do{ //main do/while - controls manual/file/quit options
        cout<<"*****************************\n";
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
                cout<<"************************* \n";
                cout<<"\nManual Entry. \n";
                manual(stackarg);
                break;
            case 2:
                cout<<"************************* \n";
                cout<<"\nFile Entry. \n";
                break;
            case 3:
                cout<<"************************* \n";
                cout<<"\nGood bye, Commander. \n";
                cout<<"It was nice knowing you. \n";
                Sleep(5000);    //pause for 5 seconds as 1 sec = 1000 ms
                break;
            default:
                cout<<"\nYou didn't enter a valid command, Sir. \n";
                cout<<"Please enter a number between 1 and 3. \n";
                break;
        }
    }while(opt != 3);   //the program does not end until the user enters '3' at the first prompt
    
    return 0;
}

//Functions
//The following section is where all of the functions for this program are located.
//I tried to keep them in order or at least some sort of logical arrangement. :\

//Function to run the program in manual mode
//this makes things more organized so that manual mode/file entry mode each have their
//own respected functions to run from.
void manual(int stack[])
{
    int comd = 0;   //option variable
    int temp = 0;   //temp int variable
    int tempc = 0;  //temp var to print out peek
    
    do{
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
            cout<<"\nPush Function. \n";
            cout<<"Enter a number to push to the stack: ";
            cin>>temp;
            push(stack, temp);
            break;
            
        case 2:
            cout<<"\nPop Function. \n";
            break;
            
        case 3:
            cout<<"\nPeek Function. \n\n";
            tempc = peek(stack);
            if(tempc == 1)
                cout<<"The stack is empty! \n";
            else
            cout<<tempc<<" is the number on the top of the stack. \n";
            break;
            
        case 4:
            cout<<"\nPrint Function. \n";
            break;
            
        case 5:
            cout<<"\nGood bye, Commander. \n\n";
            break;
            
        default:
            cout<<"\nHow did you get here? \n";
            break;
    }
    }while(comd != 5);
}

//Push Function
int push(int stack[],int tmp)
{
    //zero is the top, 9 is the bottom.
    int a, b, c;
    for(a = 0; a < 10; a++)
    {
        if(stack[a] == 0)
        {
            if(a > 0)
                stack[a-1] = tmp;
            else if(a == 0)
                stack[a] = tmp;
        }
    }
    
    if(a == 9)
        return 2;
    else    
        return 0;  
}

//Peek Function
int peek(int stack[])
{
    int a, b, c;
    for(a = 0; a < 10; a++)
    {
        if(stack[a] == 0)
        {
            b = a;
            if(a > 0)
                c = stack[a-1];
            break;
        }
    }
    
    if(b == 0)
        return 1;
    else
        return c;
}

//**************************************************************************************************************************************
//Useful Websites
//Sites that have helpful hints or tricks
/*
http://login2win.blogspot.com/2008/07/c-stacks.html

*/

/*
Useful code for the futre? How to make a 'press enter to continue' prompt
works, but DECLARE <conio.h>!!!!

    char c;             //press enter variable
    cout<<"\nTo end the program, press enter. -> ";
    do{
        c = getch();
    }while(c != 13);
*/
