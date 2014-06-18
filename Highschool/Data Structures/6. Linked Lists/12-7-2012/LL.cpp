#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

struct node
{
	int 	data;				//structure for the linked list
	node 	*next;
};

void Enter(void);		//Each function handles a different part of the program.
void Manual(void);
void File(void);

int Add(struct node* head);
int Remove(void);
void Destroy(void);
void Print(struct node* head);

main()
{
	int opt = 0, end = 0;
	
	do{
		cout<<"Linked List V1.1 \n";		//Intro/Options you can enter.
		cout<<"1. Manual Entry \n";
		cout<<"2. File Entry \n";
		cout<<"3. Quit \n";
		
		do{
			cout<<"Enter an option. => ";
			cin>>opt;
		}while(opt != 1 && opt != 2 && opt != 3);	//Can only enter options 1, 2 or 3
		
		switch(opt)
		{
			case 1:	//Manual Entry
					system("cls");	//clear the screen
					Manual();
					break;
			case 2:	//File Entry
					system("cls");	//clear the screen
					File();
					break;
			case 3: 
					cout<<"\nQuitting... \n";
					end = 1;	//Ends the program as the main do/while loop ends.
					break;
		}
   		system("cls");	//clear the screen
	}while(end != 1);	//Only ends when 1 is entered.
}

void Enter(void)	//This function is just to stop the screen from ending quickly - makes the user hit enter before the program continues.
{
	char c;
	
	do{
		cout<<"\nPress ENTER to continue. => ";
        c = getch();
   	}while(c != 13);	//Only ends when the user presses ENTER
}

void Manual(void)	//This function does the manual entry portion of the program.
{
	int a = 0, end = 0, x = 0;
	
	do{
		node *head = NULL;					//Declares the head pointer.
		
		cout<<"Manual Entry. \n\n";			//Intro/Options you can enter
		cout<<"What do you want to do? \n";		
		cout<<"1. Add \n";						//Each number is used in a switch
		cout<<"2. Remove \n";					//to call up the function requested.
		cout<<"3. Destroy \n";
		cout<<"4. Print \n";
		cout<<"5. Quit \n";
		
		do{
			cout<<"=> ";
			cin>>x;
		}while(x != 1 && x != 2 && x != 3 && x != 4 && x != 5);
		
		switch(x)
		{
			case 1:
					Add(head);		//Goes to the add function
					break;
			case 2:
					Remove();		//Remove function
					break;	
			case 3:
					Destroy();		//Destroy function
					break;
			case 4:
					Print(head);	//Print Function
					break;
			case 5:
					end = 1;	//breaks the do/while loop so the program returns to the main.
					break;
		}
		Enter();		//Calls up the press enter to continue function
   		system("cls");	//clear the screen
	}while(end != 1);
}

//Below is all the linked list related functions
int Add(node *head)
{
	int a;
	cout<<"\nHow much do you want to add? \n";	//Ask user for input.
	cout<<"Enter it here. -> ";	
	cin>>a;										//Take an input from the user.
	
	node *nextNode;								//Declare a new pointer (nextNode)
	nextNode = new node;		//Allocate nextNode
	nextNode -> data = a;						//Set it equal to int a, which is what is being added to the list.
	nextNode -> next = head;					//Make nextnode point to the first node of the list.
	head = nextNode;							//nextNode is now the head of the list.	
}

int Remove(void)
{
	cout<<"\nRemove! \n";
}

void Destroy(void)
{
	cout<<"\nDESTROYING EVERYTHING... \n";
}

void Print(node *head)
{
	cout<<"\nDis is what is in teh arrays! \n";
	node *temp = head;
	
	if(temp == NULL)
	{
		cout<<"The list is empty! \n";
	}
	else
	{
		do{
		cout<<temp->data<<" ";
		temp = temp->next; 
		}while(temp != NULL);
	}
}

/*
USEFUL LINKS:
http://cslibrary.stanford.edu/103/LinkedListBasics.pdf
http://www.bogotobogo.com/cplusplus/linkedlist.php
http://www.codeproject.com/Articles/24684/How-to-create-Linked-list-using-C-C
http://www.overclock.net/t/426671/help-c-linked-list-output
*/

void File(void)		//This function handles all the file entry related stuff.
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
	
	cout<<"\nWhat is the name of the file you would like to open? \n";
    cout<<"Enter it here: => ";
    cin>>filename;		//make sure to enter the full name ie data1.txt
    cout<<'\n';
    entry.open(filename.c_str());	//opens the file, using the name the user entered in
    
    if(!entry)     //if the inventory file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file! \n";
        Enter();
        exit(0);        //exit the program
    }
    
    //Edit the below to work for this program!!
    
    /*
    if(strncmp(command.c_str(), "ADD", 3) == 0)
    
    if(command.compare("REMOVE") == 0)
    
    if(command.compare("DESTROY") == 0)
    
    if(command.compare("PRINT") == 0)
    */
}
