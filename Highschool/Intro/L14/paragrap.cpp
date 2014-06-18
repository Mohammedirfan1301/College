#include <iostream.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

main()
{
	int a = 0, b = 0, c = 0, d = 0;
	char input[30] = {'\0'};
	char *sentence;

	cout<<"\t\t Character Counter V1.01 \n";
	cout<<"This program counts characters and tells you what they are! \n";
	cout<<"Enter some text in the space below for the program to work: \n\n";

	cout<<"--> ";

	cin.getline(input, 30);

   cout<<"\n";
	c = strlen(input);

	for(a = 0; input[a] != '\0'; a++)
	{
		b = input[a];
		cout<<input[a]<<"\t..."<<(isalnum(b)? (isdigit(b)? "Is a number" : (isalpha(b)? (islower(b)? "Is a lowercase letter" : "Is an uppercase letter") : "")) : (ispunct(b)? "Is punctuation" : "Is a space"))<<endl;

		if(input[a] == 32)
			c--;
	}

	sentence = strtok(input, " ");

	do{
		sentence = strtok(NULL, " ");
		d++;
	}while (sentence != NULL);

	cout<<"\nYou typed "<<c<<" characters (without spaces) in the above sentence. \n";
	cout<<"You typed "<<d<<sentence<<" words in the above sentence. \n";

	return 0;
}
