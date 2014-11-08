#include <iostream>
#include <string>
#include <map>
#include <stack>

using namespace std;

int main()
{
//  ****************************************************************
//      Map stuff here
//  ****************************************************************

	map<string, string> ID;            // Map, which associates student IDs with Student names

    ID["1234"] = "Jason";
    ID["9999"] = "Huy";
    ID["5643"] = "JT";

    // Try basic outputting of a map.
    cout << "1234 -> " << ID["1234"] << "\n";
    cout << "9999 -> " << ID["9999"] << "\n";
    cout << "5643 -> " << ID["5643"] << "\n";

    map<string, string> JSON;                   // Map, which could be used for JSON data.
    map<string, string>::iterator json_ptr;     // iterator for the JSON map

    JSON["title"] = "Awesome title";
    JSON["data"] = "FDfe7rf9F*823713";
    JSON["array"] = "[1, 2, 3, 5, 8, 13, 21]";

    int size_of_map = JSON.size();      // Get the map's size.
    cout << "\nSize of this map is: " << size_of_map << "\n\n";

    // Make the iterator start at the beginning of the JSON map.
    json_ptr = JSON.begin();

    // Print out all the items in the map using the iterator.
    for(json_ptr = JSON.begin(); json_ptr != JSON.end(); json_ptr++)
    {
        cout << "Key: " << json_ptr -> first << "\n";
        cout << "Mapped value: " << json_ptr -> second << "\n\n";
    }

//  ****************************************************************
//      Stack stuff here
//  ****************************************************************
    stack<int> numberz;             // Making a stack of ints.

    // Going to push 100 numbers into this stack and have some fun.
    for(int i = 0; i < 100; i++)
    {
        numberz.push(i);    // Pushes i back to the correct position in the stack.
    }

    cout << "Outputting 5 numbers on the stack: \n";

    // Output the first 5 numbers.
    for(int i = 0; i < 5; i++)
    {
        cout << numberz.top() << "\n";
        numberz.pop();
    }

    // Pop a bunch of numbers off the stack.
    for(int i = 0; i < 50; i++)
    {
        numberz.pop();
    }

    cout << "\nWhat's on top of the stack now? \n";
    cout << "Looks like: " << numberz.top() << "\n";

    // Pop all the numbers on the stack.
    for(;numberz.empty() == false; numberz.pop())
    {
        // This will just loop through and pop all the elements on the stack.
        // .empty() will force the for loop to quit once we've popped all the elements.
    }

//  ****************************************************************
//      Queue stuff here
//  ****************************************************************




//  ****************************************************************
//      Vector stuff here
//  ****************************************************************



//  ****************************************************************
//      List here
//  ****************************************************************



	return 0;
}