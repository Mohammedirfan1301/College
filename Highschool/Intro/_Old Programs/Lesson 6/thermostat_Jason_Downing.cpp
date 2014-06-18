#include <iostream.h>

int main()
{
	int a;    //needed for numbers.
	char b;   //needed for d/h to work
	cout<<"Welcome to the THERMOSTAT-3000 Program.     \n";
	cout<<"This program is designed to automatically   \n";
	cout<<"turn on or off your Air Conditioning Unit   \n";
	cout<<"depending on the temperature and humidity.  \n";
	cout<<endl;
	cout<<"Please use h for humid and d for dry.       \n";
	cout<<endl;
	cout<<"Please enter the temperature.       ";
	cin>>a;
	cout<<endl;
	cout<<"Please enter the humidity (h or d)  ";
	cin>>b;
	cout<<endl;

	/*

	CONDITIONS

	if temperature t< 70               turn A/C OFF
	if temperature t< 80 AND its dry   turn A/C OFF.

	if temperature t> 70 AND its humid turn A/C ON.
	if temperature t>=80               turn A/C ON.

	USE ONLY 2 IF STATEMENTS...
	therefor only two outcomes - on or off.
	just need to combine ands/ors

	*/

	if( (a<70)||(a<80)&&(b=='d') )
	cout<<"The A/C is OFF.";

	//less than 70, off.
	//less than 80 + dry, off

	if(((a>=70)&&(b=='h'))||(a>=80))
	cout<<"The A/C is ON.";

	//greater than or equal to 70 + humid, on
	//greater than or equal to 80, on

	/*tests:

	60+d= OFF
	60+h= OFF
	62+d= OFF
	62+h= OFF
	65+d= OFF
	65+h= OFF
	68+d= OFF
	68+h= OFF
	69+d= OFF
	69+h= OFF
	70+d= OFF
	70+h= ON
	72+d= OFF
	72+h= ON
	74+d= OFF
	74+h= ON
	75+d= OFF
	75+h= ON
	77+d= OFF
	77+h= ON
	79+d= OFF
	79+h= ON
	80+d= ON
	80+h= ON
	82+d= ON
	82+h= ON
	84+d= ON
	84+h= ON
	86+d= ON
	86+h= ON
	88+d= ON
	88+h= ON
	90+d= ON
	90+h= ON
	92+d= ON
	92+h= ON
	94+d= ON
	94+h= ON
	96+d= ON
	96+h=  ON
	98+d=  ON
	98+h=  ON
	100+d= ON
	100+h= ON

	*/
	return 0;
}