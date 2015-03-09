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
Followed Princeton's site - used a Matrix, which was a vector of vector of integers
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

Expected output:

What happened:



/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 2 GB to 16 GB.
 **********************************************************************/
Laptop - 8GB
Desktop - 12GB

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
a =
b =
largest N =

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
ecoli2500.txt
ecoli5000.txt
ecoli7000.txt
ecoli10000.txt
ecoli20000.txt
ecoli28284.txt

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
a =
b =
largest N =

/**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/



/**********************************************************************
 *  List any other comments here.
 **********************************************************************/

