#include <iostream.h> //input/output
#include <iomanip.h>  //used for setw()
#include <conio.h>    //used for getch();

main()
{
    char names[5][20] =  {    "Joe",     "Bob",      "Billy",   "Eric",     "Jason"};
	float stats[5][2] = { {.888, 99}, {.222, 20}, {.559, 40}, {.444, 33}, {.001, 1} };
    int name = 0, playernum = 1, a = 0, b = 0, x = 1;

	do{
    //introduction prompt
    cout<<"STATS \n";
    cout<<"This program accepts 5 player's names, along with their \n";
    cout<<"batting averages and number of homeruns. \n";
    cout<<"After accepting the names/stats, it then prints them to the screen. \n";
    
    playernum = 1;  //resets the player number variable to 1
    a = 0;          //resets a/b to make sure they equal 0 when rerunning the program.
    b = 0;          
    
    cout<<endl<<"**********************************************************************"<<endl<<endl;
/*    
    //user enters the names, batting average and homeruns.
    for(name = 0; name < 5; name++)
    {
        b = 0;
        cout<<"What is player #"<<playernum<<"'s name? \n";
        cout<<"Enter it here: ";
        cin>>names[name];
        cout<<endl;
        
        cout<<"What is "<<names[name]<<"'s (Player #"<<playernum<<") batting average? \n";
        cout<<"Enter it here: ";
        cin>>stats[a][b];
        cout<<endl;
        b++;
        
        cout<<"How many homeruns does "<<names[name]<<" (Player #"<<playernum<<") have? \n";
        cout<<"Enter it here: ";
        cin>>stats[a][b];
        cout<<endl<<"**********************************************************************"<<endl<<endl;
        
        playernum++;
        a++;
    }
*/    
    cout<<setw(11)<<" "<<"Player's name"<<setw(10)<<"Batting Average"<<"Number of Homeruns"<<endl;
    playernum = 1;
    
    //computer prints the table to the screen.
    for(name = 0; name < 5; name++)
    {
        cout<<"Player #"<<playernum<<": "<<names[name];
        cout<<endl;
        playernum++;
    }
    
	do{
	cout<<"\nTo continue press 1. To exit press 2. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

    system("cls"); //replace this with clrscreen!!

	}while(x == 1);

	return 0;
}
