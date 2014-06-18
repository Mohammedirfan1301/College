#include <conio.h>      //clear screen
#include <iostream.h>   //input output
#include <iomanip.h>    //setw()
#include <stdio.h>
#include <string.h>     //string commands, such as strcpy

/*
TO DO:
2. Add the finalization function
3. Make a way to delete an item from the system...?!?
*/

//main variables
int quantity[25] = {0};                 //keeps track of the quantity of each item
char descript[25][40] = { {'\0'} };     //holds all the item descriptions 
char tempdesc[40];                      //temp variable for the description when user enters an item in manually.
float price[25] = {0};                  //holds all the item prices
float total[25] = {0};                  //keeps track of the total price of each item (qty * price of 1 item
int itemnum[25] = {0};                  //keeps track of what the customer has bought - stores the item numbers.
float subtotal = 0, tax = 0, grandtotal = 0;     //used for the final calculations
int itemnumb = 0;   //used for counting the number of items
int endtran = 0;    //used for ending each transaction

//additional variables
int a = 0, b = 0;  //used where ever a loop is required.
char c;            //used for when a yes or no answer is needed.
float d = 0;        //used for when a float is needed.

//the functions
void mainmenu(void);        //main menu function - cashier selects the option from this
void clear(void);           //used for clearing of the screen
void cleararray(void);    //used to completely clear all the arrays and totals at the end of each transaction.
void display(void);         //displays a list of the items in the system
void set(void);             //sets all the descripts back to normal at the end of each transaction. (also at the beginning of the program)
void totals(void);          //totals up all the items added.
void entry(void);           //function that lets cashier enter items not listed.
void ringup(void);          //where the cashier enters the current item.    
void receipt(void);          //prints the recipt when selected.
void finalize(void);        //completes the sale - last chance to remove items/etc.

main()
{
    int onoff = 0, x = 1;

	do{

	set(); //sets all the descriptions/prices

    //Intro prompt before the register actually boots.
    cout<<"\t\t TSM REGISTER V2.0 \n";
    cout<<"This program is designed to ring up customers as quick as possible. \n\n";
    cout<<"Some features of the program include: \n\n";
    cout<<"1. No reboot between transactions - register resets after each customer. \n";
    cout<<"2. Ability to manually enter an item's price and description. \n";
    cout<<"3. Option to delete any item from the recept. \n";
    cout<<"4. Simple to use and always accurate. \n";
    cout<<"5. More features to be added in the future! \n\n";
    
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

	mainmenu();
    
    cout<<"To restart the register enter 1. To shutdown the register enter 2. \n";
    
    do{
    cout<<"Enter your selection here: "; 
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
	set();
    cout<<"\t\tTSM Register V2.0 \n";
	cout<<"Welcome Associate! Below is a list of what you can do: \n\n";
	cout<<"1. Display a list of the items for a quick item lookup \n";
	cout<<"2. Add an item into the system \n"; 
	cout<<"3. Ring up a customer \n";
	cout<<"4. Print the current recipt (list of items, prices and totals) \n";
	cout<<"5. Finalize Sale \n";
	cout<<"6. Shutdown the register \n\n";

	do{
	cout<<"Make your selection here: ";
	cin>>a;
    }while(a != 1 && a != 2 && a != 3 && a != 4 && a != 5 && a != 6);

    clear();

	switch(a)
	{
		case 1:
			display();   //works
			break;
		case 2:
            entry();     //works
            break;
		case 3:
			ringup();    //works
			break;
		case 4:
			receipt();    //works
			break;
		case 5:
			finalize();
			break;
		case 6:
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

//function that clears all values
void cleararray(void)
{
    set();
    memset(quantity, '\0', 25);
    memset(descript, '\0', 40);
    memset(price, 0, 25);
    memset(total, 0, 25);
    memset(itemnum, 0, 25);
    subtotal = 0;
    tax = 0;
    grandtotal = 0;
    itemnumb = 0;
    endtran = 0;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
        
}

//presets the descriptions//prices
void set(void)
{
	 //25 possible products - only 19 declared, 6 can be added manually.
	 //0 through 3: Bread
	 //4 is empty
	 strcpy(descript[0], "Package of one dozen bread rolls");
	 price[0] = 2.99;
	 strcpy(descript[1], "Package of six bulkie rolls");
	 price[1] = 1.25;
	 strcpy(descript[2], "Loaf of white bread");
	 price[2] = 1.49;
	 strcpy(descript[3], "Loaf of wheat bread");
	 price[3] = 1.99;

	 //5 through 9: Dairy
	 //10 = empty
	 strcpy(descript[5], "16 oz. Container of Butter");
	 price[5] = 2.50;
	 strcpy(descript[6], "1 lb of Cheese");
	 price[6] = 1.99;
	 strcpy(descript[7], "Gallon of Low fat milk");
	 price[7] = 2.49;
	 strcpy(descript[8], "Gallon of Whole milk");
	 price[8] = 2.69;
	 strcpy(descript[9], "5.3 oz. Container of Yogurt");
	 price[9] = 1.33;

	 //11 through 15: Fruit
	 //16 = empty
	 strcpy(descript[11], "Apples (1 lb)");
	 price[11] = 1.49;
	 strcpy(descript[12], "Bananas (1 lb)");
	 price[12] = .79;
	 strcpy(descript[13], "Bag of 12 Oranges");
	 price[13] = 2.99;
	 strcpy(descript[14], "Pears (1 lb)");
	 price[14] = .99;
	 strcpy(descript[15], "Watermelon (~5 lb)");
	 price[15] = 2.99;

	 //17 through 21: Vegetables
	 //22 = empty
	 strcpy(descript[17], "1 lb of Broccoli");
	 price[17] = 1.29;
	 strcpy(descript[18], "Package of Carrots (1 lb)");
	 price[18] = .99;
	 strcpy(descript[19], "Cucumbers (1 lb)");
	 price[19] = .49;
	 strcpy(descript[20], "Package of Lettuce");
	 price[20] = .99;
	 strcpy(descript[21], "Bag of Potatoes (5 lb)");
	 price[21] = 2.49;

	 //23 & 24 are left empty. They have no category - for random items that may be added.
}

void totals(void)
{
    for(a = 0; a <= itemnumb; a++)
    {
        total[a] = quantity[a] * price[itemnum[a]];
    }
    
    subtotal = total[0] + total[1] + total[2]+ total[3]+ total[4]+ total[5]+ total[6]+ total[7]+ total[8]+ total[9]+ total[10]+ total[11]+ total[12] + total[13]+ total[14] + total[15] + total[16] + total[17] + total[18] + total[19] + total[20]+ total[21]+ total[22]+ total[23] + total[24];
    tax = subtotal * .08;
    grandtotal = subtotal + tax;
}

//Function 1
//Displays a list of all the items in the register system
void display(void)
{
	cout<<"Here is a list of all the items currently in the system: \n";

	for(a = 0; a < 25; a++)
	{
		if(a == 0)
			cout<<"\nBread - Numbers 0 to 4         "<<"                  Price:  \n";
		if(a == 5)
			cout<<"\nDairy - Numbers 5 to 10        "<<"                  Price:  \n";
		if(a == 11)
			cout<<"\nFruit - Numbers 11 to 16       "<<"                  Price:  \n";
		if(a == 17)
			cout<<"\nVegetables - Numbers 17 to 22  "<<"                  Price:  \n";
		if(a == 23)
			cout<<"\nEmpty - Numbers 23 & 24        "<<"                  Price:  \n";
        
        if(a >= 0 && a <= 9)
		      cout<<"Item #"<<a<<" "<<left<<setw(41)<<descript[a]<<"$"<<price[a]<<endl;
		if(a >=10 && a < 25)
		      cout<<"Item #"<<a<<" "<<left<<setw(40)<<descript[a]<<"$"<<price[a]<<endl;
	}
	
    cout<<endl;
	
	do{
	cout<<"When you are done looking at the list, press enter. -> ";
	c = getch();
	 
	if(c == 13)
	{
	   clear();
	   mainmenu();
    }
    
    clear();
    
    }while(c != 13);
}

//Function 2
//Adds an item to the system in an available spot.
void entry(void)
{
    cout<<"\t\tTSM Register V2.0 \n";
    cout<<"Here are the empty spots: \n";
            
    for(a = 0; a < 25; a++)
    {
                
        if(price[a] == 0)
        {
            cout<<"\nItem #"<<a<<" is empty. Add item to this spot? \n";
            do{
            cout<<"Enter y for Yes / n for No: ";
            cin>>c;
            }while(c != 'y' && c != 'n');
                    
            if(c == 'y')
            {
                do{
                cout<<"\nWhat is the item called? \n";
                cout<<"Enter the description of the item: ";
                        
                for(b = 0; b < 40; b++)
                {
                    tempdesc[b] = getch();
                    cout<<tempdesc[b];
                        
                    if(tempdesc[b] == 8)
                    b = b - 2;
                            
                    if(tempdesc[b] == 13)
                    break;        
                }
                                                
                cout<<"\n\nIs this correct: "<<tempdesc<<endl;
                        
                do{
                cout<<"Enter y for Yes / n for No: ";
                cin>>c;
                }while(c != 'y' && c != 'n');
                }while(c == 'n');
                        
                strncpy(descript[a], tempdesc, b);
                        
                do{
                cout<<"\nWhat is the price of the item? \n";
                cout<<"Enter the price of the item: ";
                cin>>d;
                        
                cout<<"\nIs this correct: "<<d<<endl;
                        
                do{
                cout<<"Enter y for Yes / n for No: ";
                cin>>c;
                }while(c != 'y' && c != 'n');
                }while(c == 'n');
                        
                price[a] = d;
            }
        }
    }
    
    clear();
    mainmenu();
}

//Function 3
//The cashier enters the item # and the qty here. 
void ringup(void)
{
	
    do{
    cout<<"\t\tTSM Register V2.0 \n";
    cout<<"What item is the customer buying? \n";
    
    do{
	cout<<"Enter the item number: ";
	cin>>a;
    }while( a != 0 && a != 1 && a != 2 && a != 3 && a != 4 && a != 5 && a != 6 && a != 7 && a != 8 && a != 9 && a != 10 && a != 11 && a != 12 && a != 13 && a != 14 && a != 15 && a != 16 && a != 17 && a != 18 && a != 19 && a != 20 && a != 21 && a != 22 && a != 23 && a != 24);

	cout<<"\nIs this correct: \n";
    cout<<"Item: "<<descript[a]<<"\t Price: "<<price[a]<<"\n";
	do{
    cout<<"\nEnter y for Yes / n for No: ";
	cin>>c;
    }while(c != 'y' && c != 'n');    
    clear();
    }while(c == 'n');
    
    itemnum[itemnumb] = a;
    a = 0;
    c = '\0';
    
    /*
    do{
    cout<<"\t\tTSM Register V2.0 \n";
    cout<<"What is the price of the item the customer is buying? \n";
    cout<<"Enter the price here: ";
    cin>>d;
    
    cout<<"\nIs this correct: "<<d<<"? \n";
    do{
    cout<<"Enter y for Yes / n for No: ";
    cin>>c;
    }while(c != 'y' && c != 'n');
    clear();
    }while(c == 'n');
    
    price[itemnumb] = d;
    d = 0;
    c = '\0';
    */
    
    do{
    cout<<"\t\tTSM Register V2.0 \n";
    cout<<"How many of the item is the customer buying? \n";
    cout<<"Enter the quanity here: ";
    cin>>a;
    
    cout<<"\nIs this correct: "<<a<<"\n";
    do{
    cout<<"\nEnter y for Yes / n for No: ";
    cin>>c;
    }while(c != 'y' && c != 'n');
    clear();
    }while(c == 'n');
    
    quantity[itemnumb] = a;
    a = 0;
    c = '\0';
    itemnumb++;

    totals();
    mainmenu();
}

//Function 4
//prints out the recipt to the screen
void receipt(void)
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

    //If no items have been entered yet:
    if(itemnumb == 0 )
	{                                                      
		cout<<"*  0   NONE SELECTED                        $0       $0      * \n";
	}

	//Where the items show up: (if an item has been entered)
	if(itemnumb != 0)
	{
		for(a = 0; a < itemnumb; a++)
        {
            cout<<"* "<<right<<setw(3)<<quantity[a]<<"  "<<left<<setw(37)<<descript[itemnum[a]]<<"$"<<setw(5)<<price[itemnum[a]]<<"   "<<"$"<<setw(5)<<total[a]<<"  * \n";
        }
	}

	cout<<"*                                                            * \n";

	//Bottom part of the receipt
	cout<<"* ========================================================== * \n";
	cout<<"*                                                            * \n";
	cout<<"*    Subtotal: $"<<right<<setw(8)<<subtotal  <<"                                     * \n";
	cout<<"*         Tax: $"<<right<<setw(8)<<fixed<<setprecision (2)<<tax       <<"                                     * \n";
	cout<<"* Grand Total: $"<<right<<setw(8)<<grandtotal<<"                                     * \n";
	cout<<"*                                                            * \n";
	cout<<"* ========================================================== * \n";
	cout<<"*                                                            * \n";
	cout<<"* THANKS FOR SHOPPING AT THE SUPERMARKET - HAVE A NICE DAY!  * \n";
	cout<<"*                                                            * \n";
	cout<<"************************************************************** \n";
	
	cout<<endl;
	
	do{
	cout<<"When you are done looking at the receipt, press enter. -> ";
	c = getch();
	 
	if(c == 13)
	{
	   if(endtran == 1)
	   {
           cleararray();     
       }
       
       clear();
	   mainmenu();
    }
    
    clear();
    
    }while(c != 13);
}

//Function 5
//Completes the sale when all items have been entered.
void finalize(void)
{
    cout<<"\t\tTSM Register V2.0 \n";
    cout<<"WARNING: THE FOLLOWING WILL END THE CURRENT TRANSACTION AND RESET ALL TOTALS. \n\n";
    
    cout<<"Are you completely done entering all the items into the system? \n";
    do{
    cout<<"Enter y for Yes / n for No: ";
    cin>>c;
    }while(c != 'y' && c != 'n');
    
    if(c == 'y')
    {
        endtran = 1;
        clear();
        receipt();
    }
        
    if(c == 'n')
        mainmenu();
}
