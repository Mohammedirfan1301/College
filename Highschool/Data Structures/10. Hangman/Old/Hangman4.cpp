#include <conio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;
using std::string;

struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	string word;	//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
};
			
void Intro(void);				//"HANGMAN" ASCII Art
int  Populate(node **head);		//Makes the circle list of words
string ChooseWord(node **head);	//Randomly chooses a word between 0 and 1000.
int PlayRound(node **head);		//Plays a round of hangman
int printword(char guess[30], char input[30], char real[30]);				//Prints the word as it is guessed so far
void printman(int y);			//Prints Hangman as he appears thus far
//void compare(int c)			//Compares each guess to see if the word has been guessed correctly yet.
void Enter(void);				//For the "Press Enter To Continue..." Prompt
void Destroy(node **head); 		//DESTROYS THE BASE WHEN DA PROGRAM IS DONE!

int main()
{
	node *head = NULL; 		//head of the linked list - points to the start of the list. Set to NULL as there aren't any elements in the list (yet).
	srand(time(0));			//Seeds the random
	int x = 0, ret = 0;
	
	ret = Populate(&head);	//Calls the Populate function - fills the list with 1000 words!
	
	if(ret == -1)
		cout<<"ERROR! Populate function failed! \n";
	
	do{	
		//Introduction!
		Intro();
		Enter();
		system("cls");	//clear the screen
		
		//Play da round of da hangman!
		PlayRound(&head);
		
		//Ask if they are done!
		cout<<"\nWould you like to quit the program?";
		cout<<"\nPress 1 to continue and 2 to quit. -> ";
		cin>>x;
		system("cls");	//clear the screen
		
	}while(x == 1);		//run til the user wants to quit.
	
	Destroy(&head);	//destroy all the nodes! :#
	
	return 0;
}

void Intro(void)
{
	cout<<" ------------------------------------------------------------------------   \n";
    cout<<" |  *    *     ***     *   *   *******   *       *     ***     *   *    |   \n";
    cout<<" |  *    *    *   *    **  *   #         **     **    *   *    **  *    O   \n";
  	cout<<" |  ******   *******   * * *   #  ****   * *   * *   *******   * * *   \\|/ \n";
	cout<<" |  *    *   *     *   *  **   #     *   *  * *  *   *     *   *  **   / \\ \n";
	cout<<" |  *    *   *     *   *   *   *******   *   *   *   *     *   *   *        \n";
	cout<<" |                               V1.1                                       \n";
    cout<<" ======================================================================     \n";
}

int  Populate(node **head)
{
	ifstream entry;		                 //ifstream for opening the file
	string filename = "Wordlist.txt";    //string to hold the filename
	string line;						 //string to temp. hold each line's word
	node *temp, *temp2;		             //Temporary pointers
    int x = 0;
    
	entry.open(filename.c_str());	//opens the file, using the name the user entered in
	
	if(!entry)     //if the file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file! \n";
        Sleep(5000);    //pause for 5 seconds
        return -1;
    }
	
	do{
		getline(entry, line, '\n');		//Goes through one line of the file and stores the given word in a string
		
		if(strncmp(line.c_str(), ";", 1) == 0)
		{
			//temp -> next = *head;	//Makes the list a circle! Yay!
			entry.close();	//closes the file
			x = 1;
			break;
		}
		
		temp = new(nothrow) node;		//Make a new node and fill it with the data from the user. (NOTHROW returns NULL on failure)
		
		if(!temp)			//If temp threw a NULL, then it seems memory allocation failed!
			return -1;		//Therefore return -1 to show memory allocation failed error to the user.
		
		//Transfer word to the node
		temp -> word = line;		//'word' contains the data - transfer it to 'words' var. in the node	
		temp -> next = NULL;	    //next is equal to head as it is a circularly linked list!
		
		//Add the node to the list
		if(*head == NULL)		//IF head is NULL, then the list is empty!
			*head = temp;		//So make head point to temp! Now the list has one element! Woo Hoo!
		else
		{
			temp2 = *head;					//The list isn't empty - I will have to search for the last node.
			while(temp2 -> next != NULL)	//FIND the last node - the one just before NULL!
				temp2 = temp2 -> next;		//Temp2 now contains the address of the last node
			temp2 -> next = temp;			//Make temp the last node in the linked list.
		}
		
	}while(x == 0);
	
	return 0;
}

string ChooseWord(node **head)
{
	int rando = 0, x = 0;
	string thew;
	node *temp = *head;
	
	rando = rand()%1001;	//Generates a random number between 0 and 1000
	
	do{
		temp = temp -> next;		//Temp2 now contains the address of the node requested
		x++;
	}while(x != rando);
	
	thew = temp -> word;
	
	return thew;
}

int PlayRound(node **head)
{
	char input[30] = {'\0'};	//Array for the letters that have been guessed   (A,E,P,L, etc)
	char guess[30] = {'\0'};	//Array for the 'guessed' word, as it is so far. (ie "Gue--" for the word "Guess")
	char real[30] = {'\0'};		//Array to hold the real word.					 (ie "Guess")
	int a = 0, x = 1, tries = 0, z = 0;
	int result = 0;
	string theword;
	theword = ChooseWord(head);
	
	strcpy(real, theword.c_str());
	
	cout<<"HANGMAN V1.1 \n";
	
	do{
		printman(tries);
		cout<<"The word is: ";
    	printword(guess, input, real);
		cout<<"Guess a letter. -> ";
		cin>>input[z];
    	//x = compare();
    	z++;
	}while(x == 1);
	
	if(result == 1)
	{
		cout<<"   O Hey!     O    O     O    O           \n";
		cout<<"  \\|/        \\|/  \\|/   \\|/  \\|/     \n";
		cout<<"  / \\        / \\  / \\   / \\  / \\     \n";
		cout<<"========================================= \n\n"; 
		
		cout<<"Woo hoo! You WON! You saved Hangman! :D \n";
		cout<<"You don't win any prizes though. ;( \n";
		return 1;
	}

    if(result == 2)
    {
		cout<<"____   \n";
    	cout<<"|  |   \n";
    	cout<<"|  O   \n";
    	cout<<"| /|\\ \n";
    	cout<<"| / \\  \n";
    	cout<<"|________ \n\n";
    	
    	cout<<"Sorry, you LOST. You killed Hangman! :# \n";
    	return 2;
	}

}

void printman(int y)					//Prints the Hangman as he appears.
{
    switch(y)
    {
        case 0:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|     \n";
                cout<<"|     \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;   
            
        case 1:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|  O   \n";
                cout<<"|     \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;
            
        case 2:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|  O  \n";
                cout<<"|  |  \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;
                
        case 3:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|  O  \n";
                cout<<"| /|  \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;
            
        case 4:
                cout<<"____   \n";
                cout<<"|  |   \n";
                cout<<"|  O   \n";
                cout<<"| /|\\ \n";
                cout<<"|      \n";
                cout<<"|________ \n\n";
                break;
            
        case 5:
                cout<<"____   \n";
                cout<<"|  |   \n";
                cout<<"|  O   \n";
                cout<<"| /|\\ \n";
                cout<<"| /    \n";
                cout<<"|________ \n\n";
                break;
            
        case 6:
                cout<<"____   \n";
                cout<<"|  |   \n";
                cout<<"|  O   \n";
                cout<<"| /|\\ \n";
                cout<<"| / \\  \n";
                cout<<"|________ \n\n";
                cout<<"OH NO! HE DIED! \n";
                cout<<"YOU MONSTER! YOU KILLED HANGMAN! \n";
                break;
        default:
                cout<<"ERROR! \n";
                break;
    }   
}

int printword(char guess[30], char input[30], char real[30])	//Prints the word as it has been guessed
{
    int a = 0, c = 0;
	c = strlen(real);
    
    if(input[0] == '\0')
    {
    
        for(a = 0; a < c; a++)
        {
            if(real[a] != 32)
                cout<<"*";
            if(real[a] == 32)
                cout<<" ";
        }
    }
    
    
        for(a = 0; a < c; a++)
        {    
            cout<<guess[a];
        }
    
    
    cout<<"\n\nLETTERS GUESSED: ";
    
    for(a = 0; a < c; a++)
        cout<<input[a]<<" ";
        
    return c;
}
/*
void compare(int c)
{
    int a, b = 0;
    
    for(a = 0; a < c; a++)
    {
        if(real[a] != 32)
        {
            if(input[z-1] == real[a])
            {
                guess[a] = real[a];
                b++;
            }
        }
        
        if(real[a] == 32)
            guess[a] = ' ';
    }
    
    if(b == 0)
        //y++;
        
    if(b == 0 && y == 7)
    {
        print();
        result = 1;
    }
       
    if(strncmp(gues, real, c) == 0)
        result = 2;          
}
*/
void Destroy(node **head)
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

void Enter(void)	//This function is just to stop the screen from ending quickly - makes the user hit enter before the program continues.
{
	char c;
	
	do{
		cout<<"\nPress ENTER to continue. => ";	//PRESS ENTER!!
        c = getch();
   	}while(c != 13);	//Only ends when the user presses ENTER
}
