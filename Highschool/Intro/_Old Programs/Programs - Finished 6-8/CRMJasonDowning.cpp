#include <iostream.h>  //in/output
#include <iomanip.h>   //for set precision

main()
{
	int x = 1;                     //variable for the do/while
	int a;                         //varible for the switch(a)
	float input1, input2;          //variables for the two inputs
	float markup;                  //variables for the calculations (markup)
    float cost, retail;            //variables for the calculations (cost/retail)
    int n;                         //variable for the precison
    int y;                         //for choosing markup (retail/cost OR cost/retail) - this is for flipping the entries if entered differently.
	int z;                         //for choosing retail (cost/markup OR markup/cost) - for flipping the entries if entered differently.
	int round;                     //for rounding cost/retail
	
	cout<<"Welcome to the CRM Program.                  \n";
	cout<<"This program can calculate retail, cost and  \n";   //intro prompt
	cout<<"markup when any of the two are entered.      \n";

	do{
	input1 = 0;            //resets variable values for rerunning the program.
	input2 = 0;   
         a = 0;
         n = 0;
         y = 0;
         z = 0;
    markup = 0;
      cost = 0;
    retail = 0;

	cout<<"\nIn the below spaces, enter the two inputs.\n";
	cout<<"Enter your first input.  -> ";         //first input
	cin>>input1;
	cout<<"Enter your second input. -> ";         //second input
	cin>>input2;
	
                                                                  //different options depending
	cout<<"\nWhat do you need to calculate?                \n";   //on what the user types in.
    cout<<"Markup given retail and cost -> Enter 1         \n";   //this one does markup if given the cost and retail.                                                
    cout<<"Cost given retail and markup -> Enter 2         \n";   //this one is for cost if given the retail and markup
    cout<<"Retail given cost and markup -> Enter 3         \n";   //this one calculates retail when given the cost + markup
	cout<<"\nPlease also note that cost and retail will    \n";   //lets user know about the way the program rounds.
	cout<<"be printed out to 2 decimal places and rounded. \n";
	
    cout<<"\nEnter your choice here. -> ";                        //user inputs their choice.
	cin>>a;
	
	if (a == 1)
	{
         cout<<"\nYou want to calculate markup.                 ";
         cout<<"\nIf you entered retail and then cost, Press 1. ";
         cout<<"\nIf you entered cost and then retail, Press 2. ";
         cout<<"\nSelection -> ";
         cin>>y;
         
         cout<<"\nWhat precision would you like to calculate the markup to? \n";
         cout<<"(Precision is the number of decimal places.)              \n";
         cout<<"Enter the Precision -> ";
	     cin>>n;
         
         if (y==1)
         {
              markup = (input1-input2)/input1; //(20-10)/20 = .5
         }
         
         if (y==2)
         {
              markup = (input2-input1)/input2; //(20-10)/20 = .5

         }
    }
    
    if (a == 2)
    {
          cout<<"\nWhat precision would you like to calculate the cost to? \n";
         cout<<"(Precision is the number of decimal places.)               \n";
         cout<<"Enter the Precision -> ";
	     cin>>n;
          
          cost = input1 * input2;                    //calculations for cost
    }
    
	if (a == 3)
    {   
         cout<<"\nYou want to calculate Retail.               \n";
	     cout<<"If you entered cost and then markup, Press 1. \n";
	     cout<<"If you entered markup and then cost, Press 2. \n";
	     cout<<"Enter Selection here -> ";
	     cin>>z;
	     
	     cout<<"\nWhat precision would you like to calculate the retail to? \n";
         cout<<"(Precision is the number of decimal places.)                \n";
         cout<<"Enter the Precision -> ";
	     cin>>n;
	    
	     if (z==1)
         {
                 retail = input1 / input2;
         }
        
         if (z==2)
         {
                 retail = input2 / input1;
         }
        
	    
    }

	switch(a)       //this is the switch command that outputs the above calculations.
	{
		case 1:
				 cout<<"\nThe percentage markup is: " << setprecision (n) << markup << endl;
				 break;

        case 2:
				 cout<<"\nThe cost is: " << setprecision (n) << cost << endl;
				 break;
        case 3:
				 cout<<"\nThe retail is: " << setprecision (n) << retail << endl;
				 break;
	 
		default:
				 cout<<"\nYou entered a value that is not between 1 and 6. \n";
				 cout<<"Please try again. \n";
             break;
	}

	cout<<"\nPress 1 to continue or 2 to exit -> ";       //asks for a number to cont. or end the program.
	cin>>x;                                               //accepts the above number choice.

	}while(x==1);                                         //end of the do/while loop

	cout<<"\nThank You for using the CRM Program. ";      //ending prompt
	return 0;
}
