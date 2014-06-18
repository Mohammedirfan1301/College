#include <iostream.h>
#include <iomanip.h>
#include <conio.h>

	//the three functions:
    void findaverage(float grades[][1]);
    void highaverage(char name[][20], float grades[][1]);
    void lowaverage(char name[][20], float grades[][1]);
    
    //global variables
    int a = 0, x = 1;

main()
{
	char name[10][20] = { {"Jason Downing"}, {"Stephen Colbert"}, {"John Stewart"}, {"John Doe"}, {"Jane Doe"},
	{"Barack Obama"}, {"Mitt Romney"}, {"Ron Paul"}, {"Rick Santorum"}, {"Newt Gingrich"} };
	float grades[10][1]; //=  { {90}, {90.332}, {90.333}, {70.4}, {100.3}, {60.5}, {60.2}, {50}, {25}, {20} } ;
                         //the above #'s were usi
	do{
	cout<<"TEST SORT \n";
	cout<<"This program has ten names stored in a character array. \n";
	cout<<"You may enter grades for each of these people and then \n";
	cout<<"this program will run three functions: \n";
	cout<<"1. Find the class average. \n";
	cout<<"2. Find the highest score and print that person's full name. \n";
	cout<<"3. Find the lowest score and print that person's initials. \n\n";

	for(a = 0; a < 10; a++)
	{
	   cout<<"Enter the grade that "<<name[a]<<" recieved: ";
	   cin>>grades[a][0];
	}
 
    cout<<endl;
    
    //call up the 3 functions
	findaverage(grades);
    highaverage(name, grades);
    lowaverage(name, grades);

    do{
	cout<<"\nTo continue press 1. To exit press 2. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

    clrscr();
    
	}while(x == 1);

   cout<<"Thanks for using the TEST SORT PROGRAM.";

	return 0;
}

void findaverage(float grades[][1])
{
	float average = 0, total = 0;
    
    //finds the average by adding all the grades
    for(a = 0; a < 10; a++)
	{
	   total += grades[a][0];
	}
    //and dividing by 10 (the # of people)
	average = total/10;
	cout<<"The average for this group of people is: "<<setiosflags(ios::fixed)<<setprecision(2)<<average<<endl;
}

void highaverage(char name[][20], float grades[][1])
{
    int hname = 0;
    float max = grades[0][0];
    
    //finds the highest grade and that person's name
    for(a = 0; a < 10; a++)
    {
        if(grades[a][0] > max)
        {
            max = grades[a][0];
            hname = a;
        }
    }   
    
    //prints the highest grade and that person's full name
    cout<<"The person with the highest grade is: "<<name[hname]<<" with a score of "<<max<<endl;
}

void lowaverage(char name[][20], float grades[][1])
{
    int lname = 0;
    float min = grades[0][0];
    
    //finds the lowest grade and that person's full name
    for(a = 0; a < 10; a++)
    {
        if(grades[a][0] < min)
        {
            min = grades[a][0];
            lname = a;
        }
    }
    
    //print this first to make printing the initials easier
    cout<<"The person with the lowest grade is: ";
    
    //convert the person's name with lowest grade to initials
    //first value of lname should be that person's FIRST initial (ie 0)
    cout<<name[lname][0];
    
    //to find the second initial, reuse some code from the initials program:
    for(a = 0; a < 20; a++)
    {
		if(name[lname][a] == 32)
        {
			cout<<name[lname][a+1];
        }
    }
    
    //prints the lowest grade and that person's initials
    cout<<" with a score of "<<min<<endl;
}
