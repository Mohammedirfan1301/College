#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>		//INCLUDES
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
int SortCheck(node **head, node **tail);	//Checks to make sure the sort function worked properly
void SortReport(double times[]);			//Reports how long each sorting element took
void Destroy(node **head);					//Function to DESTROY the list at the end of the program

void BubbleSort(node **head, node **tail);
void SelectionSort(node **head, node **tail);	//Sorting functions
void MergeSort(node **head, node **tail);
void QuickSort(node **head, node **tail, node *left, node *right);

void WhichSort(int a);
int Add(int a, node **head, node **tail);	//Function to add numbers to the list
int Remove(int a, node **head, node **tail);//Removes from the list
void Print(node **head, node **tail);		//Test function - used during beta testing to make sure the sorting functions ACTUALLY sorted the data.
void Enter(void);							//For the "Press Enter to Continue..." prompt

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
		
		ret = SortCheck(&head, &tail);		//This checks to see if the BubbleSort function sorted the list correctly
		if(ret == 0)						//If ret = 0, then don't do anything
			//Do nothing
		if(ret == 1)						//If it equals 1 though there was a problem in the sorting function
			cout<<"ERROR! LIST NOT SORTED! RESULTS ARE INVALID!!! \n";
			
		Destroy(&head);				//Destroy the list so another blank, unsorted list can be created.
	
	//MERGE SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(&head, &tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		MergeSort(&head, &tail);
		end = clock();				//End time
		times[2] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		
		ret = SortCheck(&head, &tail);		//This checks to see if the BubbleSort function sorted the list correctly
		if(ret == 0)						//If ret = 0, then don't do anything
			//Do nothing
		if(ret == 1)						//If it equals 1 though there was a problem in the sorting function
			cout<<"ERROR! LIST NOT SORTED! RESULTS ARE INVALID!!! \n";
			
		Destroy(&head);				//Destroy the list so another blank, unsorted list can be created.
	
	//QUICK SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(&head, &tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		QuickSort(&head, &tail, head, tail);
		end = clock();				//End time
		times[3] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		
		ret = SortCheck(&head, &tail);		//This checks to see if the BubbleSort function sorted the list correctly
		if(ret == 0)						//If ret = 0, then don't do anything
			//Do nothing
		if(ret == 1)						//If it equals 1 though there was a problem in the sorting function
			cout<<"ERROR! LIST NOT SORTED! RESULTS ARE INVALID!!! \n";
			
		Destroy(&head);				//Destroy the list so another blank, unsorted list can be created.

		cout<<"\n\nWow, that was quick! Let's see which sort was the fastest! \n";
		
		SortReport(times);	//Calls the report function to determine which function was the quickest.
		
		cout<<"\nWould you like to run the program again? \n";
		do{
			cout<<"Press 1 to continue, 2 to quit. \n";
			cout<<"=> ";
			cin>>x;
		}while(x != 1 && x != 2);
		
		system("CLS");
			
	}while(x == 1);
	
	return 0;	//End of the program, good bye!
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
		return;				//So stop this function from continuing.
	
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
	node *curr = *head, *last = *tail, *cont = NULL, *min = NULL;	//Temp pointers. Curr/Last are head/tail. Cont is where to continue the list from
	int hold = 0;
	
	if(*head == NULL)		//If head is NULL there is no list to sort!
	{
		cout<<"\nError! Cannot sort an empty list! \n";		//-1 is an empty list (cannot sort nothing)
		return;												//Stop the function from going on
	}
	
	if(curr -> next == NULL)//There's no need to sort - there's only one element!
		return;				//So stop this function from continuing.
	
	for(curr = *head; curr -> next != NULL; curr = curr -> next)	//Run through the entire list
	{
		min = curr;		//Make min equal to the current position (to compare against the other numbers)

		for(cont = curr -> next; cont -> next != NULL; cont = cont -> next)	//Start comparing from the next node on to the end of the list
			if(cont -> next -> data < min -> next -> data)					//If it finds a value that is less then the current min
				min = cont;													//Then this becomes the new minimum!
	
		if(min != curr)	//If min is different then what it originally was (ie a swap should take place)
		{
			        hold = curr -> data;	//Hold the current data
			curr -> data = min -> data;		//Make the current equal to the minimum data
			min -> data = hold;				//Make the mimimum data equal to the hold data
		}
	}
}

void MergeSort(node **head, node **tail)
{
	node *old;		//Holds the old list's head
	old = *head;	//^
	
	if(*head == NULL)		//If head is NULL there is no list to sort!
	{
		cout<<"\nError! Cannot sort an empty list! \n";		//-1 is an empty list (cannot sort nothing)
		return;												//Stop the function from going on
	}
	
	if(old -> next == NULL)//There's no need to sort - there's only one element!
		return;				//So stop this function from continuing.
	
}

void QuickSort(node **head, node **tail, node *left, node *right)
{
	node *start, *curr;
	int hold;									
											
	if(left == right)	//If left and right are equal, there's no list to sort!
	{
		return;			//OR we've finished sorting!
	}
	
	start = left;			//Set the start/curr pointers
	curr = start -> next;
	
	do{		//Loop until curr moves all the way to the right
		if(start -> data < curr -> data)	//A swap must occur if the start data is less then the right
		{
			         hold = curr -> data;
			 curr -> data = start -> data;
			start -> data = hold;
		}
		
		if(curr == right)	//We've gone all the way to right side of the list at this point so stop
			break;
		
		curr = curr -> next;
	}while(1);	
	
	//Move right 1
			hold = left -> data;
	left -> data = curr -> data;
	curr -> data = hold;
	
	//Save the current node
	node *old = curr;
	
	//Check to see if we need to sort the left side of the current node
	curr = curr -> prev;
	if(curr != NULL)
	{
		if(left -> prev != curr && curr -> next != left)
			QuickSort(head, tail, left, curr);
	}
	
	//Check to see if we need to sort the right side of the current node
	curr = old;
	curr = curr -> next;
	if(curr != NULL)
	{
		if(curr -> prev != right && right -> next != curr)
			QuickSort(head, tail, curr, right); 
	}
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
        if(command.compare("**") == 0){
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

int Remove(int a, node **head, node **tail)
{
	int found = 0;			//Int to detect if the variable entered was in the list
	node *curr, *befo;		//Temporary pointers
	curr = *head;			//Curr now equals head
	
	if(*head == NULL)		//If the list is empty, don't even bother searching - the number isn't there! :P
		return -2;			//(thus return an error)
	else
	{
		do{								//Search through the list for the number by using temp. Check the first node's data value. 
			if(curr -> data == a)		//Then move forward one and check again. If it is found, remove it and return the given number (in this case var. a)
			{							//to indicate success!
				found = 1;
				
				if(curr -> next == NULL && curr -> prev == NULL)	//If this is the really end of the list - then we must make tail and head NULL!
				{
					*head = NULL;	//Both must equal NULL
					*tail = NULL;
					delete curr;	//Delete current node & this is also the last node :(
					return a;		//Return a for success!
				}
				
				if(curr == *head)			//If the value is found in the start of the list
				{
					*head = curr -> next;	//Then head must be reassigned - in this case just by moving it forward one. 
					befo = *head;			//Make a temp pointer equal to head
					befo -> prev = NULL;	//make sure befo's prev is equal to NULL though! or randon numbers will appear!
					delete curr;		 	//Remove the node containing 'a' (the current node)
					return a;
				}
				
				if(curr == *tail)			//If the value is the last node of the list, make sure the last node's pointer is NULL! 
				{							//or you'll have a bad pointer!
					*tail = curr -> prev;	//Make sure to reassign tail!
					befo = *tail;
					befo -> next = NULL;	//make prev's next NULL because it doesn't point to anything! its the end of the list now!
					delete curr;			//Remove the node containing 'a' (the current node)
					return a;
				}
				
				else							//If the value is somewhere in the middle, then just rearrange a few things
				{
					befo -> next = curr -> next;	//Reroute the nodes - the previous node's (temp2) next should point to the next node 
					curr -> next -> prev = befo;	//Reroute the prev's pointer as well.
					/*
					IMPORTANT LOGIC NOTE!!!!
					IF a list looks like so:
					1	2	3
					AND you try to remove 2, this else activates. Now this is tricky!!
					You must link 1 -> 3 and 3 -> 1
					befo -> next is 1. This should = 3, or curr -> next
					BUT linking 3 -> 1 is not just 'befo -> prev = curr -> prev like i thought! this would BREAK the list! and make 3 point to 2 which DOESNT EXIST
					aka a POINTER ERROR. BAD. NOT GOOD!
					so to make 3 point to 1, you must go to curr's next, or 3 and point it's prev to 1, or before! (befo)
					NOTE THIS FOR FUTURE LINKING OF LISTS!@@@@
					*/
					delete curr;					//Remove the node containing 'a' (the current node)
					return a;
				}
		
			}
			befo = curr;		 //stores the (soon to be previous) node
			curr = curr -> next; //move forward one node
		}while(curr != NULL);	
	}
	
	if(found == 0)	//WASN'T FOUND IN THE LIST! so return -1 for error!
		return -1;
}

int SortCheck(node **head, node **tail)	//Checks to make sure the sort function worked properly
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

void SortReport(double times[])	//Reports how long each sorting element took
{
	/*
	First thing I did was sort the times in order. This is tricky as I need to keep track of which time goes with which sort
	So whenever I swap times, I swap the order of the sorts.
	Also, the following is which sort is which
	0 = Bubble
	1 = Selection
	2 = Merge
	3 = Quick
	*/
	
	int hold = 0, swap = 0, a = 0;
	double temp = 0;
	int order[3];	//holds the order of the sorts originally
	
	for(a = 0; a < 4; a++)	//The Order array only contains the numbers 0, 1, 2 and 3
		order[a] = a;		//This is used for keeping track of which time is which sort
							//Ex: Everytime the BubbleSort time swaps, 0 (BubbleSort's #) swaps with it
	do{
		swap = 0;		//Reset swap/a to 0
		a = 0;
		do{
			if(times[a] > times[a+1])	
			{								//Just a bubble sort	
					  temp = times[a];		
				  times[a] = times[a+1];	//Change the order of the times
				times[a+1] = temp;		
				
				      hold = order[a];
				  order[a] = order[a+1];	//This allows me to track which sort is which
				order[a+1] = hold;
				
				      swap = 1;				//swap = 1 signals another round of sorting
			}
			a++;						//Move forward one
		}while(a < 3);	//Run through the list of times
	}while(swap == 1);	//Run as long as sorting is needed (only needed if swap equals 1 - if zero then loop breaks as sorting is done!)

	//Now that the times are in order and I know which time goes with which sort, I can report which sort was quickest and which was slowest!
	
	cout<<"1st: ";
	WhichSort(order[0]);
	cout<<" with a time of "<<times[0]<<" seconds! \n";
	
	cout<<"2nd: ";
	WhichSort(order[1]);
	cout<<" with a time of "<<times[1]<<" seconds! \n";
	
	cout<<"3rd: ";
	WhichSort(order[2]);
	cout<<" with a time of "<<times[2]<<" seconds! \n";
	
	cout<<"4th: ";
	WhichSort(order[3]);
	cout<<" with a time of "<<times[3]<<" seconds! \n";
}

void WhichSort(int a)	//Makes figuring out which sort is which much easier - only need to call a function versus
{						//Using each of these four if statements each time.
	if(a == 0)			//So rather then having 16 Ifs, I have one function of four ifs.
		cout<<"BubbleSort";
	if(a == 1)
		cout<<"SelectionSort";
	if(a == 2)
		cout<<"MergeSort";
	if(a == 3)
		cout<<"QuickSort";
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
