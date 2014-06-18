#include <iostream>
using namespace std;

/*
Bugs:

*/

int wincheck(int arr3[]);									//is the game over? winner??
void initializeboard(int arr1[], int arr2[], int arr3[]);	//make everything zero and peg1 1-8
int move(int stack1[], int stack2[]);						//moves
int print(int arr1[], int arr2[], int arr3[]);				//print teh arrays!
		//arr1 is peg1, arr2 peg2, etc.
		//EXCEPT in the move function, where stack1/stack2 correspond with which pegs have been sent to the function!
main ()
{
	int peg1[9] = {0};
	int peg2[9] = {0};
	int peg3[9] = {0};
	int a, b, w = 1, x = 1, y = 0, z = 0;
	int moves, turns, code, win = 0;
	
	b = 1;
	
	do{	//first do/while is so the game can loop through multiple game plays
	initializeboard(peg1, peg2, peg3);	//calls up the initialize function which sets everything to zero and peg1 to 1-8
	moves = 1;	//make the move variable zero for each play through
	turns = 0;
	win = 0;
	x = 1;	//make the game replayable!
	
	do{	//this do/while is for making moves and loops until the end of the game.
	print(peg1, peg2, peg3);	//print the inital arrays.	
	cout<<"\nTURN #"<<moves<<'\n';	//prints the moves variable
	
	//the following asks the user to select two pegs to move from and to
	do{
	cout<<"\nWhat peg are you moving from? (1, 2 or 3) \n";
	cout<<"-> ";
	cin>>y;
	}while(y != 1 && y != 2 && y != 3);
	
	do{
	cout<<"\nWhat peg are you moving to? (1, 2, or 3) \n";
	cout<<"-> ";
	cin>>z;
	}while(z != 1 && z != 2 && z != 3);
	
	//the following code determines which pegs to send to the move function by
	//simply comparing y and z.
	code = 0;
	if(y == 1)
	{
		if(z == 1)
			code = move(peg1, peg1);
		if(z == 2)
			code = move(peg1, peg2);
		if(z == 3)
			code = move(peg1, peg3);
	}
	
	if(y == 2)
	{
		if(z == 1)
			code = move(peg2, peg1);
		if(z == 2)
			code = move(peg2, peg2);
		if(z == 3)
			code = move(peg2, peg3);
	}
	
	if(y == 3)
	{
		if(z == 1)
			code = move(peg3, peg1);
		if(z == 2)
			code = move(peg3, peg2);
		if(z == 3)
		 	code =	move(peg3, peg3);
	}
	
	if(code == -1)	//empty array error code
		cout<<"ERROR! Can't move to empty arrays! \n";
	if(code == -2)	//illegal move error code
		cout<<"ERROR! The move is illegal! \n";
	if(code == -3)	//illegal move (same array) error code
		cout<<"ERROR! Can't move to the same array! \n";
	else if(code == 0)	//if no error code is generated, then the move was successful
	{
		cout<<"SUCCESS! \n";
		moves++;	//increase the moves counter
		turns++;
	}
	
	cout<<"\n******************************************************* \n\n";
	
	win = wincheck(peg3);	//check to see if the game has been won yet.

	if(win == 1)	//if win equals 1 someone won the game!
	{
		x = 2;	//so make the game end by making x 2 and print the below winner message
		cout<<"YOU HAVE WON DA GAME! Congratz! \n";
		cout<<"You completed teh game in "<<turns<<" moves. \n";
	}
	
	}while(x == 1);	//continue looping til the user wins (above code)
	
	//ask if the user wants to play again
	cout<<"\nDo you want to play again? \n";
	cout<<"Enter 1 to play again. Enter 2 to quit. \n";
	cout<<"-> ";
	cin>>w;
	
	}while(w == 1);	//loop until the user enters 2 to quit the whole program
	cout<<"Good bye, Player! \n";
	return 0;
}

void initializeboard(int arr1[], int arr2[], int arr3[])
{
	int a, b = 0; //b must be zero for the below code to work as it must increase to 1, and then be stored in arr1 in order.
	arr1[0] = 0; //the below doesn't set arr1 to zero, so make sure its zero for the program to work!
	
	//set the first array equal to 1-8 and the rest equal to zero.
	for(a = 0; a < 9; a++)
	{
		if(a >= 1)	//make sure arr1[1], arr1[2] arr1[3] etc is  equal to 1,2,3 etc.
			arr1[a] = b;
		arr2[a] = 0;	//make everything else equal to zero
		arr3[a] = 0;
		b++;
	}
	
}

int wincheck(int arr3[])
{
	int a, b = 0;
	//very simple win checker - check to see if peg3 has the numbers 1 through 8 stored in order. if so, the game has been won. if not, the game continues
	for(a = 0; a < 9; a++)
	{
		if(arr3[a] == b)	//if arr3[a] is 1, then b may increase.
			b++;
	}
	
	if(b == 9) //if b makes it all the way to eight, then each number has been found to be stored in peg3. the only way for this to happen
		return 1;	//is to move each number 8 7 6 5 etc, so that it displays 12345678, which is how the logic of the above check works
	else			//ie peg3[1] == 1, so b++, then peg3[2] == 2, so b++, until peg3[8] == 8, b++ and b is now 8, thus the game is over.
		return 0;	//also return 1 for win and 0 for not won yet.
}

int move(int stack1[], int stack2[])
{
	int a, b, error, top1 = 0, top2 = 0, x;
	int c, d;	//for recording the spot where each top is
	c = 0, d = 0, x = 0; //must be equal to zero for the problem to function
    
    //peek at the arrays
    for(a = 0; a < 9; a++)
    {
        if(stack1[a] != 0)	//if stack1[a] equals zero, it should be the top of the array. 
        {
            c = a;		//make b equal to a. to check if the array is empty.
            if(a > 0)	//if a is greater than zero, the array 
                top1 = stack1[a];	//top is the top most value as stack1[a] is zero but stack1[a-1] is not zero.
            break;
        }
        
        if(a == 9 && stack1[a] == 0)	//if a is 9 and stack1[a] is zero, then the array is actually empty!.
        {
            top1 == 0;	//make sure top1 is zero for testing
            break;
        }
        
    }
    
    for(a = 0; a < 9; a++)
    {   
		if(stack2[a] != 0)	//if stack2[a] equals zero, it should be the top of the array. 
        {
            d = a;		//make b equal to a. to check if the array is empty.
            if(a > 0)	//if a is greater than zero, the array 
                top2 = stack2[a];	//c is the top most value as stack2[a] is zero but stack[a-1] is not zero.
            break;
        }
        
        if(a == 9 && stack2[a] == 0)  //if a is 9 and stack2[a] isn't zero, this is actually the top most value.
        {
            top2 = 0;	//make sure top2 is zero for testing
            break;
        }
	}
    
    //logic part - determines if the moves are legal or not
    if(top1 > top2 && top2 == 0)	//ex 1 moving to peg2 at start of the game - 1 is greater then zero but its a legal move.
    	error = 0;	//zero is success
    if(top1 < top2)	//ex 1 moves to peg2 where the top value is 2 - 12 is legal so legal move
    	error = 0;
    if(top1 == top2 && top1 == 0)	//ex top1 = 0 and top1 = top2, then top2 is zero, and each array is empty, like peg2 move to peg3 at start of the game
    	error = -1; //error empty arrays!
    if(top1 > top2 && top2 != 0) 	//ex 2 moves to a 1, not legal as 12 is legal not 21
    	error = -2;	//error the move is illegal!
    if(top1 == top2 && top1 != 0)	//if top1 equals top2 and they are not zero, the user is trying to move the same number to the same array which isn't legal!
    	error = -3; //error same arrays!
    
    //this pops & pushes
    if(error != -1 && error != -2 && error != -3)
    {
		stack1[c] = 0;		//pop the number from the first array.
		
		if(d == 0)
			stack2[8] = top1;	//push the other number to the second array.
		else
			stack2[d-1] = top1;
	}
	
	return error;
}

int print(int arr1[], int arr2[], int arr3[])
{
	int a;
	//print the numbers for the pegs
	cout<<"\t1\t2\t3 \n";
	cout<<"-------------------------------- \n";
	
	//loop through and print all the pegs out. Note that "|" could not be stored in the int arrays as it couts the ascii value
	//of 124. so any zeros are just not displayed and in their place a "|" is displayed.
	for(a = 0; a < 9; a++)
	{
		if(arr1[a] == 0)
			cout<<"\t|";
		if(arr1[a] != 0)
			cout<<'\t'<<arr1[a];
		if(arr2[a] == 0)
			cout<<"\t|";
		if(arr2[a] != 0)
			cout<<'\t'<<arr2[a];
		if(arr3[a] == 0)
			cout<<"\t|\n";
		if(arr3[a] != 0)
			cout<<'\t'<<arr3[a]<<'\n';
	}
}
//Helpful site to test how many moves, how the game works, etc:
// http://www.mazeworks.com/hanoi/index.htm
