// My own class
// This class simulates car maintenance
#include <iostream>

using namespace std;

class Truck
{
public:
	Truck();	// Default constructor

	// Constructor with parameters
	Truck(int gas, int oil);

	// Simulation functions
	void Health();
	void Fill_up();
	void Oil_change();
	void Drive();

	// Accessor functions
	int get_GasLevel();
	int get_OilHealth();

private:
	int m_gas;			// Gas tank is max 20 gallons.
	int m_oil;			// Oil health - 1 - 10 scale.
	float m_miles_gas;	// How many miles driven since last fill up.
	float m_miles_oil;	// Miles driven since last oil change.


};

// Default Constructor
Truck::Truck()
{
	cout<<"Default constructor without parameters.\n";
	m_gas = 20;
	m_oil = 10;
	m_miles_gas = 0;
	m_miles_oil = 0;
}

// Constructor with parameters
Truck::Truck(int gas, int oil)
{
	cout<<"Constructor with parameters is called.\n";
	m_gas = gas;
	m_oil = oil;

	// Set both of these because they are different.
	// IE you don't change your oil every fill up.
	// They also always start at 0.
	m_miles_gas = 0;
	m_miles_oil = 0;
}

int main()
{
	cout<<"Truck Simulator V1.0\n";
	cout<<"This class simulator takes inputs of: \n";
	cout<<"Gas level (int), Oil health (int) and miles (float) \n\n";

	cout<<"First truck: \n";
	cout<<"Enter the gas level and oil health: ";
	int gas, oil;
	cin>>gas>>oil;

	Truck truck(gas, oil);	// Call constructor with parameters

	return 0;
}