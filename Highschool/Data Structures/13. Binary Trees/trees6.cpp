#include <conio.h>
#include <iostream>
using namespace std;

/*
TO DO:

2. Add to the tree for more than one value (R)
3. Print the tree out
4. Search the tree for the given value (R)
5. Finilize the File Entry part

*/

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
int Destroy(node *&headl, node *&headt);		//Function to DESTROY the list at the end of the program

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
						cout<<"ERROR! FAILED TO ADD NODE! \n";
					err = AddTree(num, headt, headt, NULL);
					if(err == -1)
						cout<<"ERROR! FAILED TO ADD NODE! \n";
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
						cout<<"ERROR! EMPTY LIST!";
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
					err = Destroy(headl, headt);
					if(err == 0)
						cout<<"Successfully destroyed both the list and the tree! \n";
					if(err == -1)
						cout<<"ERROR! Cannot destroy an empty list/tree! \n";
					Enter();
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
int AddList(int a, node *&headl, node *last, node *temp)	//Adds data to the linked list
{	
	if(temp == NULL)
	{
		last = headl;
		temp = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!temp)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//So return -1 to show memory allocation failed error to the user.
		temp -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
		temp -> next = NULL;				//next is NULL as it will be the last node when added.
	}
	
	if(headl == NULL)// && headt == NULL)		//Handle the first node case
	{
		headl = temp;						//Make each head point to their first nodes!
		return 0;							//Return success	
	}
	else if(last -> next != NULL)									
		AddList(a, headl, last -> next, temp);  //This will continue to call t until the if statement is false
	else
		last -> next = temp;			//Make curr the last node in the linked list.
	
	return 0;	//Success
}

int AddTree(int a, node *&headt, node *last, node *temp)	//Adds data to the binary tree
{
	if(headt == NULL)
	{
		headt = new(nothrow) node;			//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		if(!headt)							//If temp threw a NULL, then it seems memory allocation failed!
			return -1;						//Therefore return -1 to show memory allocation failed error to the user.
		headt -> data = a;					//'a' contains the data - transfer it to 'data' var. in the node	
		headt -> left = NULL;				//Left/Right will be NULL for now
		headt -> right = NULL;	
		return 0;							//SUCCESS!
	}
	//Note: left side is less than, right side is greater than
	//LEFT SIDE
	if(a < last -> data)				//If a is less than the current node's data, then look to the left side
	{
		if(last -> left != NULL)		//If last is not equal to NULL, keep searching for where to add the data value!
			AddTree(a, headt, last -> left, temp);	//Recusion
		else
		{
			last ->	left = temp;		//Otherwise, if it equals NULL, then this is where to add the value!
			return 0;					//Return 0 for SUCCESS!
		}
	}
	//RIGHT SIDE
	else if(a >= last -> data)			//If a is greater than the current node's data, then look at the right side
	{
		if(last -> right != NULL)		//If last is not equal to NULL, keep searching for where to add the data value!
			AddTree(a, headt, last -> right, temp);	//Recusion
		else
		{
			last ->	right = temp;		//Otherwise, if it equals NULL, then this is where to add the value!
			return 0;					//Return 0 for SUCCESS!
		}	
	}
	
	return -1;	//If it makes it here, it wasn't added to the tree!
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
	if(headl == NULL)
		return -1;
	if(last == NULL)
		return -2;
	else if(a == last -> data)
		return a;
	else if(a != last -> data)
		SearchList(a, headl, last -> next);
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
	
	cout<<"\nThis is what is in teh tree! \n";
	PrintT(tree);
	
	return 0;	//Success if the program made it here!
}

void PrintT(node *tree)
{
	if(!tree)
		return;
			
	PrintT(tree -> left);
	cout<<tree -> data<<endl;
	PrintT(tree -> right);
	
}

int Destroy(node *&headl, node *&headt)		//Function that deletes the list from memory
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
	/*
	curr = headt;
	do{
		
	}while(headt
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
