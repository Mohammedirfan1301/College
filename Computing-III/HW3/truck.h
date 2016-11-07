// truck.h
// Header file

#ifndef TRUCK_H
#define TRUCK_H

// Main class, the Truck simulator.
class Truck
{
	public:

		// Constructors and destructor
		Truck();						// Default constructor
		Truck(float gas, float oil); 	// Constructor with parameters
		Truck(const Truck& aTruck); 	// Copy constructor
		~Truck();						// Destructor

		// Simulation functions (mutators)
		void Health();
		void Fill_up();
		void Change_oil();
		void Drive(float miles);

		// Accessor functions
		float get_GasLevel();
		float get_OilHealth();

	private:
		float m_gas;		// Gas tank is max 20 gallons.
		float m_oil;		// Oil health - 1 - 10 scale.
		float m_miles_gas;	// How many miles driven since last fill up.
		float m_miles_oil;	// Miles driven since last oil change.
		static size_t count;

		// Friend class and function
		friend class Mechanic;
		friend void MPG_Calculator(const Truck&);
};

// Friend class to Truck. The Mechanic just takes a look at the truck
// and prints out his opinion on its health.
class Mechanic
{
	public:
		void Health_Report(const Truck&);
};

#endif