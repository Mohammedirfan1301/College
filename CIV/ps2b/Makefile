# Makefile for ps2b
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

# Make ps2b
all:	PhotoMagic

# ps2b executable
PhotoMagic:	PhotoMagic.o LFSR.o
	$(CC) PhotoMagic.o LFSR.o -o PhotoMagic $(SFMLFLAGS)

# object files
PhotoMagic.o:	PhotoMagic.cpp LFSR.hpp
	$(CC) -c PhotoMagic.cpp LFSR.hpp $(CFLAGS)

LFSR.o:		LFSR.cpp LFSR.hpp
	$(CC) -c LFSR.cpp $(CFLAGS)

# Cleanup
clean:
	rm *.o
	rm PhotoMagic

