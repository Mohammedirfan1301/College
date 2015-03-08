# Makefile for the sierpinski project / original recursive image
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -std=c++0x -pedantic
SFLAGS= -lsfml-system

# Make ps4
all:	EditDistance

# body executable
EditDistance:	main.o ED.o
	$(CC) main.o ED.o -o EditDistance $(SFLAGS)

# object files
main.o:	main.cpp ED.hpp
	$(CC) -c main.cpp ED.hpp $(CFLAGS)

ED.o:	ED.cpp ED.hpp
	$(CC) -c ED.cpp ED.hpp $(CFLAGS)

# Cleanup
clean:
	rm *.o
	rm *.gch
	rm EditDistance

