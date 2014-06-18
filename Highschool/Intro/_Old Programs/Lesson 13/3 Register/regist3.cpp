#include <iostream.h>
#include <iomanip.h>
#include <conio.h>

int quantity[12] = {0};
char descript[12][20] = { {'\0'}, {'\0'} };
float price[12] = {0};
float total = 0, subtotal = 0, tax = 0, grandtotal = 0;

void print(int [], char [12][20], float [], float);

main()
{
	 int x = 0;
	                               //|
			 //123456789112345678921234567893123456789412345678951234567896
	 cout<<"************************************************************** \n";
	 cout<<"*                 THE SUPERMARKET                            * \n";
	 cout<<"*                                                            * \n";
	 cout<<"*      THE LOWEST PRICES - ALL THE TIME                      * \n";
	 cout<<"*                                                            * \n";
	 cout<<"* Qty  Description                          Price    Total   * \n";
	 cout<<"*                                                            * \n";
	 cout<<"*";

	 print(quantity, descript, price, float);

			  cout<<"__________________________________  $-------  $------ * \n";
	 cout<<"*  x   __________________________________  $-------  $------ * \n";
	 cout<<"*  x   __________________________________  $-------  $------ * \n";
	 cout<<"*                                                            * \n";
	 cout<<"* ========================================================== * \n";
	 cout<<"*                                      	                     * \n";
	 cout<<"*    Subtotal: $                                             * \n";
	 cout<<"*         Tax: $                                             * \n";
	 cout<<"* Grand Total: $                                             * \n";
	 cout<<"*                                                            * \n";
	 cout<<"************************************************************** \n";


        
    return 0;
}

void print(int [], char [12][20], float [], float)
{
	cout<<"TEST... \n";
}
