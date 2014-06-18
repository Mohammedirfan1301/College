#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

main()
{
    const int ITEM=10;
    int barcode[ITEM][8];  //barcode array
    char descript[ITEM][20]; //description array
    float price[ITEM][10];  //price array
    char hold[10] = {0};    //holds the input from the text document
    int a, b, x;            //loop variables
    ifstream inventory;
    
    inventory.open ("Inventory.txt");  //opens the inventory text doc
    
    if(!inventory) //if the inventory file does not open, this is true. 
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";
    }
    
    if (inventory.is_open())
    {
        cout<<"The file is open. \n";
    }
    
    for(a = 0; a < ITEM; a++)
    {
        hold[a] << inventory;
        barcode[a] = atoi(hold[a]);
        
        descript[a] << inventory;
        
        price[a] << inventory;    
    
    }   
    
    inventory.close();
    
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
