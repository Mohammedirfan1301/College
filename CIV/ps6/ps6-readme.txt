/**********************************************************************
 *  readme.txt template
 *  Markov Model
 **********************************************************************/

Name: Jason Downing
Hours to complete assignment (optional): a lot. I'd say well over 6 hours.
Maybe 10 even. Probably a good 10 hours.


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not?
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

I feel that everything works correctly.
I pass all the unit tests, so clearly most of my code should work.
Further, I asked a question on the discussion group to clearify two
of the functions so I probably did those mostly right.
And I get pseudo random text when I run my main, which follows what
Princeton wants as far as I know.

A few examples of what I ran:

./TextGenerator 6 500 < OpeningExercises2014.txt

ORIGINAL INPUT TEXT BELOW THIS LINE.

Good afternoon and welcome to Opening Exercises.
What a special pleasure it is to greet Princetons Great Class of 2018!
I also offer a warm welcome to our new graduate students, faculty and staff
members, and all of you who are returning to campus after the summer.
Today we carry on a tradition that dates back at least to 1802, when
Nassau Hall was the site of an opening exercise for Princeton students.
The event switched to other sites before moving in 1929 to the
University Chapel, where we g

FINAL OUTPUT TEXT BELOW THIS LINE.

Good after all, why I asked at all.
Though you make your life is magic, though you and you has something to you.
Right around you this: Everyone around you have seen this kind, for presides
not in sorting hats or flying brooms, but of a new chapter, or even if most of
an environment with, and made the graduate students.
They have to know the effort to get to know what you will help to create new
knowledge, enhance the best friends whom they took the teaching is a personae,
of the Christian serv


Note: I added some formatting to the above text but otherwise its straight
from my terminal.

Also note that I cut the text after t because I felt dumping an entire
text file to the console was a dumb thing to do. The entire text file is
however stored in a std::string and I confirmed that before just ouputting only
t characters to the screen.

/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?
 **********************************************************************/

Nope.

/**********************************************************************
 *  Does your implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/

Yes, it did.
I know because NO ERRORS DETECTED shows up in the terminal.


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/

Princeton site, Course website.
Discussion board had a few interesting posts.
I also posted a question there and got a response from Prof. Grinberg.

Oh and Roy had an awesome way of doing whole file input that I used since
it works really well.

Other than class stuff:

For sorting the Alphabet, I used this awesome StackOverFlow code idea:
http://stackoverflow.com/questions/9107516/sorting-characters-of-a-c-string

Also, cplusplus.com is amazing.
http://www.cplusplus.com/reference/map/map/insert/
http://www.cplusplus.com/reference/string/string/clear/
http://www.cplusplus.com/reference/string/string/substr/
http://www.cplusplus.com/reference/string/string/compare/

etc

Also these SO posts were useful too:
http://stackoverflow.com/questions/17201590/c-convert-from-1-char-to-string

I believe this one actually saved my life and gave me the missing piece
I needed for the randk() function:
http://stackoverflow.com/questions/8529665/changing-probability-of-getting-a-random-number

/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/

randk and gen are very annoying and not very well documented on
the class site and in Princeton's assignment.

However, Prof. Grinberg wrote an excellent explantation on the class
discussion board which helped me a lot in understanding what the two
functions should be doing. And once I figured out what they should be doing,
it became easier to work on them and tackle then.

In the end I'm pretty sure randk() and gen() both work decently enough to
generate pseudo text.

/**********************************************************************
 *  List any other comments here.
 **********************************************************************/

Nothing much else to put here.
