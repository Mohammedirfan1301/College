/**********************************************************************
Program: Program1A
Author: Jason Downing
Date: 2/3/2014
Time spent: 2 Hours
Purpose: This program is designed to calculate the first 100 emirps.
	 (prime numbers that when reversed are also prime and not
	  palindromes) The program does this by running through
	  numbers until it finds 100 emirps. Each number is tested to
	  see if it is prime, not a palindrome and if it is prime
	  when reversed.
**********************************************************************/
#include <stdio.h>
#include <math.h>

// Pre-condition: array of 100 emirps has been allocated, but is blank (0s)
//Post-condition: array contains the first 100 emirps
void prime_test(int primes[]);

// Pre-condition: unknown whether given number is prime or not
//Post-condition: number is known to be prime or not.
int is_prime(int n);

// Pre-condition: given number
//Post-condition: returns given number, reversed
int reverse_number(int n);

// Pre-condition: emirp array has been filled with first 100 emirps
//Post-condition: 100 emirps printed to the screen, right aligned.
void print_primes(int arr_primes[]);

int main(int argc, char* argv[])
{
	int i;
	int primes[100] = {0};

	//Send the primes array to the test function
	prime_test(primes);

	//Send the primes array to the print function
	print_primes(primes);

	//Hold the window open
	printf("\nDo you wish to continue? -> ");
	scanf("%d", &i);

	return 0;
}

void prime_test(int primes[])
{
	int i, reverse, count = 0, test;

	for(i = 1; count < 100; i++)
	{
		test = is_prime(i);
		if(test == 1 )
		{
			//Found a prime!
			//First reverse the number i
			reverse = reverse_number(i);

			//Then test if its a palindrome
			if(i == reverse)
				test = -1;	//Yes... it is.
			else
				test = 1;

			if(test == 1)	//No, it's not! Good.
			{
				//Hold on though - is the reverse number a prime?
				test = is_prime(reverse);
				
				if(test == 1)	//Yes, it is! Success!
				{
					primes[count] = i;	//Add it to our list of emirps
					count++;			//Increase the counter.
				}
				//If test returns -1, then No, it is not an emirp.
			}
			//If test was -1 at this point, it is either a palindrome or not an emirp.
		}
		//If test as -1 at this point, the number likely wasn't prime.
	}

	return;	//After we find 100 emirps, return back to main.
}

int is_prime(int n)
{
	int a;
	
	//Test to see if a number is prime:
	for(a = 2; a < n; a++)
	{
		if(n % a == 0 && a != n)
		{
			//Number is not prime if it can be divided evenly by any number other than itself.
			//Return -1 for FAILURE
			return -1;
		}
	}

	//If we get to this point, then the number must be prime, so return 1 for SUCCESS.
	return 1;
}

int reverse_number(int n)
{
	int reverse;

	//Time to reverse the number:
	for(reverse = 0; n > 0; ) 
	{
		//This works by looking at the number from right to left
		reverse = reverse * 10 + n%10;		//Using the modulus operator to find the digits of the number
		n = n/10;							//Continue dividing by 10 to move from right to left.
	}

	//Return the reversed number.
	return reverse;
}

void print_primes(int arr_primes[])
{
	int i, count = 1;

	//To test this program: PRINT ALL THE PRIMES OUT!
	printf("Here are the first 100 EMIRP Numbers: \n\n");

	for(i = 0; i < 100; i++)
	{
		printf("%6d", arr_primes[i]);	//the '6d' part makes it right aligned to a min
										//of 6 spaces.
		if(count % 10 == 0)			//For every 10 numbers,
			printf("\n");			//Print a newline

		count++;	//This number is for easily keeping track of the numbers
	}				//To know when to print a newline.

	return;		//return back to main
}
