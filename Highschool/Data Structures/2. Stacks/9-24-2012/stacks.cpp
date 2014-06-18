#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

/*Error codes throughout the functions:
-1 = Stack underflow / Array is empty
 2 = Stack overflow
 3 = ??????
*/

int push(int stack[], int tmp);     //push function
int pop(int stack[]);				//pop  function
int peek(int stack[]);              //peek function
int print(int stack[]);             //print function
void manual(int stack[]);           //manual function - for manual entry

int main()
{
    int stackarray[10] = {0};    //stack array of 10 ints (stack is name the functions pass of this array)
    int opt = 0;               //end variable
    
    do{ //main do/while - controls manual/file/quit options
        memset(stackarray, 0, 10);	//clear the stackarray incase the program is used more than once.
		//memset(stack, 0, 10);
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
                cout<<"***************************** \n";
                cout<<"Manual Entry. \n";
                manual(stackarray);	//proceeds to the manual entry function to handle manually typing in the commands.         
                break;
            case 2:
                cout<<"***************************** \n";
                cout<<"\nFile Entry. \n";
                break;
            case 3:
                cout<<"***************************** \n";
                cout<<"\nGood bye, Commander. \n";
                Sleep(5000);    //pause for 5 seconds as 1 sec = 1000 ms. does this to prevent the window from closing instantly in dev.
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
    int temp = 0;   //temp variable for taking a number in (push)
    int code = 0;   //success/errror code variable
    
    do{
        temp = 0;
		code = 0;
		cout<<"\n------------------------- \n";
		cout<<"Welcome, Commander. \n";
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
            cout<<"\n*** Push Function. *** \n";
            cout<<"Enter a number to push to the stack: ";
            cin>>temp;
            cout<<"\n";
            code = push(stack, temp);
            if(code == 0)
                cout<<temp<<" was successfully pushed to the stack. \n";
            else if(code == 2)
                cout<<"Errror! Stack overflow! \n";
            break;
            
        case 2:
            cout<<"\n*** Pop Function. ***\n";
            code = pop(stack);
            if(code == -1)
            	cout<<"Error! Stack underflow! \n";
            else
            	cout<<code<<" was removed from the top of the stack. \n";
            break;
            
        case 3:
            cout<<"\n*** Peek Function. ***\n\n";
            code = peek(stack);
            if(code == -1)
                cout<<"The stack is empty! \n";
            else
            cout<<code<<" is the number on the top of the stack. \n";
            break;
            
        case 4:
            cout<<"\n*** Print Function. ****\n";
            code = print(stack);
            if(code == 1)
                cout<<"Error! Cannot print an empty stack!";
            cout<<"\n";
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
    //zero is the bottom, 9 is the top.
    int a, b, c;
    b = 0;
    for(a = 0; a <= 9; a++)
    {
        if(stack[a] == 0)
        {
            stack[a] = tmp;
            break;
        }
        
        if(a == 9)
        {
			if(stack[a] != 0)
			{
				b = 1;
			}
		}
        
    }
    
    if(b == 1)
        return 2;
    else    
        return 0;  
}

//Pop Function
int pop(int stack[])
{
	int a, b, c;
	b = 0;
	
	for(a = 0; a <= 9; a++)
	{
		if(stack[a] == 0)
		{	
			if(a > 0)
			{
				b = stack[a-1];
				stack[a-1] = 0;
				break;
			}
			
			if(a == 0)
			{
				b = -1;
				break;
			}
		}
	}
	
	return b;
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
        return -1;
    else
        return c;
}

//Print function
int print(int stack[])
{
    int a, b;
    
    for(a = 0; a <= 9; a++)
    {
        if(stack[a] != 0)
            cout<<stack[a]<<"\t";
       	if(stack[a] == 0)
        {
            if(a == 0)
            {
				b = 1;
           		break;
			}
			
			if(a > 0)
			{
				b = 0;
				break;
			}
        }
    }
    
    if(b == 1)
        return b;
    if(b != 1)
        return 0;
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
