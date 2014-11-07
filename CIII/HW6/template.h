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
        Student(string set_name, string set_grade, string set_HW);
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


    private:
        int person;
        int age;
        int DOB;
};


// Template class, uses STL
template <class T>
class Trio
{
    public:
        //Trio(T student);
        //Trio(const Winner& copy);
        Trio(T one, T two, T three);
        T get_element(int position);
        void set_element(int position, T value);

    private:
        T first;
        T second;
        T third;
};

// Copies an object of class Student into the Trio class.
// template <class T>
// Trio<T>::Trio(T student)
// {
//     //first = copy.name;
//     //second = copy.grade;
//     //third = copy.homework;
// }


// Default constructor which takes 3 parameters.
template <class T>
Trio<T>::Trio(T one, T two, T three)
{
    first = one;
    second = two;
    third = three;
}


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
        cout << "\nError: Position must be either 1, 2, or 3! \n";
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
        cout << "\nError: Position must be either 1, 2, or 3! \n";    }
}


Student::Student()
{
    // tell the compiler to stfu.
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
    }                                       // variable is at that position in the class.
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

#endif