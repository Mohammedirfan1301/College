#include <iostream.h>    //input output
#include <conio.h>       //used for getch();

main()
{
	 char fullname[50];        //array that holds the fullname
	 int a = 0, b = 0, c = 0;  //abc are used for the for loops
	 int x = 2;                //x is for the do/while loop

	 //introduction
	 do{
    cout<<"Welcome to the INITIALS Program. \n";
    cout<<"This program will turn a full name into initials. \n";
    cout<<"Enter your full name: ";

	 for(a = 0; a < 50; a++)
	 {
			fullname[a] = getch();
			cout<<fullname[a];

			//if a mistake is made and backspace is entered, then the mistake may be corrected.
			//as a-1 is the mistake and a must be set so the next getch will be the mistake
			//which should be 1 back, but because of a++, it is actually 2 back (ie 7 is the mistake, 8-1 = 7, but 7+1=8, so its 8-2=6+1=7.
			if(fullname[a] == 8)
			{
				a = a - 2;
			}

			//if the user enters 'enter', ascii value of 13
			if(fullname[a] == 13)
			{
				cout<<endl;  //it will make a new line
				break;       //and break the loop.
			}
	 }

	 cout<<"\nYour initials are: ";

	 //the first initial is simple: the first number or 0.

	 cout<<fullname[0];

	 //the second initial is one after the space (ascii value of 32).
	 for(b = 0; b < 50; b++)
    {
		  if(fullname[b] == 32)
        {
				cout<<fullname[b+1];
				c = b+1;    //set c equal to the second initial, used in next for loop.
				break;
        }
    }

	 //the final initial is one after the next space. by setting c equal to the second initial,
	 //i can just retest for the next space and enter that.
	 for(c; c < 50; c++)
    {
		  if(fullname[c] == 32)
        {
				cout<<fullname[c+1];
            break;
        }
    }

    do{
	 cout<<"\n\nTo stop the program, enter 1. To rerun the program, enter 2. \n";
    cout<<"Enter your selection. -> ";
	 cin>>x;
	 }while(x != 1 && x != 2);      //only lets the user enter 1 or 2.
    
	 clrscr();     //clears the screen
    
    }while(x == 2);   //runs only if 2 is entered.
    
    return 0;    
}

/*

a=7
fullname[7] == 8


012345678901234567890
		a
Jason Patrick Downing

cout<<fullname[0];
if(fullname[a] == 32)
cout<<fullname[a+1];

JPD

http://www.mybestnotes.co.in/source-code/?source=INITIALS.C

*/
