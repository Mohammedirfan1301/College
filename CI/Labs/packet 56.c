#include <stdio.h>
double get_value(void);

int main(int argc, char* argv[])
{
	int a;	
	a = get_value();
	printf("%lf", a);
	a = get_value();
	printf("%lf", a);
	return 0;
}

double get_value(void)
{
	double ans;
	do{
		printf("Please enter a POSITIVE number: ");
		scanf("%lf", &ans);
	}while(ans > 0 && ans != 0);
	return ans;
}