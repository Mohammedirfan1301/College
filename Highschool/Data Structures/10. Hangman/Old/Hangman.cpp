#include <conio.h>
#include <fstream>
#include <iostream>
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

void Enter(void);				//Each function handles a different part of the program.

main()
{
	//USE A 'CIRCULAR' LINKED LIST!
	//Basically the last node points to the head - makes a circle - hence the name!
		
	node *head = NULL; 		//head of the linked list - points to the start of the list. Set to NULL as there aren't any elements in the list (yet).
	
	cout<<" ----------------------------------------------------------------------------------------------- \n";
    cout<<" |  ##	 ##       #######      ###   ##   #######   ###       ###      #######      ###   ##    \n";
    cout<<" |  ##    ##      ###   ###     ####  ##   #         ####     ####     ###   ###     ####  ##    \n";
  	cout<<" |  ########     ###########    ## ## ##   #######   ## ##   ## ##    ###########    ## ## ##    \n";
	cout<<" |  ##    ##    ###       ###   ##  ####   #     #   ##  ## ##  ##   ###       ###   ##  ####    \n";
	cout<<" |  ##    ##   ###         ###  ##   ###   #######   ##   ###   ##  ###         ###  ##   ###    \n";
	cout<<" |                                                                                               \n";
	cout<<" |                                                                                               \n";
    cout<<" ================================================================================================\n";  
	 
	cout<<" --------       \n";
	cout<<" |      |       \n";
	cout<<" |      0       \n";
	cout<<" |     \\|/      \n";
	cout<<" |     / \\      \n";
	cout<<" |              \n";
	cout<<" =============  \n";
	
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
