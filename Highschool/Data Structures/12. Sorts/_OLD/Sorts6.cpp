#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

/*
Sorts to code:
	1. SelectionSort
	http://en.wikipedia.org/wiki/Selection_sort
	2. MergeSort
	http://en.wikipedia.org/wiki/Merge_sort
	3. QuickSort
	http://en.wikipedia.org/wiki/Quicksort
	
Also need to:
	SortCheck
	SortReport
	
DONE:
	1. ReadData
	2. Garbage Collection
	3. Bubble Sort
*/

//Doubly linked list structure
struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	int data;		//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
	node *prev;		//This will point to the last node.
};

//Functions for the program
void ReadData(node **head, node **tail);	//Handles file related stuff (takes in all the data)
void SortCheck(node **head, node **tail);	//Checks to make sure the sort function worked properly
void SortReport(node **head, node **tail);	//Reports how long each sorting element took
void Destroy(node **head);					//Function to DESTROY the list at the end of the program

void BubbleSort(node **head, node **tail);
void SelectionSort(node **head, node **tail);	//Sorting functions
void MergeSort(node **head, node **tail);
void QuickSort(node **head, node **tail);

int Add(int a, node **head, node **tail);	//Function to add numbers to the list
void Print(node **head, node **tail);		//Test function - used during beta testing to make sure the sorting functions ACTUALLY sorted the data.
void Enter(void);	//For the "Press Enter to Continue..." prompt

int main()	//ZE MAIN
{
	int x = 1, ret = 0;
	
	do{
		node *head = NULL; 		//head of the linked list - points to the start of the list. Set to NULL as there aren't any elements in the list (yet).
		node *tail = NULL;		//tail of the linked list - points from the end of the list back toward the front.
		clock_t begin, end;		//For timing how long the sort takes.
		double times[3];		//Array with the 4 times from each function
		
		cout<<"SORTS V1.1 \n";
		cout<<"\nWelcome to the SORTS program! \n";
		cout<<"This program allows you to run various sorting algorithms to find out \n";
		cout<<"which one is the fastest! \n";		
		cout<<"Are you ready to run the program? \n";
		Enter();
		
		ReadData(&head, &tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
			//Print(&head, &tail);		//Beta testing purposes
		
	//BUBBLE SORT
		begin = clock();			//Start time
		BubbleSort(&head, &tail);	//Calls the BubbleSort function up, making ret equal to whatever BubbleSort returns
		end = clock();				//End time
		times[0] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		
		ret = SortCheck(&head, &tail);		//This checks to see if the BubbleSort function sorted the list correctly
		if(ret == 0)						//If ret = 0, then don't do anything
			//Do nothing
		if(ret == 1)						//If it equals 1 though there was a problem in the sorting function
			cout<<"ERROR! LIST NOT SORTED! RESULTS ARE INVALID!!! \n";
			
		Destroy(&head);				//Destroy the list so another blank, unsorted list can be created.
		
	//SELECTION SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(&head, &tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		SelectionSort(&head, &tail);
		end = clock();				//End time
		times[1] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		Destroy(&head);				//Destroy the list so another blank, unsorted list can be created.
	
	//MERGE SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(&head, &tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		MergeSort(&head, &tail);
		end = clock();				//End time
		times[2] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		Destroy(&head);				//Destroy the list so another blank, unsorted list can be created.
	
	//QUICK SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(&head, &tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		QuickSort(&head, &tail);
		end = clock();				//End time
		times[3] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		Destroy(&head);				//Destroy the list so another blank, unsorted list can be created.

		cout<<"\n\nWow, that was quick! Let's see which sort was the fastest! \n";
		
		//SortReport	Make sure to check each sort!
		
		cout<<"Would you like to run the program again? \n";
		do{
			cout<<"Press 1 to continue, 2 to quit. \n";
			cout<<"=> ";
			cin>>x;
		}while(x != 1 && x != 2);
		
		system("CLS");
			
	}while(x == 1);
	
	return 0;
}

//THE SORTING FUNCTIONS

void BubbleSort(node **head, node **tail)
{
	int swap = 0, temp = 0;	//0 means no sort was performed, 1 means one was. Must complete on whole pass without swap = 1
	node *curr, *last;		//Temporary pointers
	curr = *head;			//Start off with curr equaling head
	last = *tail;
	
	if(*head == NULL)		//If head is NULL there is no list to sort!
	{
		cout<<"\nError! Cannot sort an empty list! \n";		//-1 is an empty list (cannot sort nothing)
		return;												//Stop the function from going on
	}
	
	if(curr -> next == NULL)//There's no need to sort - there's only one element!
		return;			//So stop this function from continuing.
	
	do{
		curr = *head;	//Set curr to *head for running through the list
		swap = 0;		//Reset swap as to 0
		
		do{    
			if(curr -> data > curr -> next -> data)		//Note: This only swaps DATA so no need to worry about the pointers!
			{
				     		temp = curr -> data;			//Hold the next node 
					curr -> data = curr -> next -> data;	//Make the next node equal to the previous node
			curr -> next -> data = curr -> data;			//Make the previous node equal to the next node
				    		swap = 1;						//Flag this pass as having a swap
			}
			curr = curr -> next;		//Move temp up one node	
		}while(curr -> next != last);	//If temp equals tail, it has hit the end of the list!
		
	}while(swap == 1);					//Run until the sort is complete, which is when one complete pass does not make swap = 1.
	//if it gets to this point the list has successfully been sorted! WOO HOO!
}

void SelectionSort(node **head, node **tail)	
{

}
void MergeSort(node **head, node **tail)
{

}
void QuickSort(node **head, node **tail)
{

}

//-----------------------------------------------------------------------------------------------------------------------------
//These functions handle the basic doubly linked operations. Ie ReadData, Adding, Deleting the list, etc.

void ReadData(node **head, node **tail)
{
	ifstream entry;		//ifstream for opening the file
    string filename("SortData.txt");    //string to hold the filename (change this for different file names!)
    string command;     //string to hold each line in the file
	int num = 0;		//final num to send to the functions
	int code = 0;		//code that holds the return value of the functions
	char c;             //press enter variable
    int a, x = 1;		//x is for the do/while loop
    
    entry.open(filename.c_str());	//opens the file, using the name the user entered in
    
    if(!entry){     //if the file does not open, this is true. the error below will then print out.
        cout<<"Unable to open the selected file! \n";
        Sleep(5000);    //pause for 5 seconds
        exit(0);        //exit the program
    }
    
    do{
		num = 0;
		getline(entry, command, '\n');
		
		//End of file command
        if(command.compare("***") == 0){
			entry.close();	//closes the file
            break;			//Breaks out of the loop
        }
		//Otherwise, just add the number!
        else{
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
	
	if(*head == NULL){					//IF head is NULL, then the list is empty!
		*head = curr;					//So make head point to temp! Now the list has one element! YAY!
		*tail = curr;					//Tail also points to temp!
	}
	else{								//IF it isn't, then search for the end!
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

void SortCheck(node **head, node **tail);	//Checks to make sure the sort function worked properly
{
	int check = 0;			//This will equal 1 if the program detects an error in the sort
	node *curr, *last;		//Temporary pointers
	curr = *head;			//Start off with curr equaling head
	last = *tail;			//and last equaling tail
	
	do{
		if(curr -> data < curr -> next -> data)	//If this current node is less then the next node
			curr = curr -> next;				//Then the sort function worked and move forward 1 node
		else{									//Otherwise something went wrong
			check = 1;							//Hmm, doesn't seem to have been sorted right!
			break;								//Stop checking, we know it's wrong if just 1 wasn't right
		}
	}while(curr != last);						//Run until the very last node
	
	if(check = 0)	//Everything was correctly sorted
		return 0;
		
	if(check = 1)	//Everything WAS NOT correctly sorted!
		return 1;
}

void SortReport(node **head, node **tail);	//Reports how long each sorting element took
{
	
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

void Print(node **head, node **tail)
{
	cout<<"\nTHE FOLLOWING IS USED FOR TESTING PURPOSES.";
	cout<<"\nThis is what is in teh list! \n\n";
	int a = 0;
	node *temp;		//Temporary pointer
	temp = *head;	//Makes temp equal to head
	
	if(temp == NULL)	//head is also NULL, aka empty list.
	{
		cout<<"ERROR! The list is empty! \n";	//eek! the list is empty!
	}
	else								//Well, the list has something stored! Print the nodes out!
	{
		//FORWARDS
		do{
			cout<<temp -> data<<'\t';	//couts the current node
			temp = temp -> next; 		//basically moves it forward one node
			a++;
			if(a == 100)
				Enter();
		}while(temp != NULL);			//run until the end of the linked list
		cout<<"\n\n";
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
