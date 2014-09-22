// truck_app.cpp
// Application file

#include <iostream>
#include "truck.h"

using namespace std;

int main()
{
	cout<<"Truck Simulator V1.2\n";
	cout<<"This class simulator takes inputs of: \n";
	cout<<"Gas level (float max 20), Oil health (float max 10) \n";
	cout<<"and miles (float, unlimited but you could run out of gas...) \n\n";

	// Make it so the numbers only output to 2 decimals.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

	// Default truck.
	{
		cout<<"Default truck: \n";
		Truck truck0;
		cout<<"The default truck has: "<<truck0.get_GasLevel()<<" gallons of gas left.\n";
		cout<<"It also has "<<truck0.get_OilHealth()<<"/10.00 oil health.\n";
	}

	// Truck 1
	cout<<"\nFirst truck: \n";
	cout<<"Enter the gas level and oil health: ";
	float gas, oil;
	cin>>gas>>oil;

	Truck truck1(gas, oil);	// Call constructor with parameters
	cout<<endl;
	
	// Functions that effect truck 1
	truck1.Health();
	cout<<endl;

	truck1.Fill_up();
	cout<<endl;

	truck1.Change_oil();
	cout<<endl;

	truck1.Drive(250);

	// Example of the copy constructor
	cout<<"\nCopying the first truck...\n";
	Truck truck2(truck1);

	cout<<"Truck2 has "<<truck2.get_GasLevel()<<" gallons of gas left.\n";
	cout<<"Truck2 also has "<<truck2.get_OilHealth()<< "/10.00 oil health.\n\n";

	return 0;
}