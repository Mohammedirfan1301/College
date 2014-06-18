#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    const int ITEM=100; //for the parallel arrays
    char barcode[ITEM][50];  //barcode array
    char descript[ITEM][50]; //description array
    float price[ITEM];      //price array

    string hold;        //hold variable
    char barhold[8];    //hold array for the barcodes.
    float total = 0;        //total of each transaction
    
    int tran = 1;       //tran is the transaction #
    int numofit = 0;    //shows the # of items in the inventory

    int a, b, t, x;     //loop variables
    
    //********************************************************************
    //Inventory File

    ifstream invent;    //stream object "inventory"
    invent.open ("Inventory.txt");  //opens the inventory text doc

    if(!invent) //if the inventory file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";
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
        
        //cout<<barcode[a]<<"\t";             //cout barcode[a] to make sure it copied correctly.
        
        hold.clear();                       //clear the hold string for the next round of copying.
        
        getline(invent, hold, '\t');        //gets the 1st part of the invent file, up to the tab and puts it into string 'hold'
        strcpy(descript[a],hold.c_str());   //copies hold to a two d char array 'descript'
        //cout<<descript[a]<<"\t";            //cout descript[a] to make sure it copied right.
        hold.clear();                       //clears the hold string for the next copy.

        getline(invent, hold, '\n');        //1st part of invent file goes to the 'hold' variable, up to the newline.
        price[a] = atof(hold.c_str());      //this converts the string 'hold' to a float array 'price'
        //cout<<price[a]<<"\t\n";             //cout price[a] to make sure it copied right.
        hold.clear();                       //clear the hold string for the next round of copying.

        a++;
    }

    invent.close();
    
        while(numofit == 0)     //finds the number of items in the transaction file
        {
            if(strcmp(barcode[a], barcode[a+1]) == 0)
                a++;
            else
                numofit = a;
        }
    //*********************************************************************
    //Transaction File Part 2
    
    ifstream transact;  //stream object called "transact"
    transact.open("Transactions.txt");       //opens 
    
    if(!transact) //if the transaction file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";
    }
    
    while(!transact.eof())      //loop until the end of the file
    {
        t = 0;
        total = 0;
        cout<<"\n TRANSACTION #"<<tran<<"\n";
        

        
        while(t != 1)           //loop for each transaction
        {
            hold.clear();                       //make sure hold is cleared
            getline(transact, hold, '\n');      //get the line of the transaction file and put it into the hold string
                        
            if(hold == "1")
            {
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
                    cout<<"ERROR! Barcode not found! \n";
                    cout<<"Try entering it again! \n";
                    break;
                }
            }
        
            cout<<descript[a]<<"\t";        //cout the following for the customer
            cout<<price[a]<<"\n";           //^
            
            total += price[a];              //continue adding the total value of the items
        }
        
        cout<<"Your total is: "<<total<<"\n";
        system("PAUSE");
    }

    cout<<"\n\n\n";

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
