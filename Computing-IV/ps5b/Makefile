# Makefile for ps5b
# Flags to save on typing all this out
CC= g++
CFLAGS= -g -Wall -Werror -std=c++0x -pedantic
SFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
Boost= -lboost_unit_test_framework

# Make ps5a & a dummy tester
all:	GuitarHero GStest

# PS5B executable
GuitarHero:	GuitarHero.o GuitarString.o RingBuffer.o
	$(CC) GuitarHero.o GuitarString.o RingBuffer.o -o GuitarHero $(SFLAGS)

# GStest executable
GStest:	GStest.o GuitarString.o RingBuffer.o
	$(CC) GStest.o GuitarString.o RingBuffer.o -o GStest $(Boost)

# Object files
GuitarHero.o: 	GuitarHero.cpp GuitarString.hpp
	$(CC) -c GuitarHero.cpp GuitarString.hpp $(CFLAGS)

GuitarString.o: GuitarString.cpp GuitarString.hpp
	$(CC) -c GuitarString.cpp GuitarString.hpp $(CFLAGS)

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	$(CC) -c RingBuffer.cpp RingBuffer.hpp $(CFLAGS)

GStest.o:	GStest.cpp
	$(CC) -c GStest.cpp $(Boost)

# Cleanup object files
clean:
	rm *.o
	rm *.gch
	rm GuitarHero
	rm GStest