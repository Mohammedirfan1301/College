#include <iostream.h> //in/out put
#include <math.h>     //math stuff like fabs (absolute value)

main()
{
	char a;          //the char variable for the symbol
	int b,c,d,e,f;   //variables for the for loops
	int x = 1;       //variable for the do-while loop
    
	do{              //i put a do while loop so it runs multiple times for multiple characters.
	cout<<"\nThis program accepts a character input and outputs a diamond. \n";    //intro prompt
	cout<<"Enter the character you want to use here. -> ";
	cin>>a;                                                                       //accepts the character input
	cout<<endl;
    
	f = 9;  //f is set equal to 9 here, for use in the for loop for the stars
    
	for(b = 0; b < 9; b++)                //run 9 times by counting up to 9.
	{    
		for(c = 0; c < fabs(b - 4); c++)  //print the number of spaces needed.
		{                                 //does this by taking the absolute value of 4-b
			cout<<" ";                     //example: the first line b is equal to 0, and runs up to 8, or 9 times, for 9 lines.
		}                                 //when b = 0, c will run for < fabs(0 - 4) or [-4] or 4 times.
													 //it will run down, 3, 2, 1 and 0, then start going up again because of fabs (absolute value)
         
          //these next two if's control the stars and when they go up and when they go down.
          //they basically say if b = 0 to 4, then the first if will run
          //and if b is 5 to 8, then the second one will run.                                                          
		
        	if(b >= 0 && b < 5)       //this does the stars up to b = 4, or basically 1, 3, 5, 7 and 9 stars (b = 0,1,2,3,4)
			{                         //does this by multiplying b by 2, then adding 1 and putting that in the e variable  
				e = 1 + (2 * b);       //this simple equation will work up until b = 5, then it starts adding too many stars (11, 13, etc)
			}
			
            f--; 
            
            if(b >= 5)               //this second if controls the second for loop when be is 5,6,7 or 8.
            {                        //the reason for this can be seen in the notes after this code.
                e = 1 + (2 * f);     //basically the equation i thought up only worked until b is 9, after that it adds too many stars
            }                        //this if is the answer to that problem as it only runs when b is greater 4 (5 or higher). allowing me to
                                     //use a second variable that decreases each time.

		for(d = 0; d < e; d++)      //this for loop does the number of stars
		{                           //the equations in the above if's are what makes it work
			cout<<a;
		}

		  cout<<endl;           //not sure if this counts as an equal 'cout' but I couldn't find another way to make the lines end after
	}                          //the spaces and stars had outputed.

	 cout<<"\nTo continue, enter 1. To exit, enter 2. -> ";       //simple prompt asking if the user wants to continue entering characters.
    cin>>x;
    
    }while(x==1);
	
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

	 2 x 5 = 10   + 1 = 11      hmm doesn't work past 9... perhaps another way? if's?
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

	 b f
	 0 8
	 1 7
    2 6
    3 5
    4 4
    5 3
    6 2
    7 1
    8 0

	TO DO:

	1. Figure out for loops more. (CHECK)
	2. Figure out how to get correct number of stars and spaces. (CHECK)

	*/

	return 0;
}
