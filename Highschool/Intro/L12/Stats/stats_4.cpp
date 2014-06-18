#include <iostream.h> //input/output
#include <iomanip.h>  //used for setw()
#include <conio.h>    //used for getch();

main()
{
    char names[5][10];  //=  {    "Joe",     "Babe",         "Billy",     "Eric",     "Jack"};  //used to test the program easily
	float stats[5][2];  //= { {.35575, 54}, {.34206, 714}, {.5598, 40}, {.4448, 33}, {.0018, 1} }; //also useful when aligning the table
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
    
    system("cls"); //replace this with clrscreen!!
    
    cout<<"**********************************************************************"<<endl;
    
    //key for the table
    cout<<right<<setw(24)<<"Player's name"<<setw(20)<<"Batting Average"<<setw(23)<<"Number of Homeruns"<<endl;
    name = 0;
    playernum = 1;
    
    //computer prints the table to the screen.
    for(a = 0; a < 5; a++)
    {
        cout<<"Player #"<<playernum<<": "<<left<<setw(13)<<names[name];  //prints the name of the player    
                            //note that the left and setw(13) is to make the next setw line up correctly
        for(b = 0; b < 2; b++)
        {
            if(b == 0)
            cout<<right<<setw(15)<< fixed << setprecision (3)<<stats[a][b];
            if(b == 1)
            cout<<right<<setw(20)<< setprecision(0) << stats[a][b];
                    
        }
        
        cout<<endl;
        name++;
        playernum++;
    }
    
    cout<<"**********************************************************************"<<endl<<endl;
    
	do{
	cout<<"To continue press 1. To exit press 2. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

    system("cls"); //replace this with clrscreen!!

	}while(x == 1);

	return 0;
}

/*
NOTES
setw() does the field width. try changing it to right or left and see how it effects the output.
right seems to work the best for the table.
setfill('*') will help with getting the correct number of spaces (ie make sure they are the same)

this site has useful information and a good example between left/right
http://www.programmersheaven.com/mb/beginnercpp/376806/376806/setw-alignment-help/

*/
