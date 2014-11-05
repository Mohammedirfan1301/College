#include <iostream>


template <class T>
class Trio
{
public:

    Trio(T one, T two, T three);
    get_element(int position);
    set_element(int position, T value);


private:
    T first;
    T second;
    T third;

};



using namespace std;

int main()
{

/*
        DONE:
        Define a template class Trio<T>, which has member variables: first, second, and third of type T, member functions: constructor with three parameters, get_element(int position), set_element(int position, T value).

        DO:
        Create objects of this class: xyz_coordinates, name_initials, full_name, car (make, model, and license plate), top_students, and winners. For first four objects choose appropriate existing parameter types T, for last two objects define classes Student and Winner (with appropriate member variables and functions) to be used as parameter type of Trio<T>.

        Modify each object (using set_element) and output first, second, and third of each object (using get_element).
*/

    Trio xyz_coordinates;
    Trio name_initials;
    Trio car;                       // make, model, and license plate
    Trio top_students;
    Trio winners;



    return 0;
}

Trio::Trio(T one, T two, T three)
{


}

Trio::get_element(int position)
{


}

Trio::set_element(int position, T value)
{


}
