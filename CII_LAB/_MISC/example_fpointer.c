#include <stdio.h>
#include <stdlib.h>

int function(int yo, char whats);
int run_million_tests(int (*fTerminate)(int x, char y));

int main(int argc, char* argv[])
{
	int test;
	
	printf("THIS PROGRAM WILL WIPE YOUR HARD DRIVES!\n");
	printf("Press 1 TO WIPE EVERYTHING NOW: ");
	scanf("%d", &test);
	
	if(test != 1)
	{
		printf("FAILED TO FOLLOW INSTRUCTIONS!1!1!1!\n");
		return 0;
	}
	
	// Function pointer syntax: type (* pNAME)(TYPE, TYPE...);
	int (* pFunction)(int, char);
	pFunction = &function;	// Set the pointer equal to a function's name.

	// Now pFunction can be sent to any function and used there to call function!
	test = run_million_tests(pFunction);
	
	// THE END.
	return 0;
}

int function(int yo, char whats)
{
	if(yo == 99999)
	{
		// HA HA quiting!
		printf("JK APRIL FOOLS!\n");
		return 0;
	}
	else if(whats == 'b');
	{
		// la la la la la
	}
}
int run_million_tests(int (*fTerminate)(int x, char y))
{
	int x, y;
	for(x = 0; x < 100000; x++)
	{
		// CALLING FUNCTION, I REPEAT, CALLING FUNCTION
		// In this case, fTerminate is actually a pointer to a function.
		// But we can simply pretend it is a function! And then this becomes
		// waaaay easier.
		printf("%d\n", x);
		y = fTerminate(x, y);
	}
}
