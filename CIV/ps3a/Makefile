# Makefile for the sierpinski project / original recursive image
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

# Make ps2b
all:	NBody

# NBody executable
NBody:		main.o nbody.o
	$(CC) main.o nbody.o -o NBody $(SFMLFLAGS)

# object files
main.o:		main.cpp nbody.hpp
	$(CC) -c main.cpp nbody.hpp $(CFLAGS)

nbody.o:	nbody.cpp nbody.hpp
	$(CC) -c nbody.cpp nbody.hpp $(CFLAGS)

# Cleanup
clean:
	rm *.o
	rm NBody

