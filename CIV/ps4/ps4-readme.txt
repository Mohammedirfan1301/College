/**********************************************************************
 *  readme template
 *  DNA Sequence Alignment
 **********************************************************************/

Name:   Jason Downing
OS:     Xubuntu 14.04LTS 64bit
Machine: ASUS Laptop / Custom built Desktop (Intel/Nvidia PCs)
Text editor:  Kate Text Editor (KDE editor)
Hours to complete assignment:  4-5 hours or so. Probably more. I lost track at some point.
Also maybe another hour to run the tests and upload the results and stuff.

/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/
I followed Princeton's site. I used a Matrix, which is a vector of vector of integers
to calculate all the possible subproblems like described on Princeton's webpage.
After I made the matrix, I had a _Matrix variable with _Matrix[0][0] being the
Edit Distance. I then retraced the Matrix like Princeton decribes, from right
to left and moving either right, diagonal, or down. I then add those characters
to a ostringstream object which I make dynamically as well and return to main,
which is then printed out for people to see.


/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file?
 *
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input:

atattat
tattata

Expected output:

Edit distance = 4
a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2

What happened:

It worked. Took 0.000132 seconds. So it was pretty quick.

/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 2 GB to 16 GB.
 **********************************************************************/
Laptop - 8GB
Desktop - 12GB ( I tested mainly on this machine, so assume this for the
tests and stuff )

/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of
 *  N. Give an answer of the form a * N^b for some constants a
 *  and b, where b is an integer. Note chars are 2 bytes long, and
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
a = 24
b = 4
largest N =

I use vectors of integers, so 4 bytes for every int that needs to be stored.
However, vectors themselves use up approximately 24 bytes - this is according
to a quick cout statement on my machine:
std::cout << "Size of vector: " << sizeof(std::vector<int>);

Assuming 24 bytes per vector and 4 bytes per int that needs to be stored:

24 * N^4
If N = 5,000:
24 * 5000^4 = 1.5x10^16

However, this doesn't seem to be the same as what I implemented. I essentially made
a matrix of ints, so really my program makes a matrix of integers which are
5000 by 5000, with a vector to hold vectors of ints. So in reality, my program should use
the following amount of RAM:

24 (master vector) + 24 * 5000 (all the vector rows) + 4 * 5000 * 5000 (all the ints that need
to be stored)

24 + 24 * 5000 + 4 * 5000 * 5000 = 1x10^8

So this should be something like 100 million bytes, or 100MB of RAM.
Which is much closer to what my program actually uses.

/**********************************************************************
 *  Were you able to run Valgrind's massif tool to verify that your
 *  implementation uses the expected amount of memory?
 *
 *  Answer yes, no, I didn't try, I tried and failed, or I used a
 *  different tool.
 *
 *  If yes, paste in the ms_print top chart of memory use over time,
 *  and also indicate which file your code was solving.
 *
 *  Explain if necessary.
/**********************************************************************

Yes, I ran valgrind.

It seems like it uses 156.5MB of RAM, for ecoli5000.txt.

That seems to be much lower than what I thought it would be, since doing them
calculations above I figured it would use most of my RAM. However, after I thought
about how I implemented the program, I realized I used a matrix of integers, which
really means that since there's 5000 characters in each string for ecoli5000.txt, there
should be 5000^2 integers saved in my Matrix, which each use 4 bytes of RAM, plus all the
RAM that the 5000 vectors use, which adds up since vectors have quite a bit of overhead.

MB
156.5^                                                                       :
|                               @#######################################:
|                             @@@#                                      :
|                           @@@@@#                                      :
|                          @@@@@@#                                      :
|                        @@@@@@@@#                                      :
|                       @@@@@@@@@#                                      :
|                     @@@@@@@@@@@#                                      :
|                   @@@@@@@@@@@@@#                                      :
|                  @@@@@@@@@@@@@@#                                      :
|                @@@@@@@@@@@@@@@@#                                      :
|              @@@@@@@@@@@@@@@@@@#                                      :
|             @@@@@@@@@@@@@@@@@@@#                                      :
|           @@@@@@@@@@@@@@@@@@@@@#                                      :
|         @@@@@@@@@@@@@@@@@@@@@@@#                                      :
|        @@@@@@@@@@@@@@@@@@@@@@@@#                                      :
|      @@@@@@@@@@@@@@@@@@@@@@@@@@#                                      :
|     @@@@@@@@@@@@@@@@@@@@@@@@@@@#                                      :
|   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@#                                      :
| @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#                                      :
0 +-----------------------------------------------------------------------> Gi
0                                                                   11.16

(I have 12GB of RAM on this machine, but 11.9GB shown as available in Xubuntu 14.04LTS)

/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt         118         0.368727 seconds      39MB
ecoli5000.txt         160         1.724110 seconds     156MB
ecoli7000.txt         194         2.660010 seconds     217MB
ecoli10000.txt        223         5.296660 seconds     622MB
ecoli20000.txt       3135         25.66290 seconds    2440MB
ecoli28284.txt       8394         48.49050 seconds    3430MB

Fill out the data here first, then go to the assignment web page for
instructions on sharing your data on iSENSE.

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730

/**********************************************************************
 *  For this question assume M=N (which is true for the sample files
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 *
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
a = 2
b = 2
largest N =

Hmm, well I'm not really sure how to do this.

I guess something like:

2 * N^2 = resulting time

So in the case of ecoli5000:

2 * 1^2 = 2

For ecoli10000:

2 * 2^2 = 6

So it sorta works I guess.

Assuming this, one day is 24 (hours in a day) * 60 (minutes in an hour) * 60 (seconds in a minute)
seconds. Or 86,400 seconds.

So the largest N could be:

86,400 = 2 * N^2
43,200 = N^2
N = sqrt(43,200)
N = 207

207 * 10000 = 2,070,000

So my implementation should be able to find the edit distance of a 2 million long string in a days
time. This assumes I did my math right and what not - it would probably less, since I'm guessing I
over estimated. So we can assume somewhere between 1 million and 2 million long strings.

/**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/

I used the following Stackoverflow post for help on doing the PrintMatrix
method (an extra debug method I made):
https://stackoverflow.com/questions/8750853/how-to-conveniently-align-numbers-centrally-in-c-cout

I also used the discussion group for misc. help and for getting the
answer tar to compare my results against.

Also - cplusplus.com was an awesome resource for random STD / STL stuff, like:
http://www.cplusplus.com/reference/stdexcept/out_of_range/
http://www.cplusplus.com/reference/vector/vector/begin/

/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/

Let's see...

1) Bottlenose didn't like my output
2) Then I tried fixing it and realized my code was broken anyway...
3) So I tried fixing it and compared against Bottlenose repeatedly.
4) FINALLY I figured out how to do try and catch and those pesky "vector
out of bounds" errors stopped and my code seemed to magically work!
I also had to add some = -1s to make it work too I think.

/**********************************************************************
 *  List any other comments here.
 **********************************************************************/

IT'S DONE YAY.
^_________^
