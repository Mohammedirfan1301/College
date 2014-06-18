#include <conio.h>
#include <iostream>
//MORE INLCUDES AS NEEDED
using namespace std;

struct node			//A structure, which contains all the data (int + pointer) for each element (node) in the linked list
{
	int data;		//This will contain the number which the user wishes to add  to the list.
	node *next;		//This will point to the next node.
	node *prev;		//This will point to the previous node.
};

void Enter(void);				//Each function handles a different part of the program.

int main()
{
		cout<<" ##   ##   ######   #######   #######  #####     \n";		//Intro - thought it was kinda cool
 		cout<<" ##   ##   ##       ##   ##   ##   ##  #   #     \n";		//(I made this)
  		cout<<" #######   ######   ##        ##   ##     #      \n";
    	cout<<" ##   ##   ##       ##        ##   ##    #  #    \n";
      	cout<<" ##   ##   ######   ##        #######   #####    \n\n";  
	
	Enter();
	
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
