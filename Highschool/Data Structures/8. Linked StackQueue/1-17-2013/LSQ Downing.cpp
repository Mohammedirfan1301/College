#include <conio.h>		//Lot's of includes
#include <fstream>		//All used somewhere in the program for some reason
#include <iostream>		//or another
#include <sstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	int data;		//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
};
				
void Stack(void);					//Each function handles a different part of the program.
void Queue(void);					//They are named logically and should explain themselves
void Destroy(node **head);		
void Enter(void);

int Push(int a, node **head);		//These are used by the above two functions (Stack & Queue)
int Pop(node **head);				//Also explains themselves
int Enqueue(int b, node **head);
int Dequeue(node **head);
int Peek(int a, node **head);
void Print(node **head);

int main()
{
	int opt = 0, end = 0;
	
	do{
		cout<<"Linked List - STACK / QUEUE VERSION \n";			//Intro/Options you can enter.
		cout<<"\nHow would you like to run this program? \n";
		cout<<"1 => Stack Mode \n";
		cout<<"2 => Queue Mode \n";
		cout<<"3 => QUIT! \n";
		
		do{
			cout<<"\nEnter an option. => ";			//type a number in and press enter.
			cin>>opt;
		}while(opt != 1 && opt != 2 && opt != 3);	//Can only enter options 1, 2 or 3
		
		switch(opt)
		{
			case 1:					//Manual Entry
					system("cls");	//clear the screen
					Stack();		//call up Manual function - handles user entry
					break;
			case 2:					//File Entry
					system("cls");	//clear the screen
					Queue();		//call up File function - handles file entry
					break;
			case 3: 
									//QUIT!
					cout<<"\nABORTING MISSION! \n=>";
					Sleep(5000);    //pause for 5 seconds
					end = 1;		//Ends the program as the main do/while loop ends.
					break;
		}
   		system("cls");	//clear the screen
	}while(end != 1);	//Only ends when 1 is entered.
}

void Stack(void)	//This function does the manual entry portion of the program.
{
	int a = 0, b = 0, end = 0, x = 0, ret = 0;	//a is for user inputs, end for ending this function, x for function selection 
												//and ret for values returned by functions.
	node *head = NULL; 							//head of the linked list - points to the start of the list. 
												//Set to NULL as there aren't any elements in the list (yet).	
	do{
		b = 1;
		cout<<"STACK \n\n";						//Intro/Options you can enter
		cout<<"What do you want to do? \n";		
		cout<<"1 => Push \n";					//Each number is used in a switch
		cout<<"2 => Pop \n";					//to call up the function requested.
		cout<<"3 => Peek \n";
		cout<<"4 => Print \n";
		cout<<"5 => Quit \n";
		
		do{
			cout<<"\nEnter an option => ";		//type a number in and press enter
			cin>>x;
		}while(x != 1 && x != 2 && x != 3 && x != 4 && x != 5);	//can only enter 1-5 otherwise the above message repeats endlessly
		
		switch(x)
		{

			case 1:
					cout<<"\nHow much do you want to push? \n";	//Ask user for input.
					cout<<"Enter it here. => ";	
					cin>>a;										//Take an input from the user.
					ret = Push(a, &head);						//Sends the input to the add function	
					
					if(ret == 0)								//everything went fine
						cout<<'\n'<<a<<" was added. \n";
					if(ret == -1)								//There was an error when adding a to the list.
						cout<<"\nERROR! Memory allocation failed! \n";					
					break;									
			case 2:												
					ret = Pop(&head);							//make ret equal to what the Remove function outputs
					
					if(ret != -1)							
						cout<<'\n'<<ret<<" was popped. \n";			//if ret = a, then the number was removed successfully
					if(ret == -1)							
						cout<<"\nERROR! Stack empty! \n";	//-1 means the list is empty!							
					
					break;												
			case 3:
					ret = Peek(b, &head);							//Peek Function
					
					if(ret != -1)
						cout<<'\n'<<ret<<" is the front value! \n";
					if(ret == -1)
						cout<<"\nERROR! Stack empty! \n";
					break;
				
			case 4:
					Print(&head);										//Print Function
					break;
			case 5:
					cout<<"\nGood bye! :( \n";
					end = 1;	//breaks the do/while loop so the program returns to the main.
					break;
		}
		Enter();		//Calls up the press enter to continue function
   		system("cls");	//Clears the screen
	}while(end != 1);
	
	Destroy(&head);		//This deletes all the elements in the linked list (frees up the memory taken by the nodes)
}

void Queue(void)		//This function does the manual entry portion of the program.
{
	int a = 0, b = 0, end = 0, x = 0, ret = 0;	//a is for user inputs, end for ending this function, x for function selection 
												//and ret for values returned by functions.
	node *head = NULL; 							//head of the linked list - points to the start of the list. 
												//Set to NULL as there aren't any elements in the list (yet).	
	do{
		b = 2;
		ret = 0;								//(Make sure ret is zero - JUST in case)
		cout<<"QUEUE \n\n";						//Intro/Options you can enter
		cout<<"What do you want to do? \n";		
		cout<<"1 => Enqueue \n";				//Each number is used in a switch
		cout<<"2 => Dequeue \n";				//to call up the function requested.
		cout<<"3 => Peek \n";
		cout<<"4 => Print \n";
		cout<<"5 => Quit \n";
		
		do{
			cout<<"\nEnter an option => ";		//type a number in and press enter
			cin>>x;
		}while(x != 1 && x != 2 && x != 3 && x != 4 && x != 5);	//can only enter 1-5 otherwise the above message repeats endlessly
		
		switch(x)
		{

			case 1:
					cout<<"\nHow much do you want to enqueue? \n";		//Ask user for input.
					cout<<"Enter it here. => ";	
					cin>>a;												//Take an input from the user.
					ret = Enqueue(a, &head);							//Sends the input to the add function	
					
					if(ret == 0)										//everything went fine
						cout<<'\n'<<a<<" was enqueued. \n";
					if(ret == -1)										//There was an error when adding a to the list.
						cout<<"\nERROR! Memory allocation failed! \n";					
					break;									
			case 2:												
					ret = Dequeue(&head);								//make ret equal to what the Remove function outputs
					
					if(ret != -1)							
						cout<<'\n'<<ret<<" was dequeued. \n";			//if ret = a, then the number was removed successfully
					if(ret == -1)								
						cout<<"\nERROR! Queue empty! \n";		//-2 means the list is empty!		
					break;												
			case 3:
					ret = Peek(b, &head);								//Peek Function
					
					if(ret != -1)
						cout<<'\n'<<ret<<" is the front value! \n";
					if(ret == -1)
						cout<<"\nERROR! Queue empty! \n";
					break;
				
			case 4:
					Print(&head);										//Print Function
					break;
			case 5:
					cout<<"\nGood bye! :( \n";
					end = 1;											//breaks the do/while loop so the program returns to the main.
					break;
		}
		Enter();		//Calls up the press enter to continue function
   		system("cls");	//Clears the screen
	}while(end != 1);
	
	Destroy(&head);		//This deletes all the elements in the linked list (frees up the memory taken by the nodes)
}

int Push(int a, node **head)
{	
	node *temp, *temp2;			//Temporary pointers
	
	temp = new(nothrow) node;	//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
	if(!temp)					//If temp threw a NULL, then it seems memory allocation failed!
		return -1;				//Therefore return -1 to show memory allocation failed error to the user.
	temp -> data = a;			//'a' contains the data - transfer it to 'data' var. in the node	
	temp -> next = NULL;		//next is NULL as it will be the last node when added.
								//(I will be adding nodes to the end of the list)
							
	if(*head == NULL)			//IF head is NULL, then the list is empty!
		*head = temp;			//So make head point to temp! Now the list has one element! YAY!
	else
	{
		temp2 = *head;					//The list isn't empty - I will have to search for the last node.
		while(temp2 -> next != NULL)	//FIND the last node - the one just before NULL!
			temp2 = temp2 -> next;		//Temp2 now contains the address of the last node
		temp2 -> next = temp;			//Make temp the last node in the linked list.
	}
	return 0;
}

int Pop(node **head)
{
	node *prev, *last;	//these are used in the do/while
	last = *head;		//make last equal to head
	int pop = 0;		//value to be returned (value popped)
	
	if(*head == NULL)	//If head's empty, the stack's empty and you can't pop anything!
		return -1;
	
	if(last -> next == NULL)	//If the first node's next equals NULL then there's only one node to be popped!
	{
		pop = last -> data;		//Set pop equal to last's data (val to be popped)
		delete last;			//Delete the node containing the popped value
		*head = NULL;			//Make head equal to NULL so that we know the stack is now EMPTY
		return pop;				//Return the popped value!
	}
	
	do{
		prev = last;				//prev will hold the next to last node.
		last = last -> next;		//last moves forward one - at some point it WILL be the last node.
	}while(last -> next != NULL);	//FIND the last node - the one just before NULL!

	pop = last -> data;		//make pop equal to what will be removed (last's data)
	prev -> next = NULL; 	//prev will soon be the last node - make sure it's pointer is NULL! since last won't exist anymore! ;(
	delete last;			//Good bye, last - you are no more!
	
	return pop;				//everything should have gone smoothly in the above code, so return success!
}

int Enqueue(int a, node **head)
{
	node *temp, *temp2;			//Temporary pointers
	
	temp = new(nothrow) node;	//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
	if(!temp)					//If temp threw a NULL, then it seems memory allocation failed!
		return -1;				//Therefore return -1 to show memory allocation failed error to the user.
	temp -> data = a;			//'a' contains the data - transfer it to 'data' var. in the node	
	temp -> next = NULL;		//next is NULL as it will be the last node when added.
								//(I will be adding nodes to the end of the list)
							
	if(*head == NULL)		//IF head is NULL, then the list is empty!
		*head = temp;		//So make head point to temp! Now the list has one element! YAY!
	else
	{
		temp2 = *head;					//The list isn't empty - I will have to search for the last node.
		while(temp2 -> next != NULL)	//FIND the last node - the one just before NULL!
			temp2 = temp2 -> next;		//Temp2 now contains the address of the last node
		temp2 -> next = temp;			//Make temp the last node in the linked list.
	}
	return 0;	
}

int Dequeue(node **head)
{
	node *top;		//Temporary pointer
	top = *head;	//Top now equals head
	int deq = 0;
	
	if(*head == NULL)	//If the list is empty, don't even bother dequeing!
		return -1;		//(return an error)
	else	
	{							//This is simple - Queues dequeue first in, first out. Just move head forward one, then			
		*head = top -> next;	//reassign head. (by setting it equal to the next node)
		deq = top -> data;
		delete top;				//Finally remove the node that is being deleted
	}	//(by making head equal to it's next, it moves it forward one)
	
	return deq;	//return success!
}

int Peek(int b, node **head)
{
	node *last;		//The node containing the value to be returned (in last's data)
	last = *head;	//Make last equal to head
	int pek = 0;	//int to hold the value to be returned
	
	//Note: the 1 / 2 refer to whether the program is in STACK mode or QUEUE mode.
	
	if(*head == NULL)	//If *head equal's NULL then the Stack / Queue is EMPTY! Can't peek an empty list!
		return -1;
	
	if(b == 1)
	{
		//Stack = 1	
		//Also Stack is LAST IN, LAST OUT - so the last node's data should be returned!
		do{
			last = last -> next;		//last moves forward one - at some point it WILL be the last node.
		}while(last -> next != NULL);	//FIND the last node - the one just before NULL!
		
		pek = last -> data;		//This just makes pek equal to last's int data which contains the value to be peeked.
		return pek;	//return the value of peek
	}
	
	if(b == 2)
	{
		//Queue = 2
		//Also Queue is FIRST IN, FIRST OUT - the head node's data should be returned!
		pek = last -> data;		//this make's pek equal to last's int data which contains the value to be peeked. 
		return pek;		//return the value of peek
	}
}

void Print(node **head)
{
	node *temp;		//Temporary pointer
	temp = *head;	//Makes temp equal to head
	
	if(temp == NULL)	//head is also NULL, aka empty list.
	{
		cout<<"\nERROR! The list is empty! \n";	//eek! the list is empty!
	}
	else	//Well, the list has something stored! Print the nodes out!
	{
		cout<<"\nThis is what is in teh list! \n\n";
		
		do{
			cout<<temp -> data<<'\t';	//couts the current node
			temp = temp -> next; 		//basically moves it forward one node
		}while(temp != NULL);	//run until the end of the linked list
		cout<<'\n';
	}	//DOES NOT NEED TO RETURN A VALUE!
}

//DESTROY FUNCTION - Called before the Stack / Queue Functions are called.
void Destroy(node **head)
{
	node *curr, *root;	//Temporary pointers
	root = *head;		//root is now equal to the first node
	if(*head == NULL)	
		return;			//if the list is empty no need to do the following else!
	else
	{					//if the list has nodes - run the following
		do{				
			curr = root;				//curr equals the first node.
			root = root -> next;		//root is now equal to the next node
			delete curr;				//curr is deleted - this means root is actually equal to the first node now (since the current one was deleted!)
			if(root -> next == NULL)	//if root's next is NULL, then the last node was deleted with the 'delete curr' line. 
				*head = NULL;			//so this means *head can be set equal to NULL (an empty list)
		}while(*head != NULL);			//and the do/while stops running as the list is empty and all nodes were deleted from memory.
	}
}

//Function for the "PRESS ENTER TO CONTINUE..." prompt
void Enter(void)	//This function is just to stop the screen from ending quickly - makes the user hit enter before the program continues.
{
	char c;
	
	do{
		cout<<"\nPress ENTER to continue. => ";	//PRESS ENTER!!
        c = getch();
   	}while(c != 13);	//Only ends when the user presses ENTER
}
