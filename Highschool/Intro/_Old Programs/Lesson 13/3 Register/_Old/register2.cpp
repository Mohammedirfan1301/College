#include <iostream.h>
#include <iomanip.h>
#include <conio.h>

char items[12][20]; //= { {;
int quantity[12];
float price[12];
float subtotal = 0, tax = 0, grandtotal = 0;

/*

4 categories
3 items each

*/

main()
{
	int x = 1, menu = 0;

	do{
	//introduction prompt
	cout<<"Welcome to the Epic Store Cash Register Program \n";
	cout<<"Epic Store employees may use this program to: \n";
	cout<<"1. Ring up customers \n";
	cout<<"2. Check the price of an item \n";
	cout<<"3. And many more options to be added in the future! \n\n";

   //what-do-you-want-to-do prompt
	cout<<"What would you like to do? \n";
	cout<<"1. Sale (Ring a customer up) \n";
	cout<<"2. Check Price (ONLY for checking prices) \n";

	do{
	cout<<"Enter your selection in the next space: ";
	cin>>menu;
	cout<<endl;
	}while(menu != 1 && menu != 2);

	switch(menu)
	{
		case 1:
			cout<<"This is the Sale Option. \n";
			cout<<"CURRENTLY UNDER CONSTRUCTION \n";
			break;

		case 2:
			cout<<"This is the Check Price Option. \n";
			cout<<"CURRENTLY UNDER CONSTRUCTION \n";
			break;

		default:
			cout<<"Please choose an option that is listed above. \n";
	}

	do{
	cout<<"\nDo you want to rerun the program or do you want to quit? \n";
	cout<<"Enter 1 to continue or 2 to quit. -> ";
	cin>>x;
   }while(x != 1 && x != 2);

   clrscr();

	}while(x == 1);

	return 0;
}

/*
	cout<<"******************************************************************* \n";
	cout<<"*                         MARKET BASKET                           * \n";
	cout<<"*WELCOME                                                          * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"*                                                                 * \n";
	cout<<"******************************************************************* \n";

*/