# Makefile for ps3b
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -std=c++0x -pedantic
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

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
	rm *.gch
	rm NBody

