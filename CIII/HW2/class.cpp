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
	void Change_oil();
	void Drive(float miles);

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

// Check the health of your truck.
void Truck::Health()
{
	cout<<"Checking the gas...\n";
	
	if(m_gas >= 15) {
		cout<<"I'm good on gas. ";
	}
	else if(m_gas >= 10) {
		cout<<"I could use some gas... ";
	}
	else if(m_gas >= 5) {
		cout<<"I'm low on gas! ";
	}
	else {
		cout<<"NEED GAS. You'll break me if you don't get gas! \n";
	}

	cout<<"\nChecking the oil health...\n";
	if(m_oil >= 7) {
		cout<<"Oil condition is good.\n";
	}
	else if(m_oil >= 5) {
		cout<<"Oil condition is OK.\n";
	}
	else if(m_oil >= 3) {
		cout<<"You should probably change my oil\n";
	}
	else {
		cout<<"CHANGE MY OIL!! I'll die if you don't! ;(\n";
	}
}

// Fills up the gas tank of the truck.
void Truck::Fill_up()
{
	cout<<"Filling up the truck...\n";
	
	// First see if we can even add gas or not.
	if(m_gas == 20) {
		cout<<"Sorry, the truck is already filled. \n";
		return;
	}

	// Now fill the truck up.
	m_gas = 20;
	cout<<"Filled up the truck - you're good to go for a drive! \n";
}

void Truck::Change_oil()
{
	cout<<"Changing the truck's oil...\n";

	// First see if the oil needs to be changed or not.
	if(m_oil == 10) {
		cout<<"Sorry, the truck's oil is already healthy. \n";
		return;
	}

	// Now change the oil.
	m_oil = 10;
	cout<<"Changed the oil - you're good to go for a drive! \n";
}

void Truck::Drive(float miles)
{
	cout<<"Going for a drive... \n";

	// Truck gets 20MPG. Max of 20 gallons. This means
	// you can drive 400 miles on one tank of gas.
	// Oil must be changed every 3000 miles. Or else the truck's
	// engine will explode.

	// Can't drive if there's no gas or the oil health is bad.
	if(m_gas == 0) {
		cout<<"Sorry, you need to fillup the truck first!\n";
		return;
	}
	if(m_oil == 0) {
		cout<<"Sorry, you need to change the oil first!\n";
		return;
	}

	// If they tried to drive further than 400 miles without filling up.
	// They didn't make it. :(
	if(miles >= 400) {
		cout<<"You tried to drive too far on one tank of gas. \n";
		cout<<"You would have been stuck in the middle of no where now.\n";
		return;
	}	// They can't drive negative miles!
	else if(miles <= 0) {
		cout<<"Try driving positive miles next time.\n";
	}

	// Let's first see how much gas this ride will take.
	float gas_usage = miles / 20;

	// Update the gas variable now.
	// First see if they would have ran out of gas.
	float gas_left = m_gas - gas_usage;
	if(gas_left <= 0) {
		cout<<"You would have ran out of gas on this trip.\n";
		return;
	}

	// Check the oil health.
	// The equation works by converting the gas_usage into oil_usage.
	float oil_usage = ((miles/3000) * 10); // Between 0 and 10
	float oil_health = m_oil - oil_usage;

	if(oil_health <= 0) {
		cout<<"Driving that far would have destroyed the truck's engine!\n";
		return;
	}

	m_gas = gas_left;
	m_oil = oil_health;
	m_miles_oil += miles;
	m_miles_gas += miles;

	// If we get here, then the truck didn't explode or run out of gas.
	cout<<"Gas usage is: "<<gas_usage<<" gallons\n";
	cout<<"Oil usage is: "<<oil_usage<<endl;
	cout<<"You've driven: "<<m_miles_gas<<" miles on this tank of gas.\n";
	cout<<"You've driven: "<<m_miles_oil<<" miles on this oil.\n";
}

int Truck::get_GasLevel()
{
	return m_gas;
}

int Truck::get_OilHealth()
{
	return m_oil;
}

int main()
{
	cout<<"Truck Simulator V1.1\n";
	cout<<"This class simulator takes inputs of: \n";
	cout<<"Gas level (int, max 20), Oil health (int, max 10) \n";
	cout<<"and miles (float, unlimited but you could run out of gas...) \n\n";

	cout<<"First truck: \n";
	cout<<"Enter the gas level and oil health: ";
	int gas, oil;
	cin>>gas>>oil;

	Truck truck(gas, oil);	// Call constructor with parameters
	cout<<endl;
	truck.Health();

	cout<<endl;
	truck.Fill_up();

	cout<<endl;
	truck.Change_oil();

	cout<<endl;
	truck.Drive(250);

	return 0;
}