// truck_app.cpp
// Application file

#include <iostream>
#include "truck.h"

using namespace std;

int main()
{
	int x = 0;
	float miles = 0, temp = 0;

	cout<<"Truck Simulator.\n";
	cout<<"This class simulator takes inputs of: \n";
	cout<<"Gas level (float max 20), Oil health (float max 10) and miles (float max 400) \n\n";

	// Make it so the numbers only output to 2 decimals.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // Make a default truck for the do/while.
    Truck truck;

    // Make a mechanic as well.
    Mechanic mechanic;

    // This do while simulates one car.
	do{
		cout<<"\nThere are the following options: \n";
		cout<<"1) Check the health of your truck. \n";
		cout<<"2) Fill up your truck with gas. \n";
		cout<<"3) Change the oil of your truck. \n";
		cout<<"4) Drive your truck. \n";
		cout<<"5) Get the fuel level of your truck.\n";
		cout<<"6) Get the oil health of your truck.\n";
		cout<<"7) Ask the Mechanic for his opinion of your truck.\n";
		cout<<"8) Use the MPG Calculator.\n";
		cout<<"9) Quit this simulator. \n";

		cout<<"Enter a selection: ";
		cin>>x;
		cout<<"\n";

		switch(x)
		{
			case 1: 
				truck.Health();
				break;

			case 2: 
				truck.Fill_up();
				break;

			case 3: 
				truck.Change_oil();
				break;

			case 4: 
				cout<<"How many miles will you drive today? -> ";
				cin>>miles;
				truck.Drive(miles);
				break;

			case 5: 
				temp = truck.get_GasLevel();
				cout<<"Your truck has "<<temp<<" gallons of gas left.\n";
				break;

			case 6: 
				temp = truck.get_OilHealth();
				cout<<"Your truck is at "<<temp<<"/10.00 oil health.\n";
				break;

			case 7:
				mechanic.Health_Report(truck);
				break;

			case 8:
				MPG_Calculator(truck);
				break;

			case 9: 
				cout<<"Good bye.\n";
				truck.~Truck();
				break;

			default:
				cout<<"The number you entered isn't valid.\n";
				break;
		}

	}while(x != 9);

	/*
		The following is left over from the first program.
		I commented it out since it isn't really being tested for this program.
	*/

	/*
	// Default truck.
	{
		cout<<"Default truck: \n";
		Truck truck0;
		cout<<"The default truck has: "<<truck0.get_GasLevel()<<" gallons of gas left.\n";
		cout<<"It also has "<<truck0.get_OilHealth()<<"/10.00 oil health.\n";
		truck0.~Truck();
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

	truck1.~Truck();
	truck2.~Truck();
	*/

	return 0;
}