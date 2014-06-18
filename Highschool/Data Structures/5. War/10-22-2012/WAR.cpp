#include <iostream>

main()
{
	int deck1[52] = {0};
	int deck2[52] = {0};
	
	/*
	First thing to do is to deal the cards (26 to each, random, only use 52 cards)
	Then look at the top most of each person's deck and determine who wins
	Then pop the enqueue the loser's card, pop that card off the loser and move everything forward 1.
	*?
		
	return 0;
}
