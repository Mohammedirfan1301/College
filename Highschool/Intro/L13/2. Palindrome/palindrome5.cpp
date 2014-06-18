#include <iostream.h>
#include <conio.h>
#include <string.h>

main()
{
	int a = 0, b = 0, length = 0;
	int x = 1;
	char word[30] = {'\0'};
                                                                                        //| 
	do{                                                                                 //|

	a = 0, b = 0, c = 0;

	//clears the array after every use.
    memset(word, '\0', 30);

	cout<<"\t\tPALIN DROME \n";                                                             //|
	cout<<"This program will accept a word and determine if it is a palin drome.  \n";
	cout<<"The program works for multiple words, capital and lower case letters.  \n";
	cout<<"The program takes these things into consideration when checking to see \n";
	cout<<"if a word is a palin drome \n\n";

	cout<<"Please enter a word: ";

	cin.getline(word, 30);
		
    cout<<"\n\nTHE WORD IS: "<<word;

	cout<<"\n\nNow to test to see if the word is a PALIN DROME... \n\n";
	
	length = strlen(word);
	
	for(

	do{
	cout<<"\n\nTo rerun the program, enter 1. To exit, enter 2. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

	//clrscr();
	system("CLS");

	}while(x == 1);

    cout<<"Thanks for using the PALIN DROME Program! \n";

	return 0;
}
