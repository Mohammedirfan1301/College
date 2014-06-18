/****************************************************************
	Example code for Groceries Program
	
	This program was written to help you through if you are having a
	tough time; NOT TO GIVE YOU A PERFECT ANSWER KEY.  Please don't
	just copy.
	
	This program reads data from an inventory file consisting of: 
	barcode\tdescription\tprice\t
	barcode\tdescription\tprice\t
	1\t

	It uses this data to compare a list of barcodes from a transaction file.  
	The transaction file is a list of barcodes sepreating individual customers
	using a 1 and ending in a 0.
	barcode
	barcode
	1
	barcode
	1
	0
	
	The program gives each customer a total, and prints the whole reciept to a 
	reciept output file. 
*******************************************************************/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

int GetInventory(char[100][10], char[100][200], float[100]);		// gets data from inventory
int FindIndex(char[100][10], char[200]);					// Returns correct index for the item
float Process(int, char[100][200], float[100]);				// Writes to the file and returns price

main()
{
	// The following arrays will be used to keep track of the inventory.
	//   They will be kept parrallel so that the index for each value aligns
	//	 With the other two arrays.
	char barcodes[100][10];			// Store the inventory's barcodes
	char descriptions[100][200];	// Store the inventory's Item Descriptions
	float prices[100];				// Sotre the Prices of each item
	
	char buffer[200]; 				// Buffer for reading in from transaction file
	
	float TotalPrice = 0;			// Keeps track of a customer's total
    float OnePrice   = 0;           // temporary value for an item's price
    
    int pads = 52;                  // for padding the output of the total line
    
	ifstream Trans;					// Input file for transactions
	ofstream reciept;				// the output file
	
	cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
	
	reciept.open("H:\\Reciept.txt");
	if (!reciept.good())
	{
		cerr << "Could not open the output file!";
		cin.sync();
		cin.ignore();
		exit(0);
	}
	
	cout << "Welcome to the Grocery Program!  Here we go:\n\n";
	reciept << "\tFirst Customer:\n";
	reciept.close();
	
	if (!GetInventory(barcodes,descriptions,prices))
	{	//  The inventory file could not be opened!  
		cerr << "There was a problem reading the inventory file!\n";
		cin.sync();
		cin.ignore();
		exit(0);
	}
	
	Trans.open("T:\\ProgrammingStudents\\DataStructuresResources\\Groceries\\Trans1.txt");
	
	if (!Trans.good())
	{	// The transaction file could not be opened!
		cerr << "There was a problem reading the transaction file!\n";
		cin.sync();
		cin.ignore();
		exit(0);
	}
	
	do			// looping through the transaction file to compare to the inventory data.
	{
		Trans.getline(buffer, 50);		// reads one line of the trans file
		
		if ((buffer[0] == '1')&& (strlen(buffer)<5))		
		{	// end of transaction
			reciept.open("H:\\Reciept.txt", std::ios::app);
			if (!reciept.good())
			{
				cerr << "Could not open the output file!";
				cin.sync();
				cin.ignore();
				exit(0);
			}
			reciept << '\n';
			cout << '\n';
	
            for (int j=10;j<1000000000;j*=10) // Setting up so that the decimals line up
            {
                if (TotalPrice/j >= 1)
                pads--; 
            }
			for (int i = pads; i > 0;i--)
			{
				reciept << ' ';
				cout << ' ';
            }	
            
            reciept.setf(ios::fixed, ios::floatfield);	// forcing 2 decimal places
            reciept.precision(2);						
			reciept << "Total:  $" << TotalPrice << "\n\n***********\n\tNext Customer:\n\n";
			cout << "Total:  $" << TotalPrice << endl;
			cin.sync();
			cin.ignore();
			cout << "\n\n***********\n\tNext Customer:\n\n";
			reciept.close();
			TotalPrice = 0;		// New Customer, reset price
			pads = 52;
		}	
		
        if ((buffer[0] == '0')&& (strlen(buffer)<5))
		{	// end of input
            reciept.open("H:\\Reciept.txt", std::ios::app);
			if (!reciept.good())
			{	// didn't open
				cerr << "Could not open the output file!";
				cin.sync();
				cin.ignore();
				exit(0);
			}
            reciept << "\tThere IS no Next Customer!\n";
            cout << "\tThere IS no Next Customer!\n\n\n";
			reciept.close();                     
			continue;			// Finished!
        }	
		// finds and processes the barcode
		OnePrice = Process(FindIndex (barcodes, buffer), descriptions, prices);  
		
		if (OnePrice == -2)
		{	// could not open the output file!
			cerr << "Error Writing to reciept file!";
			cin.sync();
			cin.ignore();
			exit(0);
		}
	
		if (OnePrice != -1)
		{	// as long as the barcode was found...
			TotalPrice += OnePrice;		// Add to the total.
		}
		else if (strlen(buffer)>4)
		{
            cout << " =>The Barcode you scanned:  "<< buffer;
            cout << "\n =>does not match any in our inventory!!\n";
        }	
	} while (Trans.good()); 		// loop until the file ends
	
	Trans.close();
	cin.sync();
	cin.ignore();
}

/*******************************************************************************************
	This function recieves input from the inventory file, and stores it into arrays.
	
	Parameters:  Takes the three arrays to be filled with data
	Return values: returns 1 for success
						   0 for failure
********************************************************************************************/
int GetInventory(char B[100][10], char D[100][200], float P[100])
{
	ifstream inven;
	int i = 0;			// Index for looping
	char buffer[50];	// Buffer to hold the Price before converting.
	
	inven.open("T:\\ProgrammingStudents\\DataStructuresResources\\Groceries\\Inventory.txt");
	if (!inven.good())
		return 0;		// Did not open!

	do
	{
		inven.getline(B[i],10,'\t');	// get barcode
		if (B[i][1]!='\0')	
		{	// It is not the end of the file.
			inven.getline(D[i],50,'\t');	// get description
			inven.getline(buffer,50);		//get price
			P[i++] = atof(buffer);			//convert price
		}
	} while (inven.good());

	inven.close();
	
	P[i] = -1; // Makes the end of the pricelist identifiable
	
	return 1;	// Read in OK
}

/********************************************************************************************
	This function finds the right index value for the item selected
	
	Parameters: the saved barcodes
				The barcode we are looking for
				
	Output: the correct index
			or -1 for code not found.
********************************************************************************************/	
int FindIndex(char B[100][10], char Code[200])	
{
	int i = 0;
	
	do
	{
		if (strlen(B[i]) < 2)
			return -1;		// barcode not found!
		if (!strcmp(B[i++], Code))
			return (i-1);	// barcode Found!
	} while (i<101); // should never get there...
	return -1; // something went wrong!
}

/*******************************************************************************************
	this function processes an order by writing to the reciept file, and returning the price.
	
	Parameters: index value
				the array of descriptions
				the array of prices

	Outputs:	The reciept file is written to
				the function returns the price of the item.
				returns -1 if the item is not found
				returns -2 if the reciept file cannot open
*******************************************************************************************/
float Process(int x, char D[100][200], float P[100])	
{
	int i = 0;
	int pads = 60;
	ofstream reciept;
		// opens the file to append.
	reciept.open("H:\\Reciept.txt", std::ios::app);

	if (!reciept.good())
		x = -2; // file did not open!
		
	if (x<0)
		return x; // return an error

    reciept.setf(ios::fixed, ios::floatfield);
    reciept.precision(2);
	
	reciept << D[x];
	cout << D[x];
	
    for (int j=10;j<1000000000;j*=10)
    {	//  padding so that decimals line up
        if (P[x]/j >= 1)
           pads--; 
    }
        
    for (i=(pads-strlen(D[x]));i>0;i--)
	{		// pad the output so it lines up
		reciept << ' ';
		cout << ' ';
	}
	reciept << '$' << P[x] << endl;
	cout << '$' << P[x] << endl;	// force 2 decimal places
	reciept.close();
	return P[x];
}
