# Makefile for ps5a
# Flags to save on typing all this out
CC= g++
CFLAGS= -g -Wall -Werror -std=c++0x -pedantic
Boost= -lboost_unit_test_framework

# Make ps5a & a dummy tester
all:	ps5a main.out

# PS5 executable
ps5a:	test.o RingBuffer.o
	$(CC) test.o RingBuffer.o -o ps5a $(Boost)

# main.out is just a basic test executable
main.out: main.o RingBuffer.o
	$(CC) main.o RingBuffer.o -o main.out

# Object files
RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	$(CC) -c RingBuffer.cpp RingBuffer.hpp $(CFLAGS)

test.o: test.cpp RingBuffer.hpp
	$(CC) -c test.cpp RingBuffer.hpp $(CFLAGS)

main.o:	main.cpp RingBuffer.hpp
	$(CC) -c main.cpp RingBuffer.hpp $(CFLAGS)

# Cleanup object files
clean:
	rm *.o
	rm *.gch
	rm ps5a
	rm *.out
