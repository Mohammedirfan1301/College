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
    Student JT("JT", "Sophomore", "Read Chap 5");
    Student Jason("Jason", "Sophomore", "None");
    Student Huy("Huy", "Sophomore", "None");

    Trio<Student> top_students(JT, Jason, Huy);
    //Trio<Student> winners("Huy", "Jamil", "Jason");

    cout << "Just recreated 6 objects. Testing them now: \n";

    // Modify the 6 objects.
    xyz_coordinates.set_element(1, 6);
    name_initials.set_element(2, "ZW");
    full_name.set_element(3, "Udit Bdfjkfdsfdc");
    car.set_element(3, "2-sl0w");

    // Changed Student Jason to Student JT.
    top_students.set_element(2, JT);

    // Changed Student Huy to Student Jason.
    top_students.set_element(3, Jason);
    //winners.set_element(2, "John");

    // Output the 6 objects.
    cout << "Y coordinate: " << xyz_coordinates.get_element(2) << "\n";
    cout << "1st Initial: " << name_initials.get_element(1) << "\n";
    cout << "3rd Full name: " << full_name.get_element(3) << "\n";
    cout << "Car Model: " << car.get_element(2) << "\n\n";

    // This is like hacking, or voodo magic, but apparently getting a class and then getting
    // a string of that class and outputting it works.
    cout << "Top student: " << top_students.get_element(1).get_element(1) << "\n";
    cout << "His grade: " << top_students.get_element(1).get_element(2) << "\n";
    cout << "Homework : " << top_students.get_element(1).get_element(3) << "\n";
    cout << "This will not work : " << top_students.get_element(1).get_element(5) << "\n";

    cout << "Runner up: " << top_students.get_element(2).get_element(1) << "\n";
    cout << "Last student: " << top_students.get_element(3).get_element(1) << "\n";

    //cout << "Winner of the contest: " << winners.get_element(1) << "\n";

    return 0;
}