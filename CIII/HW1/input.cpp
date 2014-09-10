/*
	Jason Downing
	HW Assignment 1
*/
#include <iostream>
#include <string>
using namespace std;

class Student 
{
public:
	// Take input of quizzes and exams from the user.
	void input(	float quiz, float midterm_exam,
				float final_exam, float weight_average_grade);
	// Output final numeric & letter grades.
	void output( );	

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
	Student[3];

	cout<<"Welcome to the Grade Program.";
	
	// Takes in 3 student's info/outputs the results at the end.
	for(int i=0; i<3; i++)
	{
		cout<<"Enter Student #"<<num<<"'s name: ";
		cout<<"Enter Student #"<<num<<"'s quiz score: ";
		cout<<"Enter Student #"<<num<<"'s mid term exam: ";
		cout<<"Enter Student #"<<num<<"'s final exam: ";
	}

	return 0;
}

// Public functions
void Student::input()
{


}

void Student::output()
{


}

// Private functions
void Student::calc_average()
{


}

void Student::calc_letter()
{


}