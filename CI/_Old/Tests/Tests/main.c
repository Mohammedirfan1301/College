#include <stdio.h>

int main(int argc, char* argv[])
{
	int x, y;
	x = -1;
	y = 0;
	while(x <= 3)
	{
		y += 2;
		x += 1;
	}
	printf("The final value of y is: %d", y);

	return 0;
}