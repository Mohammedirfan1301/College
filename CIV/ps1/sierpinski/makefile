# Makefile for the sierpinski project
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic
LFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

all:	sierpinski

sierpinski:	main.o sierpinski.o
	$(CC) main.o sierpinski.o -o sierpinski $(LFLAGS)

main.o:	main.cpp sierpinski.hpp
	$(CC) -c main.cpp $(CFLAGS)

sierpinski.o: sierpinski.cpp sierpinski.hpp
	$(CC) -c sierpinski.cpp $(CFLAGS)

clean:
	rm *.o
	rm sierpinski