#include <iostream.h>

main()
{
	char map[20][20];
	int a,b;

	for(a=0;a<20;a++)
	{
		for(b=0;b<20;b++)
		{
			map[a][b] = '*';
		}
	}

	for(a=0;a<20;a++)
	{
		for(b=0;b<20;b++)
		{
			map[a][b]='&';
			cout<<map[a][b];
		}
		cout<<endl;
	}
}
