/*
	Jason Downing
	HW Assignment 1
*/
#include <iostream>
#include <string>
using namespace std;

// g++ input.cpp -o inputprog

class Student 
{
public:
	// Take input of quizzes and exams from the user.
	void input();
	// Output final numeric & letter grades.
	void output();	

private:
	// Calculates the numeric grade.
	void calc_average();
	// Calculates the final letter grade.
	void calc_letter();

	// private variables to hold the variables of each object.
	string name;
	float quiz, midterm_exam, final_exam, weight_average_grade;
	char letter_grade;
};

int main()
{
	int num = 1;
	Student students[3];

	cout<<"Welcome to the Grade Program. \n";
	
	// Takes in 3 student's info/outputs the results at the end.
	for(int i=0; i<3; i++)
	{
		students[i].input();
		students[i].output();
	}

	return 0;
}

// Public functions
void Student::input()
{
	// Get all the input from the user.
	cout<<"Enter the student's name: ";
	getline(cin, name);

	cout<<"Enter the student's quiz score: ";
	cin>>quiz;
	
	cout<<"Enter the student's mid term exam: ";
	cin>>midterm_exam;

	cout<<"Enter the student's final exam: ";
	cin>>final_exam;

	// Call the calc_avg and calc_letter functions
	calc_average();
	calc_letter();
}

void Student::output()
{
	cout<<endl<<name<<"'s grades are as following: \n";
	cout<<"Quiz: "<<quiz<<endl;
	cout<<"Mid-term Exam: "<<midterm_exam<<endl;
	cout<<"Final Exam: "<<final_exam<<endl<<endl;
	cout<<"These work out to: \n";
	cout<<"Final numeric grade: "<<weight_average_grade<<endl;
	cout<<"Final letter grade: "<<letter_grade<<endl;
}

// Private functions
void Student::calc_average()
{
	// I decided to make it 20% for the quiz, 30% for the mid term and 50%
	// for the final exam.
	weight_average_grade = (quiz * .2) + (midterm_exam * .3) + (final_exam * .5);

}

void Student::calc_letter()
{
	// Less than a 65 means the student got an "F".
	if(weight_average_grade < 65)
	{
		letter_grade = "F";
	}

	// If between a 65 and below a 70, they got a "D".
	if(weight_average_grade < 70 && weight_average_grade => 65)
	{
		letter_grade = "D";
	}

	// 70 to 79 is a C-
	if(weight_average_grade < 80 && weight_average_grade => 70)
	{
		letter_grade = "C";
	}

	// 80 to 89 is a B
	if(weight_average_grade < 90 && weight_average_grade => 80)
	{
		letter_grade = "B";
	}

	// 90 to 100 is an A
	if(weight_average_grade <= 100 && weight_average_grade => 90)
	{
		letter_grade = "A";
	}
}