#include <iostream.h>
#include <conio.h>
#include <string.h>

main()
{
	int a = 0, b = 0;
	int x = 1;
	char word[30] = {'\0'};
                                                                                       //| 
	do{                                                                                 //|

	//clears the array after every use.
	for(a = 0; a < 30; a++)
	{
		word[a] = '\0';
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
		word[a] = getch();
		cout<<word[a];

		//ASCII for backspace is 8
		if(word[a] == 8)
		{
			a = a - 2;
		}

		//ASCII for enter is 13
		if(word[a] == 13)
		{
			b = strlen(word);  //b is set equal to the length of the string.
			break;
		}

		//ASCII for space is 32
		if(word[a] == 32)
		{
			a = a - 1;
		}
	}

	cout<<"\n\n"<<"THE WORD IS: \n\n";

	for(a=0;a<b;a++)
	{
		cout<<word[a];
	}

   cout<<"\n\n";

	do{
	cout<<"To rerun the program, enter 1. To exit, enter 2. -> ";
	cin>>x;
	}while(x != 1 && x != 2);

	clrscr();

	}while(x == 1);

	return 0;
}
