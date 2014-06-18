#include <iostream.h>
#include <conio.h>
#include <string.h>

main()
{
	int a = 0, b = 0, c = 0;
	int x = 1;
	char word1[30] = {'\0'};
	char word2[30] = {'\0'};
                                                                                       //| 
	do{                                                                                 //|

	a = 0, b = 0, c = 0;

	//clears the array after every use.
	for(a = 0; a < 30; a++)
	{
		word1[a] = '\0';
		word2[a] = '\0';
	}

	cout<<"PALIN DROME \n";                                                             //|
	cout<<"This program will accept a word and determine if it is a palin drome.  \n";
	cout<<"The program works for multiple words, capital and lower case letters.  \n";
	cout<<"The program takes these things into consideration when checking to see \n";
	cout<<"if a word is a palin drome \n\n";

	cout<<"Please enter a word: ";

	//takes in the word, removes any spaces, backs up if backspace is entered and ends if enter is entered.
	for(a = 0; a < 30; a++)
	{
		word1[a] = getch();
		cout<<word1[a];

		//ASCII for backspace is 8
		if(word1[a] == 8)
		{
			a = a - 2;
		}

		//ASCII for enter is 13
		if(word1[a] == 13)
		{
			b = strlen(word1);  //b is set equal to the length of the string.
			break;
		}

		//ASCII for space is 32
		if(word1[a] == 32)
		{
			a = a - 1;
		}
	}

	cout<<"\n\n"<<"THE WORD IS: ";

	for(a=0;a<b;a++)
	{
		cout<<word1[a];
	}

	cout<<"\n\nNow to test to see if the word is a PALIN DROME... \n\n";

	for(a = (b-1); a >= 0; a--)
	{
		word2[c] = word1[a];
		c++;
	}

	cout<<word2;

	if(strlen(word1) == strlen(word2))
	{
		if(strcmp(word1, word2) == 0)
		{
			cout<<"THE WORD IS A PALIN DROME!!!";
		}
	}

	do{
	cout<<"\n\nTo rerun the program, enter 1. To exit, enter 2. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

	clrscr();

	}while(x == 1);

	return 0;
}
