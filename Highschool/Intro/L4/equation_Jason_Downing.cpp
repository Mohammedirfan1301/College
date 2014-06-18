#include <iostream.h>         //header files (this one is input output).
#include <math.h>             //math header files, to make use of pow

int main()
{
	double a, x, ans1, ans2, ans3;   //variables needed
	cout<<"Welcome to the EQUATIONS PROGRAM.\n";                   //prompt/intro to the program
	cout<<"This program will evaluate the function: \n";
	cout<<"f(x)=ax^3+7 \n";
	cout<<"when you input the values for 'a' and 'x'. \n";
	cout<<"========================================== \n";
	cout<<endl;
	cout<<"Enter a value for 'a'. \n";   //asks user for 'a'. next line accepts 'a' and stores it.
	cin>>a;
	cout<<"Enter a value for 'x.' \n";   //asks user for 'x'. next line accepts 'x' and stores it.
	cin>>x;
	cout.precision(5);
	ans1=pow(x,3);               //does the math of the equation f(x)=ax^3+7
	ans2=ans1*a;
	ans3=ans2+7;
	cout<<endl;
	cout<<"The value of the function is f(" <<x <<")=" <<ans3<<"\n";        //displays the final equation.
	cout<<endl;
	cout<<"Thank You for using the EQUATIONS PROGRAM.";
	return 0;
}
