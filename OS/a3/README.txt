Assignment 3 - Producer-Consumer Problem
============================================
 Name: Jason Downing
 Date: 10/24/2016
Email: jason_downing@student.uml.edu

I believe I was 100% successful in writing the code, as the majority of it was
provided by Professor Moloney on his cs308 website:
http://www.cs.uml.edu/~bill/cs308/

As a result, I spent most of my time trying to figure out how to run to generate
graphs for the required test cases. The Makefile I have provided has everything
need to run and clean the project. The shell script included is setup to default
to 5 consumers but I left commented out code for running from 1 to 10 consumers.

I have also attached an excel file and graphs in PDF format.

Step 7:
For step 7, I ran the included shell script with loops set to 5. I also set the
script to run with 5 consumers and 1 producer. I ran each queue size twice and
took the average of the two using an Excel formula. This gave me a pretty good
idea of what queue size causes what level of deadlock. It turns out that for my
code and PC, it is around a queue size of 40. I ran the code for queue size 10
to 80 to test different sizes.

From the results graph, it seems clear that the distribution is linear. There is
clearly a linear step in the graph and it goes from 100% at queue size 10 to
0% at queue sizes 60, 70 and 80.

Step 8:
From Step 7, I knew that a queue size of 40 would produce a 50% chance of
deadlocking. As a result, I ran the shell script with loops set to 5, and queue
size set to 50. I did this for 1 to 10 consumers. I left my old consumer code
commented out in the shell script for testing purposes.

From the graph, it seems pretty straightforward that the higher the number of
consumers, the higher the chance of deadlock occurs.

Example output for 1 consumer & 1 loop:

ubuntu@desktop: a3$ ./a3.sh 1

The configuration is for 1 LOOPS

___________________________________________________________

Working on LOOP 1

Process PID: 26073
Time: 20:35:49.743
Dozen #: 1
Plain	Jelly	Coconut	Honey-dip
11	14	8	7
0	15	9	8
264901648	16	10	0
32665	17	11	0
1833602592	18	0	1835627636
32767	791621423	0	1600061541
268900179	791621423	0	1869833334
32665	791621423	0	1952802655
65280	0	0	1
0	0	0	0
0	0	0	4198541
0	0	16711935	0

Process PID: 26073
Time: 20:35:49.743
Dozen #: 2
Plain	Jelly	Coconut	Honey-dip
23	31	25	27
25	32	32	31
0	33	0	0
0	40	0	0
0	41	0	0
0	43	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.743
Dozen #: 3
Plain	Jelly	Coconut	Honey-dip
36	48	38	38
41	52	44	39
45	0	45	42
50	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.743
Dozen #: 4
Plain	Jelly	Coconut	Honey-dip
57	62	50	48
65	65	102	53
0	69	104	56
0	70	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.743
Dozen #: 5
Plain	Jelly	Coconut	Honey-dip
74	77	112	113
128	80	115	65
0	81	74	68
0	0	0	71
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.743
Dozen #: 6
Plain	Jelly	Coconut	Honey-dip
129	84	0	79
134	85	0	89
137	94	0	91
139	100	0	0
0	102	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.743
Dozen #: 7
Plain	Jelly	Coconut	Honey-dip
147	108	97	94
153	113	101	102
155	114	102	0
0	0	105	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.744
Dozen #: 8
Plain	Jelly	Coconut	Honey-dip
164	122	109	106
0	123	110	107
0	125	111	113
0	126	112	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.744
Dozen #: 9
Plain	Jelly	Coconut	Honey-dip
170	134	117	116
175	0	118	119
178	0	0	121
131	0	0	0
132	0	0	0
134	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0

Process PID: 26073
Time: 20:35:49.744
Dozen #: 10
Plain	Jelly	Coconut	Honey-dip
137	140	173	173
138	141	175	175
189	0	176	127
0	0	0	130
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0
0	0	0	0


>>>>>>>> NOW KILLING THE PRODUCER PROCESS PID: 26071
___________________________________________________________

1 loops and 0 deadlocks
