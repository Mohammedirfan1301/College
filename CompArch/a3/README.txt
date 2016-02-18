********************************************************************************
*    Fibonacci numbers                                                         *
********************************************************************************

 Name: Jason Downing
Email: jason_downing@student.uml.edu
 Date: 2/17/2016

This assignment required us to calculate Fibonacci numbers.

My approach to this assignment was to start by writing C code, so that I could
then translate it into MIC-1 Assembly. The C code I wrote can be found in the
"fib.c" file. The Makefile I included can compile this file as well, and
it can be run as "./fib".

After I wrote a fibonacci number function in C, I started translating the C code into
MIC-1 Assembly. I was able to create two data locations, one for the input numbers
and another for the final fibonacci numbers. These start at memory location 200.
I also created a few other variables for use in MIC-1. I created a main driver
which runs through the input array, and pushes the current test number onto the
stack. I also use a loop (fibn) to calculate the fibonacci number with the formula:
Fn = Fn-1 + Fn-2

I believe I was 100% successful with this assignment, as my program was able to
calculate all five required fibonacci numbers. The "actual.out" file shows an
example of running my code, and then typing location "199" followed by "f" and
"10". In this file you can see my code's output matches the Professor's example
output on the assignment page.
