#include <iostream.h>

main()
{
	int a,b,c;                                           //three variables needed.
	cout<<"Welcome to the 3-NUMBER-ORDER PROGRAM.  \n";  //prompt for the user to see
	cout<<"This program will order three numbers   \n";  //explains program.
	cout<<"in ascending order. (least to greatest) \n";
	cout<<endl;
	cout<<"Please enter the first number.   ";           //asks for first number
	cin>>a;
	cout<<endl;
	cout<<"Please enter the second number.  ";           //asks for second number
	cin>>b;
	cout<<endl;
	cout<<"Please enter the third number.   ";           //asks for third number
	cin>>c;
	cout<<endl;

	/* all the possible options are:

	None are equal
	6 possible numbers
	123     = works
	132     = works
	213     = works
	231     = works
	312     = works
	321     = works

	Some are equal
	18 possible
	121     = works
	131     = works
	212     = works
	232     = works
	313     = works
	323     = works

	112     = works
	113     = works
	221     = works
	223     = works
	331     = works
	332     = works

	122     = works
	133     = works
	211     = works
	233     = works
	311     = works
	322     = works

	All are equal
	111	  case13 = works								*/



	//None are equal

	if((a<b)&&(a<c)&&(b<c))
		cout<<"The order is: "<<a<<" "<<b<<" "<<c;   //works

	if((a<b)&&(a<c)&&(c<b))
		cout<<"The order is: "<<a<<" "<<c<<" "<<b;   //works

	if((b<a)&&(b<c)&&(a<c))
		cout<<"The order is: "<<b<<" "<<a<<" "<<c;   //works

	if((b<a)&&(b<c)&&(c<a))
		cout<<"The order is: "<<b<<" "<<c<<" "<<a;  //works

	if((c<a)&&(c<b)&&(b<a))
		cout<<"The order is: "<<c<<" "<<b<<" "<<a;  //works

	if((c<a)&&(c<b)&&(a<b))
		cout<<"The order is: "<<c<<" "<<a<<" "<<b;  //works



	//Some are equal

	if((a==b)&&(b<c))
		cout<<"The order is: "<<a<<" "<<b<<" "<<c;   //works

	if((a==b)&&(b>c))
		cout<<"The order is: "<<c<<" "<<a<<" "<<b;   //works

	if((b==c)&&(c<a))
		cout<<"The order is: "<<b<<" "<<c<<" "<<a;   //works

	if((b==c)&&(c>a))
		cout<<"The order is: "<<a<<" "<<c<<" "<<b;   //works

	if((c==a)&&(a<b))
		cout<<"The order is: "<<a<<" "<<c<<" "<<b;  //works

	if((c==a)&&(a>b))
		cout<<"The order is: "<<b<<" "<<c<<" "<<a;  //works



	//All are equal

	if((a==b)&&(b==c))
		cout<<"The order is: "<<a<<" "<<b<<" "<<c;   //works

	return 0;
}
