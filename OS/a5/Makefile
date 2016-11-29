# Jason Downing
# Assignment 5
# Operating Systems - COMP.3080
# 11/29/2016
#
# Makefile for Assignment 5
#

all: main.o first_fit.o best_fit.o buddy_sys.o alloc.o
	gcc -o a5 main.o best_fit.o first_fit.o buddy_sys.o alloc.o

main.o: main.c main.h
	gcc -c main.c

alloc.o: alloc.c main.h
	gcc -c alloc.c

best_fit.o: best_fit.c main.h
	gcc -c best_fit.c

buddy_sys.o: buddy_sys.c main.h
	gcc -c buddy_sys.c

first_fit.o: first_fit.c main.h
	gcc -c first_fit.c

clean:
	rm *.o a5
