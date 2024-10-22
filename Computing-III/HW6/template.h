#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>

using namespace std;


// Class Student
class Student
{
    public:
        Student();
        void Student(string set_name, string set_grade, string set_HW);
        string get_element(int position);
        void set_element(int position, string value);

    private:
        string name;
        string grade;
        string homework;
};


// Class Winner
class Winner
{
    public:
        Winner();
        Winner(string set_name, string set_home_town, string set_prize);
        string get_element(int position);
        void set_element(int position, string value);

    private:
        string name;
        string home_town;
        string prize;
};


// Template class, uses STL
template <class T>
class Trio
{
    public:
        Trio(T one, T two, T three);
        T get_element(int position);
        void set_element(int position, T value);

    private:
        T first;
        T second;
        T third;
};


// Default constructor which takes 3 parameters.
template <class T>
Trio<T>::Trio(T one, T two, T three)
{
    first = one;
    second = two;
    third = three;
}

// ***************************************************************
//      Trio class functions
// ***************************************************************

// Get's an element at position 1 or 2 or 3
template <class T>
T Trio<T>::get_element(int position)
{
    // Choose position
    if(position == 1)
    {
        return first;
    }
    else if(position == 2)
    {
        return second;
    }
    else if(position == 3)
    {
        return third;
    }
    else
    {
        // Error, need to pick 1, 2 or 3.
        T fourth;
        cout << "\nError: Position must be either 1, 2, or 3! Returning nothing: ";
        return fourth;
    }
}


// Sets an element at a given position, and puts the value there.
template <class T>
void Trio<T>::set_element(int position, T value)
{
    // Choose position
    if(position == 1)
    {
        first = value;
    }
    else if(position == 2)
    {
        second = value;
    }
    else if(position == 3)
    {
        third = value;
    }
    else
    {
        // Error, need to pick 1, 2 or 3.
        cout << "\nError: Position must be either 1, 2, or 3! \n";    
    }
}


// **************************************************************************
//      Class Student Functions
// **************************************************************************

Student::Student()
{
    // tell the compiler to shut up.
}


// Default constructor for Class Student. Similar to class Trio.
Student::Student(string set_name, string set_grade, string set_HW)
{
    name = set_name;
    grade = set_grade;
    homework = set_HW;
}


string Student::get_element(int position)
{
    // Choose position
    if(position == 1)
    {
        return name;                // Once we pick a position, just return whatever
    }                               // variable is at that position in the class.
    else if(position == 2)
    {
        return grade;
    }
    else if(position == 3)
    {
        return homework;
    }
    else
    {
        // Error, need to pick 1, 2 or 3.
        return "\nError: Position must be either 1, 2, or 3! \n";
    }
}


void Student::set_element(int position, string value)
{
    // Choose position
    if(position == 1)
    {
        name = value;
    }
    else if(position == 2)
    {
        grade = value;
    }
    else if(position == 3)
    {
        homework = value;
    }
    else
    {
        // Error, need to pick 1, 2 or 3.
        cout << "\nError: Position must be either 1, 2, or 3! \n";
    }
}


// **********************************************************************
//      Class Winner Functions
// **********************************************************************

Winner::Winner()
{
    // tell the compiler to shut up.
}


// Default constructor for Class Student. Similar to class Trio.
Winner::Winner(string set_name, string set_home_town, string set_prize)
{
    name = set_name;
    home_town = set_home_town;
    prize = set_prize;
}


string Winner::get_element(int position)
{
    // Choose position
    if(position == 1)
    {
        return name;            // Once we pick a position, just return whatever
    }                           // variable is at that position in the class.
    else if(position == 2)
    {
        return home_town;
    }
    else if(position == 3)
    {
        return prize;
    }
    else
    {
        // Error, need to pick 1, 2 or 3.
        return "Error: Position must be either 1, 2, or 3! \n";
    }
}


void Winner::set_element(int position, string value)
{
    // Choose position
    if(position == 1)
    {
        name = value;
    }
    else if(position == 2)
    {
        home_town = value;
    }
    else if(position == 3)
    {
        prize = value;
    }
    else
    {
        // Error, need to pick 1, 2 or 3.
        cout << "\nError: Position must be either 1, 2, or 3! \n";
    }
}

#endif