#include <iostream.h>

main()
{
	int x = 1;              //variable for the do/while
	int a;                  //varible for the switch(a)
	float input1, input2;    //variables for the two inputs
	float markup1, markup2, cost, retail1, retail2;  //variables for the calculations
	
	cout<<"Welcome to the CRM Program.                  \n";
	cout<<"This program can calculate retail, cost and  \n";   //intro prompt
	cout<<"markup when any of the two are entered.   \n";

	do{
	input1 = 0;
	input2 = 0;   //resets variable values for rerunning the program.
		 a = 0;

	cout<<"\nIn the below spaces, enter the first two inputs.";
	cout<<"\nEnter your first input. -> ";        //first input
	cin>>input1;
	cout<<"Enter your second input. -> ";       //second input
	cin>>input2;

    /*possiblities include:
    retail/cost
    retail/markup
    cost/retail
    cost/markup
    markup/cost
    markup/retail
    */
                                                           //different options depending
	cout<<"\nWhat do you need to calculate?        \n";    //on what the user types in.
	
    cout<<"Markup given retail and cost -> Enter 1 \n";    //this one does markup if given the cost and retail.
	cout<<"Markup given cost and retail -> Enter 2 \n";
	                                                              
    cout<<"Cost given retail and markup -> Enter 3 \n";   //this one is for cost if given the retail and markup
	
    cout<<"Retail given cost and markup -> Enter 4 \n";   //this one calculates retail when given the cost + markup
	cout<<"Retail given markup and cost -> Enter 5 \n";
	
    cout<<"\nEnter your choice here. -> ";                 //user inputs their choice.
	cin>>a;

    markup1 = (input1-input2)/input1;
    markup2 = (input2-input1)/input2;
	   cost = input1 * input2;                              //calculations
	retail1 = input1 / input2;
	retail2 = input2 / input1;


	switch(a)       //this is the switch command that outputs the above calculations.
	{
		case 1:
				 cout<<"\nThe percentage markup is: "<<markup1<<endl;
				 break;
		case 2:
                 cout<<"\nThe percentage markup is: "<<markup2<<endl;
                 break;
        case 3:
				 cout<<"\nThe cost is: "<<cost<<endl;
				 break;
        case 4:
				 cout<<"\nThe retail is: "<<retail1<<endl;
				 break;
		case 5:
                 cout<<"\nThe retail is: "<<retail2<<endl;
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
