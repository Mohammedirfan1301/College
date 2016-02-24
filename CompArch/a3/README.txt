********************************************************************************
*    Fibonacci numbers                                                         *
********************************************************************************

 Name: Jason Downing
Email: jason_downing@student.uml.edu
 Date: 2/18/2016

This assignment required us to calculate Fibonacci numbers.

My approach to this assignment was to start by writing C code, so that I could
then translate it into MIC-1 Assembly. The C code I wrote can be found in the
"fib.c" file. The Makefile I included can compile this file as well, and
it can be run as "./fib".

After I wrote a Fibonacci number function in C, I started translating the C code into
MIC-1 Assembly. I was able to create two data locations, one for the input numbers
and another for the final Fibonacci numbers. These start at memory location 200.
I also created a few other variables for use in MIC-1. I created a main driver
which runs through the input array, and pushes the current test number onto the
stack. I also use a loop (fibn) to calculate the Fibonacci number with the formula:
Fn = Fn-1 + Fn-2

I used Prof. Moloney's Fibonacci slides for figuring out how to store numbers in
a specific memory location using .LOC. This page in particular I found useful to
look through:
http://www.cs.uml.edu/~bill/cs305/Fibonacci_Slides.pdf

I believe I was 100% successful with this assignment, as my program is able to
calculate all five required Fibonacci numbers. The "output.txt" file shows an
example of running my code, and typing location "198" followed by "f" and
"10". In this file you can see my code's output matches the Professor's example
output on the assignment page. It also makes sense based on my Fibonacci C code,
although obviously the 25th Fibonacci number overflows the 16 bit storage that
the MIC-1 uses. You may also see the "annotated" version in the following file:
"output_annotated.txt"

You can also see the output of my code by just running "Make" and checking the
"output.txt" file. You can also manually compile it using the following commands:
	./masm < fib.asm > fib.obj
	./mic1 prom.dat fib.obj 0 1024
