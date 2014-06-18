#include <iostream.h>

int main()
{
	float x,y,z;
	
	cout<<"This program will calculate the area of \n a rectangular room in square feet. \n"; //this will print to the screen.
	cout<<endl;                                 // Ends the line to add a space to make the program look nice.
	cout<<"Enter the length of the room. \t";  // Prompt to enter the length
	cin>>x;                               // This retrieves the length and stores it.
	cout.precision(5);
	cout<<"Enter the width of the room. \t";   // Prompt to enter the width
	cin>>y;                                // This retrieves the width and stores it.
	cout.precision(5);
	z=x*y;                         // This calculates the area by multiplying width (y) times height (x).
	cout<<endl;                                // Ends line to make program look nice.
	cout<<" The area of the room is: " <<z << " square feet. ";    /*This prints the area to the screen. */

    return 0; 
}

