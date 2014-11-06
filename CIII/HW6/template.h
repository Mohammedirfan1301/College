#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>

using namespace std;

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
        cout << "Position must be either 1, 2, or 3! \n";
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
        cout << "Position must be either 1, 2, or 3! \n";
    }
}

// Class Student
class Student
{
    public:
        Student(int one);
        int get_element(int position);
        void set_element(int position, int set);

    private:
        string name;
        string 
        int GPA;
};

// Class Winner
class Winner
{
    public:


    private:
        string name;

};


#endif