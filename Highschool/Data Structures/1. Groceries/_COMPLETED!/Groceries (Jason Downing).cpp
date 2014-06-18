#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    const int ITEM=100;		 //for the parallel arrays
    char barcode[ITEM][50];  //barcode array
    char descript[ITEM][50]; //description array
    float price[ITEM];       //price array

    string hold;        //hold string for getline
    char barhold[8];    //hold array for the barcodes.
    float total = 0;    //total of each transaction
    
    int numofit = 0;    //holds the # of items in the inventory

    int a, b, e = 0, t, x, z;     //loop variables
    
    cout<<"****************************************************************** \n";
    cout<<"*                 THE BASKET GROCERY STORE                       * \n";
    cout<<"*        ALL THE FOOD YOU COULD EVER WANT - IN ONE PLACE.        * \n";
    cout<<"****************************************************************** \n";
    
    //********************************************************************
    //Inventory File

    ifstream invent;    //stream object "inventory"
    invent.open ("Inventory.txt");  //opens the inventory text doc

    if(!invent) //if the inventory file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";
        exit(0);
    }

    a = 0;

    while(!invent.eof())    //loop until the end of the file
    {
        getline(invent, hold, '\t');        //get the first part of the inventory file, up to the tab and put it into string 'hold'
        strcpy(barcode[a],hold.c_str());    //copy hold to a two d char array 'barcode'
        
        if(hold == "1")               //if barcode[a] is equal to 1, break the loop.
        {
            break;
        }
        
        hold.clear();                       //clear the hold string for the next round of copying.
        
        getline(invent, hold, '\t');        //gets the 1st part of the invent file, up to the tab and puts it into string 'hold'
        strcpy(descript[a],hold.c_str());   //copies hold to a two d char array 'descript'
        hold.clear();                       //clears the hold string for the next copy.

        getline(invent, hold, '\n');        //1st part of invent file goes to the 'hold' variable, up to the newline.
        price[a] = atof(hold.c_str());      //this converts the string 'hold' to a float array 'price'
        hold.clear();                       //clear the hold string for the next round of copying.

        a++;	//increase for the next item
    }

    invent.close();
    numofit = a;		//numofit is the number of items found in the inventory file
    
    //*********************************************************************
    //Transaction File Part 2
    
    ifstream transact;  //stream object called "transact"
    transact.open("Transactions.txt");       //opens the transaction.txt file
    
    ofstream rec;
    rec.open("Recipt.out");
    
    if(!transact) //checks to see if the transaction file is open
    {
        cout<<"Unable to open the selected file. \n";  //if not this error message prints out.
        exit(0);
	}

    if(!rec)	  //checks to see if the recipt file is open
    {
    	cout<<"Unable to open the selected file. \n";	//if not this error message prints out.
    	exit(0);
	}
	
    //this is just printed to the recipt to resemble a real recipt
    rec<<"****************************************************************** \n";
    rec<<"*                 THE BASKET GROCERY STORE                       * \n";
    rec<<"*        ALL THE FOOD YOU COULD EVER WANT - IN ONE PLACE.        * \n";
    rec<<"****************************************************************** \n";
    
    cout<<"\nTRANSACTION"<<"\n\n";
    rec << "TRANSACTION"<<"\n\n";
    
    while(e == 0) //loop until the end of the file
    {
        t = 0;          //zero the variables needed
        total = 0;      //^
        
        while(t == 0)           //loop for each transaction
        {
            hold.clear();                       //make sure hold is cleared
            getline(transact, hold, '\n');      //get the line of the transaction file and put it into the hold string
                        
            if(hold == "1")
            {
                t = 1;          //this breaks the loop if the end of the transaction is reached.
                break;
            }
            
            if(hold == "0")
            {
                e = 1;			//this breaks the loop if the end of the file is reached
                break;
            }
            
            strcpy(barhold, hold.c_str());      //copy the string 'hold' to the char array 'barhold'
        
            a = 0;      //make sure these variables are 0.
            x = 0;      //^
        
            while(x != 1)   //while x is not 1, search through the barcode array
            {
                if(strcmp(barhold, barcode[a]) == 0)      //if there is a match, do this
                {
                    x = 1;                      //if x = 1, the barcode has been found
                    break;
                }
                
                a++;        //increase a for the next round of searching.
                
                if(a > numofit)
                {
                    cout<<"ERROR! Barcode "<<barhold<<" not found! \n";
                    rec <<"ERROR! Barcode "<<barhold<<" not found! \n";
                    x = 1;
                    break;
                }
                
            }
            
            if(a < numofit)     //check how to use setw() with data
            {
                cout<<left<<setw(50)<<descript[a]<<"\t";      //cout the following for the customer
                rec << descript[a]<<"\t";
                cout<<right<<setw(10)<<"$"<<price[a]<<"\n";    //^
                rec << price[a]<<"\n";
                total += price[a];                    //continue adding the total value of the items
            }
               
        }
        
        if(e == 1)		//this marks the end the end of the file
        {
			cout<<"There are no more transactions! \n";	
			rec <<"There are no more transactions! \n";
            break;
		}
        
        if(e != 1)
        {
			//The message below prints out the total price of the transaction.
			cout<<endl<<"Your total is: \t"<<right<<setw(50)<<"$"<<total<<"\n\n";
            rec << "\nThe total for this transaction is $"<<total<<"\n";
			cout<<"Press 1 to continue. -> ";	//pauses between transactions
            cin>>z;								//also requires an input (num/letter)
            
            cout<<"\n************************************************ \n";
            rec <<"\n************************************************ \n";
            cout<<"\nTRANSACTION \n\n";
            rec <<"\nTRANSACTION \n\n";
        }
        
    }      
	
	transact.close();	//closes the file
	rec.close();		//^
	
    cout<<"\n************************************************* \n";
    cout<<"*      Thanks for shopping at The Basket!       * \n";		//prints out a thank you message
    cout<<"************************************************* \n";		//to the screen
    
    rec<<"\n************************************************* \n";
    rec<<"*      Thanks for shopping at The Basket!       * \n";		//prints out a thank you message
    rec<<"************************************************* \n";		//to the recipt
    
    cout<<"\nPress 1 to end the program. -> ";	//pauses before the program closes
    cin>>z;

    return 0;
}
