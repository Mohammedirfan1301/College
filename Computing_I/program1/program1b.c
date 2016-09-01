/***********************************************************************************************
	Program:	program1b.c
	Author:		Jason Downing
	Date:		September 22, 2013
	Time Spent:	1 hour
	Purpose:	The purpose of this program is to calculate how long it will take to pay
				off a purchase of a stereo system. The stereo system was purchased for $1,000
				and this program assumes monthly payments of $50, with 1.5% interest each month.
				The $50 first goes to interest and then to the principal. The program performs
				the necessary calculations and it then prints out how many months it will take
				to pay off the stereo purchase, as well as the total interest paid.
************************************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
	double principal = 1000, totalinterest = 0, currentinterest = 0;	//variables used in the program. self expainable names.
	double currentpayment = 0, finalpayment = 0;						//counter variable to count how many months it will take
	int months = 0;									

	while(principal > 0)	//Run while principal is greater than zero - that is, run until you've made all your payments.
	{
		currentinterest = principal * .0150;		//calculates current payment's interest
		currentpayment = 50 - currentinterest;		//calculates what the current payment on the principal will be.
		
		if((principal - currentpayment) >= 0)		//this calculation works if the principal will be greater than or equal to 0 after taking off the '$50' payment (minus interest)
			principal -= currentpayment;			//subtracts the current payment from the principal (curr pay = $50 - interest)
		else
		{
			finalpayment = principal + currentinterest;	//the final payment is equal to the principal + the interest, since the last payment may be less than $50. 
			principal -= principal;						//since the final payment is less than $50, just take off the principal to make it equal to 0.
		}

		totalinterest += currentinterest;			//keeps track of the interest paid
		months++;	//Counts the number of months that it will take to pay off the loan

		//This line is for debugging purposes (to ensure that the program is calculating correctly
		//printf("%d	%.2f	%.2f	%.2f	%.2f \n", months, principal, currentpayment, currentinterest, totalinterest);
	}

	printf("It will take %d months to pay off the loan for the stereo! \n", months);	//Printfs to show the user the number of months it will take to pay off the loan
	printf("The final payment was $%.2f dollars. \n", finalpayment);					//As well as the final payment and the amount of interest that will be paid on the loan.
	printf("Also you spent $%.2f dollars on interest! \n", totalinterest);

	return 0;	//End of the program at this point.
}
