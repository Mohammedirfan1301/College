# Makefile for Assignment 3
# File given by Prof. Moloney at the following URL:
# http://www.cs.uml.edu/~bill/cs308/assignment_3_makefile.txt

proddonuts consdonuts: donuts.h proddonuts.o consdonuts.o utilities.o
	gcc -o proddonuts proddonuts.o utilities.o
	gcc -o consdonuts consdonuts.o utilities.o

consdonuts.o: donuts.h consdonuts.c
	gcc -c consdonuts.c

proddonuts.o: donuts.h proddonuts.c
	gcc -c proddonuts.c

utilities.o:  utilities.c
	gcc -c utilities.c

clean:
	rm *.o proddonuts consdonuts
	rm c1 c2 c3 c4 c5
