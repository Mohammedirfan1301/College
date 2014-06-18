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

    int a, b, x, z;            //loop variables

    ifstream invent;     //stream object "inventory"
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
        cout<<barcode[a]<<"\t";             //cout barcode[a] to make sure it copied correctly.
        hold.clear();                       //clear the hold string for the next round of copying.
        
        getline(invent, hold, '\t');        //gets the 1st part of the invent file, up to the tab and puts it into string 'hold'
        strcpy(descript[a],hold.c_str());   //copies hold to a two d char array 'descript'
        cout<<descript[a]<<"\t";            //cout descript[a] to make sure it copied right.
        hold.clear();                       //clears the hold string for the next copy.

        getline(invent, hold, '\n');        //1st part of invent file goes to the 'hold' variable, up to the newline.
        price[a] = atof(hold.c_str());      //this converts the string 'hold' to a float array 'price'
        cout<<price[a]<<"\t\n";             //cout price[a] to make sure it copied right.
        hold.clear();                       //clear the hold string for the next round of copying.
        
        a++;
    }

    invent.close();

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
