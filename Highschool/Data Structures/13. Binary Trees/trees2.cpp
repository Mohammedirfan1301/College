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
int Add(int a, node *&headl, node *&headt);	//Function to add numbers to the list (RECURSIVE!)
int SearchTree(int a, node *headt);			//Searchs teh tree for the value
int SearchList(int a, node *headl);			//Searchs the list for the given value
int Print(node *headl, node *headt);		//Prints both the list and the search tree			
int Destroy(node *&headl, node *&headt);	//Function to DESTROY the list at the end of the program

//Misc functions
void Enter(void);							//For the "Press Enter to Continue..." prompt

int main()
{
	node *headl = NULL, *headt = NULL;
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
				Add(num, headl, headt);
			}
			if(ans == 2)
			
			if(ans == 3)
				Destroy(headl, headt);
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
		cin>>x;
	}while(x != 1 && x != 2);
	system("CLS");
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
int Add(int a, node *&headl, node *&headt)//Adds data to the linked list
{	
	/*
	Things to consider:
		1. if headl or headt = NULL
		2. 
	*/
	node *nlist, *ntree;
	
	if(headl && headt == NULL)
	{
		//LIST
		nlist = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!nlist)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//So return -1 to show memory allocation failed error to the user.
		nlist -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
		nlist -> next = NULL;				//next is NULL as it will be the last node when added.
	
		//TREE
		ntree = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!ntree)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//Therefore return -1 to show memory allocation failed error to the user.
		ntree -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
		ntree -> left = NULL;				//Left/Right will be NULL for now
		ntree -> right = NULL;
		
		headl = nlist;						//Make each head point to their first nodes!
		headt = ntree;	
	}
	else
	{
		//Figure out how to make it recursive!
		//First list
		//Then tree?
		//So
			
	}
	
	/*
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
	*/
	return 0;
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
/*
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
		}while(temp != NULL);			//run until the end of the linked list
		cout<<"\n\n";
	}
	*/
	return 0;
}

int Destroy(node *&headl, node *&headt)		//Function that deletes the list from memory
{	
	/*
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
	*/
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
