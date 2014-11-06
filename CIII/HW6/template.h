#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>

using namespace std;

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

template <class T>
Trio<T>::Trio(T one, T two, T three)
{
    first = one;
    second = two;
    third = three;
}

template <class T>
T Trio<T>::get_element(int position)
{
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
        cout << "Position must be either 1, 2, or 3! \n";
    }
}

template <class T>
void Trio<T>::set_element(int position, T value)
{
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
        cout << "Position must be either 1, 2, or 3! \n";
    }
}


#endif