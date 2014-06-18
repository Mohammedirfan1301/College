#include <iostream>
using namespace std;
//wincheck again!
int wincheck(int arr1[], int arr2[], int arr3[]);			//is the game over? winner??
void initializeboard(int arr1[], int arr2[], int arr3[]);	//make everything zero and peg1 1-8
int move(int stack1[], int stack2[]);							//moves
int print(int arr1[], int arr2[], int arr3[]);	//print teh arrays!
		//arr1 is peg1, arr2 peg2, etc.
		//EXCEPT in the move function, where stack1/stack2 correspond with which pegs have been sent to the function!
main ()
{
	int peg1[9] = {0};
	int peg2[9] = {0};
	int peg3[9] = {0};
	int a, b, w = 1, x = 1, y = 0, z = 0;
	int moves, code, win = 0;
	
	b = 1;
	
	do{	//first do/while is so the game can loop through multiple game plays
	initializeboard(peg1, peg2, peg3);	//calls up the initialize function which sets everything to zero and peg1 to 1-8
	moves = 0;	//make the move variable zero for each play through
	win = 0;
	
	do{	//this do/while is for making moves and loops until the end of the game.
	print(peg1, peg2, peg3);	//print the inital arrays.	
	cout<<"\nTURN #"<<moves<<'\n';	//prints the moves variable
	
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
	
	if(code == -1)
		cout<<"ERROR! Can't move to empty arrays! \n";
	if(code == -2)
		cout<<"ERROR! The move is illegal! \n";
	if(code == -3)
		cout<<"ERROR! Can't move to the same array! \n";
	else if(code == 0)
	{
		cout<<"SUCCESS! \n";
		moves++;
	}
	
	cout<<"\n******************************************************* \n\n";
	
	win = wincheck(peg1, peg2, peg3);
	win = 1;
	if(win == 1)
	{
		x = 2;
		cout<<"YOU HAVE WON DA GAME! Congratz! \n";
		cout<<"You completed teh game in "<<moves<<" moves. \n";
		cout<<"You did really well! I wish I could give you something... \n";
		cout<<"But alas I am just a simple computer program. \n";
	}
	
	}while(x == 1);
	
	cout<<"\nDo you want to play again? \n";
	cout<<"Enter 1 to play again. Enter 2 to quit. \n";
	cout<<"-> ";
	cin>>w;
	
	}while(w == 1);
	
	return 0;
}

void initializeboard(int arr1[], int arr2[], int arr3[])
{
	int a, b = 0;
	arr1[0] = 0;
	
	//set the first array equal to 1-8 and the rest equal to zero.
	for(a = 0; a < 9; a++)
	{
		if(a >= 1)	//make sure arr1[1], arr1[2] arr1[3] etc is  equal to 1,2,3 etc.
			arr1[a] = b;
		arr2[a] = 0;
		arr3[a] = 0;
		b++;
	}
	
}

int wincheck(int arr1[], int arr2[], int arr3[])
{
			//do this next!1!
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
            top1 == 0;
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
            top2 = 0;
            break;
        }
	}
    
    //does the logic work???
    if(top1 > top2 && top2 == 0)
    	error = 0; //fine to proceed with the rest of the function
    if(top1 < top2)
    	error = 0; //no problems
    if(top1 == top2 && top1 == 0)
    	error = -1; //error empty arrays!
    if(top1 > top2 && top2 != 0) 
    	error = -2;	//error the move is illegal!
    if(top1 == top2 && top1 != 0)
    	error = -3; //error same arrays!
    
    //cout<<top1<<'\t'<<top2;	//check to make sure tops are correct
    
    //this pops & pushes
    if(error != -1 && error != -2)
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
	
	//loop through and print all the pegs out. note: 124 = |, the ifs make the char display and not the ascii value.
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

// http://www.mazeworks.com/hanoi/index.htm
