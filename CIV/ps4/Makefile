# Makefile for ps4
# Flags to save on typing all this out
CC= g++
CFLAGS= -g -Wall -Werror -std=c++0x -pedantic
SFLAGS= -lsfml-system

# Make ps4
all:	ED

# body executable
ED:	main.o ED.o
	$(CC) main.o ED.o -o ED $(SFLAGS)

# object files
main.o:	main.cpp ED.hpp
	$(CC) -c main.cpp ED.hpp $(CFLAGS)

ED.o:	ED.cpp ED.hpp
	$(CC) -c ED.cpp ED.hpp $(CFLAGS)

# Cleanup
clean:
	rm *.o
	rm *.gch
	rm ED

