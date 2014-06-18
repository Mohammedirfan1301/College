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
void ReadData(node *&head, node *&tail);	//Handles file related stuff (takes in all the data)
int SortCheck(node *head);					//Checks to make sure the sort function worked properly
void SortReport(double times[]);			//Reports how long each sorting element took
void Destroy(node *&head);					//Function to DESTROY the list at the end of the program

void BubbleSort(node *head, node *tail);
void SelectionSort(node *head, node *tail);	//Sorting functions
struct node *MergeSort(node *head);
struct node *QuickSort(node *head);

//Other Functions
void WhichSort(int a);
int Add(int a, node *&head, node *&tail);	//Function to add numbers to the list
int Remove(int a, node *&head, node *&tail);//Removes from the list
void Print(node *head);			//Test function - used during beta testing to make sure the sorting functions ACTUALLY sorted the data.
void Enter(void);							//For the "Press Enter to Continue..." prompt

int main()	//ZE MAIN
{
	int x = 1, r = 0;
	
	do{
		node *head = NULL; 		//head of the linked list - points to the start of the list. Set to NULL as there aren't any elements in the list (yet).
		node *tail = NULL;		//tail of the linked list - points from the end of the list back toward the front.
		clock_t begin, end;		//For timing how long the sort takes.
		double times[3];		//Array with the 4 times from each function
		
		cout<<"SORTS V1.6 \n";
		cout<<"\nWelcome to the SORTS program! \n";
		cout<<"This program allows you to run various sorting algorithms to find out which \n";
		cout<<"one is the fastest! This includes Bubble Sort, Selection Sort, Merge Sort   \n";		
		cout<<"and Quicksort! Are you ready to run the program? \n";
		Enter();
		cout<<"\n\n";	//(So errors don't appear right next to the =>)
		
//===========================================================================================================================================================
		ReadData(head, tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		//Print(head);				//Beta testing purposes
		
	//BUBBLE SORT
		begin = clock();			//Start time
		BubbleSort(head, tail);		//Calls the BubbleSort function up, making ret equal to whatever BubbleSort returns
		end = clock();				//End time
		times[0] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		r = SortCheck(head);			//This checks to see if the BubbleSort function sorted the list correctly
		if(r == 1)
		{
			cout<<"BUBBLE SORT DIDN'T SORT RIGHT! SORTING ERROR! \n";
			times[0] = -1;
		}
		//Print(head);				//Beta testing purposes
		Destroy(head);				//Destroy the list so another blank, unsorted list can be created.
		
	//SELECTION SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(head, tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		SelectionSort(head, tail);
		end = clock();				//End time
		times[1] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		r = SortCheck(head);			//This checks to see if the BubbleSort function sorted the list correctly
		if(r == 1)
		{
			cout<<"SELECTION SORT DIDN'T SORT RIGHT! SORTING ERROR! \n";
			times[1] = -1;
		}
		//Print(head);				//Beta testing purposes
		Destroy(head);				//Destroy the list so another blank, unsorted list can be created.
	
	//MERGE SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(head, tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		head = MergeSort(head);
		end = clock();				//End time
		times[2] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		r = SortCheck(head);			//This checks to see if the BubbleSort function sorted the list correctly
		if(r == 1)
		{
			cout<<"MERGE SORT DIDN'T SORT RIGHT! SORTING ERROR! \n";
			times[2] = -1;
		}
		//Print(head);				//Beta testing purposes
		Destroy(head);				//Destroy the list so another blank, unsorted list can be created.
	
	//QUICK SORT
		head = NULL, tail = NULL;	//Make head/tail blank for a new list
		ReadData(head, tail);		//Builds the list of numbers. Opens file, adds to a doubly list and closes the file when it sees "***";
		begin = clock();			//Start time
		head = QuickSort(head);		//Head is equal to the sorted list
		end = clock();				//End time
		times[3] = (end-begin) / (double)CLOCKS_PER_SEC;	//Finds the time it took and records it in the times array
		r = SortCheck(head);			//This checks to see if the BubbleSort function sorted the list correctly
		if(r == 1)
		{
			cout<<"QUICK SORT DIDN'T SORT RIGHT! SORTING ERROR! \n";
			times[3] = -1;
		}
		//Print(head);				//Beta testing purposes
		Destroy(head);				//Destroy the list so another blank, unsorted list can be created.
		
//===========================================================================================================================================================
		cout<<"\nWow, that was quick! Let's see which sort was the fastest! \n";
		SortReport(times);	//Calls the report function to determine which function was the quickest.
		cout<<"\nWould you like to run the program again? \n";
		do{
			cout<<"Press 1 to continue, 2 to quit. \n";
			cout<<"=> ";
			cin>>x;
		}while(x != 1 && x != 2);	//Only works if you type 1 OR 2
		system("CLS");
	}while(x == 1);	//Program loops until USER enters 2 for the above question
	return 0;		//End of the program, good bye!
}

//THE SORTING FUNCTIONS

//Bubblesort! Simple yet slooooow!
void BubbleSort(node *head, node *tail)	
{
	int swap = 0, hold = 0;	//0 means no sort was performed, 1 means one was. Must complete on whole pass without swap = 1
	node *curr, *last;		//Temporary pointers
	curr = head;			//Start off with curr equaling head
	last = tail;
	
	if(head == NULL)		//If head is NULL there is no list to sort!
	{
		cout<<"\nError! Cannot sort an empty list! \n";		//-1 is an empty list (cannot sort nothing)
		return;												//Stop the function from going on
	}
	
	if(curr -> next == NULL)//There's no need to sort - there's only one element!
		return;				//So stop this function from continuing.
	
	do{
		curr = head;	//Set curr to *head for running through the list
		swap = 0;		//Reset swap as to 0
		
		do{    
			if(curr -> data > curr -> next -> data)			//Note: This only swaps DATA so no need to worry about the pointers!
			{
				     		hold = curr -> data;			//Hold the next node 
					curr -> data = curr -> next -> data;	//Make the next node equal to the previous node
			curr -> next -> data = hold;					//Make the previous node equal to the next node
				    		swap = 1;						//Flag this pass as having a swap
			}
			curr = curr -> next;		//Move temp up one node	
		}while(curr -> next != last);	//If temp equals tail, it has hit the end of the list!
		
	}while(swap == 1);					//Run until the sort is complete, which is when one complete pass does not make swap = 1.
	//if it gets to this point the list has successfully been sorted! WOO HOO!
}

//Selection Sort! More complex but slightly quicker then Bubble Sort!
void SelectionSort(node *head, node *tail)	
{
	node *curr, *cont, *min;	//Temp pointers. Curr/Last are head/tail. Cont is used for searching the list each time SS makes a move ahead
	int hold;					//holds an int temporarly
	
	if(head == NULL)			//If head is NULL there is no list to sort!
	{
		cout<<"\nError! Cannot sort an empty list! \n";		//-1 is an empty list (cannot sort nothing)
		return;												//Stop the function from going on
	}
	
	for(curr = head; curr -> next != NULL; curr = curr -> next)	//Run through the entire list
	{
		min = curr;		//Make min equal to the current position (to compare against the other numbers)

		for(cont = curr -> next; cont -> next != NULL; cont = cont -> next)	//Start comparing from the next node on to the end of the list
			if(cont -> data < min -> data)									//If it finds a value that is less then the current min
				min = cont;													//Then this becomes the new minimum!
	
		if(min != curr)						//If min is different then what it originally was (ie a swap should take place)
		{
			        hold = curr -> data;	//Hold the current data
			curr -> data = min -> data;		//Make the current equal to the minimum data
			 min -> data = hold;			//Make the mimimum data equal to the hold data
		}
	}
}

//Merge Sort! Quick but really annoyingly complex.
struct node *MergeSort(node *head)	
{
	//If head or head -> next is NULL then its sorted 
	if(head == NULL || head -> next == NULL)			
		return head;				//So return it!
	
	//Now split the list into two sub lists
	node *left, *right, *curr = head, *nxt, *end, *result = NULL;
	int pivot = head -> data;
	
	//Divide the list into two parts
	while(curr)								//Run to the end of the list. After curr = NULL, the list has been divided.
    {
        nxt = curr -> next;					//Nxt holds curr's next, as the node will be moved to another list in the following code!
		//LESS THAN LIST
		if(curr -> data < pivot)			//If the current node's data is less then the pivot data
        {
            curr -> next = left;			//Add to the beginning of the list. Curr points to less's first node
                    left = curr;			//and now less points to curr (now the head of this list)
        }									//and less then points to curr
        //GREATER THAN LIST
        else								
        {
            curr -> next = left;			//Other wise send it to the 'greater than' list
                   right = curr;			//Using the same add to the beginning idea as above ^
        }
        curr = nxt;							//Move forward one node
    }
	
	//Now keep calling MergeSort until the size of each list is 1
	 left = MergeSort(left);
	right = MergeSort(right);
	
	//Now merge the lists returned from the above code ^
	if(left == NULL)		//If this is NULL just return the right list
		return right;		//In both cases basically its empty so no need to merge
	else if(right == NULL)	//If this is NULL just retrun the left list
		return left;		
	else
	{
		if(left -> data < right -> data)	//Compare the first node of the list
		{
			result = left;
			left = left -> next;
			end = result;
		}
		else
		{
			result = right;
			right = right -> next;
			end = result;
		}
		
		while(left && right)				//Middle of the list
		{
			if(left -> data < right -> data)
			{
				end	-> next = left;
				end = end -> next;
				left = left -> next;
			}
			else
			{
				end -> next = right;
				end = end -> next;
				right = right -> next;
			}	
		}
		
		if(left == NULL)				//End of the list
			end -> next = right;
		else
			end -> next = left;
		
		return result;					//Return the finished list! YAY!
	}
}

//Quick Sort - Quick and *only* slightly annoying.
struct node *QuickSort(node *head)	//Note head is just a pointer, does NOT CHANGE THE ORIGINAL HEAD*
{									//****UNTIL IT IS RETURNED THAT IS!****
	if(head == NULL)	//Return if the list is NULL
		return head;	//Returning head because I must return something! (Or else the compilier becomes angry)
	
	//Less/Great hold the less/great lists. Pivot is just the head pointer. curr is the current node
	//nxt is a hold variable for the next node and end is the last node in the list
	node *less = NULL, *great = NULL, *pivot = head, *nxt, *end, *curr = head -> next;
	
	//Divide the list into two parts
	while(curr != NULL)						//Run to the end of the list. After curr = NULL, the list has been divided.
    {
        nxt = curr -> next;					//Nxt holds curr's next, as the node will be moved to another list in the following code!
		//LESS THAN LIST
		if(curr -> data < pivot -> data)	//If the current node's data is less then the pivot data
        {
            curr -> next = less;			//Add to the beginning of the list. Curr points to less's first node
                    less = curr;			//and now less points to curr (now the head of this list)
        }									//and less then points to curr
        //GREATER THAN LIST
        else								
        {
            curr -> next = great;			//Other wise send it to the 'greater than' list
                   great = curr;			//Using the same add to the beginning idea as above ^
        }
        curr = nxt;							//Move forward one node
    }

    //Sort each list by recussion
     less = QuickSort(less);	//Less than list is sorted after this
    great = QuickSort(great);	//Greater than list is sorted after this
 
    //Merge the two lists
    if(less != NULL)	//Assuming less isn't null, there's two lists to merge.
    {
        end = less;	//end points to the less node - used as a temp to traverse the list
        
        while(end -> next != NULL)	//Find the last node in the list (ends when the next val is NULL)
        	end = end -> next;		//Move forward one

         end -> next = head;		//Combine's the lists - end links to the greater than list
        head -> next = great;		//and this now points to the greater than list

        return less;        		//Return 'less' since this is now the head
    }
    else
    {
        head -> next = great;		//If less is NULL, well only the great side ended up being sorted
        return head;    			//Which, while rare, could happen. So return head (head of the great list)
    }
}

//-----------------------------------------------------------------------------------------------------------------------------
//These functions handle the basic doubly linked operations. Ie ReadData, Adding, Deleting the list, etc.

void ReadData(node *&head, node *&tail)
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

int Add(int a, node *&head, node *&tail)//Adds data to the linked list
{	
	node *curr, *befo;					//Temporary pointers
	curr = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
	if(!curr)							//If temp threw a NULL, then it seems memory allocation failed!
		return -1;						//Therefore return -1 to show memory allocation failed error to the user.
	curr -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
	curr -> next = NULL;				//next is NULL as it will be the last node when added.
	curr -> prev = NULL;				//(I will be adding nodes to the end of the list)						
	
	if(head == NULL){					//IF head is NULL, then the list is empty!
		head = curr;					//So make head point to temp! Now the list has one element! YAY!
		tail = curr;					//Tail also points to temp!
	}
	else{								//IF it isn't, then search for the end!
		befo = head;					//The list isn't empty - I will have to search for the last node.
		while(befo -> next != NULL)		//FIND the last node - the one just before NULL!
			befo = befo -> next;		//befo now contains the address of the last node
		befo -> next = curr;			//Make curr the last node in the linked list.
		curr -> prev = befo;			//Make curr's prev point to befo.
		curr -> next = NULL;			//Make sure its NULL just incase!
		tail = curr;					//Make tail point to curr, as this now the tail of the list!
	}
	return 0;
}

int Remove(int a, node *&head, node *&tail)	//Removes the node from the list as needed. & means it changes the head pointer in the main.
{
	int found = 0;			//Int to detect if the variable entered was in the list
	node *curr, *befo;		//Temporary pointers
	curr = head;			//Curr now equals head
	
	if(head == NULL)		//If the list is empty, don't even bother searching - the number isn't there! :P
		return -2;			//(thus return an error)
	else
	{
		do{								//Search through the list for the number by using temp. Check the first node's data value. 
			if(curr -> data == a)		//Then move forward one and check again. If it is found, remove it and return the given number (in this case a)
			{							//to indicate success!
				found = 1;
				
				if(curr -> next == NULL && curr -> prev == NULL)	//If this is the really end of the list - then we must make tail and head NULL!
				{
					head = NULL;	//Both must equal NULL
					tail = NULL;
					delete curr;	//Delete current node & this is also the last node :(
					return a;		//Return a for success!
				}
				
				if(curr == head)			//If the value is found in the start of the list
				{
					head = curr -> next;	//Then head must be reassigned - in this case just by moving it forward one. 
					befo = head;			//Make a temp pointer equal to head
					befo -> prev = NULL;	//make sure befo's prev is equal to NULL though! or randon numbers will appear!
					delete curr;		 	//Remove the node containing 'a' (the current node)
					return a;
				}
				
				if(curr == tail)			//If the value is the last node of the list, make sure the last node's pointer is NULL! 
				{							//or you'll have a bad pointer!
					tail = curr -> prev;	//Make sure to reassign tail!
					befo = tail;
					befo -> next = NULL;	//make prev's next NULL because it doesn't point to anything! its the end of the list now!
					delete curr;			//Remove the node containing 'a' (the current node)
					return a;
				}
				
				else							//If the value is somewhere in the middle, then just rearrange a few things
				{
					befo -> next = curr -> next;	//Reroute the nodes - the previous node's (temp2) next should point to the next node 
					curr -> next -> prev = befo;	//Reroute the prev's pointer as well.

					delete curr;					//Remove the node containing 'a' (the current node)
					return a;
				}
		
			}
			befo = curr;		 //stores the (soon to be previous) node
			curr = curr -> next; //move forward one node
		}while(curr != NULL);	 //Run until the end of the list
	}
	
	if(found == 0)			//WASN'T FOUND IN THE LIST! so return -1 for error!
		return -1;
}

int SortCheck(node *head)	//Checks to make sure the sort function worked properly
{
	if(head == NULL)		//If head is still NULL, then the list is already sorted!
		return 0;			
	node *nxt;
	
	for(node *curr = head; curr -> next != NULL; curr = curr -> next)	//Run through the entire list
	{
		nxt = curr -> next;
		if(curr -> data > nxt -> data)		//Check to make sure it sorted right. If this IF is true
			return 1;						//Then the list isn't sorted so throw an error code and return!

				//So exit and return to signal the sort was not complete!
				//Run until the SECOND TO LAST node!!
	}			//IMPORTANT TO NOTE: IF YOU COMPARE TO THE FINAL NODE IT'LL ATTEMPT TO COMPLETE LAST NODE TO LAST NODE -> NEXT -> DATA... WHICH DOESN'T EXIST!!!
				//Everything was correctly sorted
	return 0;	//So return to signal success!
}

void SortReport(double times[])	//Reports how long each sorting element took
{
	//First thing I did was sort the times in order. This is tricky as I need to keep track of which time goes with which sort
	//So whenever I swap times, I swap the order of the sorts.
	
	int hold = 0, swap = 0, a = 0;	//Temp variables
	double temp = 0;		
	int order[3];			//holds the order of the sorts originally
	
	for(a = 0; a < 4; a++)	//The Order array only contains the numbers 0, 1, 2 and 3
		order[a] = a;		//This is used for keeping track of which time is which sort
							//Ex: Everytime the BubbleSort time swaps, 0 (BubbleSort's #) swaps with it
	do{
		swap = 0;			//Reset swap/a to 0
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
			
			a++;		//Move forward one
		}while(a < 3);	//Run through the list of times
	}while(swap == 1);	//Run as long as sorting is needed (only needed if swap equals 1 - if zero then loop breaks as sorting is done!)
	
	//Here is where I swap -1s as those times are not valid.
	//Simply put if all are -1s, don't bother as the program clearly didn't sort any of the lists right!
	//If only 3 are -1, then swap the last and the first times/orders (-1 -1 -1 ?)
	//If only 2 are -1, make the last two now the first two	(-1 -1 ? ?)
	//If only 1 are -1, then move everything up one	(-1 ? ? ?)
	//NOTE: THIS WORKS BECAUSE I'VE ALREADY SORTED THE TIMES AND ORDERS!
	if(times[0] == -1 && times[1] != -1 && times[2] != -1)	
	{				
		times[0] = times[1];
		times[1] = times[2];	//Move each time and order up 1
		times[2] = times[3];
		times[3] = -1;
		order[0] = order[1];
		order[1] = order[2];
		order[2] = order[3];
		order[3] = 0;
	}
	if(times[0] == -1 && times[1] == -1 && times[2] != -1)
	{
		times[0] = times[2];
		times[1] = times[3];
		times[2] = -1;			//Swap 1/2 with 3/4
		times[3] = -1;			//Make 3/4 equal to -1
		order[0] = order[2];	//Order doesn't really matter so its made equal to 0.
		order[1] = order[3];	
		order[2] = 0;
		order[3] = 0;
	}
	
	if(times[0] == -1 && times[1] == -1 && times[2] == -1)
	{
		times[0] = times[3];
		times[3] = -1;
		order[0] = order[3];
		order[3] = 0;
	}

	if(times[0] == -1 && times[1] == -1 && times[2] == -1 && times[3] == -1)
		cout<<"All of the times are invalid. Fix sorting program Mr. Coder! \n";
	
	//Now that the times are in order and I know which time goes with which sort, I can report which sort was quickest and which was slowest!
	if(times[0] != -1)
	{
		cout<<"1st: ";
		WhichSort(order[0]);
		cout<<" with a time of "<<times[0]<<" seconds! \n";
	}
	
	if(times[1] != -1)
	{
		cout<<"2nd: ";
		WhichSort(order[1]);
		cout<<" with a time of "<<times[1]<<" seconds! \n";
	}
	
	if(times[2] != -1)
	{
		cout<<"3rd: ";
		WhichSort(order[2]);
		cout<<" with a time of "<<times[2]<<" seconds! \n";
	}
	
	if(times[3] != -1)
	{
		cout<<"4th: ";
		WhichSort(order[3]);
		cout<<" with a time of "<<times[3]<<" seconds! \n";
	}
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

void Destroy(node *&head)		//Function that deletes the list from memory
{	
	node *curr, *root;	//Temporary pointers
	root = head;		//root is now equal to the first node
	if(head == NULL)	
		return;			//if the list is empty no need to do the following else!
	else
	{					//if the list has nodes - run the following
		do{				
			curr = root;			//curr equals the first node.
			root = root -> next;	//root is now equal to the next node
			delete curr;			//curr is deleted - this means root is actually equal to the first node now (since the current one was deleted!)
			if(root -> next == NULL)//if root's next is NULL, then the last node was deleted with the 'delete curr' line. 
				head = NULL;		//so this means *head can be set equal to NULL (an empty list)
		}while(head != NULL);		//and the do/while stops running as the list is empty and all nodes were deleted from memory.
	}
}

//This function is not called in a typical run of the program. It is only to test the program and make sure everything is actually being sorted.
void Print(node *head)	
{
	cout<<"\nThis is what is in teh list! \n";
	
	int a = 0;
	node *temp;		//Temporary pointer
	temp = head;	//Makes temp equal to head
	
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
			if(a == 200)
			{
				Enter();	//This just allows me to print ONLY the first 200 nodes
				break;		//I really just wanted to see that far for testing purposes
			}
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

/*
NOTES

Ways to pass pointer to a function:
	1. *ptr , send(ptr)  -> send(*&ptr) , use as  "ptr"
	2. *ptr , send(&ptr) -> send(**ptr) , use as "*ptr"

*/
