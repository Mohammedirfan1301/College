#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//9-13-2012
int main()
{
    const int ITEM=100; //for the parallel arrays
    char barcode[ITEM][50];  //barcode array
    char descript[ITEM][50]; //description array
    float price[ITEM];      //price array

    string hold;        //hold string for getline
    char barhold[8];    //hold array for the barcodes.
    float total = 0;        //total of each transaction
    
    int tran = 1;       //tran is the transaction #
    int numofit = 0;    //holds the # of items in the inventory

    int a, b, e, t, x;     //loop variables
    
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
        
        //cout<<barcode[a]<<"\t";           //cout barcode[a] to make sure it copied correctly.
        
        hold.clear();                       //clear the hold string for the next round of copying.
        
        getline(invent, hold, '\t');        //gets the 1st part of the invent file, up to the tab and puts it into string 'hold'
        strcpy(descript[a],hold.c_str());   //copies hold to a two d char array 'descript'
        //cout<<descript[a]<<"\t";          //cout descript[a] to make sure it copied right.
        hold.clear();                       //clears the hold string for the next copy.

        getline(invent, hold, '\n');        //1st part of invent file goes to the 'hold' variable, up to the newline.
        price[a] = atof(hold.c_str());      //this converts the string 'hold' to a float array 'price'
        //cout<<price[a]<<"\t\n";           //cout price[a] to make sure it copied right.
        hold.clear();                       //clear the hold string for the next round of copying.

        a++;
    }

    invent.close();
    
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
    transact.open("Transactions.txt");       //opens 
    
    if(!transact) //if the transaction file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";   //error message
        exit(0);
    }
    
    cout<<"\nTRANSACTION #"<<tran<<"\n\n";
    e = 0;
    
    //do{      //loop until the end of the file
        t = 0;          //zero the variables needed
        total = 0;      //^
        
        while(t != 1)           //loop for each transaction
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
                e = 1;
                //goto end_transact;
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
                    cout<<"ERROR! Barcode not found! \n";
                    cout<<"Try entering it again! \n";
                    x = 1;
                    break;
                }
            }
            
            if(a < numofit)
            {
                cout<<descript[a]<<"\t";        //cout the following for the customer
                cout<<price[a]<<"\n";           //^
                total += price[a];              //continue adding the total value of the items
            }
        }
        
        //if(e == 1)
           // break;
        
        cout<<"\nYour total is: "<<total<<"\n\n";
        system("PAUSE"); 
        tran++;
        cout<<"\nTRANSACTION #"<<tran<<"\n\n";
        
    //}while(e == 0);
    //end_transact:

    cout<<"\n************************************************* \n";
    cout<<"* Thanks for using the store's register system! * \n";
    cout<<"************************************************* \n";
    
    system("PAUSE");

    return 0;
}

/*
look up f stream!

http://www.cyberiapc.com/master/clesson8.htm
^ parallel arrays

http://www.cplusplus.com/doc/tutorial/files/
^ open files and input/output

http://www.cplusplus.com/reference/iostream/fstream/
^ fstream

http://www.cplusplus.com/forum/general/13135/
http://www.cplusplus.com/forum/beginner/1176/
http://www.fredosaurus.com/notes-cpp/io/readtextfile.html


*/
