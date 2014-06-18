#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    const int ITEM=100;
    int barcode[ITEM];  //barcode array
    char descript[ITEM][50]; //description array
    float price[ITEM];  //price array

    int bar = 0;        //these are temp variables
    string desc;        //^
    float pri = 0;      //^

    string hold;        //hold var

    int a, b, x, z;            //loop variables

    ifstream invent;     //stream object "inventory"
    invent.open ("Inventory.txt");  //opens the inventory text doc

    if(!invent) //if the inventory file does not open, this is true.
    {              //the below errror will then print out.
        cout<<"Unable to open the selected file. \n";
    }

    //while(!invent.eof())    //loop until the end of the file
    //{
        std::getline(invent, hold, '\t');
        cout<<hold<<"\t";

        std::getline(invent, hold, '\t');
        cout<<hold<<"\t";

        std::getline(invent, hold, '\n');
        cout<<hold<<"\t\n";
    //}

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
