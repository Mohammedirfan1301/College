#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>		//INCLUDES
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	int data;		//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
	node *left;		//This will point to the left node.
	node *right;	//This will point to the right node.
};

//REQUIRED FUNCTIONS
int Read(node *&headl, node *&headt);			//Reads the file and adds values to the list and the tree
int AddList(int a, node *&headl, node *last, node *temp);	//Function to add numbers to the list (RECURSIVE!)
int AddTree(int a, node *&headt, node *last, node *temp);	//Adds data to the binary tree
int SearchTree(int a, node *headt, node *last);				//Searchs teh tree for the value
int SearchList(int a, node *headl, node *last);				//Searchs the list for the given value
int Print(node *list, node *tree);				//Prints both the list and the search tree			
void PrintT(node *tree);						//Uses recusion, so I made it its own function for the tree
int Destroy(node *&headl, node *&headt, node *end);		//Function to DESTROY the list at the end of the program
void DestroyTree(node *end);					//Destroys just the tree using recusion

//Misc functions
void Enter(void);							//For the "Press Enter to Continue..." prompt

int main()
{
	node *headl = NULL, *headt = NULL;	//head of the list/tree
	node *befol = NULL, *befot = NULL;	//temp pointers for the list/tree
	int ans = 0, err = 0, num = 0, x = 1;
	
	do{
		cout<<"Welcome to the BINARY SEARCH TREE PROGRAM. \n";
		cout<<"Would you like to run this program manually, or automatically? \n";
		do{
			cout<<"Enter 1 for MANUALLY, 2 for AUTOMATICALLY -> ";
			cin>>ans;
		}while(ans != 1 && ans != 2);
	
	//MANUALLY
		if(ans == 1)
		{
			do{
				system("CLS");
				err = 0;
				cout<<"MANUAL ENTRY \n";
				cout<<"You may use the following commands: \n";
				cout<<"1 > Add \n";
				cout<<"2 > SearchTree \n";
				cout<<"3 > SearchList \n";
				cout<<"4 > Print \n";
				cout<<"5 > Destroy \n";
				cout<<"6 > Quit \n";
				do{
					cout<<"Enter a command -> ";
					cin>>ans;
				}while(ans != 1 && ans != 2 && ans != 3 && ans != 4 && ans != 5 && ans != 6);
			
				if(ans == 1)
				{
					cout<<"\nWhat number do you want to add? \n";
					cout<<"Enter a number. -> ";
					cin>>num;
					err = AddList(num, headl, NULL, NULL);
					if(err == -1)
					{
						cout<<"ERROR! FAILED TO ADD NODE! \n";
						Enter();
					}
					err = AddTree(num, headt, NULL, NULL);
					if(err == -1)
					{
						cout<<"ERROR! FAILED TO ADD NODE! \n";
						Enter();
					}
				}
				
				if(ans == 2)
				{
					cout<<"\nWhat value do you want to search the tree for? \n";
					cout<<"Enter a number. -> ";
					cin>>num;
					cout<<"\nSearching the tree for the given value... \n";
					err = SearchTree(num, headt, headt);
					if(err == num)
						cout<<num<<" was found in the tree! \n";
					else if(err == -1)
						cout<<"ERROR! EMPTY LIST! \n";
					else if(err == -2)
						cout<<"ERROR! VALUE NOT FOUND IN THE LIST! \n";
					Enter();
				}
				
				if(ans == 3)
				{
					cout<<"\nWhat value do you want to search for? \n";
					cout<<"Enter a number. -> ";
					cin>>num;
					cout<<"\nSearching the list for the given value... \n";
					err = SearchList(num, headl, headl);
					if(err == num)
						cout<<num<<" was found in the list! \n";
					else if(err == -1)
						cout<<"ERROR! EMPTY LIST! \n";
					else if(err == -2)
						cout<<"ERROR! VALUE NOT FOUND IN THE LIST! \n";
					Enter();
				}
				
				if(ans == 4)
				{
					cout<<"\nPrinting what is in the list and tree! \n";
					err = Print(headl, headt);
					if(err == -1)
						cout<<"ERROR THE LISTS ARE EMPTY! \n"; //ERROR
					Enter();
				}
					
				if(ans == 5)
				{
					cout<<"\nWiping the list & tree... \n";
					err = Destroy(headl, headt, NULL);
					if(err == 0)
						cout<<"Successfully destroyed both the list and the tree! \n";
					if(err == -1)
						cout<<"ERROR! Cannot destroy an empty list/tree! \n";
					Enter();
				}
				
				if(ans == 6)
				{
					cout<<"\nQuitting to the main menu...\n";
					Destroy(headl, headt, NULL);
					Enter();
				}
			}while(ans != 6);
		}
	
	//AUTOMATICALLY (FROM A FILE)
		if(ans == 2)
		{	
			system("CLS");
			err = Read(headl, headt);
			if(err == 0)
				//SUCCESS
			if(err == -1)
				cout<<"ERROR! ERROR! \n";
		}
	
		system("CLS");
		cout<<"Do you want to rerun the program? \n";
		
		do{
			cout<<"Enter 1 to continue or 2 to quit. \n";
			cout<<"-> ";
			cin>>x;
		}while(x != 1 && x != 2);
		
		system("CLS");
		Destroy(headl, headt, NULL);	//Wipe the list & tree for the next run or for quitting the program
		
	}while(x == 1);

	return 0;
}

int Read(node *&headl, node *&headt)
{
	ifstream entry;		//ifstream for opening the file
    string filename("treedata.txt");    //string to hold the filename (change this for different file names!!!)
    string command;     //string to hold each line in the file
	int num = 0;		//final num to send to the functions
	int err = 0;		//int that holds the return value of the functions
	int ans = 0;		//Holds answer of the user
	char c;             //press enter variable
    int a, x = 1;		//x is for the do/while loop
    
    entry.open(filename.c_str());	//opens the file, using the name the user entered in
    
    if(!entry){     //if the file does not open, this is true. the error below will then print out.
        cout<<"Unable to open the selected file! \n";
        Sleep(5000);    //pause for 5 seconds
        return -1;        //exit the program
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
			err = AddList(num, headl, NULL, NULL);
			if(err == -1)
			{
				cout<<"ERROR! FAILED TO ADD NODE! \n";
				Enter();
			}
			err = AddTree(num, headt, NULL, NULL);
			if(err == -1)
			{
				cout<<"ERROR! FAILED TO ADD NODE! \n";
				Enter();
			}
		}
    }while(x == 1);	//loop until the end of the file, which is until x == 0;	
    
    do{
    	system("CLS");
		cout<<"All the numbers in the file have been added successfully. \n";
		cout<<"What would you like to do? \n";
		cout<<"1. Search the list \n";
		cout<<"2. Search the tree \n";
		cout<<"3. Print the list and tree \n";
		cout<<"4. Quit to main menu \n";
		do{
			cout<<"Enter a command -> ";
			cin>>ans;
		}while(ans != 1 && ans != 2 && ans != 3 && ans != 4);
		
		if(ans == 1)
		{
			cout<<"\nWhat value do you want to search the tree for? \n";
			cout<<"Enter a number. -> ";
			cin>>num;
			cout<<"\nSearching the tree for the given value... \n";
			err = SearchTree(num, headt, headt);
			if(err == num)
				cout<<num<<" was found in the tree! \n";
			else if(err == -1)
				cout<<"ERROR! EMPTY LIST! \n";
			else if(err == -2)
				cout<<"ERROR! VALUE NOT FOUND IN THE LIST! \n";
			Enter();
		}
				
		if(ans == 2)
		{
			cout<<"\nWhat value do you want to search for? \n";
			cout<<"Enter a number. -> ";
			cin>>num;
			cout<<"\nSearching the list for the given value... \n";
			err = SearchList(num, headl, headl);
			if(err == num)
				cout<<num<<" was found in the list! \n";
			else if(err == -1)
				cout<<"ERROR! EMPTY LIST! \n";
			else if(err == -2)
				cout<<"ERROR! VALUE NOT FOUND IN THE LIST! \n";
			Enter();
		}
				
		if(ans == 3)
		{
			cout<<"\nPrinting what is in the list and tree! \n";
			err = Print(headl, headt);
			if(err == -1)
				cout<<"ERROR THE LISTS ARE EMPTY! \n"; //ERROR
			Enter();
		}
		
		if(ans == 4)
		{
			cout<<"\nQuitting to the main menu...\n";
			Destroy(headl, headt, NULL);
			Enter();
			x = 0;
		}
		
	}while(x == 1);
    
	return 0;	//success if it made it this far!
}

int AddList(int a, node *&headl, node *last, node *temp)	//Adds data to the linked list
{	
	if(temp == NULL)						//If temp is NULL, make a new node!
	{
		last = headl;
		temp = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!temp)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//So return -1 to show memory allocation failed error to the user.
		temp -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
		temp -> next = NULL;				//next is NULL as it will be the last node when added.
	}
	
	if(headl == NULL)						//Handle the first node case
	{
		headl = temp;						//Make each head point to their first nodes!
		return 0;							//Return success	
	}
	else if(last -> next != NULL)			//Keep going until last -> next equal NULL						
		AddList(a, headl, last -> next, temp);  //This will continue to call t until the if statement is false (last -> next EQUALS NULL)
	else
		last -> next = temp;			//Make curr the last node in the linked list.
	
	return 0;	//Success
}

int AddTree(int a, node *&headt, node *last, node *temp)	//Adds data to the binary tree
{
	if(temp == NULL)						//If temp is NULL, make a new node!
	{
		last = headt;						//Set last equal to head here, for future comparision
		temp = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!temp)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//So return -1 to show memory allocation failed error to the user.
		temp -> data = a;					//Data holds the number entered
		temp -> left = NULL;				//Left/Right will be NULL for now
		temp -> right = NULL;	
	}
	
	if(headt == NULL)
	{
		headt = temp;
		return 0;
	}
	//Note: left side is less than, right side is greater than
	//LEFT SIDE
	if(a < last -> data)				//If a is less than the current node's data, then look to the left side
	{
		if(last -> left == NULL)		//If last is not equal to NULL, keep searching for where to add the data value!
		{
			last -> left = temp;		//Otherwise, if it equals NULL, then this is where to add the value!
			return 0;					//Return 0 for SUCCESS!
		}
		else
			AddTree(a, headt, last -> left, temp);	//Recusion
	}
	//RIGHT SIDE
	else 								//If a is greater than the current node's data, then look at the right side
	{
		if(last -> right == NULL)		//If last is not equal to NULL, keep searching for where to add the data value!
		{
			last -> right = temp;		//Otherwise, if it equals NULL, then this is where to add the value!
			return 0;					//Return 0 for SUCCESS!
		}
		else
			AddTree(a, headt, last -> right, temp);	//Recusion
	}
}

int SearchTree(int a, node *headt, node *last)				//Searchs teh tree for the value
{
	if(headt == NULL)		//If the list is empty, return error code -1
		return -1;
	if(last != NULL)		//As long as the list isn't equal to NULL, search!
	{
		if(a == last -> data)	//FOUND IT! SO RETURN IT!
			return a;
		if(a < last -> data)	//SEARCH LEFT
			SearchTree(a, headt, last -> left);
		else					//ELSE SEARCH RIGHT
			SearchTree(a, headt, last -> right);
	}
	else return -2;			//If it gets to this point, the number wasn't found in the tree, so return error code -2
}

int SearchList(int a, node *headl, node *last)				//Searchs the list for the given value
{
	if(headl == NULL)		//If the list is empty, return the error code -1
		return -1;
	if(last == NULL)		//If last ends up equaling NULL, the value wasn't found so return error code -2
		return -2;
	else if(a == last -> data)	//If a equals this node's data, then we found it!
		return a;				//So return the number that was originally entered!
	else if(a != last -> data)	//Run until we find a value equal to a, or last ends up equaling NULL
		SearchList(a, headl, last -> next);	//This moves last forward one node
}

int Print(node *list, node *tree)	
{
	int a = 0;
	node *temp;		//Temporary pointer
	temp = list;	//Makes temp equal to head
	
	if(temp == NULL)	//head is also NULL, aka empty list.
		return -1;
	else								//Well, the list has something stored! Print the nodes out!
	{
		cout<<"\nThis is what is in teh list! \n";
		do{
			cout<<temp -> data<<'\t';	//couts the current node
			temp = temp -> next; 		//basically moves it forward one node
		}while(temp != NULL);			//run until the end of the linked list
		cout<<"\n";
	}
	
	cout<<"\nThis is what is in teh tree! \n";	//I decided to make it easy and use recusion! So I made another function
	PrintT(tree);								//so its a function, within a function, that calls its self multiply times... o_O
	
	return 0;	//Success if the program made it here!
}

void PrintT(node *tree)
{
	if(!tree)		//While the tree exists (this copy of it anyway, so until the whole tree is printed)
		return;		//If the tree equals NULL, return since the whole tree has been printed!
			
	PrintT(tree -> left);		//This prints the left side of the tree
	cout<<tree -> data<<endl;
	PrintT(tree -> right);		//This prints the right side of the tree
	
}

int Destroy(node *&headl, node *&headt, node *end)		//Function that deletes the list from memory
{	
	node *curr, *root;	//Temporary pointers
	root = headl;		//root is now equal to the first node
	if(headl == NULL)	//if the list is empty no need to do the following else!
		return -1;			
	else if(headl != NULL)			//if the list has nodes - run the following
	{					
		if(headl -> next == NULL)	//If there's only one node, just delete it rather than run through anything else
		{
			delete headl;
			headl = NULL;
			return 0;
		}
		
		do{				
			curr = root;			//curr equals the first node.
			root = root -> next;	//root is now equal to the next node
			delete curr;			//curr is deleted - this means root is actually equal to the first node now (since the current one was deleted!)
			if(root -> next == NULL)//if root's next is NULL, then the last node was deleted with the 'delete curr' line. 
				headl = NULL;		//so this means *head can be set equal to NULL (an empty list)
		}while(headl != NULL);		//and the do/while stops running as the list is empty and all nodes were deleted from memory.
	}
	
	//Delete the tree! Similar to the print function, I went with a separate function just for the tree!
	end = headt;		//Save headt
	headt = NULL;		//Make headt equal to NULL
	DestroyTree(end);	//DELETE ALL THE NODES!
	return 0;
}

void DestroyTree(node *end)
{
	if(end != NULL)					//Run until all the nodes are deleted
	{
		DestroyTree(end -> left);	//Delete the left side
		DestroyTree(end -> right);	//Delete the right side
		delete end;
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
