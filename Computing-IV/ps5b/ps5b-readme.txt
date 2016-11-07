/**********************************************************************
 *  readme.txt template
 *  Plucking a Guitar String
 **********************************************************************/

Name: Jason Downing
CS Login: jdowning
Hours to complete assignment (optional): a lot. Like half a day probably. (6 hours easily)


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not?
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
Yes, the whole assignment is done.
It works successfully - all the keys play a song, and I can even
play some music using my keyboard program.

I know the program becauses because:
1. My RingBuffer passed all the previous Boost tests on Bottlenose,
   as well as my own tests.
2. My GuitarString passes the GStest.cpp file.
3. The GuitarHeroLite may sounds
4. My final GuitarHero program makes all 37 sounds.

/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  As a pair, or individually?
 *  If you completed the AutoGuitar, what does it play?
 **********************************************************************/
Nope, I have had enough music for a day.

/**********************************************************************
 *  Does your GuitarString implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
Yep, it passes all of them with flying colors.

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
Just a post on the discussion board which solved all my segfault problems.
1 hour of fighting with pointers, solved with 5 minutes of reading up on
how to use initializer lists.

This thread in particular was helpful:
https://groups.google.com/forum/#!topic/91-204-s15/eMlwKJlJr2s

/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/
1. Tons of segfaults when originally using pointers, switching to member
initialization lists and they went away.
2. Couldn't get my music to play using sounds[i].play(), until I realized
something funky with my code was making just the last few keys worked.
Some how I fixed that and I don't really know what I did, but tweaking it
made it work. And music plays now so yay.


/**********************************************************************
 *  List any other comments here.
 **********************************************************************/
N/A.
