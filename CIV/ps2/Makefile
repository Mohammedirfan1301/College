# Makefile for the sierpinski project / original recursive image
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic

# Make both projects
all:	main.out

# Main tester
main.out:	main.o LFSR.o
	$(CC) main.o LFSR.o -o main.out

main.o:		main.cpp LFSR.hpp
	$(CC) -c main.cpp $(CFLAGS)

LFSR.o:		LFSR.cpp LFSR.hpp
	$(CC) -c LFSR.cpp $(CFLAGS)

# Cleanup
clean:
		rm *.o
		rm *.out