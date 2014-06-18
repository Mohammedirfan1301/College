//9-13-2012         JASON DOWNING       PERIOD 2
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    const int ITEM=100; 			//for the parallel arrays
    char barcode[ITEM][50] = {0};	//barcode array
    char descript[ITEM][50] = {0}; 	//description array
    float price[ITEM] = {0};      	//price array

    string hold;         		//hold string for getline
    char barhold[9] = {0};
    char recipt[100][9] = {0};	//hold array for the barcodes.
    float total = 0;     		//total of each transaction
    
    int tran = 1;       		//tran is the transaction #
    int numofit = 0;    		//holds the # of items in the inventory

    int a, b, e = 0, t, x, z;	//loop variables
    
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

        a++;
    }

    invent.close();
    
    //find the number of items in the barcode array
    while(numofit == 0)     //finds the number of items in the transaction file
    {
        if(strcmp(barcode[a], barcode[a+1]) == 0)   //checks to see if the barcode in barcode[a] is the same size as barcode[a+1]
            a++;    //if so it increases a
        else
            numofit = a;        //if not, this means barcode[a+1] is not 8 characters long and thus not a barcode
                                    //so it must be the end of the array. or the total number of barcodes in the array.
    }
    
    //*********************************************************************
    //Transaction File Part 2
    
    ifstream transact;  //stream object called "transact"
    transact.open("Transactions.txt");       //opens the transaction.txt file
    
    if(!transact) //if the transaction file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";   //error message
    }
    
    a = 0;      //make sure a is 0 for the next step
    
    while(!transact.eof())		//this part goes through the transaction file and stores all the barcodes into an array called 'recipt'
    {
        hold.clear();						//clear the hold string - just in case
        getline(transact, hold, '\n');		//get the line of the file up to the newline and store it in a string called 'hold'
        strcpy(recipt[a], hold.c_str());	//copy the string 'hold' to an array called 'recipt'.
        a++;
    }
    
	a = 0;
	//this next part goes through the recipt array and prints the recipt to the screen and a file called 'recipt.txt'.
    
    while(e == 0) //loop until the end of the file
    {
        t = 0;          //zero the variables needed
        total = 0;      //^
        cout<<"\nTRANSACTION #"<<tran<<"\n\n";
        
        while(t == 0)           //loop for each transaction
        {
        	strcpy(barhold, recipt[b]);
        	
			if(barhold == "1")
            {
                t = 1;          //this breaks the loop if the end of the transaction is reached.
                break;
            }
            
            if(barhold == "0")
            {
                e = 1;
                break;
            }
        
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
                    //cout<<"Try entering it again! \n";
                    x = 1;
                    break;
                }
                
            }
            
            if(a < numofit)     //check how to use setw() with data
            {
                cout<<left<<setw(50)<<descript[a]<<"\t";        //cout the following for the customer
                cout<<right<<setw(8)<<"$"<<price[a]<<"\n";           //^
                total += price[a];              //continue adding the total value of the items
            }
            b++;
               
        }
        
        cout<<"Your total is: \t $"<<total<<"\n\n";
        tran++;
        cout<<"Press 1 to continue. -> ";
        cin>>z;
	}
    
	/*
	while(e == 0)	//run until the end of all the transactions
    {
		if(recipt[a] == "1")		//this checks for the end of the file and prevents extra
		{	
			if(recipt[a+1] == "0")	//transaction #s from appearing. it first checks for the end
			{
				e = 1;
				break;				//of the transaction and then it checks for the end of the file.
			}
		}
		
		t = 0, x = 0;
		total = 0;
		
		cout<<"\nTRANSACTION #"<<tran<<"\n\n";
		
		while(t == 0)	//run until the end of this current transaction
		{
			b = 0;
			
			if(recipt[a] == "1")	//this checks the end of the current transaction
			{
				t = 1;
				break;				//if recipt[a] equals 1, break the while loop (t == 0)
			}
			
			while(x != 1)   //this while loop checks to see if the current barcode matches the inventory
            {
                if(strcmp(recipt[a], barcode[b]) == 0)  //if there is a match, do this
                {
					x = 1;
					break;
                }
                
                if(b > numofit)
                {
                    cout<<"ERROR! Barcode "<<recipt[a]<<" not found! \n";
                    x = 1;
					break;
                }
                
				b++;   //increase b for the next round of searching.
			}
			
			if(b < numofit)     //if a is less then the numofit then it is a real barcode in the store's inventory
            {
                cout<<descript[a]<<"\t";        //cout the following for the customer
                cout<<"$"<<price[a]<<"\n";      //^
                total += price[a];              //continue adding the total value of the items
            }
			
			a++;
		}
		
		cout<<"Your total is: \t $"<<total<<"\n\n";
        tran++;
       	cout<<"Press 1 to end the program. -> \n";
    	cin>>z;
	}
	*/
	
    cout<<"\n************************************************* \n";
    cout<<"* Thanks for using the store's register system! * \n";
    cout<<"************************************************* \n";
    
    cout<<"Press 1 to end the program. -> \n";
    cin>>z;
    
    return 0;
}
