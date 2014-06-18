#include <conio.h>
#include <iostream.h>
#include <iomanip.h>
#include <string.h>

int quantity[25] = {0};
char descript[25][40] = { {'\0'} };
float price[26] = {0};
float total = 0, subtotal = 0, tax = 0, grandtotal = 0;
int a = 0, itemnum = 0;

void clear(void);
void intro(void);
void entry(void);
void display(void);
void print(int [], char [][40], float [], int, float);
void conclude(void);

main()
{
    int onoff = 0, x = 1;
    
	 do{

	 //25 possible products - only 19 declared, 6 can be added manually.
	 //0 through 3: Bread
	 //4 is empty
	 strcpy(descript[0], "Package of one dozen bread rolls");
	 /*
	 descript[1] = {'Package of six bulkie rolls'};
    descript[2][] = {"Loaf of white bread"};
	 descript[3][] = {"Loaf of wheat bread"};
	 descript[4][] = {'\0'};
    
	 //5 through 9: Dairy
	 //10 = empty
	 descript[5][] = {"Butter"};
    descript[6][] = {"Cheese"};
    descript[7][] = {"Low fat milk"};
    descript[8][] = {"Whole milk"};
    descript[9][] = {"Yogurt"};
	 descript[10][] = {'\0'};
    
	 //11 through 15: Fruit
	 //16 = empty
    descript[11][] = {"Apple"};
    descript[12][] = {"Banana"};
    descript[13][] = {"Orange"};
    descript[14][] = {"Pear"};
	 descript[15][] = {"Watermelon"};
	 descript[16][] = {'\0'};
    
	 //17 through 21: Vegetables
	 //22 = empty
    descript[17][] = {"Broccoli"};
    descript[18][] = {"Carrot"};
    descript[19][] = {"Corn"};
    descript[20][] = {"Lettuce"};
    descript[21][] = {"Potatoe"};
	 descript[22][] = {'\0'};
    
	 //23 & 24 are left empty. They have no category - for random items that may appear.
	 descript[23][] = {'\0'};
	 descript[24][] = {'\0'};
    */

    //Intro prompt before the register actually boots.
    cout<<"\t\t TSM REGISTER V2.0 \n";
    cout<<"This program is designed to ring up customers as quick as possible. \n\n";
    cout<<"Some features of the program include: \n\n";
    cout<<"1. NO REBOOT required between customers - register automatically clears \n";
    cout<<"the previous entries. \n";
    cout<<"2. Ability to manually enter an item's price and description. \n";
    cout<<"3. Option to delete any item from the recept and from the system. \n";
    cout<<"4. More features to be added in the future! \n\n";
    
    cout<<"To boot up the register, enter 1. To shutdown the register, enter 2. \n";
    
    do{
    cout<<"Enter your selection here: ";
    cin>>onoff;
    }while(onoff != 1 && onoff != 2);
    
    if(onoff == 2)
        x = 2;
    
    clear();
    
//------------------------------------------------------------------------------
    
    do{
    
	 intro();
	 print(quantity, descript, price, itemnum, total);
	 conclude();

    entry();
    
    cout<<"To ring another customer, enter 1. To shutdown the register, enter 2. \n";
    do{
    cout<<" Enter your selection here: "; 
    cin>>onoff;                                                    
    }while(x != 1 && x != 2);
    
    if(onoff == 2)
        x = 2;
    
    clear();
    
    }while(onoff == 1);
    }while(x == 1);
    
    cout<<"Shutting down the register... \n";
    
    return 0;
}

//===================================================================================================================================

//simple array to clear the screen whenever needed.
void clear (void)
{
    clrscr();
}

void intro(void)
{
    //Introduction
	cout<<"************************************************************** \n";
	cout<<"*                 THE SUPERMARKET                            * \n";
	cout<<"*                                                            * \n";
	cout<<"*      THE LOWEST PRICES - ALL THE TIME                      * \n";
	cout<<"*                                                            * \n";
	    //"*1 3  2    11               26                5   4    5   3 * \n";    
	cout<<"* Qty  Description                          Price    Total   * \n";
	cout<<"*                                                            * \n";
}

void entry(void)
{
	cout<<"Enter a Quanity: \n";
}

void display(void)
{
	cout<<"Here is a list of all the items currently in the system: \n\n";

	for(a = 0; a < 26; a++)
	{
		if(a == 0)
			cout<<"Bread - Numbers 0 to 4 \n";
		if(a == 5)
			cout<<"Dairy - Numbers 5 to 10 \n";
		if(a == 5)
			cout<<"Fruit - Numbers 11 to 16 \n";
		if(a == 5)
			cout<<"Vegetables - Numbers 17 to 22 \n";
		if(a == 5)
			cout<<"Empty - Numbers 23 & 24 \n";
	}
}

void print(int [], char [][40], float [], int, float)
{


	if(itemnum > 0)
	{
		cout<<"*"<<quantity[itemnum]<<" "<<descript[itemnum]<<" "<<price[itemnum]<<" "<<total<<" * \n";
	}

	if(itemnum == 0)
	{
		cout<<"*  x   __________________________________  $-------  $------ * \n";
	}
	cout<<"*                                                            * \n";
}

void conclude(void)
{
	cout<<"* ========================================================== * \n";
	cout<<"*                                                            * \n";
	cout<<"*    Subtotal: $ ?                                           * \n";
	cout<<"*         Tax: $ ?                                           * \n";	 
	cout<<"* Grand Total: $ ?                                           * \n";
	cout<<"*                                                            * \n";
	cout<<"* ========================================================== * \n";
	cout<<"*                                                            * \n";
   cout<<"* THANKS FOR SHOPPING AT THE SUPERMARKET - HAVE A NICE DAY!  * \n";
	cout<<"*                                                            * \n";
	cout<<"************************************************************** \n\n";
}

/*

	cout<<"*  x   __________________________________  $-------  $------ * \n";
	cout<<"*  x   __________________________________  $-------  $------ * \n";
	cout<<"*                                                            * \n";

*/
