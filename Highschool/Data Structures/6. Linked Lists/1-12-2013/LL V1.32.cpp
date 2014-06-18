#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

//TRY THIS:
//http://www.thegeekstuff.com/2012/08/c-linked-list-example/

struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	int data;		//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
};

void Enter(void);				//Each function handles a different part of the program.
void Manual(void);
//void File(void);

void Add(int a, node **head);
int Remove(void);
void Destroy(void);
void Print(node **head);

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
					//File();
					break;
			case 3: 
					cout<<"\nQuitting... \n";
					end = 1;		//Ends the program as the main do/while loop ends.
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
	int a = 0, end = 0, x = 0, ret = 0;
	node *head = NULL; 		//head of the linked list - points to the start of the list. Set to NULL as there aren't any elements in the list (yet).
	
	do{
		cout<<"Manual Entry. \n\n";				//Intro/Options you can enter
		cout<<"What do you want to do? \n";		
		cout<<"1 = Add \n";						//Each number is used in a switch
		cout<<"2 = Remove \n";					//to call up the function requested.
		cout<<"3 = Destroy \n";					
		cout<<"4 = Print \n";
		cout<<"5 = Quit \n";
		
		do{
			cout<<"=> ";
			cin>>x;
		}while(x != 1 && x != 2 && x != 3 && x != 4 && x != 5);
		
		switch(x)
		{
			case 1:
					cout<<"\nHow much do you want to add? \n";	//Ask user for input.
					cout<<"Enter it here. -> ";	
					cin>>a;										//Take an input from the user.
					Add(a, &head);								//Sends the input to the add function						
					break;										//NOTE FOR FUTURE:
			case 2:												//The "&" is a REFERENCE to the pointer head. This means changing head in this function will
					Remove();	//Remove function				//change the 'head' refered to in THIS function. This must be done or else the list will seem to be
					break;										//empty to the print function (as the above 'head' will still be NULL) and adding will not work as
			case 3:												//head will still be NULL and won't point to any nodes!
					Destroy();	//Destroy function
					break;
			case 4:
					Print(&head);	//Print Function
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
void Add(int a, node **head)
{	
	node *temp, *temp2;		//Temporary pointers
	
	temp = new node;		//Make a new node and fill it with the data from the user.
	temp -> data = a;		//'a' contains the data - transfer it to 'data' var. in the node	
	temp -> next = NULL;	//next is NULL as it will be the last node when added.
							//(I will be adding nodes to the end of the list)
							
	if(*head == NULL)		//IF head is NULL, then the list is empty!
		*head = temp;		//So make head point to temp! Now the list has one element! YAY!
	else
	{
		temp2 = *head;					//The list isn't empty - I will have to search for the last node.
		while(temp2 -> next != NULL)	//FIND the last node - the one just before NULL!
		temp2 = temp2 -> next;			//Temp2 now contains the address of the last node
		temp2 -> next = temp;			//Temp is now the last node in the linked list.
	}
	
	//Why does this need to return 0 for success and -1 for failure??
}

void Print(node **head)
{
	cout<<"\nThis is what is in teh arrays! \n\n";
	node *temp;		//Temporary pointer
	temp = *head;	//Makes temp equal to head
	
	if(temp == NULL)	//head is also NULL, aka empty list.
	{
		cout<<"The list is empty! \n";	//eek! the list is empty!
	}
	else	//Well, the list has something stored.
	{
		do{
			cout<<temp->data<<'\t';	//couts the current node
			temp = temp->next; 		//basically moves it forward one node
		}while(temp != NULL);	//run until the end of the linked list
		cout<<'\n';
	}
	//DOES NOT NEED TO RETURN VALUE!
}

int Remove(void)
{
	cout<<"\nRemove! \n";
}

void Destroy(void)
{
	cout<<"\nDESTROYING EVERYTHING... \n";
}

/*
USEFUL LINKS:
http://cslibrary.stanford.edu/103/LinkedListBasics.pdf
http://www.bogotobogo.com/cplusplus/linkedlist.php
http://www.codeproject.com/Articles/24684/How-to-create-Linked-list-using-C-C
http://www.overclock.net/t/426671/help-c-linked-list-output
*/
