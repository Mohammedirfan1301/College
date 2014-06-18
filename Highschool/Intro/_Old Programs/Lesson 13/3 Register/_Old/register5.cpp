#include <iostream.h>
#include <iomanip.h>
#include <conio.h>

int quantity[25] = {0};
char descript[25][40] = { {'\0'}, {'\0'} };
float price[26] = {0};
float total = 0, subtotal = 0, tax = 0, grandtotal = 0;

void clear(void);
void intro(void);
void print(int [], char [][20], float [], float);
void conclude(void);

main()
{
    int onoff = 0, x = 1;
    
    do{
    
    //18 through 22: Bread
    descript[0][] = {"Package of one dozen bread rolls"};
    descript[1][] = {"Package of six bulkie rolls"};
    descript[2][] = {"Loaf of white bread"};
    descript[3][] = {"Loaf of wheat bread"};
    descript[4][] = {'\0'};
    
    //12 through 17: Dairy
    //17 = empty
    descript[5][] = {"Butter"};
    descript[6][] = {"Cheese"};
    descript[7][] = {"Low fat milk"};
    descript[8][] = {"Whole milk"};
    descript[9][] = {"Yogurt"};
    descript[10][] = {'\0'};
    
    //0 through 5: Fruit
    //5 = empty
    descript[11][] = {"Apple"};
    descript[12][] = {"Banana"};
    descript[13][] = {"Orange"};
    descript[14][] = {"Pear"};
    descript[15][] = {"Watermelon"};
    descript[16][] = {'\0'};
    
    //6 through 11: Vegetables
    //11 = empty
    descript[17][] = {"Broccoli"};
    descript[18][] = {"Carrot"};
    descript[19][] = {"Corn"};
    descript[20][] = {"Lettuce"};
    descript[21][] = {"Potatoe"};
    descript[22][] = {'\0'};
    
    //left empty
    descript[23][] = {'\0'};  
    descript[24][] = {'\0'};
    
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
	print(quantity, descript, price, total);
    conclude();
    
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
    system("CLS");
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

void print(int [], char [][20], float [], float)
{
	cout<<"\nTEST\n\n";
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
    cout<<"*                                                            * \n";
	cout<<"************************************************************** \n\n";
}

/*

	cout<<"*  x   __________________________________  $-------  $------ * \n";
	cout<<"*  x   __________________________________  $-------  $------ * \n";
	cout<<"*                                                            * \n";

*/
