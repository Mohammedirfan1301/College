#include <iostream>		//i declared a bunch of headers but everyone is used at some point in the program
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>		//getch() - press enter to continue
#include <windows.h>	//this is used for sleep() - i used to it pause the program before it ends.
using namespace std;

//NOTE: one of the files uses '-1' but i used this as the error code! must change or leave this note here for future reference!!

/*Error codes throughout the functions:
-1 = Stack underflow / Array is empty   / array is full
-1 is the only error code used!
*/

int push(int stack[], int tmp);     //push function
int pop(int stack[]);				//pop  function
int peek(int stack[]);         		//peek function
int print(int stack[]);             //print function
void manual(int stack[]);           //manual function - for manual entry
void file(int stack[]);             //file function

int main()
{
    int stackarray[10] = {0};    //stack array of 10 ints (stack is name the functions pass of this array)
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
                cout<<"***************************** \n";
                cout<<"Manual Entry. \n";
                manual(stackarray);	//proceeds to the manual entry function to handle manually typing in the commands.         
                break;
            case 2:
                cout<<"***************************** \n";
                cout<<"\nFile Entry. \n";
                file(stackarray);   //proceeds to the file entry function.
                break;
            case 3:
                cout<<"***************************** \n";
                cout<<"\nGood bye, User. \n";
                Sleep(5000);    //pause for 5 seconds as 1 sec = 1000 ms. does this to prevent the window from closing instantly.
                break;
            default:
                cout<<"\nYou didn't enter a valid command, Sir. \n";
                cout<<"Please enter a number between 1 and 3. \n";
                break;
        }
        memset(stackarray, 0, 10);	//clear the stackarray incase the program is used more than once.
    }while(opt != 3);   //the program does not end until the user enters '3' at the first prompt
    
    return 0;
}

//******************************************************************************************************************************
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
            if(code == 0)				//success
                cout<<temp<<" was successfully pushed to the stack. \n";
            if(code == -1)				//error
                cout<<"Error! The stack is full! \n";
            break;
            
        case 2:
            cout<<"\n*** Pop Function. ***\n";
            code = pop(stack);
            if(code == -1)				//error
            	cout<<"Error! The stack is empty! \n";
            else						//success
            	cout<<code<<" was removed from the top of the stack. \n";
            break;
            
        case 3:
            cout<<"\n*** Peek Function. ***\n";
            code = peek(stack);
            if(code == -1)				//error
                cout<<"Error! The stack is empty! \n";
            else						//success
            cout<<code<<" is the number on the top of the stack. \n";
            break;
            
        case 4:
            cout<<"\n*** Print Function. ****\n";
            code = print(stack);		//will print out the array if no error code are found.
            if(code == -1)				//error
                cout<<"Error! Cannot print an empty stack!";
            cout<<"\n";
            break;
            
        case 5:
            cout<<"\nGood bye, Commander. \n\n";
            memset(stack, 0, 10);   //clear the array used in the functions, in case the program is rerun.
            break;
            
        default:
            cout<<"\nHow did you get here? \n";
            break;
    }
    }while(comd != 5);
}

void file(int stack[])
{
    ifstream entry;
    string filename;    //string to hold the filename
    string command;     //string to hold each line in the file
    string hold;		//string that holds the first part of command
    string input;		//string to hold the input (ie '3') that will then be converted to an int
	int num = 0;		//final num to push to the functions
	int code = 0;		//code that holds the return value of the functions
	char c;             //press enter variable
    int x = 1;			//x is for the do/while loop
    
    cout<<"What is the name of the file you would like to open? \n";	//this program works with any text file that has the commands
    cout<<"Enter it here: -> ";		//set up such as "PUSH 12" or "PEEK", assuming they are separated by enters ('\n')
    cin>>filename;					//make sure to type the full name though - data1.txt for instance
    cout<<'\n';
    entry.open(filename.c_str());	//opens the file
    //error checking:
    if(!entry)     //if the inventory file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file! \n";
        Sleep(5000);    //pause for 5 seconds
        exit(0);        //exit the program
    }
    
    do{
		num = 0;
		getline(entry, command, '\n');
		
        if(strncmp(command.c_str(), "PUSH", 4) == 0)	//if the first four letters are equal to the letters of push, strncmp will return a zero meaning that the push command should be launched.
        {									//the first issue to tackle is getting a num to be pushed, so:
			cout<<"\n*** Push Function. *** \n";
			//split the string into two - hold string (PUSH) and input string (#s)
			istringstream str(command);		//stream to take command, so that it can be split into two different strings
			while(!str.eof())
			{
				getline(str, hold, ' ');	//take the command part of the command string and put into the hold string.
				getline(str, input, '\n');	//take the number to be pushed into the input string.
			}
			//now convert the input string that contains #s to an int
			num = atoi(input.c_str());	//convert the input string to an int.
			
			//now pass the num int to the push function
			code = push(stack, num);	//the following works just like the manual part of the program
            if(code == 0)				//if push returns zero, everything worked fine so print the num with a message to the user.
                cout<<num<<" was successfully pushed to the stack. \n";	//message says everything is working.
            if(code == -1)				//if push returns -1 bad things happened and therefore something went wrong
                cout<<"Error! The stack is full! \n";	//so tell the user the error.
		}
		//after just call up the respected function!
		//there really doesn't need to be much explantion as this works for the most part like the manual part of the program.
        
		//the pop command
		if(command.compare("POP") == 0)
        {
            cout<<"\n*** Pop Function. ***\n";
			code = pop(stack);
            if(code == -1)		//error code
            	cout<<"Error! The stack is empty! \n";
            else				//success
            	cout<<code<<" was removed from the top of the stack. \n";
		}
		
		//the peek command
		if(command.compare("PEEK") == 0)
        {
			cout<<"\n*** Peek Function. ***\n";
			code = peek(stack);
            if(code == -1)		//error code
                cout<<"Error! The stack is empty! \n";
            else				//success
            cout<<code<<" is the number on the top of the stack. \n";
		}
		
		//the print command
		if(command.compare("PRINT") == 0)
    	{
            cout<<"\n*** Print Function. ****\n";
            code = print(stack);
            if(code == -1)
                cout<<"Error! Cannot print an empty stack!";
            cout<<"\n";
		}

		//the exit command
        if(command.compare("EXIT") == 0)
        {
            cout<<"This is the end of the file! \n";
            cout<<"Quitting to the main menu. \n\n";
            x = 0;
            break;
        }
    	
    	//the below code just makes the user press enter to continue
    	cout<<"Press ENTER to continue. -> ";
    	do{
        	c = getch();
   	 	}while(c != 13);	//enter is ASCII value 13, so only enter will allow the user to continue. 1,2,a,b etc will NOT work!
        cout<<"\n\n";
        
    }while(x == 1);	//loop until the end of the file, which is until x == 0;
}

//Push Function
int push(int stack[],int tmp)
{
    //zero is the bottom, 9 is the top.
    int a, b;
    b = 0;		//make sure b is 0!
    
    for(a = 0; a <= 9; a++)
    {
        if(stack[a] == 0)	//if stack[a] is zero, then a num can be pushed to this spot in the array
        {
            stack[a] = tmp;
            break;
        }
        
        if(a == 9)	//if stack[a] is 9, it is the end of the array. check to see if it is full by checking if its not equal to zero.
        {
			if(stack[a] != 0)	//if this is true, then the whole array is full and therefor the number cannot not be pushed.
			{
				b = -1;	//-1 is the error code
				break;
			}
		}
        
    }
    
    if(b == -1)		//-1 is the error code used
        return -1;	//in this case the array is full
    else    
        return 0;  	//zero means success - the num was pushed correctly.
}

//Pop Function
int pop(int stack[])
{
	int a, b;
	b = 0;
	
	for(a = 0; a <= 9; a++)
	{
		if(stack[a] == 0)	//if stack[a] is zero, there's two possible options
		{	
			if(a > 0)	//a is greater than zero, therefor a num can be popped from the array
			{
				b = stack[a-1];	//b is one less than stack[a] because stack[a] is zero, so a-1 is the top most value.
				//also b is returned, so b is equal to that value for returning purposes
				stack[a-1] = 0;	//make it equal to zero.
				break;
			}
			
			if(a == 0)	//if stack[a] is zero AND a equals zero, the array is empty!
			{
				b = -1;	//error code
				break;
			}
		}
		
		if(a == 9 && stack[a] != 0)	//if a is 9, it is the top of the array. if stack[a] is also not zero, it means
		{							//there is a value there to be popped.
            b = stack[a];			//top most value therefor no a-1, just make b=stack[a] to return it
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

//Print function
int print(int stack[])
{
    int a, b;
    b = 0;
    
    for(a = 0; a <= 9; a++)
    {
        if(stack[a] != 0)			//if stack[a] isn't zero, just cout it as it is a value to be outputted.
            cout<<stack[a]<<"\t";
       	if(stack[a] == 0)			//if stack[a] is zero, two possible options
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
//**************************************************************************************************************************************
/*
Useful code for the futre? How to make a 'press enter to continue' prompt
works, but DECLARE <conio.h>!!!!

    char c;             //press enter variable
    cout<<"\nTo end the program, press enter. -> ";
    do{
        c = getch();
    }while(c != 13);
*/
