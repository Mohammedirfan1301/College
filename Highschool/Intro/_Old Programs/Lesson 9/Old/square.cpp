#include <iostream.h>
#include <iomanip.h>

main()
{
	int side;        //variable for the side (ie 5x5, enter 5)
	int a,b,c,d,e;     //variables to output the square
	int x = 1;

	cout<<"Welcome to the Square Program. \n";             //introduction
	cout<<"This program will ask you to enter the length of one side \n";
	cout<<"and it will output a square with sides that large.        \n";

	while(x==1)
	{

	cout<<"\nEnter the length of a side. -> ";    //prompt to enter the length
	cin>>side;                                    //side variable stores the size
	cout<<endl;

	d = side-2;     //d is for
	e = d + 1;      //setw

											  //example:
	for(a = side; a > 0; a--)		  //enter 5. a is equal to 5, so a is 5.
	{                               //5 must be greater than 0.
		cout<<"*";                   //decrease by 1 each time. and output "*"
	}                               //this forms the top part of the square.

	for(b = d; b > 0; b--)            //b is equal to d, which would be 5-2=3, so b is 3.
	{                                 //3 must be greater than 0, decrease it by 1 each time
		cout<<endl<<"*"<<setw(e)<<"*"; //and then output "*" space "*"
	}                                 //where the space is e, or d+1 (5+1)

	cout<<endl;

	for(c = side; c > 0; c--)         //c is 5, 5 >0 and -1 each time
	{
		cout<<"*";                     //outputs "*" each time it runs.
	}

	cout<<"\n\nTest 1 Done.";

	/*

	******
	*    *
	*    *      8
	*    *
	*    *
	******
	 6x6
	 20

	*****
	*   *
	*   *       6
	*   *
	*****
	 5x5
	 16

	****
	*  *        4
	*  *
	****
	 4x4
	 12

	***
	* *         2
	***
	3x3
	 8

	**          0
	**
	2x2
	 4

	*
	1x1
	 1

	*/

	}

	return 0;
}
