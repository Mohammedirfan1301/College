#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
using std::ifstream;

main()
{
    const int ITEM=10;
    int barcode[ITEM][8];  //barcode array
    char descript[ITEM][20]; //description array
    float price[ITEM][10];  //price array
    char hold[100];         //hold char variable
    int i = 0;              //hold int variable
    int a, b, x;            //loop variables
    ifstream invent;     //stream object "inventory"
    
    invent.open ("Inventory.txt");  //opens the inventory text doc
    
    if(!invent) //if the inventory file does not open, this is true. 
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";
    }
    
    if (invent.is_open())
    {
        cout<<"The file is open. \n";
    }
    
    while(invent.good())
    {
        //for(a = 0; a < ITEM; a++)
        //{
            invent.getline(hold, 100);
            cout<<hold<<"\n";
            
            /*for(a = 0; a < 8; a++)
            {
                i = atoi(hold[a]);
                barcode[0][a] = i;
            }
            */
            //cout<<barcode[0]<<"\n";
            
            //barcode[0][] = atoi(hold);
            //cout<<barcode[a]<<"\n";
        //}
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
