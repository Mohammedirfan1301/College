#include <iostream>
using namespace std;

int wincheck(int arr1[], int arr2[], int arr3[]);			//is the game over? winner??
void initializeboard(int arr1[], int arr2[], int arr3[]);	//make everything zero and peg1 1-8
int move(int arr1[], int arr2[]);							//moves
int print(int arr1[], int arr2[], int arr3[]);	//print teh arrays!
		//arr1 is peg1, arr2 peg2, etc.
		//EXCEPT in the move function, where arr1/arr2 correspond with which pegs have been sent to the function!
main ()
{
	int peg1[9] = {0};
	int peg2[9] = {0};
	int peg3[9] = {0};
	int a, b, w = 1, x = 1, y = 0, z = 0;
	int moves;
	
	b = 1;
	
	do{	//first do/while is so the game can loop through multiple game plays
	initializeboard(peg1, peg2, peg3);	//calls up the initialize function which sets everything to zero and peg1 to 1-8
	moves = 0;	//make the move variable zero for each play through
	
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
		cout<<"ERROR! Move invalid! \n";
	
	cout<<"\n******************************************************* \n\n";
	
	}while(x == 1);
	}while(w == 1);
	
	return 0;
}

void initializeboard(int arr1[], int arr2[], int arr3[])
{
	int a, b = 0;
	arr1[0] = 0;
	
	//set the first array equal to 1-8 and the rest zeros.
	for(a = 0; a < 9; a++)
	{
		if(a >= 1)	//make sure arr1[1], arr1[2] arr1[3] etc is  equal to 1,2,3 etc.
			arr1[a] = b;
		arr2[a] = 0;
		arr3[a] = 0;
		b++;
	}
	
	//as long as each array equals zero, set it equal to '|"
	for(a = 0; a < 9; a++)
	{
		if(arr1[a] == 0)
			arr1[a] = '|';
		if(arr2[a] == 0)
			arr2[a] = '|';
		if(arr3[a] == 0)
			arr3[a] = '|';
	}
	
}

int wincheck(int arr1[], int arr2[], int arr3[])
{
		
}

int move(int arr1[], int arr2[])
{
	int a, b, top1 = 0, top2 = 0;
	
	for(a = 0; a < 9; a++)
	{
		for(b = 0; b < 9; b++)
		{
			
			if(arr1[a] != 124)
			{
				top1 = arr1[a];	
			}
			
			if(arr2[a] != 124)
			{
				top2 = arr2[a];
			}
		}
	}
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
		if(arr1[a] == 124)
			cout<<"\t|";
		if(arr1[a] != 124)
			cout<<'\t'<<arr1[a];
		if(arr2[a] == 124)
			cout<<"\t|";
		if(arr2[a] != 124)
			cout<<'\t'<<arr2[a];
		if(arr3[a] == 124)
			cout<<"\t|\n";
		if(arr3[a] != 124)
			cout<<'\t'<<arr3[a]<<'\n';
	}
}

// http://www.mazeworks.com/hanoi/index.htm
