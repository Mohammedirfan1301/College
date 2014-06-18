/**********************************************************************
Program: Program 3
Author: Jason Downing
Date: 2/28/2014
Time spent: 5 Hours
Purpose: This program uses a linked list to store integers. It lets the
		 user runs 'n' number of cases of a simulation of a ferry crossing
		 a river. Each 'test case' then prompts the user for the size of
		 the ferry, and how many cars will be traveling across the river.
		 Two linked lists are then used to store each car's length. One
		 list stores the cars on the left bank and another stores the cars
		 on the right bank. At the end of running each test case the program
		 then prints out how many trips the ferry had to make across the river.

**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_linked_list.h"

#define CM_TO_M .01

void run_cases(int number_of_cases);
int get_length_and_side(MY_LINKED_LIST hLeft, MY_LINKED_LIST hRight);
void ferry_crossing(MY_LINKED_LIST hLeft, MY_LINKED_LIST hRight, int trip_counter, int length_of_ferry);
void test_ferry_capacity(MY_LINKED_LIST hList, int length_of_ferry);

int main(int argc, char* argv[])
{
	int number_of_cases;
	
	// Get number of test cases
	printf("Enter the number of test cases: ");
	scanf("%d", &number_of_cases);
	
	// Run all the test cases
	run_cases(number_of_cases);
	
	return 0;
}

/*	 Pre: Nothing except the number of cases has been gotten from the user
	Post: "n" number of cases has been run to completion.	*/
void run_cases(int number_of_cases)
{
	MY_LINKED_LIST hLeft = NULL;
	MY_LINKED_LIST hRight = NULL;
	int length_of_ferry;\
	int trip_counter = 1;
	
	while(number_of_cases > 0)
	{	
	//  Create the lists
		hLeft = my_linked_list_init_default();
		hRight = my_linked_list_init_default();
		
	//	Check & see if they allocated.
		if(hLeft == NULL || hRight == NULL)
		{
			printf("ERROR! Couldn't alloc space for the list!\n");
			exit(0);
		}
	
	/*  Get user input - ferry length & # of cars first.
	    Then get each car's length and side 	*/
		length_of_ferry = get_length_and_side(hLeft, hRight);
		
	//  Now call a function to calculate how many crossings it will take
		ferry_crossing(hLeft, hRight, trip_counter, length_of_ferry);
		
	//  Delete the lists for the next round & to prevent memory leaks.
		my_linked_list_destroy(&hLeft);
		my_linked_list_destroy(&hRight);
		number_of_cases--;	// Decrease for the while loop
		trip_counter++;
	}
	
	return;
}

/*	 Pre: Lists have been created but are empty.
	Post: Two lists contain each the car's lengths	*/
int get_length_and_side(MY_LINKED_LIST hLeft, MY_LINKED_LIST hRight)
{
	char direction[10];
	int length_of_ferry, number_of_cars, length_of_car;
	Status code;

	// Each test must get length of the ferry & the number of cars it will ferry.
	printf("Enter the length of the ferry and how many cars to test: ");
	scanf("%d %d", &length_of_ferry, &number_of_cars);
	
	// This part will get input from the user & store it in the linked list.
	while(number_of_cars > 0)
	{
	// 	Clear the direction string for each input
		memset(direction, 0, 10);
		
	// 	Get l of the car & which bank the ferry should go to
		printf("Enter a length & direction: ");
		scanf("%d %s", &length_of_car, &direction[0]);
		
	// 	Compare the direction string to see which bank list to push to
	// 	Left Bank
		if(strncmp(direction, "left", 4) == 0)
		{
			code = my_linked_list_push_back(hLeft, length_of_car);
		}
		
	// 	Right Bank
		if(strncmp(direction, "right", 5) == 0)
		{
			code = my_linked_list_push_back(hRight, length_of_car);
		}

	// 	If we can't push to a list - throw an error & quit.
		if(code == FAILURE)
		{
			printf("ERROR! Failed to push to the back of the list!\n");
			exit(0);
		}
	
		number_of_cars--;	// Decrease for the while loop
	}

	return length_of_ferry;
}

/*	 Pre: The lists are full of car length's
	Post: Both lists are empty and the number of trips has been calculated.	*/
void ferry_crossing(MY_LINKED_LIST hLeft, MY_LINKED_LIST hRight, int trip_counter, int length_of_ferry)
{
	int trips = 0;
	/* Now the left list & right list should contain some cars to move.
	   Run while both lists contain some number of cars	*/
	while( my_linked_list_size(hLeft) > 0 || my_linked_list_size(hRight) > 0)
	{
	/* 	Start on the left bank - ferry was there to start. 
	   	Work on the left if it contains any cars.	*/
		if(my_linked_list_size(hLeft) != 0)
		{
			test_ferry_capacity(hLeft, length_of_ferry);
		}
		trips++;	// Going to to the other bank, so increase trip counter.
		
	// 	CHECK to see if both lists are empty now. This prevents an extra trip being counting!
		if(my_linked_list_size(hLeft) == 0 && my_linked_list_size(hRight) == 0)
		{
			break;
		}
		
	// 	Work on the right if it contains any cars.
		if(my_linked_list_size(hRight) != 0)
		{
			test_ferry_capacity(hRight, length_of_ferry);
		}
		trips++;  	// Back on the left side, another trip.
	}
	
	printf("Case %d had %d number of trips! \n", trip_counter, trips);
	
	return;
}

/*	 Pre: A given 'trip' has not been tested yet.
	Post: One ferry trip has been calculated. The ferry is 'full' to capacity
		  and contains the maximum number of cars it can fit.	*/
void test_ferry_capacity(MY_LINKED_LIST hList, int length_of_ferry)
{
	float ferry = 0;
	
/* 	Assume ferry starts on the left bank.
	Run while the ferry can carry cars		*/
	while(ferry <= length_of_ferry)
	{
	// 	If the list is empty, quit.
		if(my_linked_list_size(hList) == 0)
			break;
			
	// 	If the ferry cannot carry the next car, quit.
		if( ( ( *(my_linked_list_front(hList)) * CM_TO_M ) + ferry ) > length_of_ferry )
			break;
		
	// 	Otherwise: add the car that is at the front of the line to the ferry.
		ferry += *(my_linked_list_front(hList)) * CM_TO_M;
		
	//	Then pop it off the list
		my_linked_list_pop_front(hList);
	} 
	
	return;
}
