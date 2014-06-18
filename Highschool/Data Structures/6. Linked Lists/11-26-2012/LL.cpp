#include <iostream>
#include <conio.h>

using namespace std;

void Manual(void);
void File(void);
int Add(void);
int Remove(void);
void Destroy(void);
int Print(void);

main()
{
	int opt = 0, end = 0;
	
	do{
		cout<<"Linked List V1.01 \n";
		cout<<"1. Manual Entry \n";
		cout<<"2. File Entry \n";
		cout<<"3. Quit \n";
		do{
			cout<<"Enter an option. -> ";
			cin>>opt;
		}while(opt != 1 && opt != 2 && opt != 3);
		cout<<'\n';
		
		switch(opt)
		{
			case 1:	//Manual Entry
					Manual();
					break;
			case 2:	//File Entry
					File();
					break;
			case 3: 
					cout<<"\nQuitting... \n";
					end = 1;
					break;
		}
   		
   		system("cls");	//clear the screen
   		
	}while(end != 1);
}

void Manual(void)
{
	char c;
	int end = 0, x = 0;
	
	do{
		cout<<"Manual Entry. \n";
		cout<<"\nWhat do you want to do? \n";
		cout<<"1. Add \n";
		cout<<"2. Remove \n";
		cout<<"3. Print \n";
		cout<<"4. Quit \n";
		do{
			cout<<"-> ";
			cin>>x;
		}while(x != 1 && x != 2 && x != 3 && x != 4);
		
		switch(x)
		{
			case 1:
					Add();
					break;
			case 2:
					Remove();
					break;
			case 3:
					Print();
					break;
			case 4:
					end = 1;
					break;
		}
		
		do{
			cout<<"Press ENTER to continue. -> ";
        	c = getch();
   		}while(c != 13);
		
   		system("cls");	//clear the screen
	}while(end != 1);
}
void File(void)
{
	cout<<"\nFile Entry. \n";
}
int Add(void)
{
	cout<<"\nAdd! \n";
}
int Remove(void)
{
	cout<<"\nRemove! \n";
}
void Destroy(void)
{
	cout<<"\nDESTROYING ARRAYS... \n";
}
int Print(void)
{
	cout<<"Dis is what is in teh arrays! \n";
}
