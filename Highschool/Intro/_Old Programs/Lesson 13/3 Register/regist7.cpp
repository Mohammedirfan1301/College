#include <conio.h>      //clear screen
#include <iostream.h>   //input output
#include <iomanip.h>    //setw()
#include <string.h>     //string commands, such as strcpy

int quantity[25] = {0};                 //keeps track of the quantity of each item
char descript[25][40] = { {'\0'} };     //holds all the item descriptions 
float price[25] = {0};                  //holds all the item prices
int itemnum[25] = {0};                  //keeps track of what the customer has bought - stores item numbers.
float total = 0, subtotal = 0, tax = 0, grandtotal = 0;     //used for the final calculations
int a = 0, b = 0;  //used where ever a loop is required.
char c;            //used for when a yes or no answer is needed.
float d = 0;        //used for when a float is needed.
int itemnumb = 0;   //used for counting the number of items

void mainmenu(void);        //main menu function - cashier selects the option from this
void clear(void);           //used for clearing of the screen
//void cleararray(void);    //used to completely clear all the arrays and totals at the end of each transaction.
void display(void);         //displays a list of the items in the system
void descriptset(void);     //sets all the descripts back to normal at the end of each transaction. (also at the beginning of the program)
void entry(void);           //where the cashier enters the current item.
void print(int [], int[], char [][40], float [], int);  //prints the recipt when selected.

main()
{
	 int onoff = 0, x = 1;

	 do{

	 descriptset(); //sets all the descriptions

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
     //this part loops itself for each customer's transaction.
	 do{

	 //cleararray();
	 mainmenu();
    
    cout<<"\nTo ring another customer, enter 1. To shutdown the register, enter 2. \n";
    
    do{
    cout<<" Enter your selection here: "; 
    cin>>onoff;                                                    
    }while(x != 1 && x != 2);
    
    if(onoff == 2)
        x = 2;
    
    clear();
    
    }while(onoff == 1);
    }while(x == 1);
    
    cout<<"\t\t TSM REGISTER V2.0 \n";
    cout<<"Shutting down the register... \n";
    
    return 0;
}

//===================================================================================================================================

//The Main Menu
void mainmenu(void)
{
	cout<<"\t\tTSM Register V2.0 \n";
	cout<<"Welcome Associate! Below is a list of what you can do: \n\n";
	cout<<"1. Ring up a customer \n";
	cout<<"2. Display a list of the items for a quick item lookup \n";
	cout<<"3. Print the current recipt (list of items, prices and totals) \n";
	cout<<"4. Finalize Sale \n\n";

	do{
	cout<<"Make your selection here: ";
	cin>>a;
   }while(a != 1 && a != 2 && a != 3);

	switch(a)
	{
		case 1:
         clear();
			entry();
			break;
		case 2:
			clear();
			display();
			break;
		case 3:
			clear();
			print(quantity, itemnum, descript, price, total);
			break;
		case 4:
			//finalize();
			break;
		default:
			cout<<"Error: Not a valid selection! \n";
			break;
	}
}

//simple array to clear the screen whenever needed.
void clear(void)
{
	 //clrscr(); //remember to change
	 system("CLS");
}

//The cashier entries the qty and item # here. 
void entry(void)
{
	cout<<"\t\tTSM Register V2.0 \n";
	
    do{
    cout<<"What item is the customer buying? \n";
    
    do{
	cout<<"Enter the item number: ";
	cin>>a;
    }while(a <= 25 && a >= 0);

	cout<<"Is this corrent: "<<descript[a]<<" ? \n";
	do{
    cout<<"Enter y for Yes / n for No: ";
	cin>>c;
    }while(c != 'y' && c != 'n');    
    }while(c == 'n');
    
    itemnum[itemnumb] = a;
    a = 0;
    c = '\0';
    
    do{
    cout<<"What is the price of the item the customer is buying? \n";
    cout<<"Enter the price here: ";
    cin>>d;
    
    cout<<"\n\nIs this correct: "<<d<<" ? \n";
    do{
    cout<<"Enter y for Yes / n for No: ";
    cin>>c;
    }while(c != 'y' && c != 'n');
    }while(c == 'n');
    
    price[itemnumb] = d;
    d = 0;
    c = '\0';
    
    do{
    cout<<"How many of the item is the customer buying? \n";
    cout<<"Enter the quanity here: ";
    cin>>a;
    
    cout<<"\n\nIs this correct: "<<a<<" ? \n";
    do{
    cout<<"Enter y for Yes / n for No: ";
    cin>>c;
    }while(c != 'y' && c != 'n');
    
    }while(c != 'y' && c != 'n');
    
    quantity[itemnumb] = a;
    a = 0;
    c = '\0';

    itemnumb++;
}

//Displays a list of all the items in the register system
void display(void)
{
	cout<<"Here is a list of all the items currently in the system: \n";

	for(a = 0; a < 25; a++)
	{
		if(a == 0)
			cout<<"\nBread - Numbers 0 to 4 \n";
		if(a == 5)
			cout<<"\nDairy - Numbers 5 to 10 \n";
		if(a == 11)
			cout<<"\nFruit - Numbers 11 to 16 \n";
		if(a == 17)
			cout<<"\nVegetables - Numbers 17 to 22 \n";
		if(a == 23)
			cout<<"\nEmpty - Numbers 23 & 24 \n";

		cout<<"Item #"<<a<<" "<<descript[a]<<endl;
	}
}

void descriptset(void)
{
	 //25 possible products - only 19 declared, 6 can be added manually.
	 //0 through 3: Bread
	 //4 is empty
	 strcpy(descript[0], "Package of one dozen bread rolls");
	 strcpy(descript[1], "Package of six bulkie rolls");
	 strcpy(descript[2], "Loaf of white bread");
	 strcpy(descript[3], "Loaf of wheat bread");
	 strcpy(descript[4], "EMPTY - ADD IEM");

	 //5 through 9: Dairy
	 //10 = empty
	 strcpy(descript[5], "Butter");
	 strcpy(descript[6], "Cheese");
	 strcpy(descript[7], "Low fat milk");
	 strcpy(descript[8], "Whole milk");
	 strcpy(descript[9], "Yogurt");
	 strcpy(descript[10],"EMPTY - ADD IEM");

	 //11 through 15: Fruit
	 //16 = empty
	 strcpy(descript[11], "Apple");
	 strcpy(descript[12], "Banana");
	 strcpy(descript[13], "Orange");
	 strcpy(descript[14], "Pear");
	 strcpy(descript[15], "Watermelon");
	 strcpy(descript[16], "EMPTY - ADD IEM");

	 //17 through 21: Vegetables
	 //22 = empty
	 strcpy(descript[17], "Broccoli");
	 strcpy(descript[18], "Carrot");
	 strcpy(descript[19], "Corn");
	 strcpy(descript[20], "Lettuce");
	 strcpy(descript[21], "Potatoe");
	 strcpy(descript[22], "EMPTY - ADD IEM");

	 //23 & 24 are left empty. They have no category - for random items that may appear.
	 strcpy(descript[23], "EMPTY - ADD IEM");
	 strcpy(descript[24], "EMPTY - ADD IEM");
}

//prints out the recipt to the screen
void print(int [], char [][40], float [], int, float)
{
	//Top part of the recipt
	cout<<"************************************************************** \n";
	cout<<"*                 THE SUPERMARKET                            * \n";
	cout<<"*                                                            * \n";
	cout<<"*      THE LOWEST PRICES - ALL THE TIME                      * \n";
	cout<<"*                                                            * \n";
		 //"*1 3  2    11               26                5   4    5   3 * \n";
	cout<<"* Qty  Description                          Price    Total   * \n";
	cout<<"*                                                            * \n";

	//Where the items show up:
	if(itemnum[ > 0)
	{
		cout<<"*"<<quantity[itemnum]<<" "<<descript[itemnum]<<" "<<price[itemnum]<<" "<<total<<" * \n";
	}

	if(itemnum == 0)
	{
		cout<<"*  x   __________________________________  $-------  $------ * \n";
	}

	cout<<"*                                                            * \n";

	//Bottom part of the recipt
	cout<<"* ========================================================== * \n";
	cout<<"*                                                            * \n";
	cout<<"*    Subtotal: $"<<subtotal<<"                               * \n";
	cout<<"*         Tax: $"<<tax<<"                                           * \n";
	cout<<"* Grand Total: $"<<grandtotal<<"                                    * \n";
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
