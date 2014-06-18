#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

int enqueue(int queue[], int tmp);  //enqueue function
int dequeue(int queue[]);			//dequeue function
int peek(int queue[]);         		//peek function
int print(int queue[]);             //print function
void manual(int queue[]);           //manual function (handles the manual entry part)
void file(int queue[]);             //file function  (handles the file entry part)

int main()
{
	int queues[10] = {0};    //array of 10 ints. known as 'queue' in the functions.
    int opt = 0;             //end variable ("Option")
    
	do{ //main do/while - controls manual/file/quit options
		cout<<"*****************************\n";
        cout<<"Welcome. Choose an option: \n";  //the user can do three things
        cout<<"1. Manual Entry \n"; 			//manully enter numbers
        cout<<"2. File Entry \n";				//use a file to enter numbers
        cout<<"3. Quit \n";						//or end the program.
    
        do{
            cout<<"Enter an option. -> ";           //asks user to enter one of the above numbers.
            cin>>opt;
        }while(opt != 1 && opt != 2 && opt != 3);	//can ONLY enter 1, 2 or 3.
    
        cout<<'\n';
    
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
                file(queues);   //proceeds to the file entry function.
                break;
            case 3:
                cout<<"***************************** \n";
                cout<<"\nGood bye, Commander. \n";
                Sleep(5000);    //pause for 5 seconds as 1 sec = 1000 ms. does this to prevent the window from closing instantly.
                break;
            default:	//this can't happen as the above code only allows entry of numbers 1,2 or 3.
                cout<<"\nYou didn't enter a valid command, Sir. \n";
                cout<<"Please enter a number between 1 and 3. \n";
                break;
        }
        memset(queues, 0, 10);	//clear the queue array incase the program is used more than once.
    }while(opt != 3);   //the program does not end until the user enters '3' at the first prompt
    
	return 0;
}

//************************************************************************************************************************
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
        
        case 2:
            cout<<"\n*** Dequeue Function. ***\n";
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
            
        case 4:
            cout<<"\n*** Print Function. ****\n";
            code = print(queue);	//if everything works, the print function prints. it only returns -1 if there is an error ie the stack is empty.
            if(code == -1)	//error!
                cout<<"Error! Cannot print an empty stack!";
            cout<<"\n";
            break;
            
        case 5:
            cout<<"\nGood bye, Commander. \n\n";
            for(a = 0; a < 10; a++)	//run 10 times in case there are 10 values in the array.
            	dequeue(queue);		//makes sure the array is cleared for the next run through by popping any values that are still in the array.
            break;

        default:	//i made sure the user can only enter 1-5, but just in case this will print out.
            cout<<"\nHow did you get here? \n";
            break;
    }
    }while(comd != 5);	//run until the user enters 5, which quits the manual entry option.
}

//***********************************************************************************************************
//file function - used if the user decides to use a file to input all the commands.
void file(int queue[])
{
    ifstream entry;		//ifstream for opening the file
    string filename;    //string to hold the filename
    string command;     //string to hold each line in the file
    string hold;		//string that holds the first part of command
    string input;		//string to hold the input (ie '3') that will then be converted to an int
	int num = 0;		//final num to push to the functions
	int code = 0;		//code that holds the return value of the functions
	char c;             //press enter variable
    int a, x = 1;		//x is for the do/while loop
    
    cout<<"What is the name of the file you would like to open? \n";
    cout<<"Enter it here: -> ";
    cin>>filename;		//make sure to enter the full name ie data1.txt
    cout<<'\n';
    entry.open(filename.c_str());	//opens the file, using the name the user entered in
    
    if(!entry)     //if the inventory file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file! \n";
        Sleep(5000);    //pause for 5 seconds
        exit(0);        //exit the program
    }
    
    do{
		num = 0;
		getline(entry, command, '\n');
		
		//Enqueue Command
        if(strncmp(command.c_str(), "ENQUEUE", 7) == 0)	//if the first four letters are equal to the letters of push, strncmp will return a zero meaning that the push command should be launched.
        {									//the first issue to tackle is getting a num to be pushed, so:
			cout<<"\n*** Enqueue Function. *** \n";
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
			code = enqueue(queue, num);	//the following works just like the manual part of the program
            if(code == 0)				//if push returns zero, everything worked fine so print the num with a message to the user.
                cout<<num<<" was successfully pushed to the stack. \n";	//message says everything is working.
            if(code == -1)				//if push returns -1 bad things happened and therefore something went wrong
                cout<<"Error! The stack is full! \n";	//so tell the user the error.
		}
		//after just call up the respected function!
		//there really doesn't need to be much explantion as this works for the most part like the manual part of the program.
        
		//Dequeue Command
		if(command.compare("DEQUEUE") == 0)
        {
            cout<<"\n*** Dequeue Function. ***\n";
			code = dequeue(queue);
            if(code == -1)		//error code
            	cout<<"Error! The stack is empty! \n";
            else				//success
            	cout<<code<<" was removed from the top of the stack. \n";
		}
		
		//Peek Command
		if(command.compare("PEEK") == 0)
        {
			cout<<"\n*** Peek Function. ***\n";
			code = peek(queue);
            if(code == -1)		//error code
                cout<<"Error! The stack is empty! \n";
            else				//success
            cout<<code<<" is the number on the top of the stack. \n";
		}
		
		//Print Command
		if(command.compare("PRINT") == 0)
    	{
            cout<<"\n*** Print Function. ****\n";
            code = print(queue);
            if(code == -1)
                cout<<"Error! Cannot print an empty stack!";
            cout<<"\n";
		}

		//exit command
        if(command.compare("EXIT") == 0)
        {
			entry.close();	//closes the file
            cout<<"This is the end of the file! \n";
            cout<<"Quitting to the main menu. \n\n";
            x = 0;
            for(a = 0; a < 10; a++)	//run 10 times in case there are 10 values in the array.
            	dequeue(queue);		//makes sure the array is cleared for the next run through by popping any values that are still in the array.
            break;
        }
    	
    	//the below code just makes the user press enter to continue
    	cout<<"Press enter to continue. -> ";
    	do{
        	c = getch();
   	 	}while(c != 13);
        cout<<"\n\n";
        
    }while(x == 1);	//loop until the end of the file, which is until x == 0;
}

//*********************************************************************************

//Push Function
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

//Pop Function
int dequeue(int queue[])
{
	int a, b;
	b = 0;
	
	if(queue[0] == 0)	//if queue[0] is zero, the array is empty, so return -1 as an error code
		b = -1;
	if(queue[0] != 0)	//if queue[0] isn't zero, remove the value. then, shift all the elements in the array forward one.
	{
		b = queue[0];
		queue[0] = 0;	//pop off the first number (first one in is the first one out)
		
		for(a = 0; a <= 9; a++)
		{
			if(a > 0)
			{
				queue[a-1] = queue[a];
			}
			
			if(a == 9)
			{
				if(queue[a] != 0)
					queue[a] = 0;
			}
		}
		
	}
	
	return b;	//return b which is either the num popped or -1 which is an error code.
}

//Peek Function
int peek(int queue[])
{
    int a, b, c;
    b = 0;
    //peek is simple for queues - the first value is queue[0], as that will always be the first element in.
	if(queue[0] == 0)	//if the first value equals zero, then the array is empty and an error should be returned.
		b = 0;
	if(queue[0] != 0)	//if the first value isn't zero, then just make sure no errors are returned and return the value of queue[0].
	{
		b = 1;
		c = queue[0];
	}
    
    if(b == 0)	//if b is zero, a is zero and stack[a] is zero. therefore the array is empty.
        return -1;	//so return an error code.
    else
        return c;
}

//Print function
int print(int queue[])
{
    int a, b;
    b = 0;
    
    for(a = 0; a <= 9; a++)
    {
        if(queue[a] != 0)			//if queue[a] isn't zero, just cout it as it is a value to be outputted.
            cout<<queue[a]<<"\t";
       	if(queue[a] == 0)			//if queue[a] is zero, two possible options
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
