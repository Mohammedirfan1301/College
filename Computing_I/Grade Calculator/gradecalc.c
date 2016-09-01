/*
Grade calculator I made to figure out what my final grade
would be in Computing I. It just takes a bunch of grade
averages (quiz, exams, etc) and spits out what your grade should be.
*/
#include <stdio.h>

int main(int argc, char* argv[])
{
	double final_grade = 0; //Holds the final grade
	double grades[6];		//Holds the grades

	printf("Welcome to the grade calculator for Computing I 91.101.203!\n");
	printf("Please enter the grades as requested! (Estimate Avgs)\n");

	//Packet Grade Avg
	printf("Enter the packet grade average: ");
	scanf("%lf", &grades[0]);

	//Program Avg
	printf("Enter the program average: ");
	scanf("%lf", &grades[1]);

	//Quiz Avg
	printf("Enter the quiz average: ");
	scanf("%lf", &grades[2]);

	//Exam 1 Score
	printf("Enter the first Exam score: ");
	scanf("%lf", &grades[3]);

	//Exam 2 Score
	printf("Enter the second Exam score: ");
	scanf("%lf", &grades[4]);

	//Final Exam Score
	printf("Enter the final Exam score: ");
	scanf("%lf", &grades[5]);

	//Compute Class grade
	final_grade += grades[0] * .05;	// 5% for Packets
	final_grade += grades[1] * .35; //35% for programs
	final_grade += grades[2] * .10;	//10% for Quiz Avg
	final_grade += grades[3] * .15; //15% for 1st Exam
	final_grade += grades[4] * .15;	//15% for 1nd Exam
	final_grade += grades[5] * .20; //20% for Final Exam

	//Print out the final grade to the user
	printf("\n\n\n***********************\n");
	printf("YOUR FINAL GRADE IS: %.2lf\n", final_grade);

	//Thank you, good bye
	printf("THANKS, BYE. \n");

	return 0;
}