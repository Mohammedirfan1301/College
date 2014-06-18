#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

//Doubly linked list structure
struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	int data;		//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
	node *prev;		//This will point to the last node.
};

//Functions for the program
void ReadData(node **head, node **tail);	//Handles file related stuff (takes in all the data)
int Add(int a, node **head, node **tail);	//Function to add numbers to the list
void Destroy(node **head);					//Function to DESTROY the list at the end of the program
void Enter(void);	//For the "Press Enter to Continue..." prompt
//void Print(node **head, node **tail);		//For testing purposes (Making sure the file setup works)

//TEH MAIN
int main()
{
	do{
		node *head = NULL; 		//head of the linked list - points to the start of the list. Set to NULL as there aren't any elements in the list (yet).
		node *tail = NULL;		//tail of the linked list - points from the end of the list back toward the front.
		
		cout<<"SORTS V1.00 \n";
		ReadData(&head, &tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
			
		cout<<"\n\nWelcome to the SORTS program! \n";
		cout<<"This program allows you to run various sorting algorithms to find out which one is the fastest! \n";		
		cout<<"Are you ready to run the program? \n";
		Enter();
	
		/*
			1. BubbleSort
			2. SelectionSort
			3. MergeSort
			4. QuickSort
			
			Make sure to check each sort!
		*/
	
		cout<<"Wow, that was quick! Let's see which sort was the fastest! \n";
		
		//SortReport
		
		
		
		Destroy(&head);			//Destroys the doubly linked list
	}while(0);
	
	//Print(&head, &tail);	//Used for testing - to insure that there actually is a listed of something!
	
	return 0;
}

//THE SORTING FUNCTIONS
//TO BE CODED! SOON!

/*
Sorts to code:
	1. BubbleSort
	2. SelectionSort
	3. MergeSort
	4. QuickSort
	
Also need to:
	SortCheck
	SortReport
	
DONE:
	1. ReadData
	2. Garbage Collection
*/

//-----------------------------------------------------------------------------------------------------------------------------
//These functions handle the basic doubly linked operations. Ie Files, Adding, Deleting the list, etc.

void ReadData(node **head, node **tail)
{
	ifstream entry;		//ifstream for opening the file
    string filename;    //string to hold the filename
    string command;     //string to hold each line in the file
	int num = 0;		//final num to send to the functions
	int code = 0;		//code that holds the return value of the functions
	char c;             //press enter variable
    int a, x = 1;		//x is for the do/while loop
    
    cout<<"FILE ENTRY \n\n";
    cout<<"What is the name of the file you would like to open? \n";
    cout<<"Enter it here: -> ";
    cin>>filename;		//make sure to enter the full name ie data1.txt
    cout<<'\n';
    entry.open(filename.c_str());	//opens the file, using the name the user entered in
    
    if(!entry)     //if the file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file! \n";
        Sleep(5000);    //pause for 5 seconds
        exit(0);        //exit the program
    }
    
    do{
		num = 0;
		getline(entry, command, '\n');
		
		//End of file command
        if(command.compare("***") == 0)
        {
			entry.close();	//closes the file
            cout<<"\nThis is the end of the file! \n";
            cout<<"Quitting to the main menu. \n=>";
			Sleep(5000);    //pause for 5 seconds
            break;
        }
		//Otherwise, just add the number!
        else
        {
			num = atoi(command.c_str());	//convert the string to an int.
			code = Add(num, head, tail);	//Send it to the add function
			
            if(code == 0)				//if ADD returns zero, everything worked fine
            	//cout<<"SUCCESS! \n";	//(For testing purposes)
            if(code == -1)				//if ADD returns -1 bad things happened and therefore something went wrong
            {
				cout<<"ERROR! Memory allocation failed! \n";	//aka memory allocation failed	
				break;
			}
		}
    }while(x == 1);	//loop until the end of the file, which is until x == 0;	
}

int Add(int a, node **head, node **tail)	//Adds data to the linked list
{	
	node *curr, *befo;					//Temporary pointers
	
	curr = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
	if(!curr)							//If temp threw a NULL, then it seems memory allocation failed!
		return -1;						//Therefore return -1 to show memory allocation failed error to the user.
	curr -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
	curr -> next = NULL;				//next is NULL as it will be the last node when added.
	curr -> prev = NULL;				//(I will be adding nodes to the end of the list)
							
	if(*head == NULL)					//IF head is NULL, then the list is empty!
	{
		*head = curr;					//So make head point to temp! Now the list has one element! YAY!
		*tail = curr;					//Tail also points to temp!
	}
	
	else								//IF it isn't, then search for the end!
	{
		befo = *head;					//The list isn't empty - I will have to search for the last node.
		while(befo -> next != NULL)		//FIND the last node - the one just before NULL!
			befo = befo -> next;		//befo now contains the address of the last node
		befo -> next = curr;			//Make curr the last node in the linked list.
		curr -> prev = befo;			//Make curr's prev point to befo.
		curr -> next = NULL;			//Make sure its NULL just incase!
		*tail = curr;					//Make tail point to curr, as this now the tail of the list!
	}
	
	return 0;
}

void Destroy(node **head)		//Function that deletes the list from memory
{
	node *curr, *root;	//Temporary pointers
	root = *head;		//root is now equal to the first node
	if(*head == NULL)	
		return;			//if the list is empty no need to do the following else!
	else
	{					//if the list has nodes - run the following
		do{				
			curr = root;			//curr equals the first node.
			root = root -> next;	//root is now equal to the next node
			delete curr;			//curr is deleted - this means root is actually equal to the first node now (since the current one was deleted!)
			if(root -> next == NULL)//if root's next is NULL, then the last node was deleted with the 'delete curr' line. 
				*head = NULL;		//so this means *head can be set equal to NULL (an empty list)
		}while(*head != NULL);		//and the do/while stops running as the list is empty and all nodes were deleted from memory.
	}
}

void Enter(void)	//This function is just to stop the screen from ending quickly - makes the user hit enter before the program continues.
{
	char c;
	
	do{
		cout<<"\nPress ENTER to continue. => ";	//PRESS ENTER!!
        c = getch();
   	}while(c != 13);	//Only ends when the user presses ENTER
}

/* void Print(node **head, node **tail)	//This function was used for testing - I wanted to make sure the doubly linked list was set up properly.
{										//And that it also worked forwards and backwards.
	node *temp;		//Temporary pointer
	temp = *head;	//Makes temp equal to head
	
	if(temp == NULL)	//head is also NULL, aka empty list.
	{
		cout<<"ERROR! The list is empty! \n";	//eek! the list is empty!
	}
	else	//Well, the list has something stored! Print the nodes out!
	{
		//FORWARDS
		do{
			cout<<temp -> data<<'\t';	//couts the current node
			temp = temp -> next; 		//basically moves it forward one node
		}while(temp != NULL);	//run until the end of the linked list
		
		temp = *tail;					//make temp equal to the last node pointing back.
		
		//BACKWARDS
		do{
			cout<<temp -> data<<'\t';
			temp = temp -> prev;
		}while(temp != NULL);
		cout<<'\n';
	}
} */
