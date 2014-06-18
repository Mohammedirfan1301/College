#include <iostream.h>
#include <math.h>

main()
{
	char a;
	int b,c,d,e,f;
	int x = 1;
    
	do{
	cout<<"\nThis program accepts a character input and outputs a diamond. \n";
	cout<<"Enter the character you want to use here. -> ";
	cin>>a;
	cout<<endl;
    
	for(b = 0; b < 9; b++)                //run 9 times by counting up to 9.
	{
		for(c = 0; c < fabs(b - 4); c++)  //print the number of spaces needed.
		{                                 //does this by taking the absolute value of 4-b
			cout<<" ";
		}

			if(b >= 0 && b < 5)
			{
				f = b;                     //these two if's control the stars and when they go up and when they go down.
				e = 1 + (2 * f);           //this does stars up to the point where it needs to decrease (9)
			}

			if(b >= 5 && b < 6)
			{
				f = 3;
				e = 1 + (2 * f);
			}

		for(d = 0; d < e; d++)      //for(d = 0; d < 1 + ((4 - abs(b - 4)) << 1); d++)
		{
			cout<<a;
		}
		
        cout<<endl;
	}

    cout<<"\nTo continue, enter 1. To exit, enter 0. -> ";
    cin>>x;
    
    }while(x==1);
	
	/*
	
	MORE NOTES
	
	Spaces:
	
    0 - 4 = -4
    1 - 4 = -3
    2 - 4 = -2
    3 - 4 = -1
    4 - 4 = 0
    5 - 4 = 1
    6 - 4 = 2
    7 - 4 = 3
    8 - 4 = 4 
	
	Stars:
	
	2 x 0 = 0    + 1 = 1
    2 x 1 = 2    + 1 = 3
    2 x 2 = 4    + 1 = 5
    2 x 3 = 6    + 1 = 7
    2 x 4 = 8    + 1 = 9
    
    2 x 5 = 10   + 1 = 11
    2 x 6 = 12   + 1 = 13
    2 x 7 = 14   + 1 = 15
    2 x 8 = 16   + 1 = 17

    0  1
    1  3
    2  5
    3  7
    4  9
    5  7
    6  5
    7  3
    8  1
	
	*/
	
    /*
    
    NOTES

	 ssss*       4 spaces  1 stars
	 sss***      3 spaces  3 stars
	 ss*****     2 spaces  5 stars
	 s*******    1 spaces  7 stars
	 
	 *********   0 spaces  9 stars
	 
	 s*******    1 spaces  7 stars
	 ss*****     2 spaces  5 stars
	 sss***      3 spaces  3 stars
	 ssss*       4 spaces  1 stars

	TO DO:

	1. Figure out for loops more.
	2. Figure out how to get correct number of stars and spaces.

	*/

	return 0;
}
