#include <iostream>
#include <string>
#include <map>
using namespace std;

// The parent class, all the car brands derive from this class.
class Dealership
{
public:
	Dealership();		// Default Constructor
	int getTotalInventory();
	void printInventory();
	void add_car(string model, float price);
	void buy_car(string model);
	void remove_car(string model);

protected:
	int total_inventory;
	int total_cars_sold;
	map<string, float> inventory_list;
};


// Ford class, holds all the ford cars/trucks.
class Ford: public Dealership
{
public:
	// For each specific brand, I override the default constructor and the buy car function.
	// This is because each car brand is doing their own sale this month.
	Ford();
	void buy_car(string model);

private:
	float sale;			// Ford's are 20% this month, while supplies last!

};


// GM class, holds all the GM cars/trucks.
class GM: public Dealership
{
public:
	// For each specific brand, I override the default constructor and the buy car function.
	// This is because each car brand is doing their own sale this month.
	GM();
	void buy_car(string model);

private:
	float sale;				// All GM's are 15% off this month! Hurry quick!
};


// chrysler class, holds all the chrysler cars/truck.
class Chrysler: public Dealership
{
public:	
	// For each specific brand, I override the default constructor and the buy car function.
	// This is because each car brand is doing their own sale this month.
	Chrysler();
	void buy_car(string model);
		
private:
	float sale;					// chrysler's are only 5% off, better wait til next month.
};


int main()
{
	// Dealership testing here
	Dealership Lowell_Generic_Dealer;
	Lowell_Generic_Dealer.printInventory();

	Lowell_Generic_Dealer.add_car("Generic Truck", 30999);
	Lowell_Generic_Dealer.add_car("Generic Sedan", 20995);
	Lowell_Generic_Dealer.add_car("Super Awesome Generic 300", 23998);
	Lowell_Generic_Dealer.printInventory();

	Lowell_Generic_Dealer.buy_car("Chevy Cruze");		// This will fail.
	Lowell_Generic_Dealer.buy_car("Generic Truck");		// This won't.

	Lowell_Generic_Dealer.printInventory();

	// Testing the Ford class (dealership) here
	Ford Lowell_Ford;
	Lowell_Ford.printInventory();

	Lowell_Ford.add_car("F150 xLT", 30530);
	Lowell_Ford.add_car("Fiesta", 13965);
	Lowell_Ford.add_car("Focus", 16810);
	Lowell_Ford.add_car("Fusion", 22010);

	Lowell_Ford.buy_car("Fiesta");		// This one won't fail.
	Lowell_Ford.buy_car("Fiesta"); 		// This one will fail, since it no longer exists.

	Lowell_Ford.printInventory();

	// Now to test this GM class over here
	GM Lowell_GM;
	Lowell_GM.printInventory();

	Lowell_GM.add_car("Chevy Spark", 12170);
	Lowell_GM.add_car("Buick Lacrosse", 33635);
	Lowell_GM.add_car("GMC Sierra 1500", 26605);
	Lowell_GM.add_car("Cadillac ATS", 33065);
	Lowell_GM.add_car("Chevy Traverse", 30995);

	Lowell_GM.buy_car("Fiesta");		// This will fail, that's a Ford car not a GM!
	Lowell_GM.buy_car("Chevy Spark");	// This won't fail.

	Lowell_GM.printInventory();

	// Finally, just the chrysler class to test
	Chrysler Lowell_Chrysler;
	Lowell_Chrysler.printInventory();

	// Turns out Chrysler only makes 3 cars! So I included a Jeep and a Dodge
	// Since Chrysler owns them anyway.
	Lowell_Chrysler.add_car("Chrysler 200", 21700);
	Lowell_Chrysler.add_car("Chrysler 300", 31395);
	Lowell_Chrysler.add_car("Chrysler Town & Country", 30765);
	Lowell_Chrysler.add_car("Jeep Grand Cherokee", 29895);
	Lowell_Chrysler.add_car("Dodge RAM 1500", 25060);

	Lowell_Chrysler.buy_car("Chrysler 300");					// This person is buying a cool car.
	Lowell_Chrysler.buy_car("Chrysler Town & Country");			// This person is buying a not so cool car.
	Lowell_Chrysler.buy_car("Chrysler Town & Country");			// This will fail, we already sold that van!

	Lowell_Chrysler.printInventory();

	return 0;
}

//******************************************************************************
// Dealership functions
//******************************************************************************
// Default constructor
Dealership::Dealership()
{
	total_inventory = 0;
	total_cars_sold = 0;
}


// Returns the total amount of cars in the dealership.
int Dealership::getTotalInventory()
{
	return total_inventory;
}


// Prints out the current selection of cars
void Dealership::printInventory()
{
	cout << "Current number of cars: " << total_inventory << "\n";
	cout << "Total cars sold this month: " << total_cars_sold << "\n";

	map<string, float>::iterator car_ptr;

	// If there aren't any cars, then let them know the list is empty.
	if(inventory_list.begin() == inventory_list.end())
	{
		cout << "Sorry, lot's empty right now. Check back tomorrow mate.\n";
	}

	// Otherwise print out all the car models and their prices
	for(car_ptr = inventory_list.begin(); car_ptr != inventory_list.end(); car_ptr++)
	{
		cout << "Car Model: " << car_ptr -> first << endl;
		cout << "Car Price: $" << car_ptr -> second << endl;
	}

	cout << "\n";
}


void Dealership::add_car(string model, float price)
{
	// Simple, add the car / price combo to the map.
	inventory_list[model] = price;
	total_inventory++;
}


void Dealership::buy_car(string model)
{
	bool found = false;
	map<string, float>::iterator car_ptr;

	for(car_ptr = inventory_list.begin(); car_ptr != inventory_list.end(); car_ptr++)
	{
		if(car_ptr -> first == model)
		{
			// Let the user know we found their car.
			cout << "Found that car right here! Let me bring it up to the front for you.\n";
			cout << "Don't forget to buy the super awesome protection warranty too!\n";

			// Make sure to remove the car from the map.
			car_ptr = inventory_list.find(model);
			inventory_list.erase(car_ptr);
			total_cars_sold++;
			total_inventory--;

			found = true;
			break;
		}
	}

	// If we get here, we didn't find the car.
	if(found == false)
	{
		// So we should warn the user, and ask them to try again.
		cout << "Sorry mate, I couldn't find that model in my inventory.\n";
		cout << "Try searching for a different car model.\n";
	}

	cout << endl;
}


//******************************************************************************
// Ford functions
//******************************************************************************
Ford::Ford()
{
	total_inventory = 0;
	total_cars_sold = 0;
	sale = .8;
}


// Overriding the buy car function!
void Ford::buy_car(string model)
{
	bool found = false;
	map<string, float>::iterator car_ptr;

	for(car_ptr = inventory_list.begin(); car_ptr != inventory_list.end(); car_ptr++)
	{
		if(car_ptr -> first == model)
		{
			// Since the price is 20% off, let the user know their savings.
			float price = car_ptr -> second;
			price = price * sale;

			float total_savings = car_ptr -> second - price;

			// Let the user know we found their car.
			cout << "Found that car right here! Let me bring it up to the front for you.\n";
			cout << "Don't forget to buy the super awesome protection warranty too!\n";
			cout << "Oh, by the way, you saved 20% this month! Thanks for buying a Ford!\n";
			cout << "Price you would have paid: $" << car_ptr -> second << endl;
			cout << "Price you paid thanks to the Ford Dream Big Sales Event: $" << price << endl;
			cout << "Total savings: $" << total_savings << endl;

			// Make sure to remove the car from the map.
			car_ptr = inventory_list.find(model);
			inventory_list.erase(car_ptr);
			total_cars_sold++;
			total_inventory--;

			found = true;
			break;
		}
	}

	// If we get here, we didn't find the car.
	if(found == false)
	{
		// So we should warn the user, and ask them to try again.
		cout << "Sorry mate, I couldn't find that model in my inventory.\n";
		cout << "Try searching for a different car model.\n";
	}

	cout << endl;
}


//******************************************************************************
// GM functions
//******************************************************************************
GM::GM()
{
	total_inventory = 0;
	total_cars_sold = 0;
	sale = .85;
}


// Overriding the buy car function!
void GM::buy_car(string model)
{
	bool found = false;
	map<string, float>::iterator car_ptr;

	for(car_ptr = inventory_list.begin(); car_ptr != inventory_list.end(); car_ptr++)
	{
		if(car_ptr -> first == model)
		{
			// Since the price is 20% off, let the user know their savings.
			float price = car_ptr -> second;
			price = price * sale;

			float total_savings = car_ptr -> second - price;

			// Let the user know we found their car.
			cout << "Found that car right here! Let me bring it up to the front for you.\n";
			cout << "Don't forget to buy the super awesome protection warranty too!\n";
			cout << "Oh, by the way, you saved 15% this month! Thanks for buying a GM!\n";
			cout << "Price you would have paid: $" << car_ptr -> second << endl;
			cout << "Price you paid thanks to the GM Year End Event: $" << price << endl;
			cout << "Total savings: $" << total_savings << endl;

			// Make sure to remove the car from the map.
			car_ptr = inventory_list.find(model);
			inventory_list.erase(car_ptr);
			total_cars_sold++;
			total_inventory--;

			found = true;
			break;
		}
	}

	// If we get here, we didn't find the car.
	if(found == false)
	{
		// So we should warn the user, and ask them to try again.
		cout << "Sorry mate, I couldn't find that model in my inventory.\n";
		cout << "Try searching for a different car model.\n";
	}

	cout << endl;
}

//******************************************************************************
// Chrysler functions
//******************************************************************************
Chrysler::Chrysler()
{
	total_inventory = 0;
	total_cars_sold = 0;
	sale = .95;
}


// Overriding the buy car function!
void Chrysler::buy_car(string model)
{
	bool found = false;
	map<string, float>::iterator car_ptr;

	for(car_ptr = inventory_list.begin(); car_ptr != inventory_list.end(); car_ptr++)
	{
		if(car_ptr -> first == model)
		{
			// Since the price is 20% off, let the user know their savings.
			float price = car_ptr -> second;
			price = price * sale;

			float total_savings = car_ptr -> second - price;

			// Let the user know we found their car.
			cout << "Found that car right here! Let me bring it up to the front for you.\n";
			cout << "Don't forget to buy the super awesome protection warranty too!\n";
			cout << "Oh, by the way, you saved 5% this month! Thanks for buying a chrysler!\n";
			cout << "Price you would have paid: $" << car_ptr -> second << endl;
			cout << "Price you paid thanks to the chrysler Big Finish Event: $" << price << endl;
			cout << "Total savings: $" << total_savings << endl;

			// Make sure to remove the car from the map.
			car_ptr = inventory_list.find(model);
			inventory_list.erase(car_ptr);
			total_cars_sold++;
			total_inventory--;

			found = true;
			break;
		}
	}

	// If we get here, we didn't find the car.
	if(found == false)
	{
		// So we should warn the user, and ask them to try again.
		cout << "Sorry mate, I couldn't find that model in my inventory.\n";
		cout << "Try searching for a different car model.\n";
	}

	cout << endl;
}