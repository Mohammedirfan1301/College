# Makefile for the sierpinski project / original recursive image
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic
LFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

# Make both projects
all:	sierpinski original

# Original image related code
original:	o_main.o original.o
		$(CC) o_main.o original.o -o original $(LFLAGS)

o_main.o:	o_main.cpp original.hpp
		$(CC) -c o_main.cpp $(CFLAGS)

original.o:	original.cpp original.hpp
		$(CC) -c original.cpp $(CFLAGS)


# Sierpinski triangle related code
sierpinski:	main.o sierpinski.o
		$(CC) main.o sierpinski.o -o sierpinski $(LFLAGS)

main.o:		main.cpp sierpinski.hpp
		$(CC) -c main.cpp $(CFLAGS)

sierpinski.o: 	sierpinski.cpp sierpinski.hpp
		$(CC) -c sierpinski.cpp $(CFLAGS)

# Cleanup
clean:
		rm *.o
		rm sierpinski
		rm original