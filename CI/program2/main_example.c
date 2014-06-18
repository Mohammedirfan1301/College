#include <stdio.h>


int the_user_wishes(void);
void wipe_out_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	do
	{
		printf("Happy Birthday!\n");
	}while(the_user_wishes());

	return 0;
}

int the_user_wishes(void)
{
	char answer;
	printf("Do you wish to continue? (y/n) : ");
	scanf(" %c", &answer);
	wipe_out_keyboard_buffer();

	if(answer == 'y' || answer == 'Y')
	{
		return 1;
	}

	return 0;
}

void wipe_out_keyboard_buffer(void)
{
	char next;
	//gobble up a character
	scanf("%c", &next);

	while(next != '\n') //that character is not the new line
	{
		//gobble up another character
		scanf("%c", &next);
	}
	return;
}