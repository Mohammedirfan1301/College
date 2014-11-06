#include <iostream>
#include <string>
#include "template.h"

using namespace std;

int main()
{
    // These use type T's.
    Trio<int> xyz_coordinates(5, -5, 3);
    Trio<string> name_initials("JD", "JT", "HH");
    Trio<string> full_name("Jason Downing", "JT Shepple", "Huy Huyuh");
    Trio<string> car("Ford", "Ranger", "2-fa$t");     
    
    // These use class objects
    Trio<string> top_students("JT", "JT", "JT");
    Trio<string> winners("Huy", "Jamil", "Jason");

    cout << "Just recreated 6 objects. Testing them now: \n";

    // Modify the 6 objects.
    xyz_coordinates.set_element(1, 6);
    name_initials.set_element(2, "ZW");
    full_name.set_element(3, "Udit Bdfjkfdsfdc");
    car.set_element(3, "2-sl0w");

    top_students.set_element(1, "JD");
    winners.set_element(2, "John");

    // Output the 6 objects.
    cout << "Y coordinate: " << xyz_coordinates.get_element(2) << "\n";
    cout << name_initials.get_element(1) << "\n";
    cout <<  << "\n";
    cout <<  << "\n";
    cout <<  << "\n";
    cout <<  << "\n";

    return 0;
}