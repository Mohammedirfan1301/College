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

struct node
{
	int 		data;			//structure for the linked list
	struct node	*next;
};

struct node *head = NULL;		//pointers for the list
struct node *curr = NULL;

void Enter(void);				//Each function handles a different part of the program.
void Manual(void);
void File(void);

int Add(void);
int Remove(void);
void Destroy(void);
void Print(void);

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
	int a = 0, end = 0, x = 0;
	
	do{
		cout<<"Manual Entry. \n\n";				//Intro/Options you can enter
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
					int a;
					cout<<"\nHow much do you want to add? \n";	//Ask user for input.
					cout<<"Enter it here. -> ";	
					cin>>a;										//Take an input from the user.
					Add(a);										//Sends the input to the add function
					break;
			case 2:
					Remove();	//Remove function
					break;	
			case 3:
					Destroy();	//Destroy function
					break;
			case 4:
					Print();	//Print Function
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
int Add(void)
{	
	struct node *tmp1 = NULL;
	struct node *tmp2 = NULL;
	
	head = NULL;
	tmp1 = new node;							//Allocate						
	tmp1 -> data = a;							//Set it equal to int a, which is what is being added to the list.
	tmp1 -> next = NULL;						//Make nextnode point to the first node of the list.
	
	if(head == NULL)
		head = tmp1;							//nextNode is now the head of the list.	
	else
	{
		tmp2 = head;
	
		do{
			tmp2 = tmp2 -> next;
		}while(tmp2 -> next != NULL);
		
		tmp2 -> next = tmp1;
	}
}

int Remove(void)
{
	cout<<"\nRemove! \n";
}

void Destroy(void)
{
	cout<<"\nDESTROYING EVERYTHING... \n";
}

void Print(void)
{
	cout<<"\nDis is what is in teh arrays! \n";
	node *temp = head;		//makes temp equal to head
	
	if(temp == NULL)
	{
		cout<<"The list is empty! \n";	//eek! the list is empty!
	}
	else
	{
		do{
		cout<<temp->data<<" ";	//couts the current node
		temp = temp->next; 		//basically moves it forward one node
		}while(temp != NULL);	//run til the end of the linked list
	}
}

/*
USEFUL LINKS:
http://cslibrary.stanford.edu/103/LinkedListBasics.pdf
http://www.bogotobogo.com/cplusplus/linkedlist.php
http://www.codeproject.com/Articles/24684/How-to-create-Linked-list-using-C-C
http://www.overclock.net/t/426671/help-c-linked-list-output
*/
