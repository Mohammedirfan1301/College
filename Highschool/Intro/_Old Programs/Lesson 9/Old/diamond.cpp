#include <iostream.h>
#include <math.h>

main()
{
	char a;
	int b,c,d;

	cout<<"This program accepts a character input and outputs a diamond. \n";
	cout<<"Enter the character you want to use here. -> ";
	cin>>a;

	for(b=0; b<9; b++)           //run 9 times
	{
		for(c=0; fabs(4-b); c++)  //print the number of spaces needed.
		{                         //does this by taking the absolute value of 4-b
			cout<<" ";
		}

		for(d=0; 1; c++)
		{
			cout<<a;
		}
	}


	/*

	 ssss*       4 spaces  1 stars
	 sss***      3 spaces  3 stars
	 ss*****     2 spaces  5 stars
	 s*******    1 spaces  7 stars
	 *********   0 spaces  9 stars


	 s*******    1 spaces  7 stars
	 ss*****     2 spaces  5 stars
	 sss***      3 spaces  3 stars
	 ssss*       4 spaces  1 stars




	for(b=0; b<5; b++)
	{
		for(c=0; c<5; c++)
		{
			cout<<" "<<a<<endl;
		}
	}


	TO DO:

	1. Figure out for loops more.
	2. Figure out how to get correct number of stars and spaces.

   Also work on other programs.

	*/

	return 0;
}