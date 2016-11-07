#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_linked_list.h"

#define CM_TO_M .01;

void test_ferry_capacity(MY_LINKED_LIST hList, int length_of_ferry);

int main(int argc, char* argv[])
{
	int number_of_cases;
	int number_of_cars;
	int length_of_ferry;
	int length_of_car;
	int trips;
	float ferry;
	char direction[10];
	MY_LINKED_LIST hleft_queue = NULL;
	MY_LINKED_LIST hright_queue = NULL;
	Status code;

	// Get number of test cases
	printf("Enter the number of test cases: ");
	scanf("%d", &number_of_cases);
	
	while(number_of_cases > 0)
	{	
	// Reset variable values for multiple runs.
		trips = 0;
		
	// Create lists
		hleft_queue = my_linked_list_init_default();
		hright_queue = my_linked_list_init_default();
		
		if(hleft_queue == NULL || hright_queue == NULL)
		{
			printf("ERROR! Couldn't alloc space for the list!\n");
			exit(0);
		}
	
	// Each test must get length of the ferry & the number of cars it will ferry.
		printf("Enter the length of the ferry and how many cars to test: ");
		scanf("%d %d", &length_of_ferry, &number_of_cars);
		
		// This part will get input from the user & store it in the linked list.
		while(number_of_cars > 0)
		{
		// Clear the direction string for each input
			memset(direction, 0, 10);
			
			// Get l of the car & which bank the ferry should go to
			printf("Enter a length & direction: ");
			scanf("%d %s", &length_of_car, &direction[0]);
			
			// Compare the direction string to see which bank list to push to
			if(strncmp(direction, "left", 4) == 0)
			{
				code = my_linked_list_push_back(hleft_queue, length_of_car);
			}
			if(strncmp(direction, "right", 5) == 0)
			{
				code = my_linked_list_push_back(hright_queue, length_of_car);
			}

			// If we get an error, ie can't push to a list, throw an error & quit.
			if(code == FAILURE)
			{
				printf("ERROR! Failed to push to the back of the list!\n");
				exit(0);
			}
		
			number_of_cars--;	// Decrease for the do/while loop
		}
		
		// Now the left list & right list should contain some cars to move.
		// Run while both lists contain some number of cars
		printf("SIZE LEFT: %d\nSIZE RIGHT: %d\n", my_linked_list_size(hleft_queue), 
		my_linked_list_size(hright_queue));
		while( ((my_linked_list_size(hleft_queue)) != -1) && ((my_linked_list_size(hright_queue)) != -1))
		{
			//Start on the left bank - ferry was there to start. 
			//Test left.
			test_ferry_capacity(hleft_queue, length_of_ferry);
			trips++;	//Going to to the other bank, so increase trip counter.
			
			//Test Right.
			test_ferry_capacity(hright_queue, length_of_ferry);
			trips++;  //Back on the left side, another trip.
			
			printf("I'm never stopping! (L && R) \n");
		}
		
		printf("Case %d had %d number of trips! \n", number_of_cases, trips);
		
		
	// Delete the lists for the next round & to prevent memory leaks.
		my_linked_list_destroy(&hleft_queue);
		my_linked_list_destroy(&hright_queue);
		number_of_cases--;	// Decrease for the do/while loop
	}

	return 0;
}

void test_ferry_capacity(MY_LINKED_LIST hList, int length_of_ferry)
{
	int ferry = 0;
	
	/* Assume ferry starts on the left bank.
	   Run while the ferry can carry cars	*/
	while(ferry <= length_of_ferry)
	{
		// If the ferry cannot carry the next car, break before trying!
		if( (*(my_linked_list_front(hList)) + ferry) > length_of_ferry)
			break;
		
		if(find_size(hList) == 0)
			break;
		
		// Add the car at the front of the line to the ferry.
		ferry += *(my_linked_list_front(hList)) * CM_TO_M;
		my_linked_list_pop_front(hList);
		
		printf("I'm never stopping! (L or? R) \n");
	} 
	
	return;
}
