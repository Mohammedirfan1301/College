#include <iostream>
using namespace std;

int wincheck(int arr1[], int arr2[], int arr3[]);
void initializeboard(int arr1[], int arr2[], int arr3[]);
int move(int arr1[], int arr2[], int arr3[]);

main ()
{
	char peg1[9] = {0};
	char peg2[9] = {0};
	char peg3[9] = {0};
	int a, b, x;
	
	b = 1;
	
	do{
	
	
	
	cout<<"\t1\t2\t3 \n";
	cout<<"-------------------------------- \n";
	
	//test
	cout<<"\nSelect a peg to move to. (1, 2 or 3) \n";
	cout<<"-> ";
	cin>>x;
	
	}while(x == 1);
	
	return 0;
}

void initializeboard(int arr1[], int arr2[], int arr3[])
{
	int a, b;
	arr1[0] = 0;
	
	for(a = 0; a < 9; a++)
	{
		arr1[a] = '|';
		arr2[a] = '|';
		arr3[a] = '|';
		//cout<<peg1[a]<<"\t"<<peg2[a]<<"\t"<<peg3[a]<<"\n";
	}
	
	for(a = 1; a < 9; a++)
	{
		arr1[a] = b;
		arr2[a] = 0;
		arr3[a] = 0;
		b++;
	}
	return 0;
}

int wincheck(int arr1[], int arr2[], int arr3[])
{
		
}

int move(int arr1[], int arr2[], int arr3[])
{
	
}
