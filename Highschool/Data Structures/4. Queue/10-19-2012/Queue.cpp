#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

int enqueue(int queue[], int tmp);  //enqueue function
//int dequeue(int queue[]);			//dequeue function
//int peek(int queue[]);         		//peek function
int print(int queue[]);             //print function
void manual(int queue[]);           //manual function - for manual entry
//void file(int queue[]);             //file function

int main()
{
	int queues[10] = {0};    //stack array of 10 ints (stack is name the functions pass of this array)
    int opt = 0;                 //end variable
    
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
                cout<<"***************************** \n";
                cout<<"Manual Entry. \n";
                manual(queues);	//proceeds to the manual entry function to handle manually typing in the commands.         
                break;
            case 2:
                cout<<"***************************** \n";
                cout<<"\nFile Entry. \n";
                //file(queues);   //proceeds to the file entry function.
                break;
            case 3:
                cout<<"***************************** \n";
                cout<<"\nGood bye, Commander. \n";
                Sleep(5000);    //pause for 5 seconds as 1 sec = 1000 ms. does this to prevent the window from closing instantly.
                break;
            default:
                cout<<"\nYou didn't enter a valid command, Sir. \n";
                cout<<"Please enter a number between 1 and 3. \n";
                break;
        }
        memset(queues, 0, 10);	//clear the stackarray incase the program is used more than once.
    }while(opt != 3);   //the program does not end until the user enters '3' at the first prompt
    
	return 0;
}

//manual entry is handled in this function.
void manual(int queue[])
{
    int a = 0;
	int comd = 0;   //option variable
    int temp = 0;   //temp variable for taking a number in (push)
    int code = 0;   //success/errror code variable
    
    do{
        temp = 0;
		code = 0;
		cout<<"\n------------------------- \n";
		cout<<"Welcome, Commander. \n";
        cout<<"COMMANDS: \n";
        cout<<"1 -> ENQUEUE \n";
        cout<<"2 -> DEQUEUE  \n";
        cout<<"3 -> PEEK \n";
        cout<<"4 -> PRINT \n";
        cout<<"5 -> QUIT   \n";
    
        do{
            cout<<"Enter one of the above numbers. -> ";
            cin>>comd;
        }while(comd != 1 && comd != 2 && comd != 3 && comd != 4 && comd != 5);	//only lets the user enter 1-5
    
    switch(comd)
    {
        case 1:
            cout<<"\n*** Enqueue Function. *** \n";
            cout<<"Enter a number to push to the stack: ";
            cin>>temp;
            cout<<"\n";
            code = enqueue(queue, temp);	//code is equal to whatever the push function returns - which is either an error code (-1) or zero for succes
            if(code == 0)	//success!
                cout<<temp<<" was successfully pushed to the stack. \n";
            if(code == -1)	//failure!
                cout<<"Error! The stack is full! \n";
            break;
        /*    
        case 2:
            cout<<"\n*** Enqueue Function. ***\n";
            code = dequeue(queue);
            if(code == -1)	//error!!
            	cout<<"Error! The stack is empty! \n";
            else			//else success
            	cout<<code<<" was removed from the top of the stack. \n";
            break;
            
        case 3:
            cout<<"\n*** Peek Function. ***\n";
            code = peek(queue);
            if(code == -1)	//error!
                cout<<"Error! The stack is empty! \n";
            else			//success!
            cout<<code<<" is the number on the top of the stack. \n";
            break;
            */
        case 4:
            cout<<"\n*** Print Function. ****\n";
            code = print(queue);	//if everything works, the print function prints. it only returns -1 if there is an error ie the stack is empty.
            if(code == -1)	//error!
                cout<<"Error! Cannot print an empty stack!";
            cout<<"\n";
            break;
            /*
        case 5:
            cout<<"\nGood bye, Commander. \n\n";
            for(a = 0; a < 10; a++)	//run 10 times in case there are 10 values in the array.
            	//dequeue(queue);		//makes sure the array is cleared for the next run through by popping any values that are still in the array.
            break;
            */
        default:	//i made sure the user can only enter 1-5, but just in case this will print out.
            cout<<"\nHow did you get here? \n";
            break;
    }
    }while(comd != 5);	//run until the user enters 5, which quits the manual entry option.
}

//Enqueue Function
int enqueue(int queue[],int tmp)
{
    //zero is the bottom, 9 is the top.
    int a, b;
    b = 0;		//make sure b is 0!
    
    for(a = 0; a <= 9; a++)
    {
        if(queue[a] == 0)	//if stack[a] is zero, then a num can be pushed to this spot in the array
        {
            queue[a] = tmp;
            break;
        }
        
        if(a == 9)	//if stack[a] is 9, it is the end of the array. check to see if it is full by checking if its not equal to zero.
        {
			if(queue[a] != 0)	//if this is true, then the whole array is full and therefor the number cannot not be pushed.
			{
				b = -1;
				break;
			}
		}
        
    }
    
    if(b == -1)		//-1 is the error code used
        return -1;	//in this case the array is full
    else    
        return 0;  	//zero means success - the num was pushed correctly.
}

/*
//Pop Function
int pop(int queue[])
{
	int a, b;
	b = 0;
	
	for(a = 0; a <= 9; a++)
	{
		if(queue[a] == 0)	//if stack[a] is zero, there's two possible options
		{	
			if(a > 0)	//a is greater than zero, therefor a num can be popped from the array
			{
				b = queue[a-1];	//b is one less than stack[a] because stack[a] is zero, so a-1 is the top most value.
				//also b is returned, so b is equal to that value for returning purposes
				queue[a-1] = 0;	//make it equal to zero.
				break;
			}
			
			if(a == 0)	//if stack[a] is zero AND a equals zero, the array is empty!
			{
				b = -1;	//error code
				break;
			}
		}
		
		if(a == 9 && queue[a] != 0)	//if a is 9, it is the top of the array. if stack[a] is also not zero, it means
		{							//there is a value there to be popped.
            b = queue[a];			//top most value therefor no a-1, just make b=stack[a] to return it
            stack[a] = 0;			//make it equal to zero to remove the value
        }
	}
	
	return b;	//return b which is either the num popped or -1 which is an error code.
}

//Peek Function
int peek(int stack[])
{
    int a, b, c;
    b = 0;
    
    for(a = 0; a < 10; a++)
    {
        if(stack[a] == 0)	//if stack[a] equals zero, it should be the top of the array. 
        {
            b = a;		//make b equal to a. to check if the array is empty.
            if(a > 0)	//if a is greater than zero, the array 
                c = stack[a-1];	//c is the top most value as stack[a] is zero but stack[a-1] is not zero.
            break;
        }
        
        if(a == 9 && stack[a] != 0)	//if a is 9 and stack[a] isn't zero, this is actually the top most value.
        {
            b = 1;	//so make b = 1 so it doesn't send an error code by mistake.
            c = stack[a];	//and make c = stack[a] as that is the top most value.
            break;
        }
    }
    
    if(b == 0)	//if b is zero, a is zero and stack[a] is zero. therefore the array is empty.
        return -1;	//so return an error code.
    else
        return c;
}
*/

//Print function
int print(int queue[])
{
    int a, b;
    b = 0;
    
    for(a = 0; a <= 9; a++)
    {
        if(queue[a] != 0)			//if stack[a] isn't zero, just cout it as it is a value to be outputted.
            cout<<queue[a]<<"\t";
       	if(queue[a] == 0)			//if stack[a] is zero, two possible options
        {
            if(a == 0)	//a is zero and the array is therefor empty.
            {
				b = -1; //error code
           		break;
			}
			
			if(a > 0)	//a is greater than zero and the array is not empty, but it is not completely full.
			{
				b = 0;	//NOT an error code but make b zero so it doesn't send a false alarm.
				break;
			}
        }
    }
    
    if(b == -1)		//error code
        return -1;
    if(b != -1)		//success!
        return 0;
}
