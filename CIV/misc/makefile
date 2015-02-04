# Makefile for the sierpinski project
all:	sierpinski

sierpinski:	main.o sierpinski.o
		g++ main.o sierpinski.o -o sierpinski -lsfml-graphics -lsfml-window -lsfml-system

main.o:		main.cpp sierpinski.hpp
		g++ -c main.cpp -Wall -Werror -ansi -pedantic

sierpinski.o: 	sierpinski.cpp sierpinski.hpp
		g++ -c sierpinski.cpp -Wall -Werror -ansi -pedantic

clean:
		rm *.o
		rm sierpinski