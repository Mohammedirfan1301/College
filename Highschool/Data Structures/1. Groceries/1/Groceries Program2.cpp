#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    const int ITEM=10;
    int barcode[ITEM][8];  //barcode array
    char descript[ITEM][20]; //description array
    float price[ITEM][10];  //price array
    
    int bar = 0;
    string desc;
    float pri = 0;
    
    int a, b, x;            //loop variables
    
    ifstream invent("Inventory.txt");     //stream object "inventory"
    
    invent.open ("Inventory.txt", ios::in);  //opens the inventory text doc
    
    if(!invent) //if the inventory file does not open, this is true. 
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";
    }
    
    if (invent.is_open()) //if the file is open, print this
    {
        cout<<"The file is open. \n";
    }
    a=0; //make sure a is equal to 0;
    while(!invent.eof())    //loop until the end of the file
    {
        invent >> bar;
        cout<<bar;
        //barcode[a][] = bar;
        //invent >> desc;
        cout<<desc;
        //descript[a][] = desc;
        invent >> pri;
        //cout<<pri;
        //price[a][] = pri;
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
