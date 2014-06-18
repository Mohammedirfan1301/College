#include <iostream.h>    //header file for input-output
#include <iomanip.h>    //header file for input output manipulator. used for setw().
#include <math.h>      //header file for math (used for the pow and cube.)

int main()
{
	double a,b,c,d,e,f,g,h,i,j,x,xsq,xcb,asq,acb,bsq,bcb,csq,ccb,dsq,dcb,esq,ecb,fsq,fcb,gsq,gcb,hsq,hcb,isq,icb,jsq,jcb;
	cout<<"Welcome to the SQAURE CUBE Program. \n";
	cout<<"Please enter a number. This program will give you\n";
	cout<<"the square and cube of the number of you enter. \n";            //program prompt, explains program to user incase they are not in this class.
	cout<<"The program will then give you the next ten whole \n";
	cout<<"number squares and cubes. \n";
	cout<<endl;
	cout<<"Please enter a whole number. \t";
	cin>>x;
	cout<<endl;
	
	xsq=pow(x,2);       //all the math is performed in these lines. pow command is used to bring number to the correct power needed, ie square/cube it.
	xcb=pow(x,3);       //also, the next number is found simply by adding each number by 1. ie 3 is brought to 4 by adding 1, then 4 is brought to 5 by
	a=x+1;              //adding 1. except variables are used instead which results in everything working (different numbers work the same, so 6 can be
	asq=pow(a,2);       //used the same as 5, or even 10 could be entered and still the program finds the next 10 numbers, squares/cubes them and lists them.
	acb=pow(a,3);
	b=a+1;
	bsq=pow(b,2);
	bcb=pow(b,3);
	c=b+1;
	csq=pow(c,2);
	ccb=pow(c,3);
	d=c+1;
	dsq=pow(d,2);
	dcb=pow(d,3);
	e=d+1;
	esq=pow(e,2);
	ecb=pow(e,3);
	f=e+1;
	fsq=pow(f,2);
	fcb=pow(f,3);
	g=f+1;
	gsq=pow(g,2);
	gcb=pow(g,3);
	h=g+1;
	hsq=pow(h,2);
	hcb=pow(h,3);
	i=h+1;
	isq=pow(i,2);
	icb=pow(i,3);
	j=i+1;
	jsq=pow(j,2);
	jcb=pow(j,3);
	
	cout<<"Number"<<setw(10)<<"Square"<<setw(10)<<"Cube \n";    //creates the table. basically displays the finished math from the above lines of code.
    cout<<left;
    cout<<x<<setw(11)<<xsq<<setw(11)<<xcb<<"\n";					//makes use of setw() to create the table.
    cout<<a<<setw(11)<<asq<<setw(11)<<acb<<"\n";
    cout<<b<<setw(11)<<bsq<<setw(11)<<bcb<<"\n";
    cout<<c<<setw(11)<<csq<<setw(11)<<ccb<<"\n";
    cout<<d<<setw(11)<<dsq<<setw(11)<<dcb<<"\n";
    cout<<e<<setw(11)<<esq<<setw(11)<<ecb<<"\n";
    cout<<f<<setw(11)<<fsq<<setw(11)<<fcb<<"\n";
    cout<<g<<setw(11)<<gsq<<setw(11)<<gcb<<"\n";
    cout<<h<<setw(11)<<hsq<<setw(11)<<hcb<<"\n";
    cout<<i<<setw(11)<<isq<<setw(11)<<icb<<"\n";
    cout<<j<<setw(11)<<jsq<<setw(11)<<jcb<<"\n";
    
    system("Pause");
    
    return 0;
}
