#include <iostream>
#include <string>
#include <stdlib.h>     // Included stdlib for srand and rand
#include <time.h>       // Included time.h for (TIME), seeds srand
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include "template.h"       // Going to try making a list of Students

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

    // Try basic outputting of a map
    cout << "1234 -> " << ID["1234"] << "\n";
    cout << "9999 -> " << ID["9999"] << "\n";
    cout << "5643 -> " << ID["5643"] << "\n";

    map<string, string> JSON;                   // Map, which could be used for JSON data
    map<string, string>::iterator json_ptr;     // iterator for the JSON map

    JSON["title"] = "Awesome title";
    JSON["data"] = "FDfe7rf9F*823713";
    JSON["array"] = "[1, 2, 3, 5, 8, 13, 21]";

    int size_of_map = JSON.size();      // Get the map's size
    cout << "\nSize of this map is: " << size_of_map << "\n\n";

    // Make the iterator start at the beginning of the JSON map
    json_ptr = JSON.begin();

    // Print out all the items in the map using the iterator
    for(json_ptr = JSON.begin(); json_ptr != JSON.end(); json_ptr++)
    {
        cout << "Key: " << json_ptr -> first << "\n";
        cout << "Mapped value: " << json_ptr -> second << "\n";
    }

    cout << "======================================================= \n\n";

//  ****************************************************************
//      Stack stuff here
//  ****************************************************************
    stack<int> numberz;             // Making a stack of ints

    // Going to push 100 numbers into this stack and have some fun
    for(int i = 0; i < 100; i++)
    {
        numberz.push(i);    // Pushes i back to the correct position in the stack.
    }

    cout << "Outputting 5 numbers on the stack: \n";

    // Output the first 5 numbers
    for(int i = 0; i < 5; i++)
    {
        cout << numberz.top() << "\n";
        numberz.pop();
    }

    // Pop a bunch of numbers off the stack
    for(int i = 0; i < 50; i++)
    {
        numberz.pop();
    }

    cout << "\nWhat's on top of the stack now? \n";
    cout << "Looks like: " << numberz.top() << "\n\n";

    // Pop all the numbers on the stack
    for(;numberz.empty() == false; numberz.pop())
    {
        // This will just loop through and pop all the elements on the stack.
        // .empty() will force the for loop to quit once we've popped all the elements.
    }

    // Let's make sure the stack is empty
    if(numberz.empty() == true)
    {
        cout << "Yay the stack is empty! \n";
    }
    else
    {
        cout << "Boooo the stack isn't empty! \n";
    }

    cout << "======================================================= \n\n";

//  ****************************************************************
//      Queue stuff here
//  ****************************************************************
    queue<float> fqueue;        // queue of floats

    // Let's push a bunch of random numbers into this queue.
    srand(time(NULL));

    // Push 50 random numbers into fqueue.
    for(int i = 0; i < 50; i++)
    {
        fqueue.push(rand());
    }

    // Check out what's on at the front/back of the queue
    cout << "Front of the queue: " << fqueue.front() << "\n";
    cout << "Back of the queue: " << fqueue.back() << "\n";

    // Make sure size is 50
    cout << "Size of the queue: " << fqueue.size() << "\n\n";

    // Pop a few numbers off
    for(int i = 0; i < 5; i++)
    {
        fqueue.pop();
    }

    // Check out what's on at the front/back of the queue (again)
    cout << "Front of the queue: " << fqueue.front() << "\n";
    cout << "Back of the queue: " << fqueue.back() << "\n";

    // Make sure size is 45
    cout << "Size of the queue: " << fqueue.size() << "\n\n";

    // Pop all the numbers on the queue
    for(;fqueue.empty() == false; fqueue.pop())
    {
        // This will just loop through and pop all the elements on the fqueue
        // .empty() will force the for loop to quit once we've popped all the elements.
    }

    // Let's make sure the queue is empty
    if(fqueue.empty() == true)
    {
        cout << "Yay the queue is empty! \n";
    }
    else
    {
        cout << "Boooo the queue isn't empty! \n";
    }

    cout << "======================================================= \n\n";

//  ****************************************************************
//      Vector stuff here
//  ****************************************************************
    vector<char> charz;         // A vector of characters
    //vector<char>::iterator;         // Iterator for the char vector

    // Going to insert a word char by char
    charz.push_back('H');
    charz.push_back('E');
    charz.push_back('L');
    charz.push_back('L');
    charz.push_back('O');

    // Now let's find the size of the vector.
    cout << "Size of the character vector is: " << charz.size() << "\n\n";

    cout << "Outputting the vector of characters to the screen: \n";

    // Let's output the vector to the screen
    for(int i = 0; i < 5; i++)
    {
        cout << charz[i] << "\n";   // using the vector as an array.
    }

    // Let's reserve more space, and make room for 20 total characters.
    charz.reserve(20);

    // Let's check that size and capacity are different
    cout << "\nCapacity of the vector: " << charz.capacity() << "\n";   // should be 20
    cout << "Size of the vector: " << charz.size() << "\n";             // should be 5

    cout << "Outputting the vector of characters again: ";

    // Now to push another 40 characters, it will auto resize
    for(int i = 0; i < 40; i++)
    {
        charz.push_back('-');
    }

    // Let's output the vector to the screen
    for(int i = 0; i < charz.size(); i++)
    {
        cout << charz[i];   // using the vector as an array.
    }

    // Let's check that size and capacity are different
    cout << "\n\nCapacity of the vector: " << charz.capacity() << "\n";
    cout << "Size of the vector: " << charz.size() << "\n"; 

    cout << "======================================================= \n\n";          

//  ****************************************************************
//      List here
//  ****************************************************************
    list<Student> students;                 // List of students
    list<Student>::iterator ptr;            // iterator of the student list

    // 3 Student objects
    Student JT("JT", "Sophomore", "Read Chap 5");
    Student Jason("Jason", "Sophomore", "None");
    Student Huy("Huy", "Sophomore", "None");

    // Pushing those three students back into the list

    students.push_back(JT);
    students.push_back(Jason);
    students.push_back(Huy);

    cout << "Forward through the list: \n\n";

    // Print all of the student's names
    for(ptr = students.begin(); ptr != students.end(); ptr++)
    {
        Student temp;
        temp = *ptr;
        cout << "This student's name: " << temp.get_element(1) << "\n";
    }

    cout << "\nBackward through the list: \n\n";

    // Print them out in reverse order
    for(ptr = students.end(); ptr != students.begin(); )
    {
        --ptr;          // Had to put this here in order for the list to reverse correctly 
                        // and not output a bunch of gibberish
        Student temp;
        temp = *ptr;
        cout << "This student's name: " << temp.get_element(1) << "\n";
    }

	return 0;
}