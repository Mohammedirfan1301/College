#include <iostream>
using namespace std;

int wincheck(int arr1[], int arr2[], int arr3[]);
void initializeboard(int arr1[], int arr2[], int arr3[]);
int move(int arr1[], int arr2[]);
int print(int arr1[], int arr2[], int arr3[]);

main ()
{
	int peg1[9] = {0};
	int peg2[9] = {0};
	int peg3[9] = {0};
	int a, b, x = 1, y = 0, z = 0;
	
	b = 1;
	
	do{
	cout<<"\t1\t2\t3 \n";
	cout<<"-------------------------------- \n";
	initializeboard(peg1, peg2, peg3);
	print(peg1, peg2, peg3);
	
	//test
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
			move(peg1, peg1);
		if(z == 2)
			move(peg1, peg2);
		if(z == 3)
			move(peg1, peg3);
	}
	
	if(y == 2)
	{
		if(z == 1)
			move(peg2, peg1);
		if(z == 2)
			move(peg2, peg2);
		if(z == 3)
			move(peg2, peg3);
	}
	
	if(y == 3)
	{
		if(z == 1)
			move(peg3, peg1);
		if(z == 2)
			move(peg3, peg2);
		if(z == 3)
			move(peg3, peg3);
	}
	
	cout<<"\n******************************************************* \n\n";
	
	}while(x == 1);
	
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
	
}

int print(int arr1[], int arr2[], int arr3[])
{
	int a;
	
	for(a = 0; a < 9; a++)
	{
		cout<<"\t"<<arr1[a]<<"\t"<<arr2[a]<<"\t"<<arr3[a]<<"\n";
	}
}
