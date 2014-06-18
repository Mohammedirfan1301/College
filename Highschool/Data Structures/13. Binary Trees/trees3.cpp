#include <conio.h>
#include <iostream>
using namespace std;

struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	int data;		//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
	node *left;		//This will point to the left node.
	node *right;	//This will point to the right node.
};

//REQUIRED FUNCTIONS
int Read(node *&headl, node *&headt);		//Reads the file and adds values to the list and the tree
int Add(int a, node *&headl, node *&headt, node *befol, node *befot);	//Function to add numbers to the list (RECURSIVE!)
int SearchTree(int a, node *headt);			//Searchs teh tree for the value
int SearchList(int a, node *headl);			//Searchs the list for the given value
int Print(node *headl, node *headt);		//Prints both the list and the search tree			
int Destroy(node *&headl, node *&headt);	//Function to DESTROY the list at the end of the program

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
					befol = headl;
					befot = headt;		//MAKE SURE THEY EQUAL NULL!
					err = Add(num, headl, headt, befol, befot);
					if(err == 0)
						//SUCCESS
					if(err == -1)
						cout<<"ERROR!"; //ERROR
					if(err == 2)
					{
						cout<<"Hmm. \n"; 
						Enter();
					}
				}
				
				if(ans == 2)
				{
					cout<<"Searching the tree for the given value... \n";
				}
				
				if(ans == 3)
				{
					cout<<"Searching the list for the given value... \n";
				}
				
				if(ans == 4)
				{
					cout<<"\nPrinting what is in the list and tree! \n";
					err = Print(headl, headt);
					if(err == 0)
						//Enter();
					if(err == -1)
						cout<<"ERROR THE LISTS ARE EMPTY!"; //ERROR
					Enter();
				}
					
				if(ans == 5)
				{
					cout<<"\nWiping the list & tree... \n";
					err = Destroy(headl, headt);
					if(err = -1)
					{
						cout<<"ERROR! Cannot destroy an empty list/tree! \n";
						Enter();
					}
				}
				
				if(ans == 6)
				{
					cout<<"\nQuitting to the main menu...\n";
					Destroy(headl, headt);
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
		Destroy(headl, headt);	//Wipe the list & tree for the next run or for quitting the program
		
	}while(x == 1);

	return 0;
}

int Read(node *&headl, node *&headt)
{
/*
	ifstream entry;		//ifstream for opening the file
    string filename("treedata.txt");    //string to hold the filename (change this for different file names!!!)
    string command;     //string to hold each line in the file
	int num = 0;		//final num to send to the functions
	int code = 0;		//code that holds the return value of the functions
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
*/    
	return 0;	//success if it made it this far!
}

//MUST BE RECURSIVE!
int Add(int a, node *&headl, node *&headt, node *befol, node *befot)//Adds data to the linked list
{	
	node *currl = NULL, *currt = NULL;			//Temp pointers
	int x = 0;
	
	if( (headl != NULL) && (headl -> next != NULL) && (befol -> next == NULL) )		//Don't return until it finds the end of the list
		return 2;
	//if(currt -> data == a)		//^^
		//return 0;
	
	if(currl == NULL && currt == NULL)
	{
		//LIST
		currl = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!currl)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//So return -1 to show memory allocation failed error to the user.
		currl -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
		currl -> next = NULL;				//next is NULL as it will be the last node when added.
	
		//TREE
		currt = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!currt)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//Therefore return -1 to show memory allocation failed error to the user.
		currt -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
		currt -> left = NULL;				//Left/Right will be NULL for now
		currt -> right = NULL;	
	}
	
	if(headl == NULL && headt == NULL)		//Handle the first node case
	{
		headl = currl;						//Make each head point to their first nodes!
		headt = currt;
		return 0;							//Return success	
	}
	else									//Handle every other node
	{
		//LIST
		if(headl -> next != NULL)
		{
			befol = befol -> next;			//befo will contain the 2nd to last node in the list
			x = Add(a, headl, headt, befol, befot);
		}
		befol -> next = currl;			//Make curr the last node in the linked list.
		currl -> next = NULL;			//Make sure its NULL just incase!
		
		//TREE
		
		return 0;
	}
	
	return -1;	//Something happened if the program gets here!
}

int SearchTree(int a, node *headt)				//Searchs teh tree for the value
{
	return 0;	
}
int SearchList(int a, node *headl)				//Searchs the list for the given value
{
	return 0;	
}

int Print(node *headl, node *headt)	
{
	cout<<"\nThis is what is in teh list! \n";
	
	int a = 0;
	node *temp;		//Temporary pointer
	temp = headl;	//Makes temp equal to head
	
	if(temp == NULL)	//head is also NULL, aka empty list.
		return -1;
	else								//Well, the list has something stored! Print the nodes out!
	{
		//FORWARDS
		do{
			cout<<temp -> data<<'\t';	//couts the current node
			temp = temp -> next; 		//basically moves it forward one node
		}while(temp != NULL);			//run until the end of the linked list
		cout<<"\n\n";
	}
	
	cout<<"\nThis is what is in teh tree! \n";
	return 0;	//Success if the program made it here!
}

int Destroy(node *&headl, node *&headt)		//Function that deletes the list from memory
{	
	node *curr, *root;	//Temporary pointers
	root = headl;		//root is now equal to the first node
	if(headl == NULL)	
		return -1;			//if the list is empty no need to do the following else!
	else
	{					//if the list has nodes - run the following
		do{				
			curr = root;			//curr equals the first node.
			root = root -> next;	//root is now equal to the next node
			delete curr;			//curr is deleted - this means root is actually equal to the first node now (since the current one was deleted!)
			if(root -> next == NULL)//if root's next is NULL, then the last node was deleted with the 'delete curr' line. 
				headl = NULL;		//so this means *head can be set equal to NULL (an empty list)
		}while(headl != NULL);		//and the do/while stops running as the list is empty and all nodes were deleted from memory.
	}
	return 0;
}

void Enter(void)	//This function is just to stop the screen from ending quickly - makes the user hit enter before the program continues.
{	
	char c;
	do{
		cout<<"\nPress ENTER to continue. => ";	//PRESS ENTER!!
        c = getch();
   	}while(c != 13);	//Only ends when the user presses ENTER
}
