#include <iostream.h>

char convert (char);

main()
{
	int x = 1;   //for the do/while
	char b;      //to accept letter input

	do{
	cout<<"Welcome to the Letter Converter Program. \n";
	cout<<"This program will accept a letter and convert it between \n";  //introduction
	cout<<"uppercase and lower case. \n";

	cout<<"Enter a letter to convert. -> ";
	cin>>b;

	cout<<convert(b);    //does this send and not return? check

	cout<<"\nTo stop the program, enter 0. To rerun the program, enter 1. -> ";
	cin>>x;
	cout<<endl;    //put clear screen here

	}while((x==1)&&(x != 0));
	return 0;
}

char convert (char letter)
{
	cout<<"\nThis is a test. \n";
	cout<<letter<<"\n";
	return 0;
}

/*
to do:

1. figure out functions more
2. how to convert letters?
3. note that 96 difference between upper/lowercase for ascii table.

*/
