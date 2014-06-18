#include <iostream>
using namespace std;

int wincheck(int arr1[], int arr2[], int arr3[]);
void initializeboard(int arr1[], int arr2[], int arr3[]);
int move(int arr1[], int arr2[], int arr3[]);

main ()
{
	int peg1[9] = {0};
	int peg2[9] = {0};
	int peg3[9] = {0};
	int a, b, x;
	
	b = 1;
	
	do{
	
	cout<<"\t1\t2\t3 \n";
	cout<<"-------------------------------- \n";
	
	for(a = 0; a < 9; a++)
	{
		if(peg1[a] == 0)
  			cout<<'\t'<<"|"<<'\t';
		if(peg1[a] != 0)
			cout<<'\t'<<peg1[a]<<'\t';
		if(peg2[a] == 0)
			cout<<"|"<<'\t';
		if(peg2[a] != 0)
			cout<<peg2[a]<<'\t';
		if(peg3[a] == 0)
			cout<<"|"<<'\n';
		if(peg3[a] != 0)
			cout<<peg3[a]<<'\n';
	}
	
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
	
	for(a = 1; a < 9; a++)
	{
		arr1[a] = b;
		arr2[a] = 0;
		arr3[a] = 0;
		b++;
	}
}

int wincheck(int arr1[], int arr2[], int arr3[])
{
		
}

int move(int arr1[], int arr2[], int arr3[])
{
	
}
