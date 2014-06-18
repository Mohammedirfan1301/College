#include <iostream.h>

main()
{
	int g,x,y, num;

	cout<<"Welcome to the CLASS GRADE Program. \n";
	cout<<"This program will calculate the class \n";
	cout<<"grade average, invidivual grades and more! \n";
	cout<<endl;
 /*
	cout<<"Please press n for numerical grade to letter grade \n";
	cout<<"or press l for letter grade to grade range. \n";
	cin>g;

	if(g=='n')
	{ */
		cout<<"Please input a numerical grade. \n";
		cout<<"(This will calculate the letter grade) \n";
		cin>>x;

	if((x<=100)&&(x>=97))
		cout<<"A+";

	if((x<=96)&&(x>=93))
		cout<<"A";

	if((x<=92)&&(x>=90))
		cout<<"A-";

	if((x<=89)&&(x>=87))
		cout<<"B+";

	if((x<=86)&&(x>=83))
		cout<<"B";

	if((x<=81)&&(x>=80))
		cout<<"B-";



	/*
	100-97 = A+
	 96-93 = A
	 92-90 = A-
	 89-87 = B+
	 86-83 = B
	 82-80 = B-
	 79-77 = C+
	 76-73 = C
	 72-70 = C-
	 69-65 = D
	 64- 0 = F

	}

	if(g=='l')
	{
		cout<<"Please input a letter grade. \n";
		cout<<"(This will print out a grade range) \n";
		cin>y;
	}

	else
		cout<<"You didn't enter the correct number. Try again. \n";
	}
	 */
	/*
	Grades are:

	100-97 = A+
	 96-93 = A
	 92-90 = A-
	 89-87 = B+
	 86-83 = B
	 82-80 = B-
	 79-77 = C+
	 76-73 = C
	 72-70 = C-
	 69-65 = D
	 64- 0 = F
	*/

	return 0;
}