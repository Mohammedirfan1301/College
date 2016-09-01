# Makefile for ps3a
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

# Make ps2b
all:	NBody

# body executable
NBody:	main.o body.o
	$(CC) main.o body.o -o NBody $(SFMLFLAGS)

# object files
main.o:	main.cpp body.hpp
	$(CC) -c main.cpp body.hpp $(CFLAGS)

body.o:	body.cpp body.hpp
	$(CC) -c body.cpp body.hpp $(CFLAGS)

# Cleanup
clean:
	rm *.o
	rm NBody

