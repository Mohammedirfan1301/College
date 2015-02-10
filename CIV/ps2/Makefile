# Makefile for the sierpinski project / original recursive image
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic

# Make both projects
all:	ps2a

# Main tester
ps2a:	main.o LFSR.o
	$(CC) main.o LFSR.o -o ps2a

main.o:		main.cpp LFSR.hpp
	$(CC) -c main.cpp $(CFLAGS)

LFSR.o:		LFSR.cpp LFSR.hpp
	$(CC) -c LFSR.cpp $(CFLAGS)

# Cleanup
clean:
		rm *.o
		rm ps2a