// truck.cpp
// Implementation file

#include <iostream>
#include "truck.h"

using namespace std;

size_t Truck::count = 0;

// Default Constructor
Truck::Truck(): m_gas(20), m_oil(10), m_miles_gas(0), m_miles_oil(0)
{
	cout<<"Default constructor without parameters.\n";
	m_gas = 20;
	m_oil = 10;
	m_miles_gas = 0;
	m_miles_oil = 0;
	count++;
	cout<<"\nThere are "<<count<<" Trucks\n\n";
}

// Constructor with parameters
Truck::Truck(float gas, float oil): m_gas(gas), m_oil(oil), m_miles_gas(0), m_miles_oil(0)
{
	cout<<"Constructor with parameters is called.\n";
	m_gas = gas;
	m_oil = oil;

	// Set both of these because they are different.
	// IE you don't change your oil every fill up.
	// They also always start at 0.
	m_miles_gas = 0;
	m_miles_oil = 0;

	count++;
	cout<<"\nThere are "<<count<<" Trucks\n";
}

// Copy constructor
Truck::Truck(const Truck& aTruck)
{
	m_gas = aTruck.m_gas;
	m_oil = aTruck.m_oil;
	m_miles_gas = aTruck.m_miles_gas;
	m_miles_oil = aTruck.m_miles_oil;

	cout<<"\nThe truck has been copied!\n";

	count++;
	cout<<"\nThere are "<<count<<" Trucks\n\n";
}

// Destructor
Truck::~Truck()
{
	if(count > 0)
	{
		cout<<"\nThe truck has been destroyed!\n";
		count--;
		cout<<"There are: "<<count<<" trucks\n";
	}
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

	cout<<"You've driven: "<<m_miles_gas<<" miles on this tank of gas.\n";
	cout<<"You've driven: "<<m_miles_oil<<" miles on this oil.\n";
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
	m_miles_gas = 0;
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
	m_miles_oil = 0;
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
	else if(m_oil == 0) {
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
		cout<<"You should probably put some gas in the truck.\n";
		return;
	}

	// Check the oil health.
	// The equation works by converting the gas_usage into oil_usage.
	float oil_usage = ((miles/3000) * 10); // Between 0 and 10
	float oil_health = m_oil - oil_usage;

	if(oil_health <= 0) {
		cout<<"Driving that far would have destroyed the truck's engine!\n";
		cout<<"Change the oil NOW!\n";
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

float Truck::get_GasLevel()
{
	return m_gas;
}

float Truck::get_OilHealth()
{
	return m_oil;
}


/* 	Function for the Mechanic class.
	The Mechanic class is a friend of the Truck class.
	So it has access to all of the private members of
	the Truck. */
void Mechanic::Health_Report()
{
	cout<<"Let me take a look at the truck...\n";

	// Check gas and report the fuel health.
	if(m_gas >= 15)
		cout<<"Truck's good on gas.\n";
	if(m_gas >= 10)
		cout<<"Truck's halfway on gas.\n";
	if(m_gas >= 5)
	{
		cout<<"Truck's pretty low on gas.\n";
		cout<<"I don't recommend running it this low or you might break your fuel pump.\n"
	}
	if(m_gas >= 0)
	{
		cout<<"I'm surpised you drove here. You shouldn't ever run your truck this low on fuel!\n";
		cout<<"I recommend filling it up right away.\n";
		cout<<"Also - running the truck this low on fuel can burn your fuel pump!\n"
	}

	// Check oil level and report the oil health.
	if(m_oil >= 15)
		cout<<"Oil health is great!\n";
	if(m_oil >= 10)
		cout<<"Oil health is OK, keep an eye on it though.\n";
	if(m_oil >= 5)
	{
		cout<<"The truck's oil health is low. I'd recommend changing the oil\n";
		cout<<"pretty soon, within the next 500 - 1,000 miles!\n"
	}
	if(m_oil >= 0)
	{
		cout<<"Your truck's oil is really low! I suggest changing the oil now.\n";
		cout<<"If you wait any longer, you'll risk engine damage.\n"
	}
}


/*
	Friend function to the truck class.
	It calculates out how many more miles you 
	can drive on the current tank of gas.
	It also prints out how many trucks are currently alive.
*/
void MPG_Calculator()
{
	float fuel_left = 400 - m_miles_gas;
	float oil_left = 3000 - m_miles_oil;

	float gallons = fuel_left / 20;


	cout<<"Look's like you've got "<<fuel_left<<" miles left to drive on this tank of gas.\n";
	cout<<"This translates into "<<gallons<<" gallons of gas left.\n";
	cout<<"You also should get an oil change in "<<m_miles_oil<<" miles.\n";
}