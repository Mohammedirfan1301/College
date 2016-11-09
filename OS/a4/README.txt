Assignment 4 - Producer-Consumer Problem
============================================
 Name: Jason Downing
 Date: 11/8/2016
Email: jason_downing@student.uml.edu

I believe I was 90% successful in writing the code, as the majority of it was
provided by Professor Moloney on his cs308 website:
http://www.cs.uml.edu/~bill/cs308/

As a result, I spent most of my time trying to figure out how to run to generate
graphs for the required test cases. The Makefile I have provided has everything
need to run and clean the project.

I have also attached an excel file and graphs in PDF format.

I used the following command to run each test:
./A4_donut_loop.sh 5

This ran the shell script (provided by Prof. Moloney) through 5 loops, and I
varied the settings in the header file according to each test.

TEST 1: Queue Size vs % Deadlock
For the first round of tests and for graph 1, I ran the shell script with the
header file set to 50 consumers and 30 consumers, and with a hard coded value
of 200 donuts. I then varied the Queue Size (NUMSLOTS) setting for testing.
I started with a Queue Size of 26,500 and I incremented it up to 28,500. I
figured that somewhere in between I would find the 50% Queue size and not
suprisingly I did when the queue size was set to 26,800.

TEST 2: Dozens of Donuts vs % Deadlock
For the second round of tests and for graph 2, I ran the shell script with
the 50% queue size of 26,800. I then varied the amount of donut dozens, starting
with 100 and going up to 300. The results were not that suprising, as when
I set the dozens of donuts to above 200 dozens it results in a higher chance of
a deadlock, and when I set the value to below 200 dozens it resulted in a lower
chance of a deadlock.
