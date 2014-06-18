#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    const int ITEM=10;
    int barcode[ITEM];  //barcode array
    char descript[ITEM][50]; //description array
    float price[ITEM];  //price array
    
    string bar;
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
    
    while(invent.eof())    //loop until the end of the file
    {
        invent >> bar;
        cout<<bar;
        
        //barcode[a] = bar;
        
        invent >> desc;
        cout<<desc;
        /*
        for(b = 0; b < desc.length(); b++)
        {
            descript[a][b] = desc[b];
        }
        */
        invent >> pri;
        cout<<pri;
        //price[a] = pri;
    }
    
    invent.close();
    
    cout<<"\n\n\n";
    
    system("PAUSE");
    
    return 0;
}
