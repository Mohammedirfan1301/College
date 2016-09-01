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
    
    // 3 Student objects
    Student JT("JT", "Sophomore", "Read Chap 5");
    Student Jason("Jason", "Sophomore", "None");
    Student Huy("Huy", "Sophomore", "None");

    // 3 Winner Objects
    Winner Jamil("Jamil", "Boston, MA", "Gift card");
    Winner Dom("Dom", "Bolton, MA", "Nothing");
    Winner Zak("Zak", "Andover, MA", "Wii");

    Trio<Student> top_students(JT, Jason, Huy);
    Trio<Winner> winners(Jamil, Dom, Zak);

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
    
    // Changed Winner Jamil to Zak
    winners.set_element(1, Zak);

    // Zak becomes Dom
    winners.set_element(3, Dom);

    // Output the 6 objects.

    // XYZ object
    cout << "X coordinate: " << xyz_coordinates.get_element(1) << "\n";
    cout << "Y coordinate: " << xyz_coordinates.get_element(2) << "\n";
    cout << "Z coordinate: " << xyz_coordinates.get_element(3) << "\n";

    // Testing the error catcher
    cout << "\nThis will not work: ";
    cout << xyz_coordinates.get_element(5);

    // Initials object
    cout << "\n\n1st Initial: " << name_initials.get_element(1) << "\n";
    cout << "2nd Initial: " << name_initials.get_element(2) << "\n";
    cout << "3rd Initial: " << name_initials.get_element(3) << "\n\n";

    // Full_name object
    cout << "1st Full name: " << full_name.get_element(1) << "\n";
    cout << "2nd Full name: " << full_name.get_element(2) << "\n";
    cout << "3rd Full name: " << full_name.get_element(3) << "\n\n";

    // Car object
    cout << "Car  Make: " << car.get_element(1) << "\n";
    cout << "Car Model: " << car.get_element(2) << "\n";
    cout << "Car License Plate: " << car.get_element(3) << "\n\n";

    // This is like voodo magic, but apparently getting a class and then getting
    // a string of that class and outputting that works.
    cout << "Top student: " << top_students.get_element(1).get_element(1) << "\n";
    cout << "Runner up student: " << top_students.get_element(2).get_element(1) << "\n";
    cout << "Last student: " << top_students.get_element(3).get_element(1) << "\n\n";

    cout << "Top student's grade: " << top_students.get_element(1).get_element(2) << "\n";
    cout << "Runner up student's grade: " << top_students.get_element(2).get_element(2) << "\n";
    cout << "Last student's grade: " << top_students.get_element(3).get_element(2) << "\n\n";

    cout << "Top student's Homework : " << top_students.get_element(1).get_element(3) << "\n";
    cout << "Runner up student's Homework : " << top_students.get_element(2).get_element(3) << "\n";
    cout << "Last student's Homework : " << top_students.get_element(3).get_element(3) << "\n\n";
    
    // Testing else error catcher
    cout << "This will not work: " << top_students.get_element(1).get_element(5);

    // This part tests class winners
    cout << "\nWinner of the contest: " << winners.get_element(1).get_element(1) << "\n";
    cout << "Runner  up: " << winners.get_element(2).get_element(1) << "\n";
    cout << "Last place: " << winners.get_element(3).get_element(1) << "\n\n";

    // Hometowns
    cout << "Winner's hometown: " << winners.get_element(1).get_element(2) << "\n";
    cout << "Runner up's hometown: " << winners.get_element(2).get_element(2) << "\n";
    cout << "Last place's hometown: " << winners.get_element(3).get_element(2) << "\n\n";

    // Prizes
    cout << "First place prize: " << winners.get_element(1).get_element(3) << "\n";
    cout << "Second place prize: " << winners.get_element(2).get_element(3) << "\n";
    cout << "Last place prize: " << winners.get_element(3).get_element(3) << "\n\n";

    // Test the error catcher for winners as well.
    cout << "This will not work: " << winners.get_element(1).get_element(5);

    return 0;
}