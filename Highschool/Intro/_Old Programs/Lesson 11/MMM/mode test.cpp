#include <iostream.h>    
    
main()
{
    int a, b, num[10];
    
    for(a = 0; a < 10; a++)
	{
		cout<<"Please enter a number in the following space. (#"<<setw(2)<<b<<") -> ";
		cin>>num[a];
		b++;
	}
    
    int currvalue = num[0]; // start from the 1st element
    int counter = 1;
    int maxcounter = 1;
    int modevalue = num[0];
    for (int i = 1; i < n; ++i) 
    {
        if (num[i] == currvalue)
        {
            ++counter;
        }
        else 
        { 
            if (counter > maxcounter) 
            { // new mode candidate
                maxcounter = counter;
                modevalue = value;
            }
                currvalue = a[i]; // ready to count next values
                counter = 1;
        }
    }
    // Check last value, copy code...
    if (counter > maxcounter) 
    {
        maxcounter = counter;
        modevalue = value;
    }
    
    return 0;
}
