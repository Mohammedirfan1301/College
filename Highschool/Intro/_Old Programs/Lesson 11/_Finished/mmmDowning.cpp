#include <iostream.h>   //in/output
#include <iomanip.h>	//for setw()
#include <conio.h>      //clrscr();

void meanfunction(int num[]);      //the function for mean
void medianfunction(int num[]);    //the function for median
void modefunction(int num []);     //the function for mode
void orderfunction(int num[]);     //the function for ascending or descending order

main()
{
	int a = 0, b = 0, x = 0; 	// a/b are for for the loop. x for the do/while.
	int num[10];  			      // num[10] is an array with 10 numbers

	do{
	a = 0, b = 1;

	//introduction prompt
	cout<<"Welcome to the MMM & A/D Program. \n";
	cout<<"This program accepts 10 integer numbers in any order. \n";
	cout<<"It will then find the mean, median and mode of the list (MMM) \n";
	cout<<"and it will also sort the numbers in ascending or descending order (A/D). \n\n";
    
	//loops through asking the user for 10 numbers and displays which number they are on (b does this)
	for(a = 0; a < 10; a++)
	{
		cout<<"Please enter a number in the following space. (#"<<setw(2)<<b<<") -> ";
		cin>>num[a];
		b++;
	}
	
	//each of these calls up its function (ie mean calls up the mean function)
	meanfunction(num);        
	medianfunction(num);
	modefunction(num);
	orderfunction(num);
    
	//Allows the user to rerun or stop the program.
	do{
	cout<<"\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
	cout<<"Enter your selection. -> ";
	cin>>x;
	}while( (x != 1) && (x != 2) );    //only 1 and 2 can be entered.

	clrscr();   //clears the screen after the user is done with the current set of numbers.

	}while(x == 2);

	return 0;
}

void meanfunction(int num[])
{
	int a = 0;
	float total = 0, mean = 0;

	//for the mean, just add all the numbers
	for(a = 0; a < 10; a++)
	{
		total = total + num[a];
	}

	//and divide by the total number of numbers (which is 10)
	mean = total / 10;

	cout<<endl<<"The mean of the set of numbers is: "<<mean<<endl;
}

void medianfunction(int num[])
{
	int a = 0, hold = 0, pass = 0;
	float mediantotal = 0, median = 0;

	//sort the numbers in ascending order.
	for(pass = 1; pass < 10; pass++)
	{
		for(a = 0; a < 9; a++)
		{
			if(num[a] > num[a+1])
			{
				hold = num[a];
				num[a] = num[a+1];
				num[a+1] = hold;
			}
		}
	}

	//now that the numbers are in order, 4/5 is the median. Simply add and divide by 2.
	mediantotal = num[4] + num[5];
	median = mediantotal/2;

	cout<<"The median of the set of numbers is: "<<median<<endl;
}

void modefunction(int num[])
{
    /*
    This function is complex so I'll explain it:
	1. First I sorted the numbers in ascending order (least to greatest). This helps for after the comparison to prevent duplicate modes
	   (ie 1 1 1 appearing as a mode).
	2. I compare each number to all the other numbers - this is the second part. This checks to see if any number is equal.
    3. There's three possible outcomes:
       A. No mode - none of the numbers are equal
       B. One mode - just one number is equal
       C. Multiple modes - several numbers appear the most and appear the same number of times
            
    4. To explain how I worked out each outcome:
       A. Easy - if none of them are equal, the variable freq will equal 1. As they ALL will appear once. Basically no mode.
       B. More complex - but still just need to check if any numbers are equal and how many times they appear.
       C. This is the complex part. I used an array (modearray[]) to store all the many modes. These are found by comparing the frequencies of each number.
          IF for instance 2 numbers (say A and B) appear three times each, then maxfreq will equal 3. Each time A appears it will come up as "3".
          To prevent A or B from being added to modearray[] more than once, "mode != modearray[x-1]" was added. This is why I sorted them first, to make it easier to compare.
    */
    
	int hold = 0, pass = 0;                //for the ascending order sort.
	int a = 0, b = 0, freq = 0, test = 0;  //A/B are for the nested for loops. Freq is how many times a given number appears. Test is the number being compared.
	int maxfreq = 1, maxmode = 0;          //maxfreq is the number of times the current suspect 'mode' appears. Maxmode is the current mode. (maxmode is also the mode at the end if there's one mode)
	int mode = 0, modearray[10], x = 0;    //mode is store test if it could be a mode. mode array stores multiple modes if there is one.

	//first sort the numbers in ascending order
	for(pass = 1; pass < 10; pass++)
	{
		for(a = 0; a < 9; a++)
		{
			if(num[a] > num[a+1])
			{
				hold = num[a];
				num[a] = num[a+1];
				num[a+1] = hold;
			}
		}
	}

	//now compare each number and see if it is equal to any other numbers.
	for(a = 0; a < 10; a++)
	{
		test = num[a];
		freq = 0;

			for(b = 0; b < 10; b++)
			{
				if(num[b] == test) //if it is equal, it is a possible mode
				{
					mode = test;
					freq++;
				}
			}

		  if(freq > maxfreq)
		  {
            maxmode = test;
            maxfreq = freq;
            freq = 0;
		  }

        if( (freq == maxfreq) && (freq > 1) && (mode != modearray[x-1]) )
        {
            modearray[x] = mode;
            x++;
            freq = 0;
        }
    }
    
    if(maxfreq == 1)
    {
        cout<<"There is no mode for this set of numbers. \n";
    }
    
    if( (maxfreq > 1) && (x == 0) )
    {   
	   cout<<"The mode of the set of numbers is: "<<maxmode<<endl;
    }
    
    if( (maxfreq > 1) && (x > 0) )
    {
        cout<<"The mode(s) for this set of numbers is: ";

        for(a = 0; a < x; a++)
        {
            if(a != x-1)
            {
                cout<<modearray[a]<<" , ";
            }
            
            if(a == x-1)
            {
                cout<<modearray[a];
            }
        }
        cout<<endl;
    } 
}

void orderfunction(int num[])
{
	int a = 0, b = 1, hold = 0, pass = 0, x = 0;
    
	do{
	cout<<"\nDo you want to put the numbers in ASCENDING or DESCENDING order? \n";
	cout<<"Enter 1 for ascending. Enter 2 for descending. -> ";
	cin>>x;
	cout<<endl;
	}while(x != 1 && x != 2);

	if(x == 1)
	{

		//sort the numbers in ascending order.
		for(pass = 1; pass < 10; pass++)
		{
			for(a = 0; a < 9; a++)
			{
				if(num[a] > num[a+1])
				{
					hold = num[a];
					num[a] = num[a+1];
					num[a+1] = hold;
				}
			}
		}

		for(a = 0; a < 10; a++)
		{
			cout<<"#"<<b<<"\t"<<num[a]<<endl;
			b++;
		}
	}

	if(x == 2)
	{
		//sort the numbers in descending order.
		for(pass = 1; pass < 10; pass++)
		{
			for(a = 0; a < 9; a++)
			{
				if(num[a] < num[a+1])
				{
					hold = num[a];
					num[a] = num[a+1];
					num[a+1] = hold;
				}
			}
		}

		for(a = 0; a < 10; a++)
		{
			cout<<"#"<<b<<"\t"<<num[a]<<endl;
			b++;
		}
	}
	
	 cout<<endl;

}
